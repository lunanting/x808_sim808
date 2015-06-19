/*****************************************************************************************************************
																										main.c
																						designed for the project
																							2014-09-23 16:24:07
																								 by lunanting
*****************************************************************************************************************/
#define NM_VALUE_GLOBLE

#include "stm32f10x.h"
#include "module.h"



extern __task void Init_task(void);
extern void app_gpio(void);


int main(void)
{
	app_gpio();
	GPIO_ResetBits(GPIOB,GPIO_Pin_11|GPIO_Pin_12);	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,App_Offset);
	Init_sys();
	os_sys_init(Init_task);
	while(1);
}


/***end of the file***/
