#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif
 	  
 	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
	USART3->DR = (u8) ch;      
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////

#if EN_USART3_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  u8 res; 
  u8 Receive,i,j;												  
  u8 receive_flag1,receive_flag2,receive_flag_end;	
	u8 Receive_Cmd[11]={0x55,0xaa,1,1,1,1,1,1,1,1,0x12};   //倒数第二位为校验 
void USART3_IRQHandler(void)
{
u8 res;	
#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	OSIntEnter();    
#endif
	if(USART3->SR&(1<<5))//接收到数据
	{	 
		res=USART3->DR; 
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
			}else //还没收到0X0D
			{	
				if(res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=res;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}  		 									     
	}
#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	OSIntExit();  											 
#endif
} 
#endif										 
//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率
//CHECK OK
//091209
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
//	RCC->APB1ENR&=~(1<<14); 
//	RCC->APB1ENR&=~(1<<21); 
//	RCC->APB1ENR&=~(1<<22); 
	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  //使能串口3时钟 
	GPIOB->CRH&=0XFFFF00FF;//IO状态设置
	GPIOB->CRH|=0X00008B00;//IO状态设置
	RCC->APB1RSTR|=1<<18;   //复位串口3
	RCC->APB1RSTR&=~(1<<18);//停止复位	   	   
	//波特率设置
 	USART3->BRR=mantissa; // 波特率设置	 
	USART3->CR1|=0X200C;  //1位停止,无校验位.
#if EN_USART3_RX		  //如果使能了接收
	//使能接收中断
	USART3->CR1|=1<<8;    //PE中断使能
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART3_IRQn,2);//组2，最低优先级 
#endif
}

//void uart_init(u32 pclk2,u32 bound)
//{  	 
//	float temp;
//	u16 mantissa;
//	u16 fraction;	   
//	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
//	mantissa=temp;				 //得到整数部分
//	fraction=(temp-mantissa)*16; //得到小数部分	 
//    mantissa<<=4;
//	mantissa+=fraction; 
//	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
//	RCC->APB1ENR|=1<<17;  //使能串口2时钟 
//	GPIOA->CRL&=0XFFFF00FF;//IO状态设置
//	GPIOA->CRL|=0X00008B00;//IO状态设置
//		  
//	RCC->APB1RSTR|=1<<17;   //复位串口1
//	RCC->APB1RSTR&=~(1<<17);//停止复位	   	   
//	//波特率设置
// 	USART2->BRR=mantissa; // 波特率设置	 
//	USART2->CR1|=0X200C;  //1位停止,无校验位.
//#if EN_USART2_RX		  //如果使能了接收
//	//使能接收中断
//	USART2->CR1|=1<<8;    //PE中断使能
//	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
//	MY_NVIC_Init(3,3,USART2_IRQn,2);//组2，最低优先级 
//#endif
//}
