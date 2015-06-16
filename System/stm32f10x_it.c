/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "module.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/
extern u8 Usart1GetDateFlag ;
extern u16 DateGetUsart1;
extern OS_SEM u1recsem;
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
// void SVC_Handler(void)
// {
// }

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
// void PendSV_Handler(void)
// {
// }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
// void SysTick_Handler(void)
// {
// }

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
/***串口1接收中断处理***/
void USART1_IRQHandler(void)
{
	if(SET==USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		TIM_Cmd(TIM3,DISABLE);
		u1_count=0;
		u1rec_buff[u1rec_i]=USART_ReceiveData(USART1);
// 		if(u1rec_buff[u1rec_i]=='\0')
// 		{
// 			u1rec_i=0;
// 			isr_sem_send(u1recsem);
// 			return;
// 		}
		u1rec_i++;
		TIM_Cmd(TIM3,ENABLE);
	}	
}
/**/

/***串口2接受中断处理***/
void USART2_IRQHandler(void)
{
	TIM_Cmd(TIM4,DISABLE);
	u2_count=0;
	if(SET==USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		u2rec_buff[u2rec_i]=USART_ReceiveData(USART2);
		if(u2rec_buff[u2rec_i-1]==0x0d&&u2rec_buff[u2rec_i]==0x0a)				//回车检测
			u2_count=1000;
		u2rec_i++;
	}
	TIM_Cmd(TIM4,ENABLE);
}

/**/

/***TIM2中断***/
void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)!=RESET)
	{
		count++;
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}
}

/***TIM3中断处理***/
void TIM3_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)!=RESET)
	{
		u1_count++;
		TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	}
}

/***TIM4中断处理***/
void TIM4_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)!=RESET)
	{
		u2_count++;
		TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	}
}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/


