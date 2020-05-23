/*
   Radio Bluetooth Car
   Bluetooth -> Radio Part
   Written By Alex
   2020/23/05
*/

#include <SoftwareSerial.h>

const byte RADIOs = 2;
const byte RADIOr = 3;
SoftwareSerial RADIO(RADIOs, RADIOr);
const byte BTs = 4;
const byte BTr = 5;
SoftwareSerial BT(BTs, BTr);

void blink(){
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
}

void setup() {
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);

  pinMode(RADIOs, OUTPUT);
  pinMode(RADIOr, INPUT);
  
  pinMode(BTs, OUTPUT);
  pinMode(BTr, INPUT);

  RADIO.begin(9600);
  BT.begin(9600);
  Serial.begin(9600);

  char code;

  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available()) {
    code = RADIO.read();
    Serial.println(code);
    RADIO.println(code);
    blink();
  }
}
