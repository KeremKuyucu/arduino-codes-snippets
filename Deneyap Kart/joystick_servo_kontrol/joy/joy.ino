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
void setup() {
  pinMode(j1x,INPUT);
  pinMode(j1y,INPUT);
  pinMode(j2x,INPUT);
  pinMode(j2y,INPUT); 
  pinMode(j3x,INPUT);
  pinMode(j3y,INPUT); 
  Serial.begin(115200);

}

void loop() {
  int y1deger=analogRead(j1x);
  int ydeger=analogRead(j1y);
  int x1deger=analogRead(j2x);
  int xdeger=analogRead(j2y);
  int aydeger=analogRead(j3x);
  int axdeger=analogRead(j3y);
  Serial.print("axdeger");
  Serial.print("  ");
  Serial.print("aydeger");
  Serial.print("  ");
  Serial.print("x1deger");
  Serial.print("  ");
  Serial.print("xdeger");
  Serial.print("  ");
  Serial.print("y1deger");
Serial.print("  ");
  Serial.println("ydeger");
  Serial.print(axdeger);
  Serial.print("  ");
  Serial.print(aydeger);
  Serial.print("  ");
  Serial.print(x1deger);
  Serial.print("  ");
  Serial.print(xdeger);
  Serial.print("  ");
  Serial.print(y1deger);
  Serial.print("  ");
  Serial.println(ydeger);
  Serial.print("  ");
  delay(75);

}
