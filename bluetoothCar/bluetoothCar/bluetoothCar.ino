// 动手做14-2：用 Android 手机蓝牙遥控机器人
// 详细说明，请参阅第十四章，14-17页。

#include <SoftwareSerial.h>    // 引用「软件序列埠」程式库
#include <Metro.h> 
SoftwareSerial BT(12, 11);    // 设定软件序列埠(接收脚, 传送脚)

char comm;                     // 接收序列埠值的变数
const byte t = 19;             // 超声波的脉冲发射脚
const byte e = 18;             // 超声波的信号接收脚
const byte L1 = 13;             // 电机 A 的致能接脚，控制速度
const byte IA = 5;             // 电机 A 的正反转接脚
const byte IB = 7;             // 电机 A 的正反转接脚
//const byte EB = 4;             // 电机 B 的致能接脚，控制速度
const byte IC = 11;             // 电机 B 的正反转接脚
const byte ID = 10;            // 电机 B 的正反转接脚
long dd;                       // 将超声波的信号接收脚的信号转换为距离（厘米）的变量
int val;                       // 左转右转随机数变量
int b = 0;                     // 左转闪灯变量
int z = 0;                     // 右转闪灯变量
//const byte speed = 130;        // 电机转速（0~255）

void stop() {               // 电机停止
  //  analogWrite(EA, 0);        // 电机 A 的 PWM 输出
  //  analogWrite(EB, 0);        // 电机 B 的 PWM 输出
  digitalWrite(IA, LOW);
  digitalWrite(IB, LOW);
  digitalWrite(IC, LOW);
  digitalWrite(ID, LOW);
}
void forward() {             // 电机转向：前进
  //  analogWrite(EA, speed);    // 电机 A 的 PWM 输出
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
  //  analogWrite(EB, speed);    // 电机 B 的 PWM 输出
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
}
void backward() {            // 电机转向：后退
  //  analogWrite(EA, speed);    // 电机 A 的 PWM 输出
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  //  analogWrite(EB, speed);    // 电机 B 的 PWM 输出
  digitalWrite(IC, LOW);
  digitalWrite(ID, HIGH);
}
void turnLeft() {            // 电机转向：左转
  while (z < 3) {
    z = z + 1;
    light2();
    delay(50);
    low2();
    delay(50);
  }
  z = 0;
  //  analogWrite(EA, speed);    // 电机 A 的 PWM 输出
  digitalWrite(IA, LOW);     // 电机 A 反转
  digitalWrite(IB, HIGH);
  //  analogWrite(EB, speed);    // 电机 B 的 PWM 输出
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(200);//设定转方向的幅度--时间
  stop();
}
void turnRight() {           // 电机转向：右转
  while (b < 3) {
    b = b + 1;
    light1();
    delay(50);
    low1();
    delay(50);
  }
  b = 0;
  //  analogWrite(EA, speed);    // 电机 A 的 PWM 输出
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
  //  analogWrite(EB, speed);    // 电机 B 的 PWM 输出
  digitalWrite(IC, LOW);     // 电机 B 反转
  digitalWrite(ID, HIGH);
  delay(200);//设定转方向的幅度--时间
  stop();
}
void light1() {
  digitalWrite(9, HIGH);
}
void light2() {
  digitalWrite(53, HIGH);
}
void low1() {
  digitalWrite(9, LOW);
}
void low2() {
  digitalWrite(53, LOW);
}
void ping() {
  digitalWrite(t, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(10);
  digitalWrite(t, LOW);
  dd = float( pulseIn(e, HIGH) * 17 ) / 1000; //将回波时间换算成cm
}
void setup() {
  pinMode(L1, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(e, INPUT);
  pinMode(t, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(14,HIGH);
  BT.begin(9600);            // 启动软件序列埠
  Serial.begin(9600);
  pinMode(IA, OUTPUT);       // 电机 A 的致能脚位
  pinMode(IB, OUTPUT);       // 电机 B 的致能脚位
  randomSeed(analogRead(5)); // 转向随机种子
  stop();                    // 先停止电机
  digitalWrite(L1, HIGH);
  delay(500);
  digitalWrite(L1, LOW);
  digitalWrite(L1, HIGH);
  delay(500);
  digitalWrite(L1, LOW);
  digitalWrite(L1, HIGH);
  delay(500);
  digitalWrite(L1, LOW);
}
void loop() {
  ping();
  Serial.print("distance:");
  Serial.print(dd);
  Serial.println("cm");
  delay(1000);
  if (dd > 10) {
    if (BT.available() > 0) {
      comm = BT.read();
      digitalWrite(L1, HIGH);
      delay(100);
      digitalWrite(L1, LOW);
      switch (comm) {
        case  'w' :     // 接收到 'w'，前进
          forward();
          light2();
          delay(500);
          low2();
          Serial.println("forward");
          break;
        case  'x' :     // 接收到 'x'，后退
          backward();
          light2();
          delay(500);
          low2();
          Serial.println("backward");
          break;
        case  'a' :     // 接收到 'a'，左转
          turnLeft();
          light2();
          delay(500);
          low2();
          Serial.println("left");
          break;
        case  'd' :     // 接收到 'd'，右转
          turnRight();
          light2();
          delay(500);
          low2();
          Serial.println("right");
          break;
        case  's' :     // 接收到 's'，停止电机
          stop();
          light2();
          delay(500);
          low2();
          Serial.println("stop");
          break;
        case  '1' :     // 接收到 '1'，点亮LED1
          light1();
          Serial.println("light1");
          break;
        case  '2' :     // 接收到 '2'，点亮LED2
          light2();
          Serial.println("light2");
          break;
        case  'c' :     // 接收到 'c'，熄灭LED1
          low1();
          Serial.println("low1");
          break;
        case  'e' :     // 接收到 'c'，熄灭LED2
          low2();
          Serial.println("low2");
          break;
        case  'u' :
          light2();
          delay(500);
          low2();
          break;
      }
    }
  }
  else {
    stop();
    digitalWrite(4, HIGH);
    val = random(2);
    if (val == 0) {
      turnRight();
      //delay(500);
      //stop();
      //以下语句保证在遇到障碍物时，持续右转，直至避开障碍物为止。
      //障碍物定义为离小车10cm距离的目标。
      ping();
      while (dd <= 10)
      {
        turnRight();
        //delay(500);
        //stop();
        ping();
      }
    }
    else {
      turnLeft();
      delay(50);
      //stop();
      //以下语句保证在遇到障碍物时，持续左转，直至避开障碍物为止。
      //障碍物定义为离小车10cm距离的目标。
      ping();
      while (dd <= 10)
      {
        turnLeft();
        delay(50);
        //stop();
        ping();
      }
    }
    digitalWrite(4, LOW);
  }
}
