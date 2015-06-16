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

/***�������Ͷ���***/
typedef struct
{
	char *cgmm;			//ģ���ͺ�
	char *cgmr;			//ģ��̼��汾
	char *cops;			//ע�����
	char *cimi;			//CIMIֵ
	char *csq;			//�ź�ǿ��
	char *cpas;			//ģ��״̬
	char *copn;			//��Ӫ������
	char *gps;			//GPS״̬
} GPRS_status;

typedef struct
{
	char *date;					//����
	char *time;					//ʱ��
	char *coordinate;		//����
	char *speed;				//�ٶ�
	char *direction;		//����
} GPS_data;

/***��������***/
//gps_gprs.c
extern GPRS_status deal_data(char *s);
extern GPRS_status gps_gprs_init(void);
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
