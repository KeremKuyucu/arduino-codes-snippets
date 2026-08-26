#include <Servo.h>
#include <SoftwareSerial.h>

// Servo nesnelerini tanımla
Servo taban, omuz, dirsek, bilek;

// Joystick pinlerini tanımla
int tabanPin = A0;
int omuzPin = A1;
int dirsekPin = A2;
int bilekPin = A3;

// Kablosuz iletişim için yazılım seri pinlerini tanımla
SoftwareSerial bluetooth(D10,D11); // RX, TX

void setup() {
  // Servo motorları ilgili pinlere bağla
  taban.attach(D3);
  omuz.attach(D5);
  dirsek.attach(D6);
  bilek.attach(D9);

  // Seri iletişimi başlat
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // Joystick değerlerini oku
  int tabanDegeri = analogRead(tabanPin);
  int omuzDegeri = analogRead(omuzPin);
  int dirsekDegeri = analogRead(dirsekPin);
  int bilekDegeri = analogRead(bilekPin);

  // Joystick değerlerini servo pozisyonlarına dönüştür
  taban.write(map(tabanDegeri, 0, 1023, 0, 180));
  omuz.write(map(omuzDegeri, 0, 1023, 0, 180));
  dirsek.write(map(dirsekDegeri, 0, 1023, 0, 180));
  bilek.write(map(bilekDegeri, 0, 1023, 0, 180));

  // Servo pozisyonlarını kablosuz olarak bağlı cihaza gönder
  bluetooth.print(taban.read());
  bluetooth.print(",");
  bluetooth.print(omuz.read());
  bluetooth.print(",");
  bluetooth.print(dirsek.read());
  bluetooth.print(",");
  bluetooth.println(bilek.read());

  delay(50); // Düzgün hareket için gecikme ekle
}

