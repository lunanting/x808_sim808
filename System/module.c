/*************************************************************************************
																				module.c
																	designed for the peoject
																		2014-08-27 11:27:48
																				by lunanting
																				
*************************************************************************************/

#include "module.h"

extern void NVIC_TIM(TIM_TypeDef* TIMx);
extern void app_gpio(void);
/*时钟使能函数*/
void RCC_Config(void)
{
	uint16_t HSEStartUpStatus;
	
	//使能USART和GPIOA
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus==SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		FLASH_SetLatency(FLASH_Latency_2);
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_6);
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource()!=0x08);
	}

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|						//72Mhz
												 RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|
												 RCC_APB2Periph_AFIO|
												 RCC_APB2Periph_SPI1
										     ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|						//72Mhz   这是经过倍频得到72Mhz的  
												 RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4
												 ,ENABLE);
// 	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

/*GPIO设置*/
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//配置PA9为USART1 Tx
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   //配置PA10为USART1 Rx
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//配置PA9为USART2 Tx
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);	
	//配置PA10为USART2 Rx
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
   GPIO_Init(GPIOA,&GPIO_InitStructure);
	 
	 app_gpio();		//应用程序的GPIO配置
}

/*USART1，2初始化*/
void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
// 	USART_ClockInitTypeDef USART_ClockInitStructure;
//初始化UART1  8位长度 1位停止位 115200波特率
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);//使能	
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能接收中断
	
//初始化UART2 8位长度 1位停止位 115200波特率
	USART_InitStructure.USART_BaudRate=38400;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	USART_Init(USART2,&USART_InitStructure);
	
	USART_Cmd(USART2,ENABLE);//使能	
 	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//使能接收中断
}

/***SPI通信***/
void SPI_Config(SPI_TypeDef* SPIx)
{
	SPI_InitTypeDef   SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 
	if(memcmp(SPIx,SPI1,sizeof(SPI_TypeDef))==0)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推免输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if(memcmp(SPIx,SPI2,sizeof(SPI_TypeDef))==0)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推免输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_Cmd(SPIx, ENABLE); 
	
	SPI_SSOutputCmd(SPIx,ENABLE);							//释放NSS，作为IO口	注：stm32的SPI上的NSS作为软件模式并不能自动实现选择/释放从设备
	if(memcmp(SPIx,SPI1,sizeof(SPI_TypeDef))==0)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if(memcmp(SPIx,SPI2,sizeof(SPI_TypeDef))==0)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
}

/***定时器配置***/
void TIM_Config(TIM_TypeDef* TIMx)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_TIM(TIMx);	
	
	TIM_DeInit(TIMx);
	TIM_TimeBaseStructure.TIM_Period=359;
	TIM_TimeBaseStructure.TIM_Prescaler=19;						//定时0.1ms							当定时器的prescaler大于1，定时器的时钟执行倍频  *2
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;							//（period+1）*（prescaler+1）/72Mhz
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIMx,TIM_FLAG_Update);
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
// 	TIM_Cmd(TIMx,ENABLE);

}

//中断向量初始化
void NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure;

	#ifdef VECT_TAB_RAM 
     NVIC_SetVectorTable(NVIC_VectTab_RAM , 0x2000);  
	#else 
     NVIC_SetVectorTable(NVIC_VectTab_FLASH , 0x2000); 
	#endif  
	//使用一位来表示优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	//初始化UART1中断
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//初始化UART2中断
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/***定时器中断配置***/
void NVIC_TIM(TIM_TypeDef* TIMx)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	#ifdef VECT_TAB_RAM 
     NVIC_SetVectorTable(NVIC_VectTab_RAM , 0x2000);  
	#else 
     NVIC_SetVectorTable(NVIC_VectTab_FLASH , 0x2000); 
	#endif  
	//使用一位来表示优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	if(memcmp(TIMx,TIM2,sizeof(TIM_TypeDef))==0)
		NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	else if(memcmp(TIMx,TIM3,sizeof(TIM_TypeDef))==0)
		NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	else if(memcmp(TIMx,TIM4,sizeof(TIM_TypeDef))==0)
		NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	else if(memcmp(TIMx,TIM5,sizeof(TIM_TypeDef))==0)
		NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn;
	else if(memcmp(TIMx,TIM6,sizeof(TIM_TypeDef))==0)
		NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;
	else if(memcmp(TIMx,TIM7,sizeof(TIM_TypeDef))==0)
		NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/***end***/

/***end of the file***/
