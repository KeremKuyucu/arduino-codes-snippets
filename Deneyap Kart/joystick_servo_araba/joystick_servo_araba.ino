#define ina1 D12
#define ina2 D13
#define inb1 D14
#define inb2 D15
#define ena D0
#define enb D1
#define j1ms D9
#define j2ms D10
#define j3ms D11
#define j1y A4
#define j1x A5
#define j2y A2
#define j2x A3
#define j3y A0
#define j3x A1
#include <Deneyap_Servo.h>     
#include <deneyap.h>  
 //4 5 6 7 A0j3y A1j3x D9j3ms A2 j2y A3 j2x j2ms D10 A4j1y A5 j1x D11 j1ms
Servo servo1;                  
Servo servo2;                   
Servo servo3;
Servo servo4;                   
int servoa1=90;
  int servoa2=90;
  int servoa3=90;
  int servoa4=90;
void setup() {
  pinMode(j1x,INPUT);
  pinMode(j1y,INPUT);
  pinMode(j2x,INPUT);
  pinMode(j2y,INPUT); 
  pinMode(j3x,INPUT);
  pinMode(j3y,INPUT); 
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(ina1,OUTPUT);
  pinMode(ina2,OUTPUT);
  pinMode(inb1,OUTPUT);
  pinMode(inb2,OUTPUT);
  servo1.attach(D4);            
  servo2.attach(D5,1);          
  servo3.attach(D6,2); 
  servo4.attach(D7,3);
  Serial.begin(115200);
  
}

void loop() { 
  int xdeger=analogRead(j1x);
  int ydeger=analogRead(j1y);
  int x1deger=analogRead(j2x);
  int y1deger=analogRead(j2y);
  int aydeger=analogRead(j3x);
  int axdeger=analogRead(j3y);
  if (xdeger<=1500)
    servoa1-=5;
  else if (xdeger>=2500)
    servoa1+=5;
  if (x1deger<=1500)
    servoa2-=5;
  else if (x1deger>=2500)
    servoa2+=5;
  if (ydeger<=1500)
    servoa3-=5;
  else if (ydeger>=2500)
    servoa3+=5;
  if (y1deger<=1500)
    servoa4-=5;
  else if (y1deger>=2500)
    servoa4+=5;
  if (servoa1<0)
      servoa1=0;
  else if (servoa2<0)
      servoa2=0;
  if (servoa3<0)
      servoa3=0;
  else if (servoa4<0)
      servoa4=0;
  if (servoa1>180)
      servoa1=180;
  else if (servoa2>180)
      servoa2=180;
  if (servoa3>180)
      servoa3=180;
  else if (servoa4>180)
      servoa4=180;

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
  servo1.write(servoa1);
  servo2.write(servoa2);
  servo3.write(servoa3);
  servo4.write(servoa4);
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
  
  



