#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
 	   

//LED端口定义
#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	
#define JD  PCout(15) //继电器   C15
void LED_Init(void);	//初始化		 				    
#endif

















