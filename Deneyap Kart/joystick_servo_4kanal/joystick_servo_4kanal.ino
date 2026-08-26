#include "deneyap.h"
#include <Deneyap_Servo.h>
#define SW1_pin D0
#define SW2_pin D1
#define X1_pin A0
#define Y1_pin A1
#define X2_pin A2
#define Y2_pin A3
#define SERVOPIN1 D14
#define SERVOPIN2 D13
#define SERVOPIN3 D12
#define SERVOPIN4 D15

int teta1min=0;
int teta1max=3000;
int teta2min=0;
int teta2max=3000;
int teta3min=0;
int teta3max=3000;
int teta4min=1500;
int teta4max=2000;

int valin1, valin2, valin3, valin4;
int valcalc1=1500;
int valcalc2=1500;
int valcalc3=1500;
int valcalc4=1500;
int jystp=20;

void setup()
{

}

void loop ()
{
  
}