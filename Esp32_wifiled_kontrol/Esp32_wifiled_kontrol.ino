#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi ayarları
const char* ssid = "-"; // Wi-Fi SSID
const char* password = "-"; // Wi-Fi Şifresi

// Işık durumu için URL
const String url = "https://keremkk-isik.glitch.me/isikdurumu";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);

  // Wi-Fi bağlantısının sağlandığından emin ol
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi bağlantısı başarılı!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // GET isteği yap
    http.begin(url);  // URL'yi belirt
    int httpCode = http.GET();  // GET isteği gönder
    
    // Eğer istek başarılıysa
    if (httpCode == 200) {
      String payload = http.getString();  // JSON cevabını al
      Serial.println(payload);  // JSON'u yazdır
      
      // JSON verisini ayrıştır
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.println("JSON çözme hatası");
      } else {
        // Gelen JSON verisini al
        bool durum = doc["durum"];
        Serial.print("Işık Durumu: ");
        Serial.println(durum ? "Açık" : "Kapalı");
        digitalWrite(2,durum);
      }
    } else {
      Serial.println("GET isteği başarısız");
    }
    
    http.end();  // HTTP istemcisini kapat
  }

  delay(500);  // 3 saniye bekle
}
