
//sol motor 0 6 7
//sağmotor 1 4 5
#define ina1 D6;
#define ina2=D7;
#define inb1=D4;
#define inb2=D5;
#define jsx A0;
#define js=D9;
#define stepa1 D15
 #define stepb1 D0
#define stepa2 D14
 #define stepb2 D1
#define stepa3 D13
 #define stepb3 D10
#define stepa4 D12
 #define stepb4 D11
//15 14 13 12
//2 3 10 11
//int ena2=D9
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(jsx,INPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(js,INPUT);
   pinMode(stepa1,OUTPUT);
  pinMode(stepa2,OUTPUT);
  pinMode(stepa3,OUTPUT);
  pinMode(stepa4,OUTPUT);
  pinMode(stepb1,OUTPUT);
  pinMode(stepb2,OUTPUT);
  pinMode(stepb3,OUTPUT);
  pinMode(stepb4,OUTPUT);
  
  


}

void loop() {
  //in1 1 in2 0 ise ileri
  int but=analogRead(js);
  if (but==0){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  delay(100);
  }
  else
  {
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  delay(100);
  }
  int aci=analogRead(jsx);
if (aci>3500){
digitalWrite(stepa1,1);
digitalWrite(stepa2,0);
digitalWrite(stepa3,0);
digitalWrite(stepa4,0);
digitalWrite(stepb1,1);
digitalWrite(stepb2,0);
digitalWrite(stepb3,0);
digitalWrite(stepb4,0);
delay(5);
digitalWrite(stepa1,0);
digitalWrite(stepa2,1);
digitalWrite(stepa3,0);
digitalWrite(stepa4,0);
digitalWrite(stepb1,1);
digitalWrite(stepb2,0);
digitalWrite(stepb3,0);
digitalWrite(stepb4,0);
delay(5);
digitalWrite(stepa1,0);
digitalWrite(stepa2,0);
digitalWrite(stepa3,1);
digitalWrite(stepa4,0);
digitalWrite(stepb1,0);
digitalWrite(stepb2,0);
digitalWrite(stepb3,1);
digitalWrite(stepb4,0);
delay(5);
digitalWrite(stepa1,0);
digitalWrite(stepa2,0);
digitalWrite(stepa3,0);
digitalWrite(stepa4,1);
digitalWrite(stepb1,0);
digitalWrite(stepb2,0);
digitalWrite(stepb3,0);
digitalWrite(stepb4,1);
delay(5);
}
if (aci<1000){
digitalWrite(stepa1,0);
digitalWrite(stepa2,0);
digitalWrite(stepa3,0);
digitalWrite(stepa4,1);
digitalWrite(stepb1,0);
digitalWrite(stepb2,0);
digitalWrite(stepb3,0);
digitalWrite(stepb4,1);
delay(5);
digitalWrite(stepa1,0);
digitalWrite(stepa2,0);
digitalWrite(stepa3,1);
digitalWrite(stepa4,0);
digitalWrite(stepb1,0);
digitalWrite(stepb2,0);
digitalWrite(stepb3,1);
digitalWrite(stepb4,0);
delay(5);
digitalWrite(stepa1,0);
digitalWrite(stepa2,1);
digitalWrite(stepa3,0);
digitalWrite(stepa4,0);
digitalWrite(stepb1,0);
digitalWrite(stepb2,1);
digitalWrite(stepb3,0);
digitalWrite(stepb4,0);

delay(5);
digitalWrite(stepa1,1);
digitalWrite(stepa2,0);
digitalWrite(stepa3,0);
digitalWrite(stepa4,0);
digitalWrite(stepb1,1);
digitalWrite(stepb2,0);
digitalWrite(stepb3,0);
digitalWrite(stepb4,0);
delay(5);
}
}
