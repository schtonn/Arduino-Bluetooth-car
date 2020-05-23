/*
   Radio Bluetooth Car
   Car Part
   Written By Alex
   2020/23/05
*/

#include <SoftwareSerial.h>

const byte RADIOs = 10;
const byte RADIOr = 11;
SoftwareSerial RADIO(RADIOs, RADIOr);

const byte LF = 2; //Left Forward +
const byte LB = 3; //Left Back +
const byte RF = 4; //Right Forward +
const byte RB = 5; //Righy Back +
const byte LS = 6; //Left Speed
const byte RS = 7; //Right Speed

void WRITE(int s1, int s2, bool a, bool b, bool c, bool d) {
  analogWrite(LS, s1);
  analogWrite(RS, s2);

  if (a)digitalWrite(LF, HIGH);
  else digitalWrite(LF, LOW);

  if (b)digitalWrite(LB, HIGH);
  else digitalWrite(LB, LOW);

  if (c)digitalWrite(RF, HIGH);
  else digitalWrite(RF, LOW);

  if (d)digitalWrite(RB, HIGH);
  else digitalWrite(RB, LOW);
}
void S() {
  WRITE(0, 0, false, false, false, false);
}
void F(int SPEED) {
  WRITE(SPEED, SPEED, true, false, true, false);
}
void B(int SPEED) {
  WRITE(SPEED, SPEED, false, true, false, true);
}
void L(int SPEED) {
  WRITE(SPEED, SPEED, true, false, false, true);
}
void R(int SPEED) {
  WRITE(SPEED, SPEED, false, true, true, false);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(LS, OUTPUT);
  pinMode(RS, OUTPUT);

  pinMode(RADIOs, OUTPUT);
  pinMode(RADIOr, INPUT);


  RADIO.begin(9600);
  Serial.begin(9600);

  char code;

  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (RADIO.available()) {
    code = RADIO.read();
    Serial.println(code);
    switch (code) {
      case 'f':
        F();
        break;
      case 'b':
        B();
        break;
      case 'l':
        L();
        break;
      case 'r':
        R();
        break;
      default:
        S();
    }
  }
}
