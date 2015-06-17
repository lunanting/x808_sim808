/*************************************************************************************************************
gps_gprs.h
designed for gps_gprs.c
2015-06-09 10:52:49
designed by lunanting
*************************************************************************************************************/

#ifndef __GPS_GPRS_H
	#define __GPS_GPRS_H

#include "app.h"

#define OK			1
#define ERROR		0
#define X808		USART2

/***数据类型定义***/
typedef struct
{
	char cgmm[50];			//模块型号
	char cgmr[50];			//模块固件版本
	char cops[50];			//注册情况
	char cimi[50];			//CIMI值
	char csq[10];			//信号强度
	char cpas[5];			//模块活动状态
	char copn[5];			//运营商名称
	char gps[30];			//GPS状态
} GPRS_status;

typedef struct
{
	char date[15];					//日期
	char time[10];					//时间
	char coordinate[30];		//坐标
	char speed[10];				//速度
	char direction[10];		//方向
} GPS_data;

/***函数申明***/
//gps_gprs.c
extern GPRS_status deal_data(char *s);
extern u8 gps_gprs_init(void);
extern u8 *get_messege(char *data);


//gps_gprs_lib.c
extern u8 gps_gprs_cmd_state(u8 rw);
extern GPRS_status gprs_state(char *p,char*c);
extern void x808_delay(u32 dt);
extern u8 get_status(u8 s);
extern void x808_send(char *p);
extern u8 x808_cmd_parsing(char *p);
extern u8 get_enter_lacation(char *p,u8 n);
extern void discern_cmd_type(char *p,char *data);
extern u8 get_blank_lacation(char *p);

#endif
/***end of the file***/
