/***************************************************************************************************************************
																													 task.c
																											designed for the project
																												2014-08-28 23:18:02
																													by lunanting
																	  
**************************************************************************************************************************/
#define NM_VALUE_GLOBLE

#include "module.h"


volatile u32 count=0,u1_count=0,value_count=0;
volatile u8 b_kind=0,coin_kind[5];
u16 adc_value=0,limitup=0,adc_value1;
u16 view_value=0,view_detial[5][53];
char view_send[10];
u8 add_count=0,view_i=0,view_j=0,u1rec_buff[20],u1rec_i=0,send_config=1;
u16 t1=0,t2=0,i=0;
// COIN	refresh;

 COIN	refresh={
	0,
	0,
	0,
	0
};


OS_SEM adcsem;
OS_SEM iosem;
OS_SEM resultsem;
OS_SEM rfsem;
OS_SEM jbsem;
OS_SEM u1recsem;


/*RTX系统初始化*/
__task void Init_task(void)
{
	os_tsk_prio_self (100);				//提升自身优先级  	
	
  os_tsk_create (led_test_task,3);
	os_tsk_create (send_result,4);
// 	os_tsk_create (upload_refresh_data,5);
	os_tsk_create(single_jb,6);
	os_tsk_create(u1recive,3);
 	os_tsk_create (io_keep_time,8);
	os_tsk_create (get_adc_value,8);
	
	
	os_tsk_delete_self();	
}

/***接收ad转换数据 读取传感器数值 测量硬币种类***/
__task void get_adc_value(void)
{
	u8 bf=0,read_flash[2],dia_b=0,n;
	u16 adc_data=0,clear_config=0;
	u32 adc_buff=0;
	
	os_sem_init(adcsem,0);
	memset(view_detial,0,530);
	memset(view_send,0,10);
	memset(read_flash,0,4);
	ReadFlashNByte(0,read_flash,2);
	limitup=read_flash[0]+read_flash[1]*256;
	if(limitup==0||limitup==0xffff)
		limitup=7500;
	while(1)
	{
// 		os_sem_wait(adcsem,0xffff);
		while(1)
		{
			adc_value1=spi_readwrite_byte(SPI1,adc_data);
			adc_value=change_data(adc_value1);
			if((1000<adc_value&&adc_value<7500))
				break;
			clear_config++;
			if(clear_config==50000)
			{
				clear_config=0;
				memset(&refresh,0,8);
				i=0;								//5秒种没有硬币就将计数清零
			}
			os_dly_wait(1);
		}
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		os_sem_send(iosem);
		TIM_Cmd(TIM4,ENABLE);
		value_count=0;
// 		while(add_count<25)
// 		{
			while(adc_value<7500)
	// 		while(1)
			{
				adc_buff=adc_buff+adc_value;
				add_count++;													//采样次数   0.2ms一次
				view_detial[view_i][add_count]=adc_value;
				os_dly_wait(1);
				adc_value=spi_readwrite_byte(SPI1,adc_data);
				adc_value=change_data(adc_value);
	// 			if(count==50)
	// 				break;
				if(add_count==49)
					break;
			}
// 		}
// 		view_detial[view_i][add_count+2]=count;		//view_detial数据位后面第二位是金属传感器检测的时间
// 		count=0;
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		adc_buff=adc_buff/add_count;
		if(add_count>20)
		{
			dia_b=(add_count/2)-2;
			adc_buff=0;
			for(n=0;n<5;n++)
				adc_buff=view_detial[view_i][dia_b+n]+adc_buff;
			adc_buff=adc_buff/5;
		}
		else
			adc_buff=8888;
//调试看数据
		view_detial[view_i][0]=add_count;			//对金属传感器采样的详细数据个数
		view_detial[view_i][add_count+1]=adc_buff;		//view_detial数据位后面第一位是对金属传感器采样得到数据的平均值
//*** 		
 		coin_kind[bf]=deal_value(adc_buff);					//比较金属传感器的电压值，得出币种
// 		if(view_detial[view_i][10]>6000)
// 			coin_kind[bf]=0;
		view_i++;
		if(view_i==5)
			view_i=0;
		bf++;
		if(bf==5)
			bf=0;
		adc_buff=0;
		add_count=0;
		clear_config=0;
		
// 		os_sem_send(iosem);
// 		os_sem_send(resultsem);
	}
}


