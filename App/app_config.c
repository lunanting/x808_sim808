/***************************************************************************************************************
app_config.c
designed fot the application
2015-03-09 10:09:48
by lunanting
***************************************************************************************************************/
/*����޸�ʱ�䣺
2015-03-10 10:41:47
*/
#include "app.h"

OS_SEM u1recsem,sound;

/***��ĿI/O����***/
void app_gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
//����GPIO���롡PB0/1/2/10  ��������
	/*����˿�˵��
		��ϸ˵�����Բ���app.h�еġ�Ӧ�ó�������
	*/
	 GPIO_InitStructure.GPIO_Pin=K1|K2|K3|K4|IN1|IN2|IN3;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_Init(GPIOC,&GPIO_InitStructure);				//PC�˿�
	
	 GPIO_InitStructure.GPIO_Pin=IN4;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);				//PD�˿�

	  
//����GPIO��� PC4/5/6/7/8/9 ��©���
	/*����˿�˵��
		��ϸ˵�����Բ���app.h�еġ�Ӧ�ó�������
	*/
	
	 GPIO_InitStructure.GPIO_Pin=BELL|PW|OUT1|OUT2|OUT3|OUT4;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);				//PB�˿�
	 
	 GPIO_InitStructure.GPIO_Pin=DIR_485|RED_LED|SYS_LED|CS_AD|CS_DA;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);				//PA�˿�
	 
	 
//��ʼ��GPIO����״̬
	 /*�˿ڳ�ʼ״̬˵��
		 
	 */
// 	 GPIO_SetBits(GPIOB,BL|WL|KJ|OUT1|OUT2|OUT3|OUT4);		//io��ʼ��
	 GPIO_ResetBits(GPIOB,RED_LED|SYS_LED|BELL);
	 GPIO_ResetBits(GPIOA,DIR_485);
	 GPIO_SetBits(GPIOB,PW);
}

/***��Ŀ��ʱ������***/
void app_tim(void)
{
	TIM_Config(TIM2);
 	TIM_Config(TIM3);
 	TIM_Config(TIM4);
}



/***end of the file**/
