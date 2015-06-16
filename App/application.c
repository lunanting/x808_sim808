/*****************************************************************************************************
application.c
designed for the project
2015-03-05 13:24:33
designed by lunanting
****************************************************************************************************/
/*最后修改时间：
2015-03-10 10:40:01
*/

#include "app.h"

u8 action_state[3],lt_led_config=0,flt_led_config=0,lc_config=0;
u16 timer[3],lt_value=0,flt_value=0;



void app_sys_led(void)
{
	u8 sys_led_state=1;
	os_dly_wait(1000);
	signal_state(0);
	power_control(0);
	
	while(1)
	{
		switch(sys_led_state)
		{
			case 0:
				sys_led_state=1;sys_state(1);os_dly_wait(50);break;
			case 1:
				sys_led_state=0;sys_state(0);os_dly_wait(1950);break;
		}
	}
}


void app_key(void)
{
	u8 key_state[8],key_value[8],i,power_state=0;
	memset(key_state,0,8);
	memset(key_value,0,8);
	
	while(1)
	{
		key_get(key_state,key_value);
		for(i=0;i<4;i++)
		{
			if(key_value[i]==1)
			{
				switch(i)
				{
					case 0:
					{
						if(power_state==0){
							power_control(1);power_state=1;}
						else if(power_state==1){
							power_control(0);power_state=0;}
						sound_control(1);break;
					}
						
				}
			}
		}
		memset(key_value,0,8);
		os_dly_wait(1);
	}
	
}

void app_sericom(void)
{
	os_sem_init(u1recsem,0);
	memset(u1rec_buff,0,20);
	
	default_setting(3);
	while(1)
	{
// 		os_sem_wait(u1recsem,0xffff);
		analyze_u1rec_command();
		os_dly_wait(1);
	}
}

void app_485(void)
{
	while(1)
	{
//		analyze_485();
		os_dly_wait(1);
	}
}

void app_sound(void)
{
	os_sem_init(sound,0);
	
	while(1)
	{
		os_sem_wait(sound,0xffff);
		os_dly_wait(50*T);
		sound_control(0);
	}
}

void app_sms(void)
{
	memset(timer,0,6);
////	app_io(OUT,1,OUT1);
//	app_io(OUT,1,OUT2);
//	app_io(OUT,1,OUT3);
//	app_io(OUT,1,OUT4);
	while(1)
	{
		test_io();
		if(app_io(IN,0,IN1)!=0)				//调试模式
		{
			action_state[2]=1;
			if(lt_value==0)
				lt_value=180;
			app_spi(0,lt_value);
		}
		else
			action_state[2]=0;
		os_dly_wait(SMS_Time*T);
	}
}
/***end of the file***/
