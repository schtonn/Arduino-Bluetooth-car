#include  <SoftwareSerial.h>//include BlueTooth
#include <MsTimer2.h>
SoftwareSerial  BT(12, 11);//set BlueTooth send and recieve

char comm;//recieve BlueTooth
const byte t = 19;//Ping:send
const byte e = 18;//Ping:recieve
const byte L1 = 13;//LED
const byte IA = 2;//A:High or Low
const byte IB = 3;//A:High or Low
const byte IC = 4;//B:High or Low
const byte ID = 5;//B:High or Low
const byte EA = 6;//A:Speed
const byte EB = 7;//B:Speed
const byte sp = 100;//speed const of forward and backward
const byte spt = 125;//speed const of left and right
const byte distance_const = 100;//time
const byte turn_const = 10;//time
long current_distance;//current distance(centimeter)
int random_val;//random val of turn left or right

void job() {
  static unsigned int cnt = 0;
  ++cnt;
  if (cnt > 1000)cnt = 0;
  if (cnt % distance_const == 0)distance();
  if (cnt % turn_const == 0)turn();
}

void stop() {
  analogWrite(EA, 0);
  analogWrite(EB, 0);
  digitalWrite(IA, LOW);
  digitalWrite(IB, LOW);
  digitalWrite(IC, LOW);
  digitalWrite(ID, LOW);
}

void forward() {
  analogWrite(EA, sp);
  analogWrite(EB, sp);
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
}

void backward() {
  analogWrite(EA, sp);
  analogWrite(EB, sp);
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, LOW);
  digitalWrite(ID, HIGH);
}

void backward_delay() {
  analogWrite(EA, sp);
  analogWrite(EB, sp);
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, LOW);
  digitalWrite(ID, HIGH);
  delay(1000);
  stop();
}
void turnLeft() {
  analogWrite(EA, spt);
  analogWrite(EB, spt);
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
  digitalWrite(IC, LOW);
  digitalWrite(ID, HIGH);
}
void turnRight() {
  analogWrite(EA, spt);
  analogWrite(EB, spt);
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
}
void ping() {
  digitalWrite(t, LOW);//send a pulse
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(10);
  digitalWrite(t, LOW);
  current_distance = float(pulseIn(e, HIGH) * 17) / 1000; //convert the echo time into centimeter
}
void distance() {
  ping();
  if (current_distance <= 20) {
    stop();
    random_val = random(2);
    if (random_val == 0) {
      //go back and turn right until avoid the obstacle
      ping();
      while (current_distance <= 20) {
        if (current_distance >= 2000 || current_distance <= 10) {
          backward_delay();
        }
        turnRight();
        delay(500);
        stop();
        ping();
      }
    }
    else {
      //go back and turn left until avoid the obstacle
      ping();
      while (current_distance <= 20) {
        if (current_distance >= 2000 || current_distance <= 10) {
          backward_delay();
        }
        turnLeft();
        delay(500);
        stop();
        ping();
      }
    }
  }
}
void turn() {
  if (BT.available()) {
    comm = BT.read();
    Serial.println(comm);
    switch (comm) {
      case 'w'://recieve 'w',go forward
        Serial.println("forward");
        forward();
        break;
      case 'x'://recieve 'x',go back
        Serial.println("backward");
        backward();
        break;
      case 'a'://recieve 'a',turn left
        Serial.println("left");
        turnLeft();
        break;
      case 'd'://recieve 'd',turn right
        Serial.println("right");
        turnRight();
        break;
      case 's'://recirve 's',stop
        Serial.println("stop");
        stop();
        break;
      case 'u':
        break;
    }
  }
}
void setup() {
  pinMode(L1, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(e, INPUT);
  pinMode(t, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(IA, OUTPUT);//A:pinmode
  pinMode(IB, OUTPUT);//A:pinmode
  pinMode(IC, OUTPUT);//B:pinmode
  pinMode(ID, OUTPUT);//B:pinmode
  randomSeed(analogRead(5));//random seed
  MsTimer2::set(1, job);
  MsTimer2::start();
  stop();//stop first
}
void loop() {}
