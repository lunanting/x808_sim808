/**************************************************************************************************************************
task_list.c
designed for  all application of the project
2015-03-05 10:36:21
designed by lunanting
**************************************************************************************************************************/
/*����޸�ʱ�䣺
2015-03-10 10:41:24
*/
#include "app.h"

extern void app_sys_led(void);
/***�����ʼ��**/
__task void Init_task(void)
{
	os_tsk_prio_self (100);				//�����������ȼ� 
	
  __task void sys_led(void);
	os_tsk_create(sys_led,1);
	
	__task void task2(void);
	os_tsk_create(task2,2);
	
		__task void task3(void);
	os_tsk_create(task3,3);
	
	__task void task5(void);
	os_tsk_create(task5,5);
	
	__task void task6(void);
	os_tsk_create(task6,1);
	
	__task void task7(void);
	os_tsk_create(task7,5);
	
	
	
	os_tsk_delete_self();							//��ɾ
}

/***�����***/
__task void sys_led(void)
{
	app_sys_led();
}
__task void task2(void)
{
	app_sound();
}

__task void task3(void)
{
	app_sms();
}

__task void task4(void)
{
	
}

__task void task5(void)
{
	app_key();
}

__task void task6(void)
{
	app_sericom();
}

__task void task7(void)
{
	app_485();
}

__task void task8(void)
{
	
}


__task void task9(void)
{
	
}

__task void task10(void)
{
	
}


__task void task11(void)
{
	
}

__task void task12(void)
{
	
}

/***end of the file***/
