#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
 
 
//通过改变TIM1->CCR1的值来改变占空比，从而控制LED0的亮度
#define D1 TIM1->CCR1
#define D2 TIM1->CCR2

//#define M1 TIM8->CCR1
//#define M2 TIM8->CCR2
//#define M3 TIM8->CCR3
//#define M4 TIM8->CCR4

#define M1 TIM4->CCR1
#define M2 TIM4->CCR2
#define M3 TIM4->CCR3
#define M4 TIM4->CCR4

#define Servo_PWM TIM3->CCR2
extern void PWM_Init(u16 arr,u16 psc) ;
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM2_Cap_Init(u16 arr,u16 psc);
void TIM8_PWM_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
#endif























