#include <DHT.h>
DHT dht11(D0, DHT11);
float sicaklik, nem;

void setup() {
Serial.begin(115200);
dht11.begin();
}

void loop() {
  sicaklik = (float)dht11.readTemperature();
  nem = (float)dht11.readHumidity();
  Serial.print("sicaklik  :  ");
  Serial.println(sicaklik);
  Serial.print("Nem        :  ");
  Serial.println(nem);
  delay(1000);

}
