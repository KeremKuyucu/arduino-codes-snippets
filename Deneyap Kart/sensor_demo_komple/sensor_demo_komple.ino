#include <DHT.h>
#include <DHT_U.h>

#define kiza1 A0
#define kizb1 A1
#define kizc1 A2
#define ina1 D15
#define ina2 D14
#define inb1 D13
#define inb2 D12



}

void loop() {
  lcd.clear();
  int joy1=analogRead(jsx);
  int don=map(joy1,0,4095,0,180);
  Serial.print("Joystick:");
  Serial.println(don);
  servo1.write(don);
  int m=distanceSensor.measureDistanceCm();
  Serial.println(m);
  
  
  
  if (m<5){
    digitalWrite(buz,1);
  }
  if (m>5){
    digitalWrite(buz,0);
  }
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print(m);
  delay(250);




  }

  
  
  


