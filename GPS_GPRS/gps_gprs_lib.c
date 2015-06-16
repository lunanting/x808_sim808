/************************************************************************************************************
gps_gprs_lib.c
designed for the gps/gprs servers
2015-06-10 15:37:28
designed by lunanting
************************************************************************************************************/

#include "gps_gprs.h"


/***命令运行状态***/
/********************************
返回值:	  0		无正在操作指令
					1		有指令正在操作
					10	实参给定不符
					*****************
形参：rw		0		写入无操作状态
					1		写入有操作状态
					2		读此刻操作状态
					*****************
作用：在有命令执行、操作时，不能再发送指令，应避免指令冲突
********************************/
u8 gps_gprs_cmd_state(u8 rw)
{
	static u8 state;
	
	if(state>2)return 10;
	if(state==2)return state;
	state=rw;
	
	return state;
}


/***获取指令状态***/
/*******************************
返回值：			0：	ERROR
						1：	OK
						2:	未接收
						*****************
形参：s			0:	写入状态0
						1：	写入状态1
						2：	读取状态
作用：确认指令执行状态
*******************************/
u8 get_status(u8 s)
{
	static u8 state=2;
	u8 bf;
	if(s>1){bf=state;state=2;return bf;}
	else{state=s;return state;}
}


/***gprs状态信息维护***/
/**************************************
返回值：state		状态信息
								**********************
形参：	*p				待被写入/读取存放的新状态信息指针
			*c				写状态标志	：'cgmm'等
								"read":	读取数据
								**********************
作用：作为GPRS状态信息交换的中心，保持这里的状态信
息是是最新的，且可被随时读取。
**************************************/
GPRS_status gprs_state(char *p,char*c)
{
	static GPRS_status state={0,0,0,0,0,0,0,0};
	GPRS_status state_null={0,0,0,0,0,0,0,0};
	if(strcmp(c,"read")==0)return state;
	else if(strcmp(c,"cgmm")==0)strcpy(state.cgmm,p);
	else if(strcmp(c,"cgmr")==0)strcpy(state.cgmm,p);
	else if(strcmp(c,"cimi")==0)strcpy(state.cimi,p);
	else if(strcmp(c,"copn")==0)strcpy(state.copn,p);
	else if(strcmp(c,"cops")==0)strcpy(state.cops,p);
	else if(strcmp(c,"cpas")==0)strcpy(state.cpas,p);
	else if(strcmp(c,"csq")==0)strcpy(state.csq,p);
	else if(strcmp(c,"gps")==0)strcpy(state.gps,p);
	else return state_null;
	return state;
}


/***gps数据信息维护***/
/****************************************
返回值：data			gps数据信息
								**********
形参：*p					待处理数据
								**********
作用：作为gps数据信息交换中心，保持这里的数据是最新的
且可随时被读取
****************************************/
GPS_data gps_data(char *p)
{
	static GPS_data data={0,0,0,0,0};
	char bf[30]={NULL},*s=bf;u8 i;
	if(strcmp(p,"read")==0)return data;
	s=strtok(p,",");
	for(i=0;i<10;i++)
	{
		switch(i)
		{
			case 1:strcpy(data.time,s);break;
			case 3:strcpy(data.coordinate,s);break;
			case 4:strcat(data.coordinate,s);break;
			case 5:strcat(data.coordinate,s);break;
			case 6:strcat(data.coordinate,s);break;
			case 7:strcpy(data.speed,s);break;
			case 8:strcpy(data.direction,s);break;
			case 9:strcpy(data.date,s);break;
		}
		s=strtok(NULL,",");
	}
	return data;
}


/***获取OD字符位置****/
/****************************************
返回值：dr				0D在字符串中的位置
								*****************
形参：	*p				待查询的字符串
			n					查询第N个OD的位置
								*****************
作用：获取字符串中的回车位置
****************************************/
u8 get_enter_lacation(char *p,u8 n)
{
	u8 dr=0,i,count=0;
	for(i=0;i<strlen(p);i++)
	{
		if(*(p+i)==0x0d)
		{
			count++;
			if(count==n){dr=i;return dr;}
		}
	}
	return dr;
}


/***空格检测***/
/******************************************
返回值：dr				空格在字符串中的位置
								*******************
形参：	*p				待检测的字符串
								*******************
作用：检测字符串中是否有空格，并返回其位置
******************************************/
u8 get_blank_lacation(char *p)
{
	u8 dr=0,i;
	for(i=0;i<strlen(p);i++){
		if(*(p+i)==0x20){dr=i;return dr;}}
	return dr;
}



/***分辨数据归属命令类型，并更新其数据***/
/******************************************
返回值：str				指令名称指针
									***********
形参：*p						待检测字符串
									***********
作用：辨别指令类型
******************************************/
void discern_cmd_type(char *p,char *data)
{
	//模块gprs状态
	if(strncmp(p,"cgmm",4)==0)gprs_state(data,"cgmm");
	else if(strncmp(p,"cgmr",4)==0)gprs_state(data,"cgmr");
	else if(strncmp(p,"cimi",4)==0)gprs_state(data,"cimi");
	else if(strncmp(p,"copn",4)==0)gprs_state(data,"copn");
	else if(strncmp(p,"cops",4)==0)gprs_state(data,"cops");
	else if(strncmp(p,"cpas",4)==0)gprs_state(data,"cpas");
	else if(strncmp(p,"csq",3)==0)gprs_state(data,"csq");
	//模块gps状态
	else if(strncmp(p,"cgpsstatus",10)==0)gprs_state(data,"gps");
	else if(strncmp(p,"cgpsinf",7)==0)gps_data(data);
	return ;
}





/***处理指令数据***/
/******************************************


******************************************/
void dispose_cmd_data(char *tp,char *data)
{
	
}

/************************************x808模块与外界接口************************************************/
/***延时接口***/
/*****************************
形参：dt		延时参数，单位ms
					***************
作用：为通信模块接入外界实现延时功能的方法
*****************************/
void x808_delay(u32 dt)
{
	os_dly_wait(dt);
}

/***串口通信接口***/
/***************************
形参：*s			带发送字符串
						***************
作用：为通信模块接入外界实现 通信功能的方法
***************************/
void x808_send(char *s)
{
	usart_send_str(X808,s);
}

/***end of the file***/
