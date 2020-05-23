// 动手做14-2：用 Android 手机蓝牙遥控机器人
// 详细说明，请参阅第十四章，14-17页。

const byte L1 = 13;             // 电机 A 的致能接脚，控制速度
const byte IA = 5;             // 电机 A 的正反转接脚
const byte IB = 7;             // 电机 A 的正反转接脚
//const byte EB = 4;             // 电机 B 的致能接脚，控制速度
const byte IC = 11;             // 电机 B 的正反转接脚
const byte ID = 10;            // 电机 B 的正反转接脚

const int SensorLeft = 12;      //左感測器輸入腳
const int SensorRight = 13;     //右感測器輸入腳

int SL;    //左感測器狀態
int SR;    //右感測器狀態

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
//  analogWrite(EA, speed);    // 电机 A 的 PWM 输出
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
//  analogWrite(EB, speed);    // 电机 B 的 PWM 输出
  digitalWrite(IC, LOW);     // 电机 B 反转
  digitalWrite(ID, HIGH);
  delay(200);//设定转方向的幅度--时间
  stop();
}
void setup() {
  pinMode(IA, OUTPUT);       // 电机 A 的致能脚位
  pinMode(IB, OUTPUT);
  pinMode(IC, OUTPUT);
  pinMode(ID, OUTPUT);
  stop();                    // 先停止电机
}
void loop() {
 SL = digitalRead(SensorLeft);
 // SM = digitalRead(SensorMiddle);
 SR = digitalRead(SensorRight);
       if (SL == LOW&&SR==LOW)//
   { 
             forward();
         }      
       
       else // 
      {  
         if (SL == HIGH & SR == LOW)// 左黑右白, 快速左轉 
        {  
          turnLeft();
          delay(500);
          stop();
        }
         else if (SR == HIGH & SL == LOW) // 左白右黑, 快速右轉
        {  
          turnRight();
          delay(500);
          stop();
        }
         else // 都是白色, 停止
        {
          stop();    
        }}}


