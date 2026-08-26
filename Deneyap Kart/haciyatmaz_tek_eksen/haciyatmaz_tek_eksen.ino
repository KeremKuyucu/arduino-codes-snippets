#include <lsm6dsm.h>
#define ina1 D14
#define ina2 D15
#define hiz D13
// x eksenli ina1 ina2  y eksenli inb1 inb2
LSM6DSM IMU;
void setup() {
  pinMode(ina1,OUTPUT);
  pinMode(hiz,OUTPUT);
  pinMode(ina2,OUTPUT);
  Serial.begin(115200);
  IMU.begin();
}

void loop() {
  analogWrite(hiz,180);
  float accAngleX;
  accAngleX = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2) + 0.001)) * 180 / PI;
delay(50);
Serial.print("accAngleX:");
  Serial.println(accAngleX);
if(accAngleX<5 && accAngleX>-5)
Xdur(1);
if(accAngleX<-5)
X(20);
Xdur(0);
if(accAngleX>5)
Xters(20);
Xdur(0);
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
void Xdur(int a) {
digitalWrite(ina1,1);
digitalWrite(ina2,1);
delay(a);
}
  



