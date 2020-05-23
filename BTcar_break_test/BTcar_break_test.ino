//char getstr;
//void setup()
//{
//  Serial.begin(9600);
//}
//void loop()
//{
//  getstr=Serial.read();
//  if(getstr=='h')
//  {
//    Serial.println("I am here!");
//  }
//  else if(getstr=='b'){
//    Serial.println("See you!");
//  }
//}



//#include "I2Cdev.h"
//#include "MPU6050_6Axis_MotionApps20.h"
// 
//MPU6050 mpu; //实例化一个 MPU6050 对象，对象名称为 mpu
//int16_t ax, ay, az, gx, gy, gz;
// 
////********************angle data*********************//
//float Gyro_y; //Y轴陀螺仪数据暂存
//float Gyro_x;
//float Gyro_z;
//float angleAx;
//float angle6;
//float K1 = 0.05; // 对加速度计取值的权重
//float Angle; //一阶互补滤波计算出的小车最终倾斜角度
//float accelz = 0;
// 
////********************angle data*********************//
// 
////***************Kalman_Filter*********************//
//float P[2][2] = {{ 1, 0 },
//  { 0, 1 }
//};
//float Pdot[4] = { 0, 0, 0, 0};
//float Q_angle = 0.001, Q_gyro = 0.005; //角度数据置信度,角速度数据置信度
//float R_angle = 0.5 , C_0 = 1;
//float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//float timeChange = 5; //滤波法采样时间间隔毫秒
//float dt = timeChange * 0.001; //注意：dt的取值为滤波器采样时间
////***************Kalman_Filter*********************//
// 
//void Angletest()
//{
//  //平衡参数
//  Angle = atan2(ay , az) * 57.3;           //角度计算公式
//  Gyro_x = (gx - 128.1) / 131;              //角度转换
//  Kalman_Filter(Angle, Gyro_x);            //卡曼滤波
//  //旋转角度Z轴参数
//  if (gz > 32768) gz -= 65536;              //强制转换2g  1g
//  Gyro_z = -gz / 131;                      //Z轴参数转换
//  accelz = az / 16.4;
// 
//  angleAx = atan2(ax, az) * 180 / PI; //计算与x轴夹角
//  Gyro_y = -gy / 131.00; //计算角速度
//  //一阶互补滤波
//  angle6 = K1 * angleAx + (1 - K1) * (angle6 + Gyro_y * dt);
//}
// 
//////////////////////////kalman/////////////////////////
//float angle, angle_dot;                                //平衡角度值
//void Kalman_Filter(double angle_m, double gyro_m)
//{
//  angle += (gyro_m - q_bias) * dt;
//  angle_err = angle_m - angle;
//  Pdot[0] = Q_angle - P[0][1] - P[1][0];
//  Pdot[1] = - P[1][1];
//  Pdot[2] = - P[1][1];
//  Pdot[3] = Q_gyro;
//  P[0][0] += Pdot[0] * dt;
//  P[0][1] += Pdot[1] * dt;
//  P[1][0] += Pdot[2] * dt;
//  P[1][1] += Pdot[3] * dt;
//  PCt_0 = C_0 * P[0][0];
//  PCt_1 = C_0 * P[1][0];
//  E = R_angle + C_0 * PCt_0;
//  K_0 = PCt_0 / E;
//  K_1 = PCt_1 / E;
//  t_0 = PCt_0;
//  t_1 = C_0 * P[0][1];
//  P[0][0] -= K_0 * t_0;
//  P[0][1] -= K_0 * t_1;
//  P[1][0] -= K_1 * t_0;
//  P[1][1] -= K_1 * t_1;
//  angle += K_0 * angle_err; //角度
//  q_bias += K_1 * angle_err;
//  angle_dot = gyro_m - q_bias; //角速度
//}
// 
// 
//void setup() {
//  Wire.begin();                            //加入 I2C 总线序列
//  Serial.begin(9600);                       //开启串口，设置波特率
//  delay(1000);
//  mpu.initialize();                       //初始化MPU6050
//}
// 
//void loop() {
//  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //IIC获取MPU6050六轴数据 ax ay az gx gy gz  
// 
//  Angletest();                                      //获取angle 角度和卡曼滤波
// 
//  Serial.print(ax);Serial.print(",");
//  Serial.print(ay);Serial.print(",");
//  Serial.print(az);Serial.print("---");
//  Serial.print(angle);Serial.print(",");
//  Serial.print(angle_dot);Serial.print(",");
//  Serial.println(angle6);
//  
//  delay(5);
//}


