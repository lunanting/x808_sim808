/************************************************************************************************************
gps_gprs_lib.c
designed for the gps/gprs servers
2015-06-10 15:37:28
designed by lunanting
************************************************************************************************************/

#include "gps_gprs.h"


/***��������״̬***/
/********************************
����ֵ:	  0		�����ڲ���ָ��
					1		��ָ�����ڲ���
					10	ʵ�θ�������
					*****************
�βΣ�rw		0		д���޲���״̬
					1		д���в���״̬
					2		���˿̲���״̬
					*****************
���ã���������ִ�С�����ʱ�������ٷ���ָ�Ӧ����ָ���ͻ
********************************/
u8 gps_gprs_cmd_state(u8 rw)
{
	static u8 state;
	
	if(state>2)return 10;
	if(state==2)return state;
	state=rw;
	
	return state;
}


/***��ȡָ��״̬***/
/*******************************
����ֵ��			0��	ERROR
						1��	OK
						2:	δ����
						*****************
�βΣ�s			0:	д��״̬0
						1��	д��״̬1
						2��	��ȡ״̬
���ã�ȷ��ָ��ִ��״̬
*******************************/
u8 get_status(u8 s)
{
	static u8 state=2;
	u8 bf;
	if(s>1){bf=state;state=2;return bf;}
	else{state=s;return state;}
}


/***gprs״̬��Ϣά��***/
/**************************************
����ֵ��state		״̬��Ϣ
								**********************
�βΣ�	*p				����д��/��ȡ��ŵ���״̬��Ϣָ��
			*c				д״̬��־	��'cgmm'��
								"read":	��ȡ����
								**********************
���ã���ΪGPRS״̬��Ϣ���������ģ����������״̬��
Ϣ�������µģ��ҿɱ���ʱ��ȡ��
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


/***gps������Ϣά��***/
/****************************************
����ֵ��data			gps������Ϣ
								**********
�βΣ�*p					����������
								**********
���ã���Ϊgps������Ϣ�������ģ�������������������µ�
�ҿ���ʱ����ȡ
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


/***��ȡOD�ַ�λ��****/
/****************************************
����ֵ��dr				0D���ַ����е�λ��
								*****************
�βΣ�	*p				����ѯ���ַ���
			n					��ѯ��N��OD��λ��
								*****************
���ã���ȡ�ַ����еĻس�λ��
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


/***�ո���***/
/******************************************
����ֵ��dr				�ո����ַ����е�λ��
								*******************
�βΣ�	*p				�������ַ���
								*******************
���ã�����ַ������Ƿ��пո񣬲�������λ��
******************************************/
u8 get_blank_lacation(char *p)
{
	u8 dr=0,i;
	for(i=0;i<strlen(p);i++){
		if(*(p+i)==0x20){dr=i;return dr;}}
	return dr;
}



/***�ֱ����ݹ����������ͣ�������������***/
/******************************************
����ֵ��str				ָ������ָ��
									***********
�βΣ�*p						������ַ���
									***********
���ã����ָ������
******************************************/
void discern_cmd_type(char *p,char *data)
{
	//ģ��gprs״̬
	if(strncmp(p,"cgmm",4)==0)gprs_state(data,"cgmm");
	else if(strncmp(p,"cgmr",4)==0)gprs_state(data,"cgmr");
	else if(strncmp(p,"cimi",4)==0)gprs_state(data,"cimi");
	else if(strncmp(p,"copn",4)==0)gprs_state(data,"copn");
	else if(strncmp(p,"cops",4)==0)gprs_state(data,"cops");
	else if(strncmp(p,"cpas",4)==0)gprs_state(data,"cpas");
	else if(strncmp(p,"csq",3)==0)gprs_state(data,"csq");
	//ģ��gps״̬
	else if(strncmp(p,"cgpsstatus",10)==0)gprs_state(data,"gps");
	else if(strncmp(p,"cgpsinf",7)==0)gps_data(data);
	return ;
}





/***����ָ������***/
/******************************************


******************************************/
void dispose_cmd_data(char *tp,char *data)
{
	
}

/************************************x808ģ�������ӿ�************************************************/
/***��ʱ�ӿ�***/
/*****************************
�βΣ�dt		��ʱ��������λms
					***************
���ã�Ϊͨ��ģ��������ʵ����ʱ���ܵķ���
*****************************/
void x808_delay(u32 dt)
{
	os_dly_wait(dt);
}

/***����ͨ�Žӿ�***/
/***************************
�βΣ�*s			�������ַ���
						***************
���ã�Ϊͨ��ģ��������ʵ�� ͨ�Ź��ܵķ���
***************************/
void x808_send(char *s)
{
	usart_send_str(X808,s);
}

/***end of the file***/
