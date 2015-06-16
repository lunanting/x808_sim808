/*******************************************************************************************
															 	pack.h
												   desiged for pack.c
												   2014-08-28 09:45:08
															by lunanting
													  
*******************************************************************************************/
#ifndef __PACK_H
#define __PACK_H
#include "module.h"


/***pack.cº¯Êý¿â***/
void usart_send_enter(USART_TypeDef* USARTx);
void usart_send_byte(USART_TypeDef* USARTx, u8 Data);
void usart_send_data(USART_TypeDef* USARTx, u8 Data[],int len);
void usart_send_str(USART_TypeDef* USARTx,char *s);
u16 spi_readwrite_byte(SPI_TypeDef* SPIx, u16 Data);
void spi_readwrite_data(SPI_TypeDef* SPIx, u16 Data[],int len,u16 recbuff[]);
u8 *usart_rec_data(USART_TypeDef* USARTx,u8 *data,u8 len);
void WriteFlashOneWord(uint32_t WriteAddress,uint32_t WriteData);
int ReadFlashNByte(uint32_t ReadAddress, uint8_t *ReadBuf, int32_t ReadNum);
u8 *rt_485(USART_TypeDef* USARTx,u8 *data,u8 len);



#endif
//end of the file

