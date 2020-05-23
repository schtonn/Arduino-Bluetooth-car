/******************************************************************************
----------------本例程仅供学习使用，未经作者允许，不得用于其他用途。-----------
------------------------版权所有，仿冒必究！-----------------------------------
----------------1.开发环境:Arduino IDE-----------------------------------------
----------------2.测试使用开发板型号：Arduino Leonardo or Arduino UNO R3-------
----------------3.单片机使用晶振：16M------------------------------------------
----------------4.淘宝网址：Ilovemcu.taobao.com--------------------------------
----------------------------epic-mcu.taobao.com--------------------------------
----------------5.作者：神秘藏宝室---------------------------------------------
******************************************************************************/
#include <Arduino.h>
#include <EEPROM.h>

#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 8
#define SEG_H 9
#define Pot A0

#define COM1 10
#define COM2 11
#define COM3 12
#define COM4 13

#define KEY 0
int i = 0;
int a = 0;
unsigned int SUM = 0;
int Flag_up = 1;

unsigned char table[10][8] =
{
	{0,	0,	1,	1,	1,	1,	1,	1},			//0
	{0,	0,	0,	0,	0,	1,	1,	0},			//1
	{0,	1,	0,	1,	1,	0,	1,	1},			//2
	{0,	1,	0,	0,	1,	1,	1,	1},			//3
	{0,	1,	1,	0,	0,	1,	1,	0},			//4
	{0,	1,	1,	0,	1,	1,	0,	1},			//5
	{0,	1,	1,	1,	1,	1,	0,	1},			//6
	{0,	0,	0,	0,	0,	1,	1,	1},			//7
	{0,	1,	1,	1,	1,	1,	1,	1},			//8
	{0,	1,	1,	0,	1,	1,	1,	1}			//9
};

void setup()
{
	pinMode(SEG_A,OUTPUT);		//设置为输出引脚
	pinMode(SEG_B,OUTPUT);
	pinMode(SEG_C,OUTPUT);
	pinMode(SEG_D,OUTPUT);
	pinMode(SEG_E,OUTPUT);
	pinMode(SEG_F,OUTPUT);
	pinMode(SEG_G,OUTPUT);
	pinMode(SEG_H,OUTPUT);

	pinMode(COM1,OUTPUT);
	pinMode(COM2,OUTPUT);
	pinMode(COM3,OUTPUT);
	pinMode(COM4,OUTPUT);

  pinMode(KEY,INPUT_PULLUP);		//按键IO设定为带上拉输入
//  SUM = EEPROM.read(0);
  SUM = EEPROM_read_short(0);
  
  if( !SUM )
    SUM = 0;
}

void loop()
{
  if( ScanKey() == 1)				//当有按键按下时
  {
    SUM++;								//SUM加一
    if(SUM>9999)					//最大值9999，不再累加
    {
      SUM = 0;
    }
    //EEPROM.write(0,SUM);
    //e2_memory.a=SUM;
    EEPROM_write_short(0, SUM);

  }
//  SUM++;
//  delay(500);
  Display(1,SUM/1000);		//显示SUM千位值
  delay(3);
  Display(2,SUM%1000/100);	//显示SUM百位值
  delay(3);
  Display(3,SUM%100/10);		//显示SUM十位值
  delay(3);
  Display(4,SUM%10);				//显示SUM个位值
  delay(3);
}

unsigned char ScanKey()			//按键扫描程序，返回键值
{
  if(Flag_up  && digitalRead(KEY) == LOW)		//当Flag_up = 1并且按键按下时
  {
    Flag_up = 0;										//清空Flag_up
    delay(20);											//延时去抖动
    if(digitalRead(KEY) == LOW)			//按键按下
    {
      return 1;											//返回键值1
    }
  }
  if(digitalRead(KEY) == HIGH)			//按键松开时候
  {
    Flag_up = 1;										//置位Flag_up
  }
  return 0;													//返回键值0
}

void Display(unsigned char com,unsigned char num)
{
	digitalWrite(SEG_A,LOW);			//去除余晖
	digitalWrite(SEG_B,LOW);
	digitalWrite(SEG_C,LOW);
	digitalWrite(SEG_D,LOW);
	digitalWrite(SEG_E,LOW);
	digitalWrite(SEG_F,LOW);
	digitalWrite(SEG_G,LOW);
	digitalWrite(SEG_H,LOW);

	switch(com)						//选通位选
	{
		case 1:
			digitalWrite(COM1,LOW);		//选择位1
			digitalWrite(COM2,HIGH);
			digitalWrite(COM3,HIGH);
			digitalWrite(COM4,HIGH);
			break;
		case 2:
			digitalWrite(COM1,HIGH);
			digitalWrite(COM2,LOW);		//选择位2
			digitalWrite(COM3,HIGH);
			digitalWrite(COM4,HIGH);
			break;
		case 3:
			digitalWrite(COM1,HIGH);
			digitalWrite(COM2,HIGH);
			digitalWrite(COM3,LOW);		//选择位3
			digitalWrite(COM4,HIGH);
			break;
		case 4:
			digitalWrite(COM1,HIGH);
			digitalWrite(COM2,HIGH);
			digitalWrite(COM3,HIGH);
			digitalWrite(COM4,LOW);		//选择位4
			break;
		default:break;
	}

	digitalWrite(SEG_A,table[num][7]);			//a查询码值表
	digitalWrite(SEG_B,table[num][6]);
	digitalWrite(SEG_C,table[num][5]);
	digitalWrite(SEG_D,table[num][4]);
	digitalWrite(SEG_E,table[num][3]);
	digitalWrite(SEG_F,table[num][2]);
	digitalWrite(SEG_G,table[num][1]);
	digitalWrite(SEG_H,table[num][0]);
}

///////////reference page: http://www.51hei.com/arduino/3829.html
// Write an uint value to EEPROM
void EEPROM_write_short(unsigned int Address, unsigned int Data)
{
   unsigned int DataL = Data&0x00FF;
   unsigned int DataH = Data>>8;
   EEPROM.write(Address,   DataL);
   EEPROM.write(Address+1, DataH);
}                      

// Read an uint value from EEPROM
unsigned int EEPROM_read_short(unsigned int Address)
{
   unsigned int DataL = EEPROM.read(Address);
   unsigned int DataH = EEPROM.read(Address+1);
   return((DataH<<8) + DataL);
}

