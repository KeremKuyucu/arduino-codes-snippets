#define kiza1 A0
#define kizb1 A1
#define kizc1 A2
#define ina1 D15
#define ina2 D14
#define inb1 D13
#define inb2 D12
#define ina D0
#define inb D1
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(D15,OUTPUT);
  pinMode(D14,OUTPUT);
  pinMode(D13,OUTPUT);
  pinMode(D12,OUTPUT);
  Serial.begin(115200);
    pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
}


void loop() {
 analogWrite(D0,255);
  analogWrite(D1,255);

ileri(100);
}
void sol(int a){

digitalWrite(ina1,1);
digitalWrite(ina2,0);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);
}

void sag(int a) {
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,1);
digitalWrite(inb2,0);
delay(a);
  
}



void geri(int a){
digitalWrite(ina1,0);
digitalWrite(ina2,1);
digitalWrite(inb1,0);
digitalWrite(inb2,1);
delay(a);



}



void ileri(int a){
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


