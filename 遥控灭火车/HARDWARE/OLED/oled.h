/*
 * File:        nokia.h
 * Purpose:     Serial Input/Output routines
 *
 */

#ifndef _OLED_H
#define _OLED_H

#include "sys.h"
/********************************************************************/
/*-----------------------------------------------------------------------
LCD_init          : OLED初始化

编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/
//#define u8 uint8_t
//#define u16 uint16_t
extern u8 i_sc[20];
extern float temp;
 extern u8 lanzhou96x64[768];
 void OLED_Init(void);
 void OLED_CLS(void);
 void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);
 void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
 void OLED_P14x16Str(u8 x,u8 y,u8 ch[]);
 void OLED_Print(u8 x, u8 y, u8 ch[]);
 void OLED_PutPixel(u8 x,u8 y);
 void OLED_Rectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 gif);
 void OLED_Set_Pos(u8 x, u8 y);
 void OLED_WrDat(u8 data);
 void Draw_LibLogo(void);
 void Draw_Landzo(void);
 void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 bmp[]);
 void OLED_Fill(u8 dat);
 void Dly_ms(u16 ms);
 void xianshi(float abc,int x,int y);




/********************************************************************/

#endif
