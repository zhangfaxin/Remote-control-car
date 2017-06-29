#include "sys.h"	
#include "delay.h"	
#include "timer.h"
#include "oled.h"
#include "PORT.h"
#include "function.h"
#include "PID.h"
int ModeFlag=0;//1 2 3 4�ֱ��Ӧ1 2 3 4 �ŷ�
 int Find_Flag;
void init()
{
	JDQ_Init();

	MiddleS_Init();//PB9

	LeftUpS_Init(); //PB8
	RightUpS_Init();//PB7
	LeftS_Init();//PB6
	RightS_Init();//PB5

    MotorInit();
	Servo_Init();
	G_Init();
	K_Init();
	Stop();
}

void Servo_Init()
{
	PWM_Init(199,7199);	//100Khz�ļ���Ƶ�ʣ�������2000Ϊ20ms
	Servo_PWM=Servo_Mid;	
}
void BackStart()//�������
{
   
}
void FindFire() //���ֻ�Դ
{
    Find_Flag=1;//���ֻ�Դ
	
}
void MotorInit()
{
	TIM4_PWM_Init(1999,7);//2000Hz ���PC6 PC7 PC8 PC9
}