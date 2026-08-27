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
// OTOMASYON / TERMOSTAT AYARLARI
// ==========================================
float targetTemperature = 22.0;
float hysteresis = 0.5;
bool devicePowerState = true;
String thermostatMode = "HEAT";
bool rfState = false;
bool sinricConnected = false;

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
    delay(10);
  }
}

void setRfState(bool state) {
  if (rfState == state) return;
  
  rfState = state;
  digitalWrite(LED_GREEN, state ? HIGH : LOW); // Yeşil LED: Kombi Durumu

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
  devicePowerState = state;
  if (!devicePowerState) {
    setRfState(false);
  } else {
    lastTempCheck = 0;
  }
  return true;
}

bool onTargetTemperature(const String &deviceId, float &temp) {
  targetTemperature = temp;
  Serial.printf("[SinricPro]: Yeni Hedef Sicaklik -> %.1f C\r\n", targetTemperature);
  lastTempCheck = 0;
  return true;
}

bool onAdjustTargetTemperature(const String &deviceId, float &tempDelta) {
  targetTemperature += tempDelta;
  Serial.printf("[SinricPro]: Hedef Sicaklik Degistirildi -> %.1f C\r\n", targetTemperature);
  lastTempCheck = 0;
  return true;
}

bool onThermostatMode(const String &deviceId, String &mode) {
  mode.toUpperCase();
  thermostatMode = mode;
  Serial.printf("[SinricPro]: Mod Degisti -> %s\r\n", mode.c_str());
  
  if (mode == "OFF") {
    setRfState(false);
  }
  lastTempCheck = 0;
  return true;
}

void setupWiFi() {
  Serial.printf("\r\n[WiFi]: %s agina baglaniliyor", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  bool blinkState = false;
  while (WiFi.status() != WL_CONNECTED) {
    blinkState = !blinkState;
    setBlueLedBrightness(blinkState ? 100 : 0); // Baglanirken belirgin sekilde yanip soner
    delay(300);
    Serial.print(".");
  }
  
  setBlueLedBrightness(BLUE_DIM_DUTY); // Baglanti basarili -> Parlaklik hemen kısılarak loşa düşer
  Serial.printf("\n[WiFi]: Baglanti basarili! IP: %s\r\n", WiFi.localIP().toString().c_str());
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
    setBlueLedBrightness(BLUE_DIM_DUTY); // Buluta bagliyken los yanar
  });
  
  SinricPro.onDisconnected([](){ 
    Serial.println("[SinricPro]: Baglanti kesildi."); 
    sinricConnected = false;
    setBlueLedBrightness(0); // Baglanti koptugunda tamamen soner
  });
  
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void handleTemperatureAutomation() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastTempCheck < tempCheckInterval) return;
  lastTempCheck = currentMillis;

  float currentTemp = dht.readTemperature();
  float currentHumidity = dht.readHumidity();

  // Sensor Hatasi Kontrolu
  if (isnan(currentTemp) || isnan(currentHumidity)) {
    Serial.println("[HATA]: DHT11 verisi okunamadi!");
    digitalWrite(LED_RED, HIGH); // Kirmizi LED: Sensor Hatasi
    return;
  }
  digitalWrite(LED_RED, LOW); // Sensor saglam, kirmizi led kapali

  String currentMode = thermostatMode;
  currentMode.toUpperCase();

  Serial.printf("[DHT11]: Sicaklik: %.1f C | Nem: %.1f %% | Hedef: %.1f C | Mod: %s\r\n", 
                currentTemp, currentHumidity, targetTemperature, currentMode.c_str());

  SinricProThermostat &myThermostat = SinricPro[THERMOSTAT_ID];
  myThermostat.sendTemperatureEvent(currentTemp, currentHumidity);

  if (!devicePowerState || currentMode == "OFF") {
    if (rfState) setRfState(false);
    return;
  }

  if (currentMode == "HEAT" || currentMode == "AUTO") {
    if (currentTemp < targetTemperature && !rfState) {
      Serial.printf("[Otomasyon]: Sicaklik (%.1f C) hedefin altinda -> CALISTIRILIYOR\r\n", currentTemp);
      setRfState(true);
    } else if (currentTemp >= (targetTemperature + hysteresis) && rfState) {
      Serial.printf("[Otomasyon]: Sicaklik (%.1f C) hedefe ulasti -> DURDURULUYOR\r\n", currentTemp);
      setRfState(false);
    }
  } else if (currentMode == "COOL") {
    if (!rfState) setRfState(true);
  }
}

void setup() {
  Serial.begin(115200);

  // Mavi LED PWM Kurulumu
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcAttach(LED_BLUE, BLUE_PWM_FREQ, BLUE_PWM_RES);
#else
  ledcSetup(BLUE_PWM_CHANNEL, BLUE_PWM_FREQ, BLUE_PWM_RES);
  ledcAttachPin(LED_BLUE, BLUE_PWM_CHANNEL);
#endif
  setBlueLedBrightness(0);

  // Diger LED'ler
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  pinMode(RF_PIN, OUTPUT);
  digitalWrite(RF_PIN, LOW);

  dht.begin();

  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
  handleTemperatureAutomation();
}
