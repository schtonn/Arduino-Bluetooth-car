//作者:Alexander xiang
//创建于2017/2/24
//循迹智能小车
const byte IA = 2;                                   //左电机
const byte IB = 3;                                   //左电机
const byte IC = 4;                                   //右电机
const byte ID = 5;                                   //右电机
const byte E = 6;                                    //超声波
const byte T = 7;                                    //超声波
const byte sensorl = 8;                              //循迹模块
const byte sensorr = 9;                              //循迹模块
const byte error = 11;                               //蜂鸣器
int SL;                                              //循迹参数
int SR;                                              //循迹参数
int val;
long a;                                              //超声波参数

void stop() {                                        // 电机停止
  digitalWrite(IA, LOW);
  digitalWrite(IB, LOW);
  digitalWrite(IC, LOW);
  digitalWrite(ID, LOW);
}
void forward() {                                     // 电机转向：前进
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(100);                                        //设定转方向的幅度--时间
}
void backward() {                                    // 电机转向：后退
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, LOW);
  digitalWrite(ID, HIGH);
  delay(100);                                        //设定转方向的幅度--时间
}
void turnLeft() {                                    // 电机转向：左转
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(100);                                        //设定转方向的幅度--时间
}
void turnRight() {                                   // 电机转向：左转
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(100);                                        //设定转方向的幅度--时间
}
void ping() {
  digitalWrite(T, LOW);                              //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(T, HIGH);
  delayMicroseconds(10);
  digitalWrite(T, LOW);
  a = float( pulseIn(E, HIGH) * 17 ) / 1000;         //将回波时间换算成cm
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IA, OUTPUT);                               //使能左电机
  pinMode(IB, OUTPUT);                               //使能左电机
  pinMode(IC, OUTPUT);                               //使能右电机
  pinMode(ID, OUTPUT);                               //使能右电机
  pinMode(E, INPUT);                                 //使能超声波
  pinMode(T, OUTPUT);                                //使能超声波
  pinMode(sensorl, INPUT);                           //使能循迹模块
  pinMode(sensorr, INPUT);                           //使能循迹模块
  pinMode(error, OUTPUT);
  randomSeed(analogRead(5));                         //转向随机种子
  Serial.println("ready");
  digitalWrite(error, HIGH);                         //提示准备完毕
  delay(1500);
  digitalWrite(error, LOW);
  delay(500);
  digitalWrite(error, HIGH);
  delay(100);
  digitalWrite(error, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  ping();                                            //超声波测距
  Serial.print(a);
  Serial.println(' ');
  if (a < 15) {                                      //如果10厘米内有障碍物
    digitalWrite(error, HIGH);                       //提示
    delay(100);
    digitalWrite(error, LOW);
    delay(150);
    Serial.println("too close");
    val = random(2);
    if (val == 0) {
      turnRight();
      //delay(500);
      //stop();
      //以下语句保证在遇到障碍物时，持续右转，直至避开障碍物为止。
      //障碍物定义为离小车10cm距离的目标。
      ping();
      while (a <= 15)
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
      while (a <= 15)
      {
        turnLeft();
        delay(50);
        //stop();
        ping();
      }
    }
    //    stop();                                          //停止
    //    digitalWrite(error, HIGH);                       //提示
    //    delay(100);
    //    digitalWrite(error, LOW);
    //    delay(150);
    //    Serial.println("too close");
  }
  else {                                             //如果10厘米内没有障碍物
    forward();
    //    SL = digitalRead(sensorl);
    //    SR = digitalRead(sensorr);
    //    if (SL == HIGH && SR == HIGH) {                  //如果两边都白
    //      forward();                                     //直行
    //      stop();
    //      Serial.println("forward");
    //    }
    //    else {
    //      if (SL == LOW && SR == HIGH) {                 //如果左黑右白
    //        turnLeft();                                  //左转
    //        stop();
    //        Serial.println("turnleft");
    //      }
    //      else if (SL == HIGH && SR == LOW) {            //如果左白右黑
    //        turnRight();                                 //右转
    //        stop();
    //        Serial.println("turnright");
    //      }
    //      else {                                         //如果以上情况都不是
    //        stop();                                      //停止
    //        Serial.println("a>10, sl = low, sr = low.");
    //        digitalWrite(error, HIGH);                   //提示故障
    //        delay(1000);
    //        digitalWrite(error, LOW);
    //        delay(1000);
    //      }
    //    }
  }
}
