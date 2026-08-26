#define ina1 D12
#define ina2 D13
#define inb1 D14
#define inb2 D15
#define ena D0
#define enb D1
#define j3ms D11
#define j3y A0
#define j3x A1
#include <Deneyap_Servo.h>     
#include <deneyap.h> 
void setup() {
  pinMode(j3x,INPUT);
  pinMode(j3y,INPUT); 
  pinMode(j3ms,INPUT); 
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(ina1,OUTPUT);
  pinMode(ina2,OUTPUT);
  pinMode(inb1,OUTPUT);
  pinMode(inb2,OUTPUT);
  Serial.begin(115200);
  

}

void loop() {
  int aydeger=analogRead(j3x);
  int axdeger=analogRead(j3y);
  if(axdeger>=2500 &&(aydeger<=2500  && aydeger>=1500)){
    analogWrite(ena,255);
    analogWrite(enb,255);
    sol(5);
  }
  else if(axdeger<=1500 &&(aydeger<=2500 && aydeger>=1500)){
    analogWrite(ena,255);
    analogWrite(enb,255);   
    sag(5);
  }
  if(aydeger<=1500 &&(axdeger<=2500  && axdeger>=1500)){
    analogWrite(ena,255);
    analogWrite(enb,255);
    ileri(5);
  }
  else if(aydeger>=2500 &&(axdeger<=2500 && axdeger>=1500)){
    analogWrite(ena,255);
    analogWrite(enb,255);
    geri(5);
  }
  else if(aydeger>=2500 && axdeger>=2500){
    analogWrite(ena,255);
    analogWrite(enb,150);
    geri(5);
  }
  else if(aydeger>=2500 && axdeger<=1500){
    analogWrite(ena,150);
    analogWrite(enb,255);
    geri(5);
  }
  else if(aydeger<=1500 && axdeger<=1500){
    analogWrite(ena,255);
    analogWrite(enb,150);
    ileri(5);
  }
  else if(aydeger<=1500 && axdeger>=2500){
    analogWrite(ena,150);
    analogWrite(enb,255);
    ileri(5);
  }
  else if(aydeger>=1500 && aydeger<=2500 && axdeger>=1500 && axdeger<=2500){
    dur(0);
  }
  delay(10);
 


}
void sol(int a){
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,1);
digitalWrite(inb2,0);
delay(a);
}
void sag(int a) {
digitalWrite(ina1,1);
digitalWrite(ina2,0);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a); 
}
void geri (int a){
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);
}
void ileri(int a){
digitalWrite(ina1,1);
digitalWrite(ina2,0);
digitalWrite(inb1,1);
digitalWrite(inb2,0);
delay(a);
}
void dur(int a){
digitalWrite(ina1,0);
digitalWrite(ina2,0);
digitalWrite(inb1,0);
digitalWrite(inb2,0);
delay(a);
}
void sertdur(int a){
digitalWrite(ina1,1);
digitalWrite(ina2,1);
digitalWrite(inb1,1);
digitalWrite(inb2,1);
delay(a);
}

