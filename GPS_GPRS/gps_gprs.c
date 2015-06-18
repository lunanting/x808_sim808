/**************************************************************************************************
gps_gprs.c
designed by lunanting
2015-06-09 10:49:31
designed for opration of GPS_GPRS module
**************************************************************************************************/

#include "gps_gprs.h"




/***发送指令方法***/
/**************************************
放回值：			0		等待上条指令完成超时
						1		发送成功，指令执行错误
						2		发送完成，指令执行正确
						3		发送成功，但对方未接收
						*************************
形参：*p			发送指令代码
						*************************
作用：主要用于状态信息的指令
**************************************/
u8 x808_cmd_send(char *p)
{
	u8 count=0,bf;
	char s2[30]="at+";
	while(gps_gprs_cmd_state(2)!=0)
	{
		x808_delay(1);
		count++;if(count>200)return 0;			//等待超时，返回0
	}
	gps_gprs_cmd_state(1);
	memcpy(s2+3,p,strlen(p));
	x808_send(s2);
	count=0;
	while(1)
	{
		bf=get_status(2);
		if(bf==2)
		{
			x808_delay(1);
			count++;if(count>100)return 3;	//发送完成且对方未接收，返回3
		}
		else if(bf==1)return 2;						//发送完成且正确执行，返回2
		else if(bf==0)return 1;					  //发送完成却执行错误，返回1
	}
}


/***解析数据***/
/******************************
返回值：				0：	接收为非指令返回数据
							1：	指令解析完成且指令正确执行
							10：指令解析完成且指令执行错误
							****************************
形参：*p				从模块接收的数据
							****************************
作用：解析与x808通信接收的数据
******************************/
u8 x808_cmd_parsing(char *p)
{
	char bf[100]={NULL},cmd[15]={NULL};;u8 len=0,dr=0;
//	char *str=NULL;
	
	len=strlen(p);
	memcpy(cmd,p,len);
	if(strncmp(cmd,"at+",3)!=0)return 0;					//非指令返回数据，返回0
	memset(cmd,0,len);
	memcpy(cmd,p-4,4);
	if(strncmp(cmd,"OK",2)!=0){get_status(0);gps_gprs_cmd_state(0);return 10;}			//指令执行错误，返回10
	len=get_enter_lacation(p,1)+3;
	if((strlen(p)-len)<5){get_status(1);gps_gprs_cmd_state(0);return 1;}						//指令正确执行，返回1
	memset(cmd,0,4);
	len=get_enter_lacation(p,1)-3;
	memcpy(cmd,p+3,len);
	if(strncmp(cmd,"cgpsout",7)==0)return 1;			//gps自动输出
	dr=get_blank_lacation(p);
	if(dr==0){																		//无空格数据
		len=get_enter_lacation(p,2)-(get_enter_lacation(p,1)+3);
		memcpy(bf,(p+get_enter_lacation(p,1)+3),len);}
	else{																					//有空格数据
		len=get_enter_lacation(p,2)-(get_blank_lacation(p)+1);
		memcpy(bf,(p+get_blank_lacation(p)+1),len);}
	discern_cmd_type(cmd,bf);											//区分指令类型并处理数据
	
	get_status(1);
	return 1;
}



/***GPRS模块初始化***/
u8 x808_init(void)
{
	u8 state=0;
	u8 data[100];
	memset(data,0,100);
	state=x808_cmd_send("cgmm");					//gprs部分状态信息
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cgmr");
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cgmr");
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cops?");
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cimi");
	if(state==3||state==0)return 0;
	state=x808_cmd_send("csq");
	if(state==3||state==0)return 0;
	
	state=x808_cmd_send("cgpspwr=1");			//gps部分状态信息
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cgpsstatus?");
	if(state==3||state==0)return 0;
	
	state=x808_cmd_send("cmgf=1");				//sms部分状态信息
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cpms=\"sm\",\"sm\",\"sm\"");
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cnmi=2,1");
	if(state==3||state==0)return 0;

	return 1;
}



/***发送短信功能***/
/******************************************
返回值：state			信息发送结果
									************
形参：*str 				信息内容
			*num				信息目标号码
									************
作用：发送短信消息
******************************************/
u8 x808_sms_send(char *str,char *num)
{
	char s[20]="cmgs=\"",s1[3]={0x1a};u8 state=0;
	strcat(s,num);
	strcat(s,"\"");
	state=x808_cmd_send(s);
	if(state==3||state==0)return 0;
	x808_delay(100);
	x808_send(str);
	x808_send(s1);
	
	return 1;
}
/***end of the file***/
