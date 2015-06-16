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
 
/**flash������������***/
#define  STARTADDR  0x0800f000				//�洢������ʼ��ַ	����R8��64k flash��˵������4k�洢�ռ�
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;      //Flash����״̬����

/***************************************����*********************************************/
/***��������***/
void usart_send_enter(USART_TypeDef* USARTx)  //���ͻس���
{
	usart_send_byte(USARTx,0x0d);
	usart_send_byte(USARTx,0x0a);
}

/***����ͨ�ŷ��͵�������***/
/*ʵ�ֲ���
1.������ڷ�����ɱ�־λ
2.ʹ�ÿ⺯�� USART_SendData()��������Data
3.�ȴ�������ɱ�־λ��λ����λ�������־λ����ɷ�������
*/
void usart_send_byte(USART_TypeDef* USARTx, u8 Data)
{
	USART_ClearFlag(USARTx,USART_FLAG_TC);
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
	USART_ClearFlag(USARTx,USART_FLAG_TC);	
}

/***����ͨ�ŷ������ݰ�***/
void usart_send_data(USART_TypeDef* USARTx, u8 Data[],int len)
{
	int i;
	for(i=0;i<len;i++)
			usart_send_byte(USARTx,Data[i]);
}

/***����ͨ�ŷ����ַ���***/
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

/*********************************************************���ڽ��ճ���****************************************/
/***���ڽ������ݰ�RS232***/
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

/***485�������ݰ�***/
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

/**************************************************��дƬ��flash***********************************************/
/***дflashһ���ֳ���***/
void WriteFlashOneWord(uint32_t WriteAddress,uint32_t WriteData)
{
	FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
  FLASHStatus = FLASH_ErasePage(STARTADDR);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress, WriteData);    //flash.c ��API����
		//FLASHStatus = FLASH_ProgramWord(StartAddress+4, 0x56780000);                      //��Ҫд���������ʱ����
		//FLASHStatus = FLASH_ProgramWord(StartAddress+8, 0x87650000);                      //��Ҫд���������ʱ����
	}
	FLASH_LockBank1();
} 
/***end***/

/***��flash���ֽڳ���***/
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

/********************************SPIͨ��******************************************/
/***SPI����/���� 2/�����ֽڵ�����***/
u16 spi_readwrite_byte(SPI_TypeDef* SPIx, u16 Data) 
{
	u8 retry=0;
	u16 recbuff=0;
	
	if(memcmp(SPIx,SPI1,sizeof(SPI_TypeDef))==0)
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	/***����ɼ�����Ҫ��SPI�˿�***/
	
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)   //���ָ����SPI���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)
			return 0;
	}
	SPI_I2S_SendData(SPIx,Data);		//����2byte����
	retry=0;
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)   //���ָ����SPI���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)
			return 0;
	}
	recbuff=SPI_I2S_ReceiveData(SPIx);
	if(memcmp(SPIx,SPI1,sizeof(SPI_TypeDef))==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	/***����ɼ�����Ҫ��SPI�˿�***/
	
	return recbuff;	//����2byte����
}

/***SPI����/�������ݰ�***/
void spi_readwrite_data(SPI_TypeDef* SPIx, u16 Data[],int len,u16 recbuff[])
{
	u8 i;
	for(i=0;i<len;i++)
			recbuff[i]=spi_readwrite_byte(SPIx,Data[i]);
}


//end of the file
