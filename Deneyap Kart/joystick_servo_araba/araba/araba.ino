#define ina1 D12
#define ina2 D13
#define inb1 D14
#define inb2 D15
#define ena D0
#define enb D1
#include <Deneyap_Servo.h>     
#include <deneyap.h>  
void setup() {
pinMode (ena,OUTPUT);
pinMode (enb,OUTPUT);
pinMode(ina1,OUTPUT);
pinMode(ina2,OUTPUT);
pinMode(inb1,OUTPUT);
pinMode(inb2,OUTPUT);
Serial.begin(115200);
}
void loop() {
analogWrite(ena,255);
analogWrite(enb,255);
ileri(1000);


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
