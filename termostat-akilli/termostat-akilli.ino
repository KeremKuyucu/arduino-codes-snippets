// ============================================================================
// DURUM LED'LERİ VE PİN ŞEMASI (3 LED TEŞHİS MİMARİSİ)
// ============================================================================
// 1. MAVİ LED (GPIO 18 - LED_BLUE):
//    - Yanıp Sönüyor (Tam Güç) : Wi-Fi ağına bağlanmaya çalışıyor.
//    - Loş / Kısık Sabit Yanıyor: Wi-Fi ve Sinric Pro bulut bağlantısı başarılı (%6 parlaklık).
//    - Sönük                   : Ağ veya bulut bağlantısı kesildi / yok.
//
// 2. YEŞİL LED (GPIO 19 - LED_GREEN):
//    - Sabit Yanıyor           : Kombi / Isıtıcı devrede (RF Açma Sinyali Aktif).
//    - Sönük                   : Kombi kapalı (Hedefe ulaşıldı veya mod kapalı).
//
// 3. KIRMIZI LED (GPIO 21 - LED_RED):
//    - Sönük                   : Donanım sağlam, sensör düzgün çalışıyor.
//    - Sabit Yanıyor           : HATA! DHT11 okunamıyor (NaN / Kablo temassızlığı).
//
// DİĞER DONANIM PİNLERİ:
//    - GPIO 22                 : DHT11 Sıcaklık ve Nem Sensörü DATA Pini
//    - GPIO 23                 : FS1000A 433MHz RF Verici DATA Pini
// ============================================================================

#include <WiFi.h>
#include <esp_task_wdt.h>
#include <Preferences.h>
#include <SinricPro.h>
#include <SinricProThermostat.h>
#include <DHT.h>

// ==========================================
// KİMLİK BİLGİLERİ (env.h dosyasından okunur)
// ==========================================
#if __has_include("env.h")
  #include "env.h"
#elif __has_include("env.example.h")
  #include "env.example.h"
  #warning "env.h bulunamadi, varsayilan ornek sablon (env.example.h) yuklendi!"
#else
  #error "env.h veya env.example.h dosyasi bulunamadi!"
#endif

// ==========================================
// PİN TANIMLAMALARI & PWM AYARLARI
// ==========================================
#define RF_PIN            23    // FS1000A RF Verici DATA Pini
#define DHTPIN            22    // DHT11 Data Pini
#define DHTTYPE           DHT11

// Durum LED Pinleri
#define LED_BLUE          18    // Mavi: Wi-Fi & Bulut Bağlantı Durumu (PWM ile sürülür)
#define LED_GREEN         19    // Yeşil: Kombi / Isıtma Devrede (RF Aktif)
#define LED_RED           21    // Kırmızı: Donanım / Sensör Hatası

#define BLUE_PWM_CHANNEL  0
#define BLUE_PWM_FREQ     5000
#define BLUE_PWM_RES      8
#define BLUE_DIM_DUTY     15    // 0-255 arası parlaklık değeri (15 = yaklaşık %6 yumuşak loş ışık)

// ==========================================
// OTOMASYON / TERMOSTAT AYARLARI & NVS
// ==========================================
float targetTemperature = 22.0f;
float hysteresis = 0.5f;
bool devicePowerState = true;
char thermostatMode[16] = "HEAT";
bool rfState = false;
bool sinricConnected = false;
bool dhtErrorActive = false;     // DHT11 sensör hata durumu takibi
int dhtFailCount = 0;            // Ardışık hatalı okuma sayacı
const int DHT_MAX_CONSECUTIVE_FAILS = 3; // 3 ardışık hata (~9 sn) olmadan hata tetiklenmez

// Minimum RF Değişim Aralığı (Kombi Kısa Döngü / Short-cycling Koruması)
unsigned long lastRfChangeTime = 0;
const unsigned long MIN_RF_CHANGE_INTERVAL_MS = 60000; // Açma/kapama arasında minimum 60 sn

