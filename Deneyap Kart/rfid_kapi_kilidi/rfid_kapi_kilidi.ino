#include <MFRC522.h>
#include <Deneyap_Servo.h>
//D10 sda d5 sck d7 mosi d6 miso d4 rst 
#define ss D10
#define rst D4
MFRC522 rfid(ss,rst);
byte ID[4] ={195,169,170,18};
Servo servom;



void setup() {
  servom.attach(D1);
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if(!rfid.PICC_IsNewCardPresent())
    return;
  if(!rfid.PICC_ReadCardSerial())
    return;
  if(rfid.uid.uidByte[0]==ID[0] &&     rfid.uid.uidByte[1]==ID[1] &&     rfid.uid.uidByte[2]==ID[2] &&     rfid.uid.uidByte[3]==ID[3] ) {
      Serial.println("Kapini aciliyor...");
      ekranayazdir();
      servom.write(180);
      delay(5000);
      servom.write(0);
      Serial.println("Kapini kapaniyor...");
      delay(1000);
     }
     else{
      Serial.println("Yanlis Kart!!!");
      ekranayazdir();
     }
     rfid.PICC_HaltA();
}
void ekranayazdir(){
Serial.print("ID Numarasi : ");
for(int i=0;i<4;i++){
  Serial.print(rfid.uid.uidByte[i]);
  Serial.print(" ");
}
  Serial.println("");
}
//131 179 25 19


