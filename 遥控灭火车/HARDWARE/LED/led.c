#include "sys.h"   
#include "led.h"
	   

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	
  RCC->APB2ENR|=1<<3;	   //使能PORTB时钟
	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 推挽输出   	 
  GPIOA->ODR|=1<<8;      //PA8 输出高
	      //A12\A14\B0\B2\B4\A0\A1\A2\A3\A4
  GPIOC->CRH&=0X0FFFFFFF;
	GPIOC->CRH|=0X30000000;//PC.15推挽输出
	GPIOC->ODR|=1<<15;      //PC.15输出高 

	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2推挽输出
	GPIOD->ODR|=1<<2;      //PD.2输出高 
}