// Wi-Fi Runtime İzleme
unsigned long lastWiFiCheck = 0;
const unsigned long WIFI_CHECK_INTERVAL = 5000; // 5 sn'de bir Wi-Fi kontrolü

// NVS & Flash Aşınma Koruması (Debounce)
Preferences preferences;
bool settingsDirty = false;
unsigned long lastSettingChangeTime = 0;
const unsigned long NVS_SAVE_DEBOUNCE_MS = 5000; // Değişiklikten 5 sn sonra Flash'a yaz

// ==========================================
// WATCHDOG TIMER (WDT) AYARLARI
// ==========================================
#define WDT_TIMEOUT_SECONDS 15

// ==========================================
// DHT11 & ZAMANLAMA
// ==========================================
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastTempCheck = 0;
const unsigned long tempCheckInterval = 3000;

// ============================================================
// DOĞRULANMIŞ AÇMA PAKETİ (Paket 127)
// ============================================================
const uint16_t pktOpen[] PROGMEM = {
  396, 464, 368, 876, 396, 2540, 372, 456, 884, 460, 372, 460, 372, 872, 372, 876, 400, 456, 372, 460, 
  788, 1704, 404, 872, 1204, 456, 376, 868, 408, 2528, 380, 452, 888, 452, 380, 452, 380, 868, 376, 868, 
  408, 452, 380, 448, 796, 1696, 412, 864, 1212, 452, 380, 864, 408, 2528, 384, 448, 896, 448, 384, 448, 
  384, 860, 384, 864, 412, 448, 380, 448, 800, 1696, 408, 864, 1216, 448, 380, 868, 408, 2524, 384, 448, 
  896, 444, 384, 448, 384, 864, 384, 860, 412, 448, 384, 444, 800, 1692, 416, 860, 1216, 448, 384, 860, 
  412, 2524, 384, 448, 896, 444, 388, 444, 384, 864, 388, 856, 412, 448, 384, 444, 804, 1692, 412, 864, 
  1216, 444, 384, 860, 416, 2520, 388, 444, 904, 444, 388, 444, 384, 860, 388, 860, 412, 444, 388, 444, 
  804, 1688, 416, 860, 1220, 448, 380, 860, 416, 2520, 388, 440, 960
};

// ============================================================
// DOĞRULANMIŞ KAPATMA PAKETİ (Paket 55)
// ============================================================
const uint16_t pktClose[] PROGMEM = {
  124, 448, 892, 452, 380, 452, 380, 864, 380, 868, 408, 448, 380, 452, 796, 1696, 412, 1276, 1216, 1280, 
  408, 864, 384, 860, 800, 448, 896, 444, 388, 444, 384, 864, 384, 860, 412, 448, 384, 448, 800, 1692, 
  412, 1276, 1220, 1272, 416, 860, 388, 856, 804, 444, 904, 444, 388, 440, 388, 860, 388, 856, 416, 444, 
  388, 444, 800, 1692, 416, 1272, 1220, 1276, 412, 860, 388, 856, 808, 440, 900, 444, 388, 440, 392, 856, 
  388, 860, 416, 440, 388, 444, 804, 1688, 416, 1272, 1224, 1272, 416, 856, 392, 856, 804, 440, 900, 444, 
  388, 444, 388, 856, 388, 860, 416, 440, 392, 440, 804, 1688, 420, 1272, 1220, 1272, 416, 856, 392, 856, 
  804, 444, 904, 444, 388, 440, 392, 856, 388, 856, 420, 440, 388, 444, 804, 1688, 420, 1268, 1224, 1272, 
  416, 856, 392, 856, 804, 440
};