#include  <SoftwareSerial.h>  //引用BlueTooth库
#include <MsTimer2.h>
SoftwareSerial  BT(12,11);  //设定BlueTooth接收脚,  传送脚
const int intA = 40;  //每 250 ms 做一次 myJobOne
const int intB = 250;  // 每 250 ms 做一次 myJobTwo
int led2 = 52;  // pin 8
int btin1 = 11;
int btin2 = 12;
const int INTERVAL = 1;   // 0.001 秒 = 1ms
char  comm;      //接收BT值
static unsigned int cnt = 0;

void ggyy( ) {
   static unsigned int gy = 0;
   ++gy;
   if(gy > 1000) gy = 0;
   if( gy % intA == 0) myJobOne( );   // gy 除以 intA 的餘數是 0
   if( gy % intB == 0) myJobTwo( );
}
void myJobOne( ) {
    if(BT.available()  >  0){
      comm  =  BT.read();
      Serial.println(comm);
      switch(comm){
        case  'w'  :  //接收到  'w'，前进
          Serial.println("forward");
          myNewJob( );
          break;
        case  'x'  :  //接收到  'x'，后退
          Serial.println("backward");
          myJobTwo( );
          break;
      }
    }

}
  
void setup( ) {
  BT.begin(9600);    //启动BlueTooth
  Serial.begin(9600);
  pinMode(53, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(btin1,INPUT);
  pinMode(btin2,INPUT);
  MsTimer2::set(INTERVAL, ggyy); // INTERVAL ms 
  MsTimer2::start( );
}
  
void loop( ) {
  cntReset();
  Serial.println(cnt);
  delay(100);
}

void cntReset()
{
  ++cnt;
  if(cnt > 1000)
    cnt = 0;  
}

void myNewJob( ){
   static int gy = 0;
   gy = 1- gy;  // toggle 0, 1
   digitalWrite(53, gy);  // pin 13 LED
   delay(cnt);
}

//void myJobOne( ) {
//   static int gy = 0; // 故意與 myJobOne 內gy不同 !
//   gy = 1- gy;  // toggle 0, 1
//   digitalWrite(led1, gy);  // pin 8 LED
////   delay(cnt+500);
//}

void myJobTwo( ) {
   static int gy = 1; // 故意與 myJobOne 內gy不同 !
   gy = 1- gy;  // toggle 0, 1
   digitalWrite(led2, gy);  // pin 8 LED
//   delay(cnt+500);
}







//#include  <SoftwareSerial.h>  //引用BlueTooth库
//#include <MsTimer2.h>
//const int intA = 400;  //每 250 ms 做一次 myJobOne
//const int intB = 250;  // 每 250 ms 做一次 myJobTwo
//int led2 = 52;  // pin 8
//const int INTERVAL = 1;   // 0.001 秒 = 1ms
//  
//void ggyy( ) {
//   static unsigned int gy = 0;
//   ++gy;
//   Serial.println(gy);
//   if(gy > 1000)
//   gy =0;
//   if( gy % intA == 0) myJobOne( );   // gy 除以 intA 的餘數是 0
//   if( gy % intB == 0) myJobTwo( );
//}
//  
//void setup( ) {
//  Serial.begin(9600);
//  pinMode(53, OUTPUT);
//  pinMode(led2, OUTPUT);
//  MsTimer2::set(INTERVAL, ggyy); // INTERVAL ms 
//  MsTimer2::start( );
//}
//  
//void loop( ) {
//  delay(6123);  // 故意
//  MsTimer2::stop( );  delay(3388);  MsTimer2::start( );
//}
//  
//void myJobOne( ) {
//   static int gy = 0;
//   gy = 1- gy;  // toggle 0, 1
//   digitalWrite(53, gy);  // pin 13 LED
//}
//  
//void myJobTwo( ) {
//   static int gy = 1; // 故意與 myJobOne 內gy不同 !
//   gy = 1- gy;  // toggle 0, 1
//   digitalWrite(led2, gy);  // pin 8 LED
//}



//定时器库的 头文件
//#include <MsTimer2.h>
////中断处理函数，改变灯的状态
//void flash()
//{                       
//   static boolean output = HIGH;
//   digitalWrite(53, output);
//   output = !output;
//}
//void flash2()
//{
//  static boolean output2= HIGH;
//  digitalWrite(52, output2);
//  output2=!output2;
//}
//void setup()
//{
//   pinMode(53, OUTPUT); 
//   pinMode(52, OUTPUT);
//   // 中断设置函数，每 500ms 进入一次中断
//   MsTimer2::set(500, flash);
//   //MsTimer2::set(100,flash2);
//   //开始计时
//   MsTimer2::start(); 
//}
//   
//void loop(){}



//动手做14-2：用  Android  手机蓝牙遥控机器人
//详细说明，请参阅第十四章，14-17页。

//#include  <SoftwareSerial.h>  //引用BlueTooth库
//#include  <Metro.h>  //引用Metro库
////SoftwareSerial  BT(12,11);  //设定BlueTooth接收脚,  传送脚
//
//const int blinkPin1 = 52; //定义 LED 引脚13
//const int blinkPin2 = 53; //定义 LED 引脚12
// 
//boolean blink1State = false;   //定义 blink1State 为false状态
//boolean blink2State = false;   //定义 blink2State 为false状态  
// 
//Metro blink1Metro = Metro(1000);   //把 blink1Metro 实例化 Metro 对象 ，并设置间隔时间
//Metro blink2Metro = Metro(700);     //把 blink2Metro 实例化 Metro 对象 ，并设置间隔时间
// 
// 
//void setup(){
//  pinMode(blinkPin1 , OUTPUT);   //设置blinkPin1 为输出模式
//  pinMode(blinkPin2 , OUTPUT);   //设置blinkPin2 为输出模式
//}
// 
// 
//void loop(){
// 
//  if(blink1Metro.check()){  //检查blink1Metro间隔(我的理解是计时器每隔100毫秒就会返回true，就执行以下程序)
//    blink1State = !blink1State;   //反转blink1State的逻辑真或假（false or true）
//    digitalWrite(blinkPin1, blink1State); //数字引脚，设置为blink1State的状态
//  }
// 
// 
//  if(blink2Metro.check()){
//    blink2State = !blink2State;
//    digitalWrite(blinkPin2, blink2State);
//  }
//  
//}




//char  comm;      //接收BT值
//const byte t = 19;   //超声波的脉冲发射脚
//const byte e = 18;   //超声波的信号接收脚
//const byte L1 = 13;  //LED接脚
//const byte IA = 2;   //电机  A  的正反转接脚
//const byte IB = 3;   //电机  A  的正反转接脚
//const byte IC = 4;   //电机  B  的正反转接脚
//const byte ID = 5;   //电机  B  的正反转接脚
//const byte EA = 6;   //电机  A  的speed接脚
//const byte EB = 7;   //电机  B  的speed接脚
//const byte sp = 100;  //speed
//const byte time = 200;  //time
//long dd;      //将超声波的信号接收脚的信号转换为距离（厘米）的变量
//int val;      //左转右转随机数变量
//
//void  stop(){       //停止
//  analogWrite(EA,0);
//  analogWrite(EB,0);
//  digitalWrite(IA,LOW);
//  digitalWrite(IB,  LOW);
//  digitalWrite(IC,  LOW);
//  digitalWrite(ID,  LOW);
//}
//void  forward(){    //前进
//  analogWrite(EA,sp);
//  analogWrite(EB,sp);
//  digitalWrite(IA,  HIGH);
//  digitalWrite(IB,  LOW);
//  digitalWrite(IC,  HIGH);
//  digitalWrite(ID,  LOW);
//  delay(time);
//  stop();
//}
//void  backward(){    //后退
//  analogWrite(EA,sp);
//  analogWrite(EB,sp);
//  digitalWrite(IA,  LOW);
//  digitalWrite(IB,  HIGH);
//  digitalWrite(IC,  LOW);
//  digitalWrite(ID,  HIGH);
//  delay(time);
//  stop();
//}
//void  turnLeft(){    //左转
//  analogWrite(EA,sp);
//  analogWrite(EB,sp);
//  digitalWrite(IA,  HIGH);
//  digitalWrite(IB,  LOW);
//  digitalWrite(IC,  LOW);
//  digitalWrite(ID,  HIGH);
//  delay(time);
//  stop();
//}
//void  turnRight(){    //右转
//  analogWrite(EA,sp);
//  analogWrite(EB,sp);
//  digitalWrite(IA,  LOW);
//  digitalWrite(IB,  HIGH);
//  digitalWrite(IC,  HIGH);
//  digitalWrite(ID,  LOW);
//  delay(time);
//  stop();
//}
//void  ping(){
//  digitalWrite(t,  LOW);  //低高低电平发一个短时间脉冲
//  delayMicroseconds(2);
//  digitalWrite(t,  HIGH);
//  delayMicroseconds(10);
//  digitalWrite(t,  LOW);
//  dd  =  float(  pulseIn(e,  HIGH)  *  17  )  /  1000;  //将回波时间换算成cm
//}
//void  setup(){
//  pinMode(L1,  OUTPUT);
//  pinMode(4,  OUTPUT);
//  pinMode(e,  INPUT);
//  pinMode(t,  OUTPUT);
//  pinMode(8,  OUTPUT);
//  pinMode(9,  OUTPUT);
//  digitalWrite(9,HIGH);
//  pinMode(14,  OUTPUT);
//  digitalWrite(14,HIGH);
//  BT.begin(9600);    //启动BlueTooth
//  Serial.begin(9600);
//  pinMode(IA,  OUTPUT);  //电机  A  的致能脚位
//  pinMode(IB,  OUTPUT);  //电机  A  的致能脚位
//  pinMode(IC,  OUTPUT);  //电机  B  的致能脚位
//  pinMode(ID,  OUTPUT);  //电机  B  的致能脚位
//  randomSeed(analogRead(5));  //转向随机种子
//  stop();      //先停止电机
///*  digitalWrite(L1,  HIGH);
//  delay(500);
//  digitalWrite(L1,  LOW);
//  digitalWrite(L1,  HIGH);
//  delay(500);
//  digitalWrite(L1,  LOW);
//  digitalWrite(L1,  HIGH);
//  delay(500);
//  digitalWrite(L1,  LOW);
//  */
//}
//void  loop(){
//  ping();
//  Serial.print("distance:");
//  Serial.print(dd);
//  Serial.println("cm");
//  delay(100);
//  if(dd  >  10){
//    if(BT.available()  >  0){
//      comm  =  BT.read();
//      Serial.println(comm);
//      digitalWrite(L1,  HIGH);
//      delay(100);
//      digitalWrite(L1,  LOW);
//      switch(comm){
//        case  'w'  :  //接收到  'w'，前进
//          Serial.println("forward");
//          forward();
//          break;
//        case  'x'  :  //接收到  'x'，后退
//          Serial.println("backward");
//          backward();
//          break;
//        case  'a'  :  //接收到  'a'，左转
//          Serial.println("left");
//          turnLeft();
//          break;
//        case  'd'  :    //接收到  'd'，右转
//          Serial.println("right");
//          turnRight();
//          break;
//        case  's'  :    //接收到  's'，停止电机
//          Serial.println("stop");
//          stop();
//          break;
//        case  'u'  :  
//          break;
//      }
//    }
//  }
//  else{
//  stop();
//  val  =  random(2);
//  if(val  ==  0){
//    //以下语句保证在遇到障碍物时，持续右转，直至避开障碍物为止。
//    //障碍物定义为离小车10cm距离的目标。
//    ping();
//    while(dd  <=  10){
//    turnRight();
//    delay(500);
//    stop();
//    ping();
//    }
//  }
//  else{
//    //以下语句保证在遇到障碍物时，持续左转，直至避开障碍物为止。
//    //障碍物定义为离小车10cm距离的目标。
//    ping();
//    while(dd  <=  10){
//    turnLeft();
//    delay(500);
//    stop();
//    ping();
//    }
//  }
//}
//}
