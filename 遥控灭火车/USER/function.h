#ifndef _FUNCTION_H
#define _FUNCTION_H
#include "sys.h"	
#include "delay.h"	
#include "timer.h"
#include "PORT.h"
#include "function.h"
#define Servo_Mid  16
#define Servo_Left 24
#define Servo_Right 7
extern void init();
extern void MotorInit();

extern void Search();//寻路

extern void Find_L();
extern void Servo_Init();
extern void FindFire();//发现火源
#endif