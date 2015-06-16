/*****************************************************************************************************************
app_lib.c
designed for the project
2015-03-09 13:44:43
by lunanting
*****************************************************************************************************************/
/*����޸�ʱ�䣺
2015-03-10 10:42:13
*/
#include "app.h"

/***����ź�֪ͨ***/
/*������
			0		����
			1		����
*/
u8 signal_state(u8 state)
{
	switch (state)
	{
		case 0:
			GPIO_SetBits(GPIOA,RED_LED);break;
		case 1:
			GPIO_ResetBits(GPIOA,RED_LED);break;
	}
	if(state!=0||state!=1)
		return 1;
	else
		return 0;
}
/**/

/***ϵͳ����״̬***/
/*������
			0		����
			1		����
*/
u8 sys_state(u8 state)
{
	switch (state)
	{
		case 0:
			GPIO_SetBits(GPIOA,SYS_LED);break;
		case 1:
			GPIO_ResetBits(GPIOA,SYS_LED);break;		
	}
	if(state==0||state==1)
		return 1;
	else
		return 0;
}
/**/

/***����ɨ��***/
void key_get(u8 *state,u8 *key)
{
	u8 key_state[8];
	memcpy(key_state,state,8);
	if(GPIO_ReadInputDataBit(GPIOC,K1)==0)		//K1
	{
		key_state[0]++;
		if(key_state[0]>20)
			key_state[0]=21;
	}
	else if(key_state[0]>20)
	{
		key[0]=1;
		key_state[0]=0;
	}
	
	if(GPIO_ReadInputDataBit(GPIOC,K2)==0)		//K2
	{
		key_state[1]++;
		if(key_state[1]>20)
			key_state[1]=21;
	}
	else if(key_state[1]>20)
	{
		key[1]=1;
		key_state[1]=0;
	}
	
	if(GPIO_ReadInputDataBit(GPIOC,K3)==0)		//K3
	{
		key_state[2]++;
		if(key_state[2]>40)
		{
			key_state[2]=0;
			key[2]=1;
		}
	}
	else
		key_state[2]=0;
	
	
	if(GPIO_ReadInputDataBit(GPIOC,K4)==0)		//K4
	{
		key_state[3]++;
		if(key_state[3]>40)
		{
			key_state[3]=0;
			key[3]=1;
		}
	}
	else
		key_state[3]=0;
	
	
	memcpy(state,key_state,8);
	return ;
}
/**/


/***sound����***/
void sound_control(u8 state)
{
	switch(state)
	{
		case 0:		//����
			GPIO_ResetBits(GPIOB,BELL);break;
		case 1:		//��
			GPIO_SetBits(GPIOB,BELL);os_sem_send(sound);break;
	}
}
/**/

/***�ػ�����***/
void power_down(u8 time)
{
	u8 f=2;
	time=time*f;
	while(time)
	{
		time--;
		sound_control(1);
		os_dly_wait(1000/f);
	}
}
/**/

/***dacоƬSPI����***/
void app_spi(u8 dac,u16 data)
{
	if(dac==0)
		data=(1<<12)+(data<<4);
	else if(dac==1)
		data=(1<<12)|(1<<14)+(data<<4);
	spi_readwrite_byte(SPI1,data);
	return ;
}
/**/

/***I/O����***/
u8 app_io(u8 io,u8 state,u16 pin)
{
	u8 ret=1;
	switch(io)
	{
		case IN:			//����
		{
			if(pin!=IN4){
				ret=GPIO_ReadInputDataBit(GPIOC,pin);}
			else if(pin==IN4){
				ret=GPIO_ReadInputDataBit(GPIOB,pin);}
			if(ret==1)
				ret=1;
			else
				ret=0;
			return(ret);
		}
		case OUT:			//���
		{
			switch(state)
			{
				case 0:GPIO_ResetBits(GPIOB,pin);break;			//����
				case 1:GPIO_SetBits(GPIOB,pin);break;			//����
			}
			break;
		}
	}
	return (ret);
}
/**/

/***����io��***/
void test_io(void)
{
	u8 i;
	u16 pin;
	for(i=0;i<4;i++)
	{
		switch(i)
		{
			case 0:
				pin=IN1;break;
			case 1:
				pin=IN2;break;
			case 2:
				pin=IN3;break;
			case 3:
				pin=IN4;break;
		}
		if(app_io(IN,0,pin)!=0)
			printf("������Ķ˿���IN%d   ע����ΪJ1��%d���������ź�\r\n",(i+1),(i+3));
	}
}
/**/

/***485ͨѶ����***/
void dir_485(u8 dir)
{
	switch(dir)
	{
		case 0:GPIO_ResetBits(GPIOA,DIR_485);break;
		case 1:GPIO_SetBits(GPIOA,DIR_485);break;
	}
}
/**/

/***485ͨѶ  �ַ���***/
void send_485(char *s)
{
	dir_485(TX);
	usart_send_str(USART2,s);
	dir_485(RX);
}

void analyze_485(void)
{
	u8 data[100];
	
	memset(data,0,100);
//	printf("\r\n�ѽ���485���շ���\r\n");
//	os_dly_wait(1);
	rt_485(USART2,data,100);
	usart_send_data(USART1,data,100);
	
	printf("\r\n");
}
/**/

/***3.3V�ⲿ��Դ����***/
void power_control(u8 state)
{
	switch(state)
	{
		case 0:
			GPIO_ResetBits(GPIOB,PW);break;
		case 1:
			GPIO_SetBits(GPIOB,PW);break;
	}
}
/**/
/***end of the file***/
