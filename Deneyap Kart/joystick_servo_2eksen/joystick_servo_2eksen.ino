#include <Deneyap_Servo.h>
#define yordinat  A0
#define xapsis  A1
#define tus D4
Servo sev;
Servo sev2;
int xdinat,ydinat;
void setup() {
  sev.attach(D0);
  sev2.attach(D1,1);
  pinMode(tus,INPUT_PULLUP);
  digitalWrite(tus,1);
  Serial.begin(115200);
  pinMode(yordinat,INPUT);
  pinMode(xapsis,INPUT);
}

void loop() {
  int dly=5;
  if(tus<1){
  if(dly==5) dly=10;
  else{
if(dly==10) 
dly=20;
else if 
(dly==20) dly=5;
  } 
  delay(500); 
  }
  xdinat=analogRead(xapsis)/22.75;
  ydinat=analogRead(yordinat)/22.75;
  sev2.write(xdinat);
  sev.write(ydinat);
  Serial.print("yordinat: ");
  Serial.println(ydinat);
  Serial.print("xapsis: ");
  Serial.println(xdinat);
  delay(dly);
}