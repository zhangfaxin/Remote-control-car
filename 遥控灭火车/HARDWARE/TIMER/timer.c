#include "timer.h"
#include "led.h"	 
extern u16 PD2,PD1;
extern u8 tmp_buf[256];
extern float step,step2;
extern u16 D1max,D1min;

void PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    
	RCC->APB2ENR|=1<<2; //?? PORTB ??
  	
	GPIOA->CRL&=0X0FFFFFFF;//PA7���
	GPIOA->CRL|=0XB0000000;//���ù������ 	  
	//GPIOA->ODR|=1<<7;//PA7����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=6<<12;  //CH2 PWM2ģʽ		 
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��	   

	TIM3->CCER|=1<<4;   //OC2 ���ʹ��	   

	TIM3->CR1=0x8000;   //ARPEʹ�� 
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 										  
}  	

void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��    
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	GPIOA->CRH&=0XFFFFFF00;	//PA8\PA9���֮ǰ������
	GPIOA->CRH|=0X000000BB;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM1->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<0;   	//OC1 ���ʹ��
	
	TIM1->CCMR1|=7<<12;  	//CH2 PWM2ģʽ		 
	TIM1->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<4;   	//OC2 ���ʹ��
	
	TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	   

	TIM1->CR1=0x0080;   	//ARPEʹ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 		
  D1=13400;	
	D2=13210;	
} 
void TIM2_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<0; 	//TIM2ʱ��ʹ��    
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	GPIOA->CRL&=0XFFFFFF00;	//PA0\PA1���֮ǰ������
	GPIOA->CRL|=0X000000BB;	//���ù������ 
	
	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ������
  
	TIM2->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM2->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM2->CCER|=1<<0;   	//OC1 ���ʹ��
	
	TIM2->CCMR1|=7<<12;  	//CH2 PWM2ģʽ		 
	TIM2->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��	 
 	TIM2->CCER|=1<<4;   	//OC2 ���ʹ��
	
	TIM2->BDTR|=1<<15;   	//MOE �����ʹ��	   

	TIM2->CR1=0x0080;   	//ARPEʹ�� 
	TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 		
}

 void TIM8_PWM_Init(u16 arr,u16 psc)    //���
{
	RCC->APB2ENR|=1<<13; 	//TIM8ʱ��ʹ��  
  RCC->APB2ENR|=1<<4;   //ʹ��PORTC��ʱ�� 
  RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��   
	GPIOC->CRL&=0X00FFFFFF;	//PC6/PC7���֮ǰ������
	GPIOC->CRL|=0XBB000000;	//���ù������ 
	GPIOC->CRH&=0XFFFFFF00;	//PC8/PC9���֮ǰ������
	GPIOC->CRH|=0X000000BB;	//���ù������ 
  GPIOB->CRL&=0XFFFFFF00;	//PB8/PB9���֮ǰ������
	GPIOB->CRL|=0X000000BB;	//���ù������ 
	
	TIM8->ARR=arr;			//�趨�������Զ���װֵ 
	TIM8->PSC=psc;			//Ԥ��Ƶ������
  
	TIM8->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM8->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM8->CCER|=1<<0;   	//OC1 ���ʹ��
//	TIM8->CCER|=1<<2;   	//OC2 ����ʹ��
	
	TIM8->CCMR1|=7<<12;  	//CH2 PWM2ģʽ		 
	TIM8->CCMR1|=1<<11; 		//CH2Ԥװ��ʹ��	 
 	TIM8->CCER|=1<<4;   	//OC2 ���ʹ�
//	TIM8->CCER|=1<<6;

  TIM8->CCMR2|=7<<4;  	//CH3 PWM2ģʽ		 
	TIM8->CCMR2|=1<<3; 		//CH3Ԥװ��ʹ��	 
 	TIM8->CCER|=1<<8;   	//OC3 ���ʹ��
//	TIM8->CCER|=1<<10;
	
	TIM8->CCMR2|=7<<12;  	//CH4 PWM2ģʽ		 
	TIM8->CCMR2|=1<<11; 		//CH4Ԥװ��ʹ��	 
 	TIM8->CCER|=1<<12;   	//OC4 ���ʹ��
	
	TIM8->BDTR|=1<<15;   	//MOE �����ʹ��	   

	TIM8->CR1=0x0080;   	//ARPEʹ�� 
	TIM8->CR1|=0x01;    	//ʹ�ܶ�ʱ��8 
		M1=0;
		M2=0;
		M3=0;
		M4=0;	
}
void TIM4_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2; 	//TIM8ʱ��ʹ��  
    RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ�� 

	
	GPIOB->CRL&=0X00FFFFFF;	//PC6/PC7���֮ǰ������
	GPIOB->CRL|=0XBB000000;	//���ù������ 
	
	GPIOB->CRH&=0XFFFFFF00;	//PC8/PC9���֮ǰ������
	GPIOB->CRH|=0X000000BB;	//���ù������ 

	
	
	TIM4->ARR=arr;			//�趨�������Զ���װֵ 
	TIM4->PSC=psc;			//Ԥ��Ƶ������
  
	TIM4->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM4->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM4->CCER|=1<<0;   	//OC1 ���ʹ��
