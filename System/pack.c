/*****************************************************************************************
																					pack.c
															desiged for series port comunication
																			2014-08-28 09:41:16
																					by lunanting
																					
*****************************************************************************************/
#include "module.h"
#include "pack.h"


 volatile u32 count,u1_count=0,value_count,u2_count=0;
 u8 u1rec_i,u1rec_buff[20],u2rec_i,u2rec_buff[20];
 
/**flash操作变量定义***/
#define  STARTADDR  0x0800f000				//存储数据起始地址	对于R8的64k flash来说将会有4k存储空间
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;      //Flash操作状态变量

/***************************************串口*********************************************/
/***辅助函数***/
void usart_send_enter(USART_TypeDef* USARTx)  //发送回车符
{
	usart_send_byte(USARTx,0x0d);
	usart_send_byte(USARTx,0x0a);
}

/***串口通信发送单个数据***/
/*实现步骤
1.清除串口发送完成标志位
2.使用库函数 USART_SendData()发送数据Data
3.等待发送完成标志位置位，置位后清楚标志位，完成发送数据
*/
void usart_send_byte(USART_TypeDef* USARTx, u8 Data)
{
	USART_ClearFlag(USARTx,USART_FLAG_TC);
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
	USART_ClearFlag(USARTx,USART_FLAG_TC);	
}

/***串口通信发送数据包***/
void usart_send_data(USART_TypeDef* USARTx, u8 Data[],int len)
{
	int i;
	for(i=0;i<len;i++)
			usart_send_byte(USARTx,Data[i]);
}

/***串口通信发送字符串***/
void usart_send_str(USART_TypeDef* USARTx,char *s)
{
	int len=strlen(s)-1;
	int i;
	for(i=0;i<len;i++)
		usart_send_byte(USARTx,s[i]);
	if(s[i]=='\0')
		usart_send_enter(USARTx);
	else
	{
		usart_send_byte(USARTx,s[i]);
		usart_send_enter(USARTx);
	}
}

/*********************************************************串口接收程序****************************************/
/***串口接收数据包RS232***/
u8 *usart_rec_data(USART_TypeDef* USARTx,u8 *data,u8 len)
{
	u8 i;
	if(len>19||len==0)
		len=20;
	while(u1_count<100)
		os_dly_wait(1);
	TIM_Cmd(TIM3,DISABLE);
	u1_count=0;
	for(i=0;i<len;i++)
		data[i]=u1rec_buff[i];
	memset(u1rec_buff,0,20);
	u1rec_i=0;
	return data;
}
/***end***/

/***485接收数据包***/
u8 *rt_485(USART_TypeDef* USARTx,u8 *data,u8 len)
{
	u8 i;
	if(len>100||len==0)
		len=100;
	while(u2_count<100)
		os_dly_wait(1);
	TIM_Cmd(TIM4,DISABLE);
	u2_count=0;
	for(i=0;i<len;i++)
		data[i]=u2rec_buff[i];
	memset(u2rec_buff,0,100);
	u2rec_i=0;
	return data;
}

/***end***/

/**************************************************读写片内flash***********************************************/
/***写flash一个字长度***/
void WriteFlashOneWord(uint32_t WriteAddress,uint32_t WriteData)
{
	FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
  FLASHStatus = FLASH_ErasePage(STARTADDR);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress, WriteData);    //flash.c 中API函数
		//FLASHStatus = FLASH_ProgramWord(StartAddress+4, 0x56780000);                      //需要写入更多数据时开启
		//FLASHStatus = FLASH_ProgramWord(StartAddress+8, 0x87650000);                      //需要写入更多数据时开启
	}
	FLASH_LockBank1();
} 
/***end***/

/***读flash多字节长度***/
int ReadFlashNByte(uint32_t ReadAddress, uint8_t *ReadBuf, int32_t ReadNum)
{
	int DataNum = 0;
	ReadAddress = (uint32_t)STARTADDR + ReadAddress; 
	while(DataNum < ReadNum) 
	{
		*(ReadBuf + DataNum) = *(__IO uint8_t*) ReadAddress++;
		DataNum++;
	}
	return DataNum;
}
/***end***/

/********************************SPI通信******************************************/
/***SPI发送/接受 2/单个字节的数据***/
u16 spi_readwrite_byte(SPI_TypeDef* SPIx, u16 Data) 
{
	u8 retry=0;
	u16 recbuff=0;
	
	if(memcmp(SPIx,SPI1,sizeof(SPI_TypeDef))==0)
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	/***后面可加上需要的SPI端口***/
	
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)   //检查指定的SPI发送缓存空标志位
	{
		retry++;
		if(retry>200)
			return 0;
	}
	SPI_I2S_SendData(SPIx,Data);		//发送2byte数据
	retry=0;
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)   //检查指定的SPI接受缓存非空标志位
	{
		retry++;
		if(retry>200)
			return 0;
	}
	recbuff=SPI_I2S_ReceiveData(SPIx);
	if(memcmp(SPIx,SPI1,sizeof(SPI_TypeDef))==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	/***后面可加上需要的SPI端口***/
	
	return recbuff;	//接受2byte数据
}

/***SPI发送/接受数据包***/
void spi_readwrite_data(SPI_TypeDef* SPIx, u16 Data[],int len,u16 recbuff[])
{
	u8 i;
	for(i=0;i<len;i++)
			recbuff[i]=spi_readwrite_byte(SPIx,Data[i]);
}


//end of the file
