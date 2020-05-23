//动手做14-2：用  Android  手机蓝牙遥控机器人
//详细说明，请参阅第十四章，14-17页。

#include  <SoftwareSerial.h>  //引用BlueTooth库
SoftwareSerial  BT(12,11);  //设定BlueTooth接收脚,  传送脚

char  comm;      //接收BT值
const byte t = 19;   //超声波的脉冲发射脚
const byte e = 18;   //超声波的信号接收脚
const byte L1 = 13;  //LED接脚
const byte IA = 2;   //电机  A  的正反转接脚
const byte IB = 3;   //电机  A  的正反转接脚
const byte IC = 4;   //电机  B  的正反转接脚
const byte ID = 5;   //电机  B  的正反转接脚
const byte EA = 6;   //电机  A  的speed接脚
const byte EB = 7;   //电机  B  的speed接脚
const byte sp = 100;  //speed
const byte time = 200;  //time
long dd;      //将超声波的信号接收脚的信号转换为距离（厘米）的变量
int val;      //左转右转随机数变量

void  stop(){       //停止
  analogWrite(EA,0);
  analogWrite(EB,0);
  digitalWrite(IA,LOW);
  digitalWrite(IB,  LOW);
  digitalWrite(IC,  LOW);
  digitalWrite(ID,  LOW);
}
void  forward(){    //前进
  analogWrite(EA,sp);
  analogWrite(EB,sp);
  digitalWrite(IA,  HIGH);
  digitalWrite(IB,  LOW);
  digitalWrite(IC,  HIGH);
  digitalWrite(ID,  LOW);
  delay(time);
  stop();
}
void  backward(){    //后退
  analogWrite(EA,sp);
  analogWrite(EB,sp);
  digitalWrite(IA,  LOW);
  digitalWrite(IB,  HIGH);
  digitalWrite(IC,  LOW);
  digitalWrite(ID,  HIGH);
  delay(time);
  stop();
}
void  turnLeft(){    //左转
  analogWrite(EA,sp);
  analogWrite(EB,sp);
  digitalWrite(IA,  HIGH);
  digitalWrite(IB,  LOW);
  digitalWrite(IC,  LOW);
  digitalWrite(ID,  HIGH);
  delay(time);
  stop();
}
void  turnRight(){    //右转
  analogWrite(EA,sp);
  analogWrite(EB,sp);
  digitalWrite(IA,  LOW);
  digitalWrite(IB,  HIGH);
  digitalWrite(IC,  HIGH);
  digitalWrite(ID,  LOW);
  delay(time);
  stop();
}
void  ping(){
  digitalWrite(t,  LOW);  //低高低电平发一个短时间脉冲
  delayMicroseconds(2);
  digitalWrite(t,  HIGH);
  delayMicroseconds(10);
  digitalWrite(t,  LOW);
  dd  =  float(  pulseIn(e,  HIGH)  *  17  )  /  1000;  //将回波时间换算成cm
}
void  setup(){
  pinMode(L1,  OUTPUT);
  pinMode(4,  OUTPUT);
  pinMode(e,  INPUT);
  pinMode(t,  OUTPUT);
  pinMode(8,  OUTPUT);
  pinMode(9,  OUTPUT);
  digitalWrite(9,HIGH);
  pinMode(14,  OUTPUT);
  digitalWrite(14,HIGH);
  BT.begin(9600);    //启动BlueTooth
  Serial.begin(9600);
  pinMode(IA,  OUTPUT);  //电机  A  的致能脚位
  pinMode(IB,  OUTPUT);  //电机  A  的致能脚位
  pinMode(IC,  OUTPUT);  //电机  B  的致能脚位
  pinMode(ID,  OUTPUT);  //电机  B  的致能脚位
  randomSeed(analogRead(5));  //转向随机种子
  stop();      //先停止电机
/*  digitalWrite(L1,  HIGH);
  delay(500);
  digitalWrite(L1,  LOW);
  digitalWrite(L1,  HIGH);
  delay(500);
  digitalWrite(L1,  LOW);
  digitalWrite(L1,  HIGH);
  delay(500);
  digitalWrite(L1,  LOW);
  */
}
void  loop(){
  ping();
  Serial.print("distance:");
  Serial.print(dd);
  Serial.println("cm");
  delay(100);
  if(dd  >  10){
    if(BT.available()  >  0){
    comm  =  BT.read();
    Serial.println(comm);
    digitalWrite(L1,  HIGH);
    delay(100);
    digitalWrite(L1,  LOW);
    switch(comm){
    case  'w'  :  //接收到  'w'，前进
      Serial.println("forward");
      forward();
      break;
    case  'x'  :  //接收到  'x'，后退
      Serial.println("backward");
      backward();
      break;
    case  'a'  :  //接收到  'a'，左转
      Serial.println("left");
      turnLeft();
      break;
    case  'd'  :    //接收到  'd'，右转
      Serial.println("right");
      turnRight();
      break;
    case  's'  :    //接收到  's'，停止电机
      Serial.println("stop");
      stop();
        break;
      case  'u'  :  
        break;
      }
    }
  }
  else{
  stop();
  val  =  random(2);
  if(val  ==  0){
    //以下语句保证在遇到障碍物时，持续右转，直至避开障碍物为止。
    //障碍物定义为离小车10cm距离的目标。
    ping();
    while(dd  <=  10){
    turnRight();
    delay(500);
    stop();
    ping();
    }
  }
  else{
    //以下语句保证在遇到障碍物时，持续左转，直至避开障碍物为止。
    //障碍物定义为离小车10cm距离的目标。
    ping();
    while(dd  <=  10){
    turnLeft();
    delay(500);
    stop();
    ping();
    }
  }
}
}
