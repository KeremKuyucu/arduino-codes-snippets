# Esp32_wifiled_kontrol

## ESP32 ile Express.js Kullanarak Işık Kontrolü
ESP32 geliştirme kartını kullanarak uzaktan ışık kontrolü sağlayan bir proje. Çok basit şekilde get isteği atarak sunucudan ışık durumunu çekerek kontrol ediyor sunucuya biraz fazla yük bindiriyor websocket kullanılırsa daha iyi olur fakat glitch desteklemediği için get komutu ile çektim 3-5 saniye arasında get atarsa biraz gecikme olur ama sunucuya fazla yük binmez.
### Express.js Kodu
Aşağıdaki kod, Express.js kullanarak bir sunucu oluşturur ve ışık kontrolü için API sağlar.
Sunucu ile uğraşmamak için direkt glitch projesini remixleyebilirsiniz.
Glitch Proje Linki [Tıkla](https://glitch.com/edit/#!/keremkk-isik)
```const express = require("express");
const path = require("path");
require("dotenv").config();

const app = express();

app.use(express.static(path.join(__dirname)));
app.use(express.json());

let isikDurumu = false;

app.get("/isikac", (req, res) => {
    isikDurumu = true;
    res.json({ mesaj: "Işık açıldı", durum: isikDurumu });
});

app.get("/isikkapat", (req, res) => {
    isikDurumu = false;
    res.json({ mesaj: "Işık kapatıldı", durum: isikDurumu });
});

app.get("/isikdurumu", (req, res) => {
    res.json({ mesaj: "Işık Durumu", durum: isikDurumu });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log("Çalışıyor");
});
```
### ESP32 Kodu
ESP32, Wi-Fi üzerinden Express.js sunucusuna bağlanarak ışık durumunu kontrol eder.
```#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";
const String url = "https://keremkk-isik.glitch.me/isikdurumu";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    pinMode(2, OUTPUT);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi bağlantısı başarılı!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();

        if (httpCode == 200) {
            String payload = http.getString();
            Serial.println(payload);
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                bool durum = doc["durum"];
                Serial.println(durum ? "Açık" : "Kapalı");
                digitalWrite(2, durum);
            }
        }
        http.end();
    }
    delay(500);
}
```
### HTML Sayfası
Sunucuya sinyal göndermek için basit bir sayfa. Bunun yerine başka uygulamalardan HTTP POST atabilirsiniz.
```<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Işık Kontrol</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
            background: linear-gradient(135deg, #64b3f4, #c2e9fb);
            color: #333;
        }
        h1 {
            font-size: 36px;
            margin-bottom: 30px;
            color: #444;
        }
        .container {
            text-align: center;
            background-color: rgba(255, 255, 255, 0.8);
            padding: 40px;
            border-radius: 15px;
            box-shadow: 0px 10px 20px rgba(0, 0, 0, 0.1);
            width: 300px;
        }
        button {
            font-size: 20px;
            padding: 15px 25px;
            margin: 15px;
            border: none;
            border-radius: 50px;
            cursor: pointer;
            width: 100%;
            transition: all 0.3s ease;
        }
        .ac {
            background-color: #28a745;
            color: white;
        }
        .kapat {
            background-color: #dc3545;
            color: white;
        }
        button:hover {
            opacity: 0.9;
            transform: scale(1.05);
        }
        button:focus {
            outline: none;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Işık Kontrol</h1>
        <button class="ac" onclick="kontrolEt('/isikac')">Işığı Aç</button>
        <button class="kapat" onclick="kontrolEt('/isikkapat')">Işığı Kapat</button>
    </div>

    <script>
        function kontrolEt(url) {
            fetch(url, { method: 'GET' })
                .then(response => response.text())
                .then(data => console.log(data))
                .catch(error => console.error('Hata:', error));
        }
    </script>
</body>
</html>
```