/*****************************************************************************************************************
																								app_plug.c
																					designed for the project
																						2014-09-23 13:07:21
																							 by lunanting
*****************************************************************************************************************/
#include "module.h"


extern void resum(void);
extern void help(void);
extern void restart(void);
extern void limitup_help(void);


/***������ʾ����״̬***/
void default_setting(u8 config)
{
	printf("\r\n\r\n                  System Description\r\n");
	if(config==0)
		printf("\r\nDefault show total value \r\n\r\n");
	else if(config==1)
		printf("\r\nDefault show detail value \r\n");
	printf("You can choose one of the two choice below \r\n");
	printf("Detail:Will show detail value          total:Will show total value \r\n");
	printf("Notice:Please don't choose the choice: 'Send new line' of the port test chain\r\n");
	printf("\r\nThis command system design for cleaning-separating mechanical system\r\n");
	printf("\r\nDesigned by lunanting       ");
	printf("lunanting@yeah.net\r\n");
	printf("\r\nIf you are unfamiliar with this command system,you can use the 'help' command to learn commands of this system\r\n");
	printf("\r\nϵͳ�������ɹ�\r\n\r\n������ָ�\r\n");
}
/***end***/

/***����USART1���յ�����***/
void analyze_u1rec_command(u8 *p,u16 *l)
{
	u16 data[10];
	u32 limit=0;
	char *s=(char *)malloc(10);
	
	*l=0;
	memset(data,0,20);
	usart_rec_data(USART1,(u8 *)data,10);
	printf("\r\n���������");
	usart_send_str(USART1,(char *)data);
	usart_send_enter(USART1);
	printf("��Ӧ��");
	if(strcmp((char *)data,"total")==0)
	{
		usart_send_str(USART1,"Will show total value\r\n");
		*p=0;
	}
	else if(strcmp((char *)data,"detail")==0)
	{
		usart_send_str(USART1,"Will show detail value\r\n");
		*p=1;
	}
	else if(strcmp((char *)data,"limitup")==0)
	{
		while(1)
		{
			printf("������������ֵ\r\n");
			memset(data,0,20);
			usart_rec_data(USART1,(u8 *)data,10);
			if(strcmp((char *)data,"back")==0)
			{
				printf("\r\n���������back\r\n");
				printf("��Ӧ����ȡ������ȡֵ����ֵ\r\n");
				break;
			}
			else if(strcmp((char *)data,"help")==0)
			{
				limitup_help();
				continue;
			}
			else
			{
				strcpy(s,(char *)data);
				limit=atoi(s);
				if(1000<limit&&limit<10000)
				{
					printf("\r\n����������ֵ��");
				  usart_send_str(USART1,(char *)data);
			  	usart_send_enter(USART1);
					*l=limit;
					WriteFlashOneWord(0,limit);
					break;
				}
				else
				{
					printf("\r\n�������ַ���");
				  usart_send_str(USART1,(char *)data);
			  	usart_send_enter(USART1);
					printf("\r\n�������ݲ����ϱ�׼  ��ʾ����������ֵ��Χ��1000~10000���������ַ�����ʽ��\r\n");
					os_dly_wait(6000);
					printf("\r\n����������\r\n\r\n");
					os_dly_wait(6000);
					continue;
				}
			}
		}
	}
	else if(strcmp((char *)data,"restart")==0)
	{
		restart();
	}
	else if(strcmp((char *)data,"back")==0)
	{
		printf("ָ�����\r\nԭ���������������\r\n");
	}
	else if(strcmp((char *)data,"help")==0)
	{
		help();
	}
	else if(strcmp((char *)data,"designer")==0)
	{
		resum();
	}
	else
		printf("ָ�����\r\nԭ�򣺷Ǳ�ϵͳָ��\r\n��������ȷָ��       ��ʹ��'help'ָ��Ѱ�����\r\n");	
}
/***end***/



/*************************************�������****************************************/

/***designer����***/
void resum(void)
{
	printf("Individual Resume\r\n");
	printf("This system is designed by lunanting\r\n\r\n");
	printf("lunanting\r\n���ã���LOL\r\n��λ������V����������ǿ����ˮƽ~�Ǻ�~��\r\n�ó�λ�ӣ��е�������\r\n���ó�Ӣ�ۣ��������ȣ�Ƥ�ǵ�һ����~����~��\r\n");
	printf("������Ƥ�Ǿ���\r\n�ʺţ������һ�Դ\r\n��Ѱһ���������ѣ����ŵĸо������ң�̫�á�\r\n\r\n");
	os_dly_wait(6000);
	printf("\r\n�����´����鹹��������ͬ��������Ϯ\r\n");
	os_dly_wait(6000);
	printf("\r\n������ϵͳ����ָ��:\r\n");
}
/***end***/

/***help����***/
void help(void)
{
	printf("��ʾϵͳ����˵��\r\n");
	printf("\r\n1.total:Will show the total value;\r\n");
	printf("\r\n2.detail:Will show the detail value;\r\n");
	printf("\r\n3.limitup:You can input the sensor up-limit;\r\n");
	printf("\r\n4.restart:The system will be restart;\r\n");
	printf("\r\n5.back:Go back on one-up layer;\r\n");
	printf("\r\n6.help:Will show the command of the system;\r\n");
	os_dly_wait(20000);
	printf("\r\n\r\n��ѡ����Ҫ������ָ�\r\n");
}
/***end***/

/***restart����***/
void restart(void)
{
	printf("ϵͳ��������������\r\n");
	os_dly_wait(6000);
	printf("\r\nϵͳ����������\r\n");
	os_dly_wait(6000);
	printf("\r\nϵͳ��������\r\n");
	os_dly_wait(6000);
	printf("\r\n���������ɹ������ڵ�½\r\n");
	os_dly_wait(6000);
	mcu_reset();
}
/***end***/

/***limitup��help����***/
void limitup_help(void)
{
	printf("\r\n���������help\r\n");
	printf("��Ӧ����ʾ����������\r\n");
	printf("\r\n1.����1000~10000֮�����ֵ��ע���ַ�������	\r\n2.ʹ��back�����˳��������������\r\n\r\n");
	os_dly_wait(6000);
}
/***end***/
/***end of the file***/
