#include "24l01.h"
#include "delay.h"
//#include "spi.h"

 
#define uint8_t u8	 

const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址


//u8 TX_ADDRESS[5]  = {0x34,0x43,0x10,0x10,0x01};  //数据通道0的40位地址，任意定，只要发射和接收一致即可
u8 CurrentData;
u8 Rx[9];
/******************************延时函数，晶振为12MHz********************************/
//void Delay1us(int i)
//{
//	while(i--);
//}

//void Delay1ms(int ms)
//{
//	u32 i,j,k;
//	for(i=0;i< ms;i++)
//		for(j=0;j<73;j++)
//			for(k=0;k<3;k++)
//			;
//}
/**********************************************************************************/
void init_io(void)
{
	NRF24L01_CE=0;
	NRF24L01_CSN=1;
	NRF24L01_SCK=0;
}
/************************************SPI******************************************/
/*写一字节到nrf24L01*/
void SPI_RW(u8 byte)
{
  u8 k;
	for(k=0;k<8;k++)
	{     
		NRF24L01_SCK=0;               // _|~
		if(byte&0x80)
		NRF24L01_MOSI=1;
		else 
		NRF24L01_MOSI=0;
		delay_us(2);
		NRF24L01_SCK=1;               // ~|_
		byte<<=1;  		    	 
	}
	NRF24L01_SCK=0; 
	NRF24L01_MOSI=0;
}
/*从nrf24L01中读一字节*/
u8 SPI_RD()
{
	u8 k,ibuf;
	for(k=0;k<8;k++)
	{  
		 ibuf<<=1;
		 NRF24L01_SCK=1;
		 if(NRF24L01_MISO)
		 ibuf |=0x01;
		 else
		 ibuf &=0xfe;		
		 NRF24L01_SCK=0;
	}
	return ibuf; 
}

/*写数据到寄存器,并返回寄存器读回的数据*/
u8 NRF24L01_Write_Reg(u8 reg, u8 value)		 //unsigned char
{
	NRF24L01_CSN=0;                 
  	SPI_RW(reg);                           // select register  选择寄存器，即写寄存器的地址
  	SPI_RW(value);                         // ..and write value to it..
	NRF24L01_CSN=1;                  
  	return(0);                       // return nRF24L01 status byte   ？？？明显无效嘛
}
/*读取寄存器中的数据*/
u8 NRF24L01_Read_Reg(u8 reg)
{
	uint8_t reg_val;
	NRF24L01_CSN=0;                
  	SPI_RW(reg);                        // Select register to read from..  选择你想要读的寄存器
  	reg_val = SPI_RD();                 // ..then read registervalue
	NRF24L01_CSN=1;                  
  	return(reg_val);                   // return register value
}
/*读取读取寄存器reg的值，并存在pBuf缓冲区--数组中*/
u8 NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 bytes)		  
{
	uint8_t byte_ctr;

	NRF24L01_CSN=0;
  	SPI_RW(reg);       		                     // Select register to write to 

  	for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    pBuf[byte_ctr] = SPI_RD();                 // Perform SPI_RW to read byte from nRF24L01
	NRF24L01_CSN=1;

  	return(0);                                 
}
/*把数组中的数据写到寄存器reg中*/
u8 NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes)
{
	uint8_t byte_ctr;
	NRF24L01_CSN=0;

  	SPI_RW(reg);    								// Select register to write to 
  	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) 	// then write all byte in buffer(*pBuf)
    SPI_RW(pBuf[byte_ctr]);
	NRF24L01_CSN=1;;
  	return(0);          							// return nRF24L01 status byte
}
/************************************SPI_end******************************************/

							    
//初始化24L01的IO口
void NRF24L01_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
	RCC->APB2ENR|=1<<4;    //使能PORTC口时钟 
	GPIOA->CRL&=0X000000FF;//PA4输出
	GPIOA->CRL|=0X38333300; 
	GPIOA->ODR|=7<<2;	   //PA2.3.4 输出1		 
	GPIOC->CRL&=0XFF00FFFF;//PC4输出 PC5输出
	GPIOC->CRL|=0X00830000; 
	GPIOC->ODR|=3<<4;	   //上拉	 
	//SPIx_Init();    //初始化SPI
	NRF24L01_CE=0; 	//使能24L01
	NRF24L01_CSN=1;	//SPI片选取消		  		 		  
}
//检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	//SPIx_SetSpeed(SPI_SPEED_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   	 
	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}	 	 
		   
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
// 	SPIx_SetSpeed(SPI_SPEED_8);//spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	NRF24L01_CE=0;
  NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	NRF24L01_CE=1;//启动发送	   
	while(NRF24L01_IRQ!=0);//等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
//	SPIx_SetSpeed(SPI_SPEED_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
	NRF24L01_Write_Reg(WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}					    
//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void RX_Mode(void)
{
	NRF24L01_CE=0;	  
  	NRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	  
  	NRF24L01_Write_Reg(WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答    
  	NRF24L01_Write_Reg(WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址  	 
  	NRF24L01_Write_Reg(WRITE_REG+RF_CH,40);	     //设置RF通信频率		  
  	NRF24L01_Write_Reg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
  	NRF24L01_Write_Reg(WRITE_REG+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg(WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  	NRF24L01_CE = 1; //CE为高,进入接收模式 
}						 
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
  	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
  	NRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

  	NRF24L01_Write_Reg(WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
  	NRF24L01_Write_Reg(WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
  	NRF24L01_Write_Reg(WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
  	NRF24L01_Write_Reg(WRITE_REG+RF_CH,40);       //设置RF通道为40
  	NRF24L01_Write_Reg(WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE=1;//CE为高,10us后启动发送
}		  




