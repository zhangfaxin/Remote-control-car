#include "sys.h"	
#include "delay.h"	
#include "timer.h"
#include "oled.h"
#include "PORT.h"
#include "function.h"
#include "PID.h"
#define Fan_Time 300
#define Time1 350
int Speed=1200;
extern float YaotouFlag;
void Up()
{
	M2=0;M1=Speed;
	M4=0;M3=Speed;
}

void Back()//调头
{
	M2=Speed;M1=0;
	M3=0;M4=Speed;
}

void Stop()
{
	M2=0;M1=0;
	M4=0;M3=0;
	JDQ=0;
	YaotouFlag=0;
}

void Left()
{
	M2=0;M1=Speed;
	M3=0;M4=Speed;
}
void LeftM()
{
	M2=0;M1=2000;
	M4=2000;M3=0;
}
void Right()
{
	M2=Speed;M1=0;
	M3=Speed;M4=0;
}

void Add_speed()
{
	Speed+=200;
}

void Cut_speed()
{
	Speed-=200;
}

void Diaotou()
{
	M2=Speed;M1=0;
	M3=Speed;M4=0;
	delay_ms(Time1);
	Stop();
}
void Turn_Fan()
{
	int s=0,n,PWM;
	s=F1+F2+F4+F5;
	n=2*F5+F4-F2-2*F1;
	PWM=n/s;
	PWM=Servo_Mid+PWM*(Servo_Right-Servo_Mid)/2;
	Servo_PWM=PWM;
}	
void Auto()   //自动模式
{
	        if(!MiddleS)
			{
				LeftM();
			}
			else if(!RightUpS)
			{
				Left();
			}
	
			else if(!RightS)
			{
				Up();
			}
			else if(RightS)
			{
				M2=0;M1=0;           //00 00
				M3=2000;M4=0;
			}
}