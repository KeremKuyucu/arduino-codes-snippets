
#define ina1 D4
#define ina2 D9
#define inb1 D7
#define inb2 D1
#define ena D0
#define enb D5



void setup() {
   pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(ina1,OUTPUT);
  pinMode(ina2,OUTPUT);
  pinMode(inb1,OUTPUT);
  pinMode(inb2,OUTPUT);
  Serial.begin(115200);
  
  
}

void loop() {
  digitalWrite(ena,255);
  digitalWrite(enb,255);

 

  sag(1250);
  sertdur(1);

  delay(10000000);
 

  


}
void sag(int a){

digitalWrite(ina1,1);
digitalWrite(ina2,0);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);
}

void sol(int a) {
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,1);
digitalWrite(inb2,0);
delay(a);
  
}



void ileri (int a){
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);



}



void geri(int a){
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


