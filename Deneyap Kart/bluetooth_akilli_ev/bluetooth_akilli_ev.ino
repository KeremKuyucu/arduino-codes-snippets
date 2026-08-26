
#include <Deneyap_Servo.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
//#define led D
#define lamb D12
#define lamb1 D1
#define lamb2 D13
#define lamb3 D9
#define lamb4 D14
//const int ledPin = led;
#define gazsensoru A0
#define hareketsensoru D4
#define buz D10
Servo servo;
String gelendeger="";
  int aa1=0,aa2=0,aa3=0,aa4=0,aa5=0,aa6=0;

void setup() {
  //pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("Seyitrobutu3"); 
  servo.attach(D15);
  pinMode(gazsensoru,INPUT);
  pinMode(hareketsensoru,INPUT);
  pinMode(lamb,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(lamb1,OUTPUT);
  pinMode(lamb2,OUTPUT);
  pinMode(lamb3,OUTPUT);
  pinMode(lamb4,OUTPUT);
int kapi=0;
  

}

void loop() {
    delay(50);
int gazdeger=analogRead(gazsensoru);
int hareketdeger=digitalRead(hareketsensoru);
if (hareketdeger==1){
  digitalWrite(buz, 0);}
else{
  digitalWrite(buz, 1);
  SerialBT.print("İzinsiz Giriş Var");
}
    if(gazdeger>=300){
    digitalWrite(buz,1);
    delay(30);
    digitalWrite(buz,0);
    delay(30);
    SerialBT.print("YANGIIIIN VAAAAR");
    }
    else
    digitalWrite(buz,0);
    if (hareketdeger==1){
      SerialBT.print("İzinsiz Giriş Var");}
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
      digitalWrite(lamb1,aa2);
      Serial.println(aa2);
    }
    if (gelendeger=="lavoboisikac" || gelendeger == "3"){
      aa3++;
      if(aa3>1)
      aa3=0;
      digitalWrite(lamb2,aa3);
      Serial.println(aa3);
    }
    if (gelendeger=="koridorisikac" || gelendeger == "4"){
      aa4++;
      if(aa4>1)
      aa4=0;
      digitalWrite(lamb3,aa4);
      Serial.println(aa4);
    }
    if (gelendeger=="yatakisikac" || gelendeger == "5"){
      aa5++;
      if(aa5>1)
      aa5=0;
      digitalWrite(lamb4,aa5);
      Serial.println(aa5);
    }
    if (gelendeger=="kapiac" || gelendeger == "6"){
      aa6++;
      if(aa6>1)
      aa6=0;
      servo.write(aa6*60);
      Serial.println(aa6);
    }
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
