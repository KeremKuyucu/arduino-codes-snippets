#include <lsm6dsm.h>
#define ina1 D12
#define ina2 D13
#define inb1 D14
#define inb2 D15
// x eksenli ina1 ina2  y eksenli inb1 inb2
LSM6DSM IMU;
void setup() {
  pinMode(ina1,OUTPUT);
  pinMode(ina2,OUTPUT);
  pinMode(inb1,OUTPUT);
  pinMode(inb2,OUTPUT);
  Serial.begin(115200);
  IMU.begin();
}

void loop() {
  float accAngleX;
  float accAngleY;
  accAngleX = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2) + 0.001)) * 180 / PI;
  accAngleY = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2) + 0.001)) * 180 / PI;
delay(50);
if(accAngleX>1)
X(50);
else if(accAngleX<-1)
Xters(50);
else
Xdur(10);
if(accAngleY>1)
Y(50);
else if(accAngleY<-1)
Yters(50);
else 
Ydur(50);
 Serial.print("accAngleX:");
  Serial.println(accAngleX);
  Serial.print("accAngleY:");
  Serial.println(accAngleY);
}

void X(int a){
digitalWrite(ina1,1);
digitalWrite(ina2,0);
delay(a);
}

void Xters(int a) {
digitalWrite(ina1,0);
digitalWrite(ina2,1);
delay(a);
  
}
void Y(int a){
digitalWrite(inb1,1);
digitalWrite(inb2,0);
delay(a);
}
void Yters(int a){
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);
}
void Xdur(int a){
digitalWrite(ina1,0);
digitalWrite(ina2,0);
delay(a);
}
void Ydur(int a){
digitalWrite(inb1,0);
digitalWrite(inb2,0);
delay(a);




}
