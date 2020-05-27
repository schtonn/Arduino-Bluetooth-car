/*
   2020 May 24th
*/

void write(bool a)
{
  if (a)
  {
    digitalWrite(13, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(13, LOW);
    delay(500);
  }
}

void setup()
{
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);

  Serial.begin(9600);

  delay(3000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("true");
  write(1);
  delay(500);
  Serial.println("false");
  write(0);
  delay(500);
}

