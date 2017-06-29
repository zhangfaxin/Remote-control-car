#include "sys.h"	
#include "usart.h"	
#include "delay.h"	
#include "timer.h"
#include "PORT.h"
#include "function.h"
#include "PID.h"
int Mobile_Con_Flag=0;
float YaotouFlag=0;
void Get_Control();
void Mobile_Con(u8 ch[]);
int main(void)
{     					 
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,19200);	//串口初始化为19200
	delay_init(72);	   	 	//延时初始化 
	init();
 	while(1)
	{
		if(F1||F2||F4||F5||F3)
		{
			JDQ=1;
			while(F1||F2||F4||F5||F3)
			{
				Turn_Fan();
			}
			JDQ=0;
		}
		Servo_PWM=Servo_Mid;
		Get_Control();
	}	  
}
                                                                    
void Get_Control()
{
	u16 t;
	u16 len;	
	u16 times=0;
	if(USART_RX_STA&0x8000)
	{					   
			len=USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				USART3->DR=USART_RX_BUF[t];
				while((USART3->SR&0X40)==0);//等待发送结束
			}
			USART_RX_STA=0;
	}
	Mobile_Con(USART_RX_BUF);	
	if(Mobile_Con_Flag)
	{
		Auto();
	}
}

void Mobile_Con(u8 ch[])
{
	switch(*ch)
		{
		case '1':
			//Run();
			break;
		case '2':
			Up();
			break;
		case '3':
			Stop();
			break;
		case '4':
			Left();
			break;
		case '5':
			Back();
			break;
		case '6':
			Right();
			break;
		case '7':
			Add_speed();  
			break;       
		case '8':
			Cut_speed();
			break;
		case '9':
			Diaotou();
			break;
		case 'C':
			JDQ=1;
		    break;
		case ':':
			Mobile_Con_Flag=1;
		    break;
		case 0X3B:
			Mobile_Con_Flag=0;
			Stop();
		    break;
		defalut:
		    Stop();
			break;
			
		}
}
