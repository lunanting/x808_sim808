/*****************************************************************************************************************
																								app_plug.c
																					designed for the project
																						2014-09-23 13:07:21
																							 by lunanting
*****************************************************************************************************************/
#include "app.h"


extern void resum(void);
extern void help(void);
extern void restart(void);
extern void limitup_help(void);
extern void project(void);


/***������ʾ����״̬***/
void default_setting(u8 config)
{
	printf("\r\n\r\n                             System Description\r\n");
	if(config==0)
		printf("\r\nDefault show total value \r\n\r\n");
	else if(config==1)
		printf("\r\nDefault show detail value \r\n");
	printf("Notice:Please don't choose the choice: 'Send new line' of the port test chain\r\n");
	printf("\r\nThis command system design for debugging system\r\n");
	printf("\r\nDesigned by lunanting       ");
	printf("lunanting@yeah.net\r\n");
	printf("\r\nIf you are unfamiliar with this command system,you can use the 'help' command to learn commands of this system\r\n");
	printf("\r\nϵͳ�������ɹ�\r\n\r\n������ָ�\r\n");
}
/***end***/

/***����USART1���յ�����***/
void analyze_u1rec_command(void)
{
	u8 data[20];
	char *s=(char *)malloc(10);
	
	memset(data,0,20);
	usart_rec_data(USART1,data,10);
	printf("\r\n���������");
	usart_send_str(USART1,(char *)data);
	usart_send_enter(USART1);
	printf("��Ӧ��");
	if(strncmp((char *)data,"restart",strlen("restart"))==0)
		restart();
	else if(strncmp((char *)data,"back",strlen("back"))==0)
		printf("ָ�����\r\nԭ���������������\r\n");
	else if(strncmp((char *)data,"help",strlen("help"))==0)
		help();
	else if(strncmp((char *)data,"designer",strlen("designer"))==0)
		resum();
	else if(strncmp((char *)data,"project",strlen("project"))==0)
		project();
		
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
	os_dly_wait(600*T);
	printf("\r\n�����´����鹹��������ͬ��������Ϯ\r\n");
	os_dly_wait(600*T);
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
	os_dly_wait(2000*T);
	printf("\r\n\r\n��ѡ����Ҫ������ָ�\r\n");
}
/***end***/

/***restart����***/
void restart(void)
{
	printf("ϵͳ��������������\r\n");
	os_dly_wait(600*T);
	printf("\r\nϵͳ����������\r\n");
	os_dly_wait(600*T);
	printf("\r\nϵͳ��������\r\n");
	os_dly_wait(600*T);
	printf("\r\n���������ɹ������ڵ�½\r\n");
	os_dly_wait(600*T);
	mcu_reset();
}
/***end***/

/***project***/
void project(void)
{
	printf("����ĿΪΪ�г�����\r\n"
						"�����Ҫ�������Ϊ��\r\n"
							"1.�ⲿ�ź�����\r\n"
							"2.�ڲ��ź����\r\n"
							"3.��������\r\n"
							"4.�ⲿ�źſ���������\r\n"
							"5.485�źŽ��\r\n"
	);
}

/**/
/***end of the file***/
