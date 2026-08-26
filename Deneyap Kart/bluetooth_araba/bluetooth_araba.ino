#include "BluetoothSerial.h"
#define ina1 D15
#define ina2 D14
#define inb1 D13
#define inb2 D12
#define hiz D0// sag motor
#define hiz2 D1 // sol motor
#define but D9 
#define but2 D10
BluetoothSerial SerialBT;
//d0 na 
void setup() {
  Serial.begin(115200);
pinMode(ina1,OUTPUT);
pinMode(ina2,OUTPUT);
pinMode(inb1,OUTPUT);
pinMode(inb2,OUTPUT);
pinMode(hiz,OUTPUT);
pinMode(hiz2,OUTPUT);
pinMode(but,INPUT);
pinMode(but2,INPUT);
}
void loop() {
  analogWrite(D0,255);
  analogWrite(D1,255);



}

void sol(int a){

digitalWrite(ina1,1);
digitalWrite(ina2,0);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);
}

void sag(int a) {
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,1);
digitalWrite(inb2,0);
delay(a);
  
}



void geri(int a){
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

