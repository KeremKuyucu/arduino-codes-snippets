#define kirmizi D9
#define yesil SDA
#define mavi SCL
#define pot A0
void setup() {
pinMode(kirmizi,OUTPUT);
pinMode(yesil,OUTPUT);
pinMode(mavi,OUTPUT);
pinMode(pot,INPUT);
}

void loop() {
   int deger=analogRead(pot);
   rgbcolor(deger/5,deger,deger);
   delay(25);


 
}

void rgbcolor(int red,int green,int blue){
  analogWrite(kirmizi,red);
  analogWrite(mavi,blue);
  analogWrite(yesil,green);


}
