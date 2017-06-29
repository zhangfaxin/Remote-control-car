#include "PORT.h"
#include <stm32f10x.h> 
void BEEP_Init(void)
{
	RCC->APB2ENR|=1<<4;    	//ʹ��PORTCʱ��	   	  
	GPIOC->CRL&=0XFFF0FFFF; 
	GPIOC->CRL|=0X00030000;	//PC.4 �������   
	GPIOC->ODR|=1<<4;      //PC4 �����	
	BEEP=1;					//�رշ��������
}
void JDQ_Init(void)
{
	RCC->APB2ENR|=1<<4;    	//ʹ��PORTCʱ��	   	  
	GPIOC->CRL&=0X0FFFFFFF; 
	GPIOC->CRL|=0X30000000;	//PC.4 �������   
	GPIOC->ODR|=1<<7;      //PC4 �����	
	JDQ=0;	
	
	GPIOC->CRH&=0XFFFFFFF0; 
	GPIOC->CRH|=0X00000003;	//PC.4 �������   
	PCout(8)=0;	
}

void G_Init()
{
	RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��	   	  
	
	GPIOA->CRL&=0XFF000FFF; 
	GPIOA->CRL|=0X00888000;	
}

void Fire_Init()
{
	RCC->APB2ENR|=1<<4;    	//ʹ��PORTCʱ��
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTCʱ��
	
	GPIOB->CRH&=0X00000FFF; 
	GPIOB->CRH|=0X88888000;
	
	GPIOC->CRL&=0X00FFFFF0; 
	GPIOC->CRL|=0X88000008;
	
}
	
void MiddleS_Init()//PB5
{
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��	   	  
	GPIOB->CRL&=0XFF0FFF0F; 
	GPIOB->CRL|=0X00800080;	 
}	


void LeftUpS_Init(void) //PB3
{
	RCC->APB2ENR|=1<<4;    	//ʹ��PORTCʱ��	   	  
	GPIOC->CRH&=0XFFFFF0FF; 
	GPIOC->CRH|=0X00000800;	    
}

void RightUpS_Init(void)//PB4
{
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTCʱ��	   	  
	GPIOB->CRL&=0XFFF0FFFF; 
	GPIOB->CRL|=0X00080000;       
}
void K_Init()
{
	RCC->APB2ENR|=1<<2;    	//ʹ��PORTCʱ��
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTCʱ��
	GPIOA->CRL&=0XF00FFFFF; 
	GPIOA->CRL|=0X08800000;
	
	GPIOB->CRL&=0XFFFFFFF0; 
	GPIOB->CRL|=0X00000008;
	
	GPIOB->CRH&=0XFFFFF0FF; 
	GPIOB->CRH|=0X00000800;
}
void LeftS_Init(void)//PC11
{
	RCC->APB2ENR|=1<<4;    	//ʹ��PORTCʱ��	   	  
	GPIOC->CRH&=0XFFFF0FFF; 
	GPIOC->CRH|=0X00008000;       	
}

void RightS_Init(void)//PC12
{
	RCC->APB2ENR|=1<<4;    	//ʹ��PORTCʱ��	   	  
	GPIOB->CRH&=0XFFF0FFFF; 
	GPIOB->CRH|=0X00080000; 
}