/***读取IO状态  对IO特定状态计时 测量硬币直径***/
__task void io_keep_time(void)
{
	u8 bf=0,n=0;
	os_sem_init(iosem,0);

	while(1)
	{
 		os_sem_wait(iosem,0xffff);
/***光钎传感器  测直径***/
		while(1)
		{
			if(get_diasensor_state()==0)
			{
				TIM_Cmd(TIM2,ENABLE);
				TIM_Cmd(TIM4,DISABLE);
				value_count=0;
				break;
			}
			iotask_overtime();
			os_dly_wait(1);
		}
		while(1)
		{
			if(get_diasensor_state()==1)
			{
				TIM_Cmd(TIM2,DISABLE);
				n=view_detial[view_j][0];
				view_detial[view_j][n+2]=count;		//view_detial数据位后面第三位是光钎传感器测得的时间
				t2=count;
				count=0;
				break;
			}
			os_dly_wait(1);
		}
	/***  ***/		
			if(coin_kind[bf]!=0)
			{
				if(coin_kind[bf]==1&&deal_time(t2)==1)
					coin_kind[bf]=1;			//比较通过时间长度 得出币种
				else if(coin_kind[bf]==2&&deal_time(t2)>1)
				{
					coin_kind[bf]=deal_time(t2);
				}
				else
					coin_kind[bf]=0;
			}
			b_kind=coin_kind[bf];
			bf++;
			if(bf==5)
				bf=0;
			view_detial[view_j][n+3]=b_kind;
			view_j++;
			if(view_j==5)
				view_j=0;
			deal_coin(b_kind);
// 			b_kind=0;
			if(b_kind==0)
				os_sem_send(jbsem);
	// 		no_i=0;
	// 		os_sem_send(rfsem);		
			os_sem_send(resultsem);
	}
}

/***usart1.2发送数据   将测量结果提供给主板***/
__task void send_result(void)
{
	u8 j=0;
	u8 send_i=0;
	os_sem_init(resultsem,0);
	
	while(1)
	{
		os_sem_wait(resultsem,0xffff);
		if(send_config==1)
		{
			for(j=view_detial[send_i][0]+1;j<view_detial[send_i][0]+4;j++)
			{
				itoa(view_detial[send_i][j],view_send,10);
				usart_send_str(USART1,view_send);
				usart_send_str(USART1," ");
			}
		}
/***      ***/
		else
		{
			itoa(refresh.yy,view_send,10);
			usart_send_str(USART1,view_send);
			usart_send_str(USART1," ");
			itoa(refresh.wj,view_send,10);
			usart_send_str(USART1,view_send);
			usart_send_str(USART1," ");
			itoa(refresh.yj,view_send,10);
			usart_send_str(USART1,view_send);
			usart_send_str(USART1," ");
			itoa(refresh.jb,view_send,10);
			usart_send_str(USART1,view_send);
			usart_send_str(USART1," ");
		}
/*******/
		
// 		usart_send_str(USART1," ");
// 		itoa(t1,view_send,10);
// 		usart_send_str(USART1,view_send);
		
// 		usart_send_str(USART1," ");
// 		itoa(t2,view_send,10);
// 		usart_send_str(USART1,view_send);
		
/***调试  计数***/
		memset(view_detial[send_i],0,106);	
		send_i++;
		if(send_i==5)
			send_i=0;
		i++;
		itoa(i,view_send,10);
		usart_send_str(USART1," ");
		usart_send_str(USART1,view_send);
/***  ***/

		memset(view_send,0,10);
		usart_send_enter(USART1);
		
	}
}

/***上传测量数据任务   100ms上传一次***/
__task void upload_refresh_data(void)
{
	u16 data[4];
	
	os_sem_init(rfsem,0);
	memset(data,0,8);
	
	while(1)
	{
		os_sem_wait(rfsem,0xffff);
		
		data[0]=refresh.yy;
		data[1]=refresh.wj;
		data[2]=refresh.yj;
		data[3]=refresh.jb;
		usart_send_data(USART2,(u8 *)data,4);
		
		os_dly_wait(1000);	
		os_sem_init(rfsem,0);
	}
}


/***假币报警***/
__task void single_jb(void)
{
	os_sem_init(jbsem,0);
	
	while(1)
	{
		os_sem_wait(jbsem,0xffff);
		give_single_state(0);
		os_dly_wait(30);
		give_single_state(1);
	}
}

__task void u1recive(void)
{
// 	char str[20],*s="hello,word!";
	u16 limit=0;
	
	os_sem_init(u1recsem,0);
	memset(u1rec_buff,0,20);
// 	memset(str,0,20);
	default_setting(send_config);
	while(1)
	{
		analyze_u1rec_command(&send_config,&limit);
		if(limit!=0)
			limitup=limit;
		os_dly_wait(1000);
	}
}


/***end of the file***/
