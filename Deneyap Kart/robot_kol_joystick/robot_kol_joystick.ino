#include <Servo.h>
#include <SoftwareSerial.h>

// Define servo objects
Servo base, shoulder, elbow, wrist;

// Define joystick pins
int basePin = A0;
int shoulderPin = A1;
int elbowPin = A2;
int wristPin = A3;

// Define software serial pins for wireless communication
SoftwareSerial bluetooth(10, 11); // RX, TX

void setup() {
  // Attach servos to their respective pins
  base.attach(3);
  shoulder.attach(5);
  elbow.attach(6);
  wrist.attach(9);

  // Initialize serial communication
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // Read joystick values
  int baseValue = analogRead(basePin);
  int shoulderValue = analogRead(shoulderPin);
  int elbowValue = analogRead(elbowPin);
  int wristValue = analogRead(wristPin);

  // Map joystick values to servo positions
  base.write(map(baseValue, 0, 1023, 0, 180));
  shoulder.write(map(shoulderValue, 0, 1023, 0, 180));
  elbow.write(map(elbowValue, 0, 1023, 0, 180));
  wrist.write(map(wristValue, 0, 1023, 0, 180));

  // Send servo positions to the connected device via Bluetooth
  bluetooth.print(base.read());
  bluetooth.print(",");
  bluetooth.print(shoulder.read());
  bluetooth.print(",");
  bluetooth.print(elbow.read());
  bluetooth.print(",");
  bluetooth.println(wrist.read());

  delay(50); // Delay to allow for smooth movement
}
