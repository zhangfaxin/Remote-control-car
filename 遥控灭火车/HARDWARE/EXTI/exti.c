#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1)	//WK_UP按键 
	{
		LED0=!LED0;
		LED1=!LED1;	
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
//外部中断9~5服务程序
void EXTI9_5_IRQHandler(void)
{			
	delay_ms(10);   //消抖			 
    if(KEY0==0)		//按键0
	{
		LED0=!LED0;
	}
 	EXTI->PR=1<<5;     //清除LINE5上的中断标志位  
}
//外部中断15~10服务程序
void EXTI15_10_IRQHandler(void)
{			
	delay_ms(10);   //消抖			 
    if(KEY1==0)		//按键1
	{
		LED1=!LED1;
	}
 	EXTI->PR=1<<15; //清除LINE15上的中断标志位  
}
//外部中断初始化程序
//初始化PA0,PC5,PA15为中断输入.
void EXTI_Init(void)
{
	KEY_Init();
	Ex_NVIC_Config(GPIO_A,0,RTIR); 		//上升沿触发
	Ex_NVIC_Config(GPIO_C,5,FTIR);		//下降沿触发
	Ex_NVIC_Config(GPIO_A,15,FTIR);		//下降沿触发

	MY_NVIC_Init(2,2,EXTI0_IRQn,2);    	//抢占2，子优先级2，组2
	MY_NVIC_Init(2,1,EXTI9_5_IRQn,2);  	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,0,EXTI15_10_IRQn,2);	//抢占2，子优先级0，组2	   
}












