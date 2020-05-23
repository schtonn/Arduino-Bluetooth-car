/*作者:Alexander xiang
  创建于2017/2/24
  红外循迹+超声波避障智能小车*/
const byte IA = 2;                                   //左电机
const byte IB = 3;                                   //左电机
const byte IC = 4;                                   //右电机
const byte ID = 5;                                   //右电机
const byte ENA = 6;                                  //左电机
const byte ENB = 7;                                  //右电机
const byte USPinE = 18;                              //超声波
const byte USPinT = 19;                              //超声波
const byte sensorl = 8;                              //循迹模块
const byte sensorr = 9;                              //循迹模块
const byte error = 11;                               //蜂鸣器
int SL;                                              //循迹参数
int SR;                                              //循迹参数
static int USDST;                                    //超声波参数
bool inter_L = false;
bool inter_R = false;
bool inter_F = false;
bool inter_S = false;
bool inter_B = false;

void stop() {                                        // 电机停止
  digitalWrite(IA, LOW);
  digitalWrite(IB, LOW);
  digitalWrite(IC, LOW);
  digitalWrite(ID, LOW);
}
void forward() {                                     // 电机转向：前进
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IA, HIGH);
  digitalWrite(IB, LOW);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(100);                                        //设定转方向的幅度--时间
}
void backward() {                                    // 电机转向：后退
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, LOW);
  digitalWrite(ID, HIGH);
  delay(100);                                        //设定转方向的幅度--时间
}
void turnLeft() {                                    // 电机转向：左转
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(100);                                        //设定转方向的幅度--时间
}
void turnRight() {                                   // 电机转向：左转
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IA, LOW);
  digitalWrite(IB, HIGH);
  digitalWrite(IC, HIGH);
  digitalWrite(ID, LOW);
  delay(100);                                        //设定转方向的幅度--时间
}
void ping() {
  digitalWrite(USPinT, LOW);                         //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(USPinT, HIGH);
  delayMicroseconds(10);
  digitalWrite(USPinT, LOW);
  USDST = float( pulseIn(USPinE, HIGH) * 17 ) / 1000;//将回波时间换算成cm
}

//中位值滤波算法
#define FILTER_NUM 11
int filter_buf[FILTER_NUM] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
static int filterred = 0;
int filter(long USdistance)
{
  int Inside_filter_buf[FILTER_NUM];
  int i, j;
  int filter_temp;
  if (filterred == FILTER_NUM)
    filterred = 0;
  filter_buf[filterred++] = USdistance;
  for (i = 0; i < FILTER_NUM; i++)
    Inside_filter_buf[i] = filter_buf[i];
  for (j = 0; j < FILTER_NUM - 1; j++)
    for (i = 0; i < FILTER_NUM - j - 1; i++)
    {
      if (Inside_filter_buf[i] > Inside_filter_buf[i + 1])
      {
        filter_temp = Inside_filter_buf[i];
        Inside_filter_buf[i] = Inside_filter_buf[i + 1];
        Inside_filter_buf[i + 1] = filter_temp;
      }
    }
  return Inside_filter_buf[(FILTER_NUM - 1) / 2];
}

volatile int curDST = 0;

void printUSmsg() {

  //  Serial.print(USDST);
  //  Serial.println(' ');
  //  delay(100);
  volatile int filterredUSDST = filter(USDST);
  curDST = filterredUSDST;

  if (filterredUSDST < 20) {                         //如果20厘米内有障碍物
    //    stop();
    inter_S = false;
    inter_L = false;
    inter_R = false;
    inter_F = false;
    inter_B = true;
    //    digitalWrite(error, HIGH);
    //    delay(100);
    //    digitalWrite(error, LOW);
    //    delay(150);
    Serial.println("too close");
  }

  else {                                             //如果10厘米内没有障碍物
    SL = digitalRead(sensorl);
    SR = digitalRead(sensorr);
    if (SL == LOW && SR == LOW) {                    //如果两边都白
      //      forward();
      inter_S = false;
      inter_L = false;
      inter_R = false;
      inter_F = true;
      inter_B = false;
      //      stop();
      Serial.println("forward");
    }
    else {
      if (SL == HIGH && SR == LOW) {                 //如果左黑右白
        //        turnLeft();
        inter_S = false;
        inter_L = true;
        inter_R = false;
        inter_F = false;
        inter_B = false;
        //        stop();
        Serial.println("turnleft");
      }
      else if (SL == LOW && SR == HIGH) {            //如果左白右黑
        //        turnRight();
        inter_S = false;
        inter_L = false;
        inter_R = true;
        inter_F = false;
        inter_B = false;
        //        stop();
        Serial.println("turnright");
      }
      else {                                         //如果以上情况都不是
        //        stop();止
        inter_S = true;
        inter_L = false;
        inter_R = false;
        inter_F = false;
        inter_B = false;
        Serial.println("a>10, sl = high, sr = high.");
        digitalWrite(error, HIGH);                   //提示故障
        delay(1000);
        digitalWrite(error, LOW);
        delay(1000);
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IA, OUTPUT);                               //使能左电机
  pinMode(IB, OUTPUT);                               //使能左电机
  pinMode(IC, OUTPUT);                               //使能右电机
  pinMode(ID, OUTPUT);                               //使能右电机
  pinMode(USPinT, OUTPUT);                           //使能超声波
  pinMode(USPinE, INPUT);                            //使能超声波
  pinMode(sensorl, INPUT);                           //使能循迹模块
  pinMode(sensorr, INPUT);                           //使能循迹模块
  pinMode(error, OUTPUT);                            //使能蜂鸣器
  Serial.println("ready");                           //提示准备完毕
  digitalWrite(error, HIGH);
  delay(1500);
  digitalWrite(error, LOW);
  delay(500);
  digitalWrite(error, HIGH);
  delay(100);
  digitalWrite(error, LOW);
  attachInterrupt(5, printUSmsg, FALLING);           //设置中断
}
//int numm = 0;
void loop() {
  // put your main code here, to run repeatedly:
  ping();                                            //超声波测距
  //  delay(50);

  int filterredUSDST = filter(USDST);

  Serial.print(curDST);
  Serial.print("**");
  Serial.print(USDST);
  Serial.println(' ');

  if (inter_S){
    stop();
  }else if (inter_F){
    forward();
    stop();
  }else if (inter_B){
    backward();
    stop();
  }else if (inter_L){
    turnLeft();
    stop();
  }else if (inter_R){
    turnRight();
    stop();
  }else{
    stop();
  }
}
