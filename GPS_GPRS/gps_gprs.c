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
u8 x808_cmd_send(u8 *p)
{
	u8 count=0,bf;
	char s2[20]="at+";
	while(gps_gprs_cmd_state(2)!=0)
	{
		x808_delay(1);
		count++;if(count>5)return 0;			//�ȴ���ʱ������0
	}
	gps_gprs_cmd_state(1);
	memcpy(s2+3,p,strlen((char *)p));
	x808_send(s2);
	count=0;
	while(1)
	{
		bf=get_status(2);
		if(bf==2)
		{
			x808_delay(1);
			count++;if(count>10)return 3;		//��������ҶԷ�δ���գ�����3
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
	char *str=NULL;
	
	len=strlen(p);
	memcpy(cmd,p,len);
	if(strncmp(cmd,"at+",3)!=0)return 0;											//��ָ������ݣ�����0
	memset(cmd,0,len);
	memcpy(cmd,p-4,4);
	if(strncmp(cmd,"OK",2)!=0){get_status(0);gps_gprs_cmd_state(0);return 10;}			//ָ��ִ�д��󣬷���10
	memset(cmd,0,4);
	len=get_enter_lacation(p,1)-3;
	memcpy(cmd,p+3,len);
	if(strncmp(cmd,"cgpsout",7)==0)							//gps�Զ����
		return 1;
	dr=get_blank_lacation(p);
	if(dr==0){																	//�޿ո�����
		len=get_enter_lacation(p,2)-(get_enter_lacation(p,1)+3);
		memcpy(bf,(p+get_enter_lacation(p,1)+3),len);}
	else{																				//�пո�����
		len=get_enter_lacation(p,2)-(get_blank_lacation(p)+1);
		memcpy(bf,(p+get_blank_lacation(p)+1),len);}
	discern_cmd_type(cmd,bf);											//����ָ������
	
	
	return 1;
}


/***��ȡ��Ϣ���ݷ���***/
u8 *get_messege(char *data)
{
	u8 i,l=0,j=0,d[2];
	memset(d,0,2);
	l=strlen(data)-1;
	u8 messege[l];
	u8 *p=messege;
	memset(messege,0,l);
	for(i=0;i<l;i++)
	{
		if(data[i]==0x0a)		//���س�
		{
			d[j]=i;j++;
			if(j>1)
				break;
		}
	}
	memcpy(messege,data+d[0],d[1]-d[0]-1);
	return p;
}

/***����ָ��ظ���Ϣ***/
/*
GPRS_status deal_data(char *s)
{
	GPRS_status	status={0,0,0,0,0,0,0};
	u8 data[100];
	memset(data,0,100);
	rt_485(USART2,data,100);
		if(strcmp("cgmm",s)==0)			//ģ���ͺ�
		{
			if(get_status(data)==OK)
				status.cgmm=(char *)get_messege("cgmm");
			else
				status.cgmm="error";
		}
		else if(strcmp("cgmr",s)==0)		//ģ��̼�
		{
			if(get_status(data)==OK)
				status.cgmr=(char *)get_messege("cgmr");
			else
				status.cgmr="error";
		}
		else if(strcmp("cops",s)==0)		//SIM��ע�����
		{
			if(get_status(data)==OK)
				status.cops=(char *)get_messege("cops");
			else
				status.cops="error";
		}
		else if(strcmp("cimi",s)==0)		//SIM��CIMIֵ
		{
			if(get_status(data)==OK)
				status.cimi=(char *)get_messege("cimi");
			else
				status.cimi="error";
		}
		else if(strcmp("csq",s)==0)		//�ź�ǿ��
		{
			if(get_status(data)==OK)
				status.csq=(char *)get_messege("csq");
			else
				status.csq="error";
		}
		else if(strcmp("cpas",s)==0)		//ģ��״̬
		{
			if(get_status(data)==OK)
				status.cpas=(char *)get_messege("cpas");
			else
				status.cpas="error";
		}
		status.cops="�й���ͨ/�й��ƶ�";
		
		return status;
}
*/

/***GPRSģ���ʼ��***/
GPRS_status gps_gprs_init(void)
{
	GPRS_status gprs_status;
	u8 data[100];
	memset(data,0,100);
	usart_send_str(USART2,"at+cgmm");

	return gprs_status;
}

/***end of the file***/