//	TIM8->CCER|=1<<2;   	//OC2 ����ʹ��
	
	TIM4->CCMR1|=7<<12;  	//CH2 PWM2ģʽ		 
	TIM4->CCMR1|=1<<11; 		//CH2Ԥװ��ʹ��	 
 	TIM4->CCER|=1<<4;   	//OC2 ���ʹ�
//	TIM8->CCER|=1<<6;

  TIM4->CCMR2|=7<<4;  	//CH3 PWM2ģʽ		 
	TIM4->CCMR2|=1<<3; 		//CH3Ԥװ��ʹ��	 
 	TIM4->CCER|=1<<8;   	//OC3 ���ʹ��
//	TIM8->CCER|=1<<10;
	
	TIM4->CCMR2|=7<<12;  	//CH4 PWM2ģʽ		 
	TIM4->CCMR2|=1<<11; 		//CH4Ԥװ��ʹ��	 
 	TIM4->CCER|=1<<12;   	//OC4 ���ʹ��
	
	TIM4->BDTR|=1<<15;   	//MOE �����ʹ��	   

	TIM4->CR1=0x0080;   	//ARPEʹ�� 
	TIM4->CR1|=0x01;    	//ʹ�ܶ�ʱ��8 
		M1=0;
		M2=0;
		M3=0;
		M4=0;	
}	
//��ʱ��2ͨ��1���벶������
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_Cap_Init(u16 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<0;   	//TIM2 ʱ��ʹ�� 
	RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��  
	 
	GPIOA->CRL&=0XFFFFFFF0;	//PA0 ���֮ǰ����  
	GPIOA->CRL|=0X00000008;	//PA0 ����   
	GPIOA->ODR|=0<<0;		//PA0 ����
	  
 	TIM2->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM2->PSC=psc;  		//Ԥ��Ƶ�� 

	TIM2->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
 	TIM2->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
 	TIM2->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 

	TIM2->CCER|=0<<1; 		//CC1P=0	�����ز���
	TIM2->CCER|=1<<0; 		//CC1E=1 	��������������ֵ������Ĵ�����

	TIM2->DIER|=1<<1;   	//��������ж�				
	TIM2->DIER|=1<<0;   	//��������ж�	
	TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��2
	MY_NVIC_Init(2,0,TIM2_IRQn,2);//��ռ2�������ȼ�0����2	   
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
//[5:0]:����ߵ�ƽ������Ĵ���
u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
//��ʱ��2�жϷ������	 
void TIM2_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM2->SR;
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//����1���������¼�
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			    TIM2CH1_CAPTURE_VAL=TIM2->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM2->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{ 
				TIM2CH1_CAPTURE_VAL=0;
				TIM2CH1_CAPTURE_STA=0X40;		//��ǲ�����������
				TIM2->CNT=0;					//���������
				TIM2->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز��� 
			}		    
		}			     	    					   
 	}
	TIM2->SR=0;//����жϱ�־λ 	    
}




















