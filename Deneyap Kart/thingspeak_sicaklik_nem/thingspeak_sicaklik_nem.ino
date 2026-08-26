#include <WiFi.h>
#include "HTTPClient.h"
#include "DHT.h"

DHT dht_D14(D14,DHT11);
float sicaklik;
float nem;

const char* server= "api.thingspeak.com";
const char* ssid ="Kerem";
const char* password = "kerem1234";
String apiKey ="QLQAL5M03PBAHF8E";

WiFiClient client;
const int httpPort=80;

void setup() {
dht_D14.begin();
Serial.begin(115200);

Serial.print(ssid);
Serial.print(" Kablosuz agina baglaniliyor");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED){
delay(500);
Serial.print(".");
}

Serial.println();
Serial.println("Kablosuz aga baglanildi! .. ") ;
Serial.print("IP adresi: "); Serial.println (WiFi.localIP());
}

 void loop() {
//.lS1.catl1.k de:9'eri e.Laru.yor ve seri terminale ya=.1l1yor 'I
sicaklik = dht_D14.readTemperature();
Serial.print("Sicaklik: ");
Serial.println (sicaklik);
nem= dht_D14.readHumidity();
Serial.print("Nem: ");
Serial. println (nem);

//.lS1.catl1k dEgeri ThingSpeak göndi:riliyor 1
client.connect(server, httpPort);

String data_to_send = apiKey;
data_to_send += "&field1=";
data_to_send += String(sicaklik);
data_to_send += "&field2=";
data_to_send += String(nem);
data_to_send += "\r\n\r\n";


client.print("POST /update HTTP/1.1\n");
client. print("Host: api.thingspeak.com\n");
client. print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+ apiKey + "\n");
client. print ("Content-Type: application/x-www-form-urlencoded\n");
client. print ("Content-Length: ");
client.print(data_to_send.length());
client .print("\n\n");
client.print(data_to_send);

delay(1000);
} 
