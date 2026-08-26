#include <Deneyap_Servo.h>
#include <lsm6dsm.h>
#define al D14
#define ver D15
#define buz D12
LSM6DSM IMU;

Servo sev;
int pos = 0;
long sure;
long uzaklik;

void setup() {
  Serial.begin(115200);
  sev.attach(D0); // Servo motoru kontrol etmek için pin ataması
  pinMode(ver, OUTPUT);
  pinMode(al, INPUT);
  pinMode(buz, OUTPUT); // Buz pinine bir pin numarası ataması
  IMU.begin();
}

void loop() {
  /*digitalWrite(ver, 0);
  delay(5);
  digitalWrite(ver, 1);
  delay(10);
  digitalWrite(ver, 0);
  sure = pulseIn(al, HIGH);

  uzaklik = sure / 29.1 / 2;
  
  if (uzaklik < 10)
    digitalWrite(buz, HIGH);
  else
    digitalWrite(buz, LOW);

  if (uzaklik != 0) {
    pos = map(uzaklik, 0, 40, 0, 180); // Servo pozisyonunu düzeltme
    sev.write(pos);
    Serial.print("Uzaklik: ");
    Serial.print(uzaklik);
    Serial.println(" cm");
    delay(5);
  }
  */
  Serial.print("accel_x:");
  Serial.println(IMU.readFloatAccelX());
  Serial.print("accel_y:");
  Serial.println(IMU.readFloatAccelY());
  Serial.print("accel_z:");
  Serial.println(IMU.readFloatAccelZ());
  delay(50);
}
