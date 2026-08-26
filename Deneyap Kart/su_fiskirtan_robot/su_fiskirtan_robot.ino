#define ina1 D15
#define ina2 D14
#define inb1 D13
#define inb2 D12



void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
   pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(D15,OUTPUT);
  pinMode(D14,OUTPUT);
  pinMode(D13,OUTPUT);
  pinMode(D12,OUTPUT);
  Serial.begin(115200);
  
  
}

void loop() {
While()
  
 

  


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