// ============================================================
// NVS (PREFERENCES) AYAR YÖNETİMİ & DEBOUNCE
// ============================================================
void loadSettingsFromNVS() {
  if (!preferences.begin("thermostat", true)) {
    Serial.println("[NVS]: Namespace acilamadi, varsayilan ayarlar kullaniliyor.");
    return;
  }
  targetTemperature = preferences.getFloat("targetTemp", 22.0f);
  hysteresis = preferences.getFloat("hysteresis", 0.5f);
  devicePowerState = preferences.getBool("powerState", true);
  String modeStr = preferences.getString("mode", "HEAT");
  strncpy(thermostatMode, modeStr.c_str(), sizeof(thermostatMode) - 1);
  thermostatMode[sizeof(thermostatMode) - 1] = '\0';
  preferences.end();

  Serial.printf("[NVS]: Ayarlar yuklendi -> Hedef: %.1f C | Histerezis: %.1f C | Guc: %s | Mod: %s\r\n",
                targetTemperature, hysteresis, devicePowerState ? "ACIK" : "KAPALI", thermostatMode);
}

void saveSettingsToNVS() {
  if (!preferences.begin("thermostat", false)) {
    Serial.println("[NVS]: Yazma icin namespace acilamadi!");
    return;
  }
  preferences.putFloat("targetTemp", targetTemperature);
  preferences.putFloat("hysteresis", hysteresis);
  preferences.putBool("powerState", devicePowerState);
  preferences.putString("mode", thermostatMode);
  preferences.end();
  settingsDirty = false;
  Serial.println("[NVS]: Ayarlar Flash bellege (NVS) basariyla kaydedildi.");
}

void markSettingsChanged() {
  settingsDirty = true;
  lastSettingChangeTime = millis();
}

void handleNvsDebounce() {
  if (settingsDirty && (millis() - lastSettingChangeTime >= NVS_SAVE_DEBOUNCE_MS)) {
    saveSettingsToNVS();
  }
}

// ============================================================
// WATCHDOG TIMER (WDT) YARDIMCILARI
// ============================================================
void initWatchdog() {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  esp_task_wdt_config_t wdt_config = {
    .timeout_ms = WDT_TIMEOUT_SECONDS * 1000,
    .idle_core_mask = 0,
    .trigger_panic = true
  };
  esp_task_wdt_reconfigure(&wdt_config);
#else
  esp_task_wdt_init(WDT_TIMEOUT_SECONDS, true);
#endif
  esp_task_wdt_add(NULL);
  Serial.println("[WDT]: Watchdog Timer baslatildi.");
}

void feedWatchdog() {
  esp_task_wdt_reset();
}

// Mavi LED Parlaklık Kontrol Yardımcısı
void setBlueLedBrightness(uint8_t duty) {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcWrite(LED_BLUE, duty);
#else
  ledcWrite(BLUE_PWM_CHANNEL, duty);
#endif
}

void sendRawSignal(const uint16_t* signal, size_t length, int repeats = 5) {
  for (int r = 0; r < repeats; r++) {
    bool state = true;
    for (size_t i = 0; i < length; i++) {
      uint16_t duration = pgm_read_word(&signal[i]);
      digitalWrite(RF_PIN, state ? HIGH : LOW);
      delayMicroseconds(duration);
      state = !state;
    }
    digitalWrite(RF_PIN, LOW);
    feedWatchdog();
    delay(10);
  }
}

void setRfState(bool state, bool force = false) {
  if (rfState == state) return;

  unsigned long currentMillis = millis();
  if (!force && (currentMillis - lastRfChangeTime < MIN_RF_CHANGE_INTERVAL_MS) && lastRfChangeTime != 0) {
    Serial.printf("[RF]: Degisim engellendi (Kombi kisa dongu korumasi: %lu sn beklemede)\r\n", 
                  (MIN_RF_CHANGE_INTERVAL_MS - (currentMillis - lastRfChangeTime)) / 1000);
    return;
  }

  rfState = state;
  lastRfChangeTime = currentMillis;
  digitalWrite(LED_GREEN, state ? HIGH : LOW);

  if (state) {
    sendRawSignal(pktOpen, sizeof(pktOpen) / sizeof(pktOpen[0]));
    Serial.println("[RF]: ACMA Sinyali Gonderildi (YESIL LED: ON)");
  } else {
    sendRawSignal(pktClose, sizeof(pktClose) / sizeof(pktClose[0]));
    Serial.println("[RF]: KAPATMA Sinyali Gonderildi (YESIL LED: OFF)");
  }
}

bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("[SinricPro]: Termostat Gucu -> %s\r\n", state ? "ACIK" : "KAPALI");
  if (devicePowerState != state) {
    devicePowerState = state;
    markSettingsChanged();
  }
  if (!devicePowerState) {
    setRfState(false, true);
  } else {
    lastTempCheck = 0;
  }
  return true;
}

bool onTargetTemperature(const String &deviceId, float &temp) {
  if (abs(targetTemperature - temp) > 0.01f) {
    targetTemperature = temp;
    markSettingsChanged();
  }
  Serial.printf("[SinricPro]: Yeni Hedef Sicaklik -> %.1f C\r\n", targetTemperature);
  lastTempCheck = 0;
  return true;
}

bool onAdjustTargetTemperature(const String &deviceId, float &tempDelta) {
  targetTemperature += tempDelta;
  markSettingsChanged();
  Serial.printf("[SinricPro]: Hedef Sicaklik Degistirildi -> %.1f C\r\n", targetTemperature);
  lastTempCheck = 0;
  return true;
}

bool onThermostatMode(const String &deviceId, String &mode) {
  mode.toUpperCase();
  if (strcmp(thermostatMode, mode.c_str()) != 0) {
    strncpy(thermostatMode, mode.c_str(), sizeof(thermostatMode) - 1);
    thermostatMode[sizeof(thermostatMode) - 1] = '\0';
    markSettingsChanged();
  }
  Serial.printf("[SinricPro]: Mod Degisti -> %s\r\n", thermostatMode);
  
  if (strcmp(thermostatMode, "OFF") == 0) {
    setRfState(false, true);
  }
  lastTempCheck = 0;
  return true;
}

void setupWiFi() {
  Serial.printf("\r\n[WiFi]: %s agina baglaniliyor", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  bool blinkState = false;
  while (WiFi.status() != WL_CONNECTED) {
    feedWatchdog();
    blinkState = !blinkState;
    setBlueLedBrightness(blinkState ? 100 : 0);
    delay(300);
    Serial.print(".");
  }
  
  feedWatchdog();
  setBlueLedBrightness(BLUE_DIM_DUTY);
  Serial.printf("\n[WiFi]: Baglanti basarili! IP: %s\r\n", WiFi.localIP().toString().c_str());
}

void handleWiFiRuntime() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastWiFiCheck < WIFI_CHECK_INTERVAL) return;
  lastWiFiCheck = currentMillis;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi]: Baglanti koptu! Yeniden baglaniliyor...");
    setBlueLedBrightness(0);
    WiFi.reconnect();
  }
}

void setupSinricPro() {
  SinricProThermostat &myThermostat = SinricPro[THERMOSTAT_ID];
  
  myThermostat.onPowerState(onPowerState);
  myThermostat.onTargetTemperature(onTargetTemperature);
  myThermostat.onAdjustTargetTemperature(onAdjustTargetTemperature);
  myThermostat.onThermostatMode(onThermostatMode);

  SinricPro.onConnected([](){ 
    Serial.println("[SinricPro]: Baglanti kuruldu."); 
    sinricConnected = true;
    setBlueLedBrightness(BLUE_DIM_DUTY);
  });
  
  SinricPro.onDisconnected([](){ 
    Serial.println("[SinricPro]: Baglanti kesildi."); 
    sinricConnected = false;
    setBlueLedBrightness(0);
  });
  
  SinricPro.begin(APP_KEY, APP_SECRET);
  feedWatchdog();
}

