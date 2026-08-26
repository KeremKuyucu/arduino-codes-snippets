
#include <Deneyap_Servo.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#define led D1
#define lamb D13
const int ledPin = led; // Deneyap Kartında yer alan LED pin numarası
#define gazsensoru A0
#define isinem D0
#define isiksensoru D0
#define hareketsensoru D0
Servo servo;
String gelendeger="";
  int aa1=0,aa2=0,aa3=0,aa4=0,aa5=0,aa6=0;
  int kapi=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("Seyitinrobutu"); // Bluetooth cihaz adı
  Serial.println("Bluetooth başladı! Şimdi eşleştirme yapabilirsiniz.");
  servo.attach(D9);
  pinMode(gazsensoru,INPUT);
  pinMode(isinem,INPUT);
  pinMode(isiksensoru,INPUT);
  pinMode(hareketsensoru,INPUT);
  pinMode(lamb,OUTPUT);

  

}

void loop() {
    delay(150);
  if(aa6>1)
  aa6=0;
  if (SerialBT.available()) {
    
    String gelendeger=degeroku();
        Serial.println(gelendeger);
    if (gelendeger=="salonisikac" || gelendeger == "1"){
      aa1++;
      if(aa1>1)
      aa1=0;
      digitalWrite(lamb,aa1);
      Serial.println(aa1);
    }
    if (gelendeger=="mutfakisikac" || gelendeger == "2"){
      aa2++;
      if(aa2>1)
      aa2=0;
      digitalWrite(lamb,aa2);
      Serial.println(aa2);
    }
    if (gelendeger=="lavoboisikac" || gelendeger == "3"){
      aa3++;
      if(aa3>1)
      aa3=0;
      digitalWrite(lamb,aa3);
      Serial.println(aa3);
    }
    if (gelendeger=="yatakisikac" || gelendeger == "4"){
      aa4++;
      if(aa4>1)
      aa4=0;
      digitalWrite(lamb,aa4);
      Serial.println(aa4);
    }
    if (gelendeger=="koridorisikac" || gelendeger == "5"){
      aa5++;
      if(aa5>1)
      aa5=0;
      digitalWrite(lamb,aa5);
      Serial.println(aa5);
    }
    if (gelendeger=="kapiac" || gelendeger == "6"){
      aa6++;
      if(aa6>1)
      aa6=0;
      if(aa6=0)
      int kapi=0;
      if(aa6=1)
      int kapi=60;
      servo.write(kapi);
      Serial.println(aa6);
    }
    
  }
   
    /*if (gelendeger=="salonisikac"){
      digitalWrite(lamb,1);
    }
    if (gelendeger=="salonisikkapat"){
      digitalWrite(lamb,0);
    }
    if (gelendeger=){
      digitalWrite()
    }*/

}


String degeroku() {
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar >= '1' && incomingChar <= '6') {
      return String(incomingChar); 
    }
    if (incomingChar == '/') {
      String gelendeger1 = "";
      while (SerialBT.available()) {
        char nextChar = SerialBT.read();
        if (nextChar == ';') {
          break;
        }
        gelendeger1 += nextChar;
      }
      return gelendeger1; 
    }
  }
  return "";
}
