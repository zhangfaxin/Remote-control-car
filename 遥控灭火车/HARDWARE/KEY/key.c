#include "key.h"
#include "delay.h"
	 
 	    
//按键初始化函数 
//PA0.15和PC5 设置成输入
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	RCC->APB2ENR|=1<<3;	   //使能PORTB时钟
	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	JTAG_Set(SWD_ENABLE);	//关闭JTAG,开启SWD
//	GPIOA->CRL&=0XFFFFFFF0;	//PA0设置成输入	  
//	GPIOA->CRL|=0X00000008;   
	GPIOA->CRH&=0XFFF00FFF;	//PA11 PA12设置成输入	  
	GPIOA->CRH|=0X00088000; 			 
	GPIOA->ODR|=3<<11;	   	//PA11上拉,PA12上拉
	//A10\A14\B0\B2\B4\A0\A1\A2\A3\A4
	GPIOA->CRH&=0XFFFFF0FF;		
	GPIOA->CRH|=0X00000800;//PA10 上拉输入
	GPIOA->ODR|=8<<3;    //PA10 输出高
	GPIOA->CRH&=0XF0FFFFFF;		
	GPIOA->CRH|=0X08000000;//PA14 上拉输入
	GPIOA->ODR|=255<<6;    //PA14 输出高
  GPIOA->CRL&=0XFFF00000;		
	GPIOA->CRL|=0X00088888;//PA0 PA1 PA2 PA3 PA4 上拉输入
	GPIOA->ODR|=31<<0;    //PA0 PA1 PA2 PA3 PA4 输出高
	GPIOB->CRL&=0X0F000000;		
	GPIOB->CRL|=0X80888888;//PB0 PB2  PB4 PB3 PB5 PB7 上拉输入
	GPIOB->ODR|=189<<0;     //PB0 PB2 PB4 PB3 PB5  PB7 输出高
	
	GPIOB->CRH&=0XFFFFFF0F;		
	GPIOB->CRH|=0X00000080;//PB9 上拉输入
	GPIOB->ODR|=4<<2;     //PB9 输出高
	GPIOA->CRL&=0XF0FFFFFF;		
	GPIOA->CRL|=0X08000000;//PA6 上拉输入
	GPIOA->ODR|=64<<6;    //PA6 输出高	
	GPIOA->CRL&=0XFFFF0F00;		
	GPIOA->CRL|=0X00008088;//PA6 PA0 PA1 上拉输入
	GPIOA->ODR|=11<<0;    //PA6 PA0 PA1 输出高	
	GPIOA->CRL&=0XFF0FFFFF;		
	GPIOA->CRL|=0X00800000;//PA6 上拉输入
	GPIOA->ODR|=1<<6;    //PA6 输出高		
	GPIOB->CRL&=0XFFF00000;		
	GPIOB->CRL|=0X00088888;//PB0 PB1 PB2 PB3 PB4上拉输入
	GPIOB->ODR|=31<<0;     //PB0 PB1 PB2 PB3 PB4 输出高
	GPIOC->CRH&=0X0FFFFFFF;		
	GPIOC->CRH|=0X80000000;//PB9 上拉输入
	GPIOC->ODR|=1<<15;     //PB9 输出高
	GPIOB->ODR|=3<<0;
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// 无按键按下
}




















