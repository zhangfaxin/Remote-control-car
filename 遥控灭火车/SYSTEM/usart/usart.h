#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
extern   u8 receive_flag1,receive_flag2,receive_flag_end;
extern 	u8 Receive_Cmd[11];   //�����ڶ�λΪУ��
extern u8 res; 	  	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	 

void uart_init(u32 pclk2,u32 bound);

#endif	  













