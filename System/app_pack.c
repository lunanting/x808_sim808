/****************************************************************************************************************
																								    app_pack.c
																							cdesigned for the project
																							  2014-10-08 16:02:34
																								   by lunanting
****************************************************************************************************************/

#include "module.h"

void iotask_overtime(void)
{
	if(value_count>80)
	{
		TIM_Cmd(TIM4,DISABLE);
		value_count=0;
		printf("\r\n\r\n光钎传感器未检测到目标\r\n");
		while(1)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_4);
			os_dly_wait(1000);
			GPIO_ResetBits(GPIOC,GPIO_Pin_4);
			os_dly_wait(1000);
		}
	}
}


/***end of the film***/
