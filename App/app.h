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



/***�߳��ź�������***/
extern OS_SEM u1recsem,sound;

/**/

/***Ӧ�ó�����***/
//PA	����˿�
#define DIR_485		GPIO_Pin_1			//485����
#define CS_AD			GPIO_Pin_4			//ADоƬƬѡ
#define CS_DA			GPIO_Pin_8			//DAоƬƬѡ
#define RED_LED		GPIO_Pin_11			//���	����
#define SYS_LED		GPIO_Pin_12			//ϵͳ����ָʾ��

//PB	����˿�
#define IN4				GPIO_Pin_3			//�����4
#define OUT1			GPIO_Pin_4			//���1
#define OUT2			GPIO_Pin_5			//���2
#define OUT3			GPIO_Pin_6			//���3
#define OUT4			GPIO_Pin_7			//���4
#define BELL			GPIO_Pin_8			//������
#define PW				GPIO_Pin_9			//3.3���

//PC	����˿�
#define K1				GPIO_Pin_0			//K1
#define K2				GPIO_Pin_1			//K2
#define K3				GPIO_Pin_2			//K3
#define K4				GPIO_Pin_3			//K4
#define IN1				GPIO_Pin_10			//�����1
#define IN2 			GPIO_Pin_11			//�����2
#define IN3				GPIO_Pin_12			//�����3

#define IN	0
#define OUT 1
#define RX	0
#define TX	1
/**/

/***Ӧ�ó������***/
extern u16 timer[3],lt_value,flt_value;
extern u8 action_state[3];
/**/

/***�¼���־��***/
extern u8 lt_led_config,flt_led_config,lc_config;
/**/

/***Ӧ�ó���������***/
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
// <h>���徧��ѡ��
//		<o>����Ƶ�� HSE_VALUE <8000000=>8000000 <12000000=>12000000
//		<i>default: 8000000
#ifdef HSE_VALUE
	#undef HSE_VALUE 
#endif
#ifndef HSE_VALUE
	#define HSE_VALUE 12000000
#endif
// </h>

//<h>ϵͳʱ���׼
//		<o>ϵͳ��Сʱ��ѡ��(��֤ϵͳ������1ms��׼)   ��λ��ms	T <1=>1 <10=>0.1
//		<i>default:1
#ifndef	T
	#define T	1
#endif
//</h>

//<h>�ػ���ʾʱ��
//		<o>ʱ�����	PDT <5-200>
//		<i>default: 5
#ifndef PDT
	#define PDT	5
#endif
//</h>

//<h>�Զ�����ʱ��
//		<o>ʱ�������LCT <1-200>
//		<i>default:5
#ifndef LCT
	#define LCT 5
#endif
//</h>

//<h>�ź���Ϣɨ�������
//		<o>����ʱ�䣺SMS_Time <1-1000>
//		<i>default:100
#ifndef SMS_Time
	#define SMS_Time	1
#endif
//</h>

// **********************<<< end of configuration section >>>**************************

/***end of the file***/
