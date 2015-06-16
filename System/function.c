/**************************************************************************************
																		function.c
															designed for the project
																2014-08-27 11:52:35
																    by lunanting
																		
**************************************************************************************/
#include "module.h"
#include "stdbool.h"
// #include "rtl.h"
extern void app_tim(void);

u32 test_t[10];


/*系统初始化*/
 void Init_sys(void)
{
	RCC_Config();
	NVIC_Config();
	GPIO_Config();
	USART_Config();
	SPI_Config(SPI1);
	app_tim();				//应用程序的定时器配置
}



	/**********************itoa转换*******************/
char *itoa(int num,char *str,int radix)
{
		char *start;
		char temp;
		const char table[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		char *ptr = str;
		bool negative = false;
		if(num == 0)
			{              //num=0
				*ptr++='0';
				*ptr='\0';                // don`t forget the end of the string is '\0'!!!!!!!!!
				return str;
			}
		if(num<0)
			{               //if num is negative ,the add '-'and change num to positive
				*ptr++='-';
				num*=-1;
				negative = true;
			}
		while(num)
			{
				*ptr++ = table[num%radix];
				num/=radix;
		  }
		*ptr = '\0';            //if num is negative ,the add '-'and change num to positive
		// in the below, we have to converse the string
		start =(negative?str+1:str); //now start points the head of the string
		ptr--;                           //now prt points the end of the string
		while(start<ptr)
			{
				temp = *start;
				*start = *ptr;
				*ptr = temp;
				start++;
				ptr--;
		 }
		return str;		 
}

/***配合c库里面的printf函数使用***/
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	//等待发送完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	return ch;		
}

/***cpu reset***/
void mcu_reset(void)
{
	__disable_fault_irq();
	NVIC_SystemReset();
}
/***end***/
/***end of file***/
