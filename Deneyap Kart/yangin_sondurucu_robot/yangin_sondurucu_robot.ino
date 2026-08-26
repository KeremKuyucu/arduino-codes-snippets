#define yaniyorsag A2
#define yaniyorsol A1
#define yaniyorarka A0
#define ina1 D4
#define ina2 D9
#define inb1 D7
#define inb2 D1
#define su D15
#define ena D0
#define enb D5



void setup() {
  pinMode(yaniyorarka,INPUT);
  pinMode(yaniyorsag,INPUT);
  pinMode(yaniyorsol,INPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(ina1,OUTPUT);
  pinMode(ina2,OUTPUT);
  pinMode(inb1,OUTPUT);
  pinMode(inb2,OUTPUT);
  pinMode(su,OUTPUT);

  Serial.begin(115200);
}

void loop() {
  digitalWrite(ena,255);
  digitalWrite(enb,255);

  int arka=analogRead(yaniyorarka);
  int sag1=analogRead(yaniyorsag);
  int sol1=analogRead(yaniyorsol);

  if( arka > 500 && sag1 <500 && sol1 <500){
  sag(2500);
  sertdur(1);
  }
  if(sag1>500 && sol1<500 && arka <500){
    sag(350);
    sertdur(1);
  }
  if(sol1 >500 && sag1<500 && arka <500){
    sol(350);
    sertdur(1);
  }
  if(sag1>450 && sol1>450){
  digitalWrite(su,1);
  delay(1000);
  }
  else
  {digitalWrite(su,0);
  delay(1000);}
  

  Serial.print(sag1);Serial.print("-");
  Serial.print(sol1);Serial.print("-");
  Serial.println(arka);
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


