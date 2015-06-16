/*********************************************************************************************************
                                                module.h
																				  designed for module.c
																					 2014-08-27 11:16:25
																					
*********************************************************************************************************/
#ifndef __MODULE_H
#define __MODULE_H

#include "stm32f10x.h"
#include <stdio.h>
#include "rtl.h"
#include "stdint.h"
#include "string.h"
#include "pack.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_tim.h"
#include "app_plug.h"
#include "stdlib.h"
#include "app_pack.h"
#include "project_config.c"
#include "globle.h"
#include "task.h"

//¶¨Òåº¯Êý

/*module.c*/
void RCC_Config(void);
void GPIO_Config(void);
void USART_Config(void);
void NVIC_Config(void);
void SPI_Config(SPI_TypeDef* SPIx);
void TIM_Config(TIM_TypeDef* TIMx);



/*function.c*/
void Init_sys(void);
char *itoa(int num,char *str,int radix);
int fputc(int ch,FILE *f);
void mcu_reset(void);

extern COIN coin_count;



#endif
