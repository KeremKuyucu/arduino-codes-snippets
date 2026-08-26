#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(D0, D1);  // Initialize sensor that uses digital pins 13 and 12.

void setup() {


pinMode(D15,OUTPUT);
pinMode(D14,OUTPUT);
pinMode(D13,OUTPUT);
pinMode(D12,OUTPUT);
pinMode(D9,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D5,OUTPUT);
Serial.begin(115200);

}

void loop() {
int m=distanceSensor.measureDistanceCm();
Serial.println(m);
if ((m >= 0 ) && ( m <=5)){
digitalWrite(D5,1);
digitalWrite(D6,0);
digitalWrite(D7,0);
digitalWrite(D9,0);
digitalWrite(D12,0);
digitalWrite(D13,0);
digitalWrite(D14,0);
digitalWrite(D15,0);
delay(50);

}else if ((m <= 5 ) && ( m <= 10)){
  digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,0);
digitalWrite(D9,0);
digitalWrite(D12,0);
digitalWrite(D13,0);
digitalWrite(D14,0);
digitalWrite(D15,0);
delay(50);


}else if ((m <= 10 ) && ( m <= 15)){
digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,1);
digitalWrite(D9,0);
digitalWrite(D12,0);
digitalWrite(D13,0);
digitalWrite(D14,0);
digitalWrite(D15,0);
delay(50);

}else if ((m <= 15 ) && ( m <= 20)){
digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,1);
digitalWrite(D9,1);
digitalWrite(D12,0);
digitalWrite(D13,0);
digitalWrite(D14,0);
digitalWrite(D15,0);
delay(50);
}else if ((m <= 20 ) && ( m <= 25)){
digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,1);
digitalWrite(D9,1);
digitalWrite(D12,1);
digitalWrite(D13,0);
digitalWrite(D14,0);
digitalWrite(D15,0);
delay(50);

}else if ((m <= 25 ) && ( m <= 30)){
digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,1);
digitalWrite(D9,1);
digitalWrite(D12,1);
digitalWrite(D13,1);
digitalWrite(D14,0);
digitalWrite(D15,0);
delay(50);
}else if ((m <= 30) && ( m <= 35)){
digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,1);
digitalWrite(D9,1);
digitalWrite(D12,1);
digitalWrite(D13,1);
digitalWrite(D14,1);
digitalWrite(D15,0);
delay(50);
}else if ((m <= 35 ) && ( m <= 40)){
digitalWrite(D5,1);
digitalWrite(D6,1);
digitalWrite(D7,1);
digitalWrite(D9,1);
digitalWrite(D12,1);
digitalWrite(D13,1);
digitalWrite(D14,1);
digitalWrite(D15,1);
delay(50);
}
}
//s=t/58