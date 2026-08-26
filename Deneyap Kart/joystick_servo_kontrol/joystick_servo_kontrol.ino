#define joyx A0
#define joyy A1
#define joy1x A2
#define joy1y A3
#define joyax A2
#define joyay A3
#include <Deneyap_Servo.h>     
#include <deneyap.h>  
Servo servo1;                  
Servo servo2;                   
Servo servo3;
Servo servo4;                   
int servoa1=90;
  int servoa2=90;
  int servoa3=90;
  int servoa4=90;
void setup() {
  pinMode(joyx,INPUT);
  pinMode(joyy,INPUT);
  pinMode(joy1x,INPUT);
  pinMode(joy1y,INPUT);
  pinMode(joyx,INPUT                                    );
  pinMode(joyy,INPUT);
  pinMode(joy1x,INPUT);
  pinMode(joy1y,INPUT); 
  servo1.attach(D0);            
  servo2.attach(D1,1);          
  servo3.attach(D4,2); 
  servo4.attach(D5,3);
  Serial.begin(115200);
  
}

void loop() { 
  int xdeger=analogRead(joyx);
  int ydeger=analogRead(joyy);
  int x1deger=analogRead(joy1x);
  int y1deger=analogRead(joy1y);
  if (xdeger<=1500)
    servoa1-=5;
   if (xdeger>=2500)
    servoa1+=5;
     if (x1deger<=1500)
    servoa2-=5;
   if (x1deger>=2500)
    servoa2+=5;
     if (ydeger<=1500)
    servoa3-=5;
   if (ydeger>=2500)
    servoa3+=5;
    if (y1deger<=1500)
    servoa4-=5;
   if (y1deger>=2500)
    servoa4+=5;
    if (servoa1<0)
      servoa1=0;
    if (servoa2<0)
      servoa2=0;
   if (servoa3<0)
      servoa3=0;
    if (servoa4<0)
      servoa4=0;
  if (servoa1>180)
      servoa1=180;
    if (servoa2>180)
      servoa2=180;
   if (servoa3>180)
      servoa3=180;
    if (servoa4>180)
      servoa4=180;

  delay(50);
  servo1.write(servoa1);
  servo2.write(servoa2);
  servo3.write(servoa3);
  servo4.write(servoa4);
  Serial.println(servoa1);
  Serial.println(servoa2);
  Serial.println(servoa3);
  Serial.println(servoa4);
  
  


}
