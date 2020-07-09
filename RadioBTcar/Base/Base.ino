/*
   Radio Bluetooth Car
   Bluetooth -> Radio Part
   Written By Alex
   2020 May 23rd
*/

#include <SoftwareSerial.h>

const byte RADIOs = 2; //Radio Send
const byte RADIOr = 3; //Radio Recieve
SoftwareSerial RADIO(RADIOs, RADIOr);
const byte BTs = 4; //Bluetooth Send
const byte BTr = 5; //Bluetooth Recieve
SoftwareSerial BT(BTs, BTr);

char code;

void blink()
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}

void setup()
{
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);

  pinMode(RADIOs, OUTPUT);
  pinMode(RADIOr, INPUT);

  pinMode(BTs, OUTPUT);
  pinMode(BTr, INPUT);

  RADIO.begin(9600);
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("start: ");

  delay(3000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (BT.available())
  {
    Serial.println("yes: ");
    code = RADIO.read();
    Serial.println(code);
    RADIO.write(code);
    blink();
  }
  if(Serial.available()){
    Serial.println("chuajnkouyouxinhao!!!!youxinhao!!!!");
  }
}
