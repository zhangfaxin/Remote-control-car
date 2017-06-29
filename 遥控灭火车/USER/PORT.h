#ifndef __PORT_H
#define __PORT_H	  
#include <stm32f10x.h> 
#include <sys.h> 


#define BEEP PCout(4)	// BEEP,蜂鸣器接PC4
#define JDQ PCout(7)	// 继电器接PC5

#define MiddleS  PBin(5)//5号激光头
#define BackS1 PCin(12)//1号激光头
#define RightUpS PBin(4)//2号激光头
#define LeftS  PCin(10)//3号激光头
#define RightS  PCin(11)//4号激光头
#define LeftUpS PBin(0)
#define F1 PBin(12)
#define F2 PBin(13)
#define F3 PBin(14)
#define F4 PBin(15)
#define F5 PCin(6)
#define F6 PAin(5)

#define BackS PBin(1)
#define Start PBin(10)

#define G2   PAin(4)
#define G3   PAin(3)
extern void Right90();
extern void Left90();
extern void Turn_Fan();
extern void G_Init();
extern void K_Init();
extern void JDQ_Init(void);
extern void MiddleS_Init();
extern void BEEP_Init(void);
extern void LeftUpS_Init(void); //PB11
extern void RightUpS_Init(void);//PB10
extern void LeftS_Init(void);//PB1
extern void RightS_Init(void);//PB0
#endif