void handleTemperatureAutomation() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastTempCheck < tempCheckInterval) return;
  lastTempCheck = currentMillis;

  float currentTemp = dht.readTemperature();
  float currentHumidity = dht.readHumidity();

  if (isnan(currentTemp) || isnan(currentHumidity)) {
    dhtFailCount++;
    Serial.printf("[HATA]: DHT11 verisi okunamadi! (Ardisik Hata: %d/%d)\r\n", 
                  dhtFailCount, DHT_MAX_CONSECUTIVE_FAILS);

    if (dhtFailCount >= DHT_MAX_CONSECUTIVE_FAILS) {
      digitalWrite(LED_RED, HIGH);

      if (rfState) {
        Serial.println("[GUVENLIK]: Kalici sensor arizasi nedeniyle kombi KAPATILIYOR!");
        setRfState(false, true);
      }

      if (!dhtErrorActive) {
        dhtErrorActive = true;
        Serial.println("[HATA]: DHT11 Sensor Arizasi Aktif! (Kombiye kapatma sinyali gonderildi)");
      }
    }
    return;
  }

  dhtFailCount = 0;

  if (dhtErrorActive) {
    dhtErrorActive = false;
    digitalWrite(LED_RED, LOW);
    Serial.println("[BILGI]: DHT11 sensoru tekrar normale dondu.");
  } else {
    digitalWrite(LED_RED, LOW);
  }

  Serial.printf("[DHT11]: Sicaklik: %.1f C | Nem: %.1f %% | Hedef: %.1f C (±%.1f) | Mod: %s\r\n", 
                currentTemp, currentHumidity, targetTemperature, hysteresis, thermostatMode);

  if (sinricConnected) {
    SinricProThermostat &myThermostat = SinricPro[THERMOSTAT_ID];
    myThermostat.sendTemperatureEvent(currentTemp, currentHumidity);
  }

  if (!devicePowerState || strcmp(thermostatMode, "OFF") == 0) {
    if (rfState) setRfState(false, true);
    return;
  }

  if (strcmp(thermostatMode, "HEAT") == 0 || strcmp(thermostatMode, "AUTO") == 0) {
    float lowerThreshold = targetTemperature - hysteresis;
    float upperThreshold = targetTemperature + hysteresis;

    if (currentTemp <= lowerThreshold && !rfState) {
      Serial.printf("[Otomasyon]: Sicaklik (%.1f C) alt esik altinda (<= %.1f C) -> CALISTIRILIYOR\r\n", 
                    currentTemp, lowerThreshold);
      setRfState(true);
    } else if (currentTemp >= upperThreshold && rfState) {
      Serial.printf("[Otomasyon]: Sicaklik (%.1f C) ust esige ulasti (>= %.1f C) -> DURDURULUYOR\r\n", 
                    currentTemp, upperThreshold);
      setRfState(false);
    }
  } else if (strcmp(thermostatMode, "COOL") == 0) {
    if (!rfState) setRfState(true);
  }
}

void setup() {
  Serial.begin(115200);

  esp_reset_reason_t resetReason = esp_reset_reason();

  initWatchdog();
  feedWatchdog();

  loadSettingsFromNVS();

#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcAttach(LED_BLUE, BLUE_PWM_FREQ, BLUE_PWM_RES);
#else
  ledcSetup(BLUE_PWM_CHANNEL, BLUE_PWM_FREQ, BLUE_PWM_RES);
  ledcAttachPin(LED_BLUE, BLUE_PWM_CHANNEL);
#endif
  setBlueLedBrightness(0);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  pinMode(RF_PIN, OUTPUT);
  digitalWrite(RF_PIN, LOW);

  dht.begin();

  setupWiFi();

  if (resetReason == ESP_RST_TASK_WDT || resetReason == ESP_RST_WDT || 
      resetReason == ESP_RST_INT_WDT || resetReason == ESP_RST_PANIC) {
    Serial.printf("[WDT]: UYARI - Cihaz kilitlenme/WDT sonrasi yeniden baslatildi! (Kod: %d)\r\n", (int)resetReason);
  }

  setupSinricPro();
  feedWatchdog();
}

void loop() {
  feedWatchdog();
  handleWiFiRuntime();
  SinricPro.handle();
  handleTemperatureAutomation();
  handleNvsDebounce();
  yield();
}
