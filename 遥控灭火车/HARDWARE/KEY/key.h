#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 

#define KEY0_PRES	1		//KEY0按下
#define KEY1_PRES	2		//KEY1按下
#define WKUP_PRES	3		//WK_UP按下
#define G1 PAin(2)  //光电传感器1 A2
#define G2 PAin(3)  //光电传感器2 A3
#define G3 PAin(4)  //光电传感器3 A4
#define G4 PAin(5)  //光电传感器4 A5
#define G5 PAin(6)  //光电传感器5 A6
/*
#define H1  PAin(10) //红外传感器5  A10
#define H2  PAin(14) //红外传感器4  A14
#define H3  PBin(2) //红外传感器3   B0
#define H4  PAin(4) //红外传感器2   A4
#define H5  PAin(2) //红外传感器1   A2
#define SH  PAin(6) //声音传感器1   A6
#define G1  PAin(3) //光电传感器1   A3
#define G2  PAin(5) //光电传感器2   A5
#define G3  PBin(3) //光电传感器3   B3
#define G4  PBin(4) //光电传感器4   B4
#define Y1  PBin(5) //火焰传感器1   B5
#define Y2  PBin(7) //火焰传感器2   B7
#define Y3  PBin(9) //火焰传感器3   B9*/
#define KEY0  PAin(11)   	//PC5
#define KEY1  PAin(12)	 	//PA15 
#define WK_UP PAin(0)	 	//PA0  WK_UP
	 
void KEY_Init(void);		//IO初始化
u8 KEY_Scan(u8 mode);		//按键扫描函数
#endif
