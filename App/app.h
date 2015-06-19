/**************************************************************************************************
app.h
designed for application of the project
2015-03-09 09:23:53
by lunanting
**************************************************************************************************/

#ifndef __APP_H
#define __APP_H

#include "module.h"
#include "app_lib.h"
#include "gps_gprs.h"



/***线程信号量申明***/
extern OS_SEM u1recsem,sound;

/**/

/***应用程序常量***/
//PA	输出端口
#define DIR_485		GPIO_Pin_1			//485方向
#define CS_AD			GPIO_Pin_4			//AD芯片片选
#define CS_DA			GPIO_Pin_8			//DA芯片片选
#define RED_LED		GPIO_Pin_11			//红灯	报警
#define SYS_LED		GPIO_Pin_12			//系统运行指示灯

//PB	输出端口
#define IN4				GPIO_Pin_3			//输入口4
#define OUT1			GPIO_Pin_4			//输出1
#define OUT2			GPIO_Pin_5			//输出2
#define OUT3			GPIO_Pin_6			//输出3
#define OUT4			GPIO_Pin_7			//输出4
#define BELL			GPIO_Pin_8			//蜂鸣器
#define PW				GPIO_Pin_9			//3.3输出

//PC	输入端口
#define K1				GPIO_Pin_0			//K1
#define K2				GPIO_Pin_1			//K2
#define K3				GPIO_Pin_2			//K3
#define K4				GPIO_Pin_3			//K4
#define IN1				GPIO_Pin_10			//输入口1
#define IN2 			GPIO_Pin_11			//输入口2
#define IN3				GPIO_Pin_12			//输入口3

#define IN	0
#define OUT 1
#define RX	0
#define TX	1
/**/

/***应用程序变量***/
extern u16 timer[3],lt_value,flt_value;
extern u8 action_state[3];
/**/

/***事件标志量***/
extern u8 lt_led_config,flt_led_config,lc_config;
/**/

/***应用程序函数申明***/
extern __task void Init_task(void);
extern void app_sys_led(void);
extern void app_key(void);
extern void app_sericom(void);
extern void app_sound(void);
extern void app_sms(void);
extern void app_485(void);
extern void power_control(u8 state);

/**/

#endif

// ****************<<< Use Configuration Wizard in Context Menu >>>********************
// <h>主板晶振选择
//		<o>晶振频率 HSE_VALUE <8000000=>8000000 <12000000=>12000000
//		<i>default: 8000000
#ifdef HSE_VALUE
	#undef HSE_VALUE 
#endif
#ifndef HSE_VALUE
	#define HSE_VALUE 12000000
#endif
// </h>

//<h>系统时间基准
//		<o>系统最小时间选择(保证系统运行在1ms基准)   单位：ms	T <1=>1 <10=>0.1
//		<i>default:1
#ifndef	T
	#define T	1
#endif
//</h>

//<h>关机提示时间
//		<o>时间参数	PDT <5-200>
//		<i>default: 5
#ifndef PDT
	#define PDT	5
#endif
//</h>

//<h>自动锁定时间
//		<o>时间参数：LCT <1-200>
//		<i>default:5
#ifndef LCT
	#define LCT 5
#endif
//</h>

//<h>信号消息扫描的周期
//		<o>周期时间：SMS_Time <1-1000>
//		<i>default:100
#ifndef SMS_Time
	#define SMS_Time	1
#endif
//</h>

// **********************<<< end of configuration section >>>**************************

/***end of the file***/
