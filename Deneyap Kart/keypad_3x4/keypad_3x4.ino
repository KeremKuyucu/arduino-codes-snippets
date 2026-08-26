#include <Key.h>
#include <Keypad.h>
const byte satir = 4;
const byte sutun = 3;
char tus;
char tuslar[satir] [sutun] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte satir_pinleri[satir] = {D0,D1,D4,D5};
byte sutun_pinleri[sutun] = {D6,D7,D9};
Keypad tus_takimi = Keypad(makeKeymap(tuslar), satir_pinleri, sutun_pinleri, satir, sutun );

void setup() {
Serial.begin(115200);

  

}

void loop() {
  tus = tus_takimi.getKey();
Serial.println(tus);
if (tus ==0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9){
  Serial.println(tus);
}
delay(250);
}
