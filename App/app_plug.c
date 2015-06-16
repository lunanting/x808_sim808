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


/***串口提示设置状态***/
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
	printf("\r\n系统已启动成功\r\n\r\n请输入指令：\r\n");
}
/***end***/

/***解析USART1接收的命令***/
void analyze_u1rec_command(void)
{
	u8 data[20];
	char *s=(char *)malloc(10);
	
	memset(data,0,20);
	usart_rec_data(USART1,data,10);
	printf("\r\n已输入命令：");
	usart_send_str(USART1,(char *)data);
	usart_send_enter(USART1);
	printf("响应：");
	if(strncmp((char *)data,"restart",strlen("restart"))==0)
		restart();
	else if(strncmp((char *)data,"back",strlen("back"))==0)
		printf("指令错误\r\n原因：已在最外命令层\r\n");
	else if(strncmp((char *)data,"help",strlen("help"))==0)
		help();
	else if(strncmp((char *)data,"designer",strlen("designer"))==0)
		resum();
	else if(strncmp((char *)data,"project",strlen("project"))==0)
		project();
		
	else
		printf("指令错误\r\n原因：非本系统指令\r\n请输入正确指令       可使用'help'指令寻求帮助\r\n");	
}
/***end***/



/*************************************命令解析****************************************/

/***designer命令***/
void resum(void)
{
	printf("Individual Resume\r\n");
	printf("This system is designed by lunanting\r\n\r\n");
	printf("lunanting\r\n爱好：打LOL\r\n段位：白银V（不过是最强王者水平~呵呵~）\r\n擅长位子：中单、射手\r\n最擅长英雄：卡特琳娜（皮城第一卡特~哈哈~）\r\n");
	printf("大区：皮城警备\r\n帐号：明恋桃花源\r\n急寻一名暴力队友，五排的感觉缠绕我，太久。\r\n\r\n");
	os_dly_wait(600*T);
	printf("\r\n本故事纯属虚构，如有雷同，纯属抄袭\r\n");
	os_dly_wait(600*T);
	printf("\r\n请输入系统操作指令:\r\n");
}
/***end***/

/***help命令***/
void help(void)
{
	printf("显示系统命令说明\r\n");
	printf("\r\n1.total:Will show the total value;\r\n");
	printf("\r\n2.detail:Will show the detail value;\r\n");
	printf("\r\n3.limitup:You can input the sensor up-limit;\r\n");
	printf("\r\n4.restart:The system will be restart;\r\n");
	printf("\r\n5.back:Go back on one-up layer;\r\n");
	printf("\r\n6.help:Will show the command of the system;\r\n");
	os_dly_wait(2000*T);
	printf("\r\n\r\n请选择需要操作的指令：\r\n");
}
/***end***/

/***restart命令***/
void restart(void)
{
	printf("系统将启动重启操作\r\n");
	os_dly_wait(600*T);
	printf("\r\n系统将重新启动\r\n");
	os_dly_wait(600*T);
	printf("\r\n系统正在重启\r\n");
	os_dly_wait(600*T);
	printf("\r\n重新启动成功，正在登陆\r\n");
	os_dly_wait(600*T);
	mcu_reset();
}
/***end***/

/***project***/
void project(void)
{
	printf("此项目为为中钞科信\r\n"
						"设计主要功能设计为：\r\n"
							"1.外部信号输入\r\n"
							"2.内部信号输出\r\n"
							"3.键盘输入\r\n"
							"4.外部信号开关量控制\r\n"
							"5.485信号借口\r\n"
	);
}

/**/
/***end of the file***/
