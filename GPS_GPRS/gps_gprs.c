/**************************************************************************************************
gps_gprs.c
designed by lunanting
2015-06-09 10:49:31
designed for opration of GPS_GPRS module
**************************************************************************************************/

#include "gps_gprs.h"




/***����ָ���***/
/**************************************
�Ż�ֵ��			0		�ȴ�����ָ����ɳ�ʱ
						1		���ͳɹ���ָ��ִ�д���
						2		������ɣ�ָ��ִ����ȷ
						3		���ͳɹ������Է�δ����
						*************************
�βΣ�*p			����ָ�����
						*************************
���ã���Ҫ����״̬��Ϣ��ָ��
**************************************/
u8 x808_cmd_send(char *p)
{
	u8 count=0,bf;
	char s2[30]="at+";
	while(gps_gprs_cmd_state(2)!=0)
	{
		x808_delay(1);
		count++;if(count>200)return 0;			//�ȴ���ʱ������0
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
			count++;if(count>100)return 3;	//��������ҶԷ�δ���գ�����3
		}
		else if(bf==1)return 2;						//�����������ȷִ�У�����2
		else if(bf==0)return 1;					  //�������ȴִ�д��󣬷���1
	}
}


/***��������***/
/******************************
����ֵ��				0��	����Ϊ��ָ�������
							1��	ָ����������ָ����ȷִ��
							10��ָ����������ָ��ִ�д���
							****************************
�βΣ�*p				��ģ����յ�����
							****************************
���ã�������x808ͨ�Ž��յ�����
******************************/
u8 x808_cmd_parsing(char *p)
{
	char bf[100]={NULL},cmd[15]={NULL};;u8 len=0,dr=0;
//	char *str=NULL;
	
	len=strlen(p);
	memcpy(cmd,p,len);
	if(strncmp(cmd,"at+",3)!=0)return 0;					//��ָ������ݣ�����0
	memset(cmd,0,len);
	memcpy(cmd,p-4,4);
	if(strncmp(cmd,"OK",2)!=0){get_status(0);gps_gprs_cmd_state(0);return 10;}			//ָ��ִ�д��󣬷���10
	len=get_enter_lacation(p,1)+3;
	if((strlen(p)-len)<5){get_status(1);gps_gprs_cmd_state(0);return 1;}						//ָ����ȷִ�У�����1
	memset(cmd,0,4);
	len=get_enter_lacation(p,1)-3;
	memcpy(cmd,p+3,len);
	if(strncmp(cmd,"cgpsout",7)==0)return 1;			//gps�Զ����
	dr=get_blank_lacation(p);
	if(dr==0){																		//�޿ո�����
		len=get_enter_lacation(p,2)-(get_enter_lacation(p,1)+3);
		memcpy(bf,(p+get_enter_lacation(p,1)+3),len);}
	else{																					//�пո�����
		len=get_enter_lacation(p,2)-(get_blank_lacation(p)+1);
		memcpy(bf,(p+get_blank_lacation(p)+1),len);}
	discern_cmd_type(cmd,bf);											//����ָ�����Ͳ���������
	
	get_status(1);
	return 1;
}



/***GPRSģ���ʼ��***/
u8 x808_init(void)
{
	u8 state=0;
	u8 data[100];
	memset(data,0,100);
	state=x808_cmd_send("cgmm");					//gprs����״̬��Ϣ
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
	
	state=x808_cmd_send("cgpspwr=1");			//gps����״̬��Ϣ
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cgpsstatus?");
	if(state==3||state==0)return 0;
	
	state=x808_cmd_send("cmgf=1");				//sms����״̬��Ϣ
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cpms=\"sm\",\"sm\",\"sm\"");
	if(state==3||state==0)return 0;
	state=x808_cmd_send("cnmi=2,1");
	if(state==3||state==0)return 0;

	return 1;
}



/***���Ͷ��Ź���***/
/******************************************
����ֵ��state			��Ϣ���ͽ��
									************
�βΣ�*str 				��Ϣ����
			*num				��ϢĿ�����
									************
���ã����Ͷ�����Ϣ
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
