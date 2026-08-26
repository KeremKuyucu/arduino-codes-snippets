#include <Deneyap_Servo.h>     
#include <deneyap.h>  
 
Servo servo1;                  
Servo servo2;                   
Servo servo3;
Servo servo4;  
void setup() {
  servo1.attach(D0);            
  servo2.attach(D1,1);          
  servo3.attach(D4,2); 
  servo4.attach(D5,3);
  Serial.begin(115200)
}

void loop() {
 

}
