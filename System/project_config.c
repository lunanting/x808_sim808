/***********************************************************************************************************************

																												project_config.c
																										designed for the project
																											2014-10-13 10:37:27
																												 by lunanting

***********************************************************************************************************************/
/***project_config.c文件说明**************************************
本配置文件主要用于工程参数的配置
主要有两个方面：1.主板是晶振的配置 
								2.工程标准参数的配置
								
此配置文件使用了configuration wirzard格式书写，
可直接使用配置页面进行配置。
***************end***********************************************/

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

// <h>硬币标准电压参数配置  单位：mv
//		<o>1元参数上限 YYMAX <1000-10000>
//		<i>default: 6300
#ifndef YYMAX
	#define YYMAX 6050
#endif
//		<o>1元参数下限 YYMIN <1000-10000>
//		<i>default: 5700
#ifndef YYMIN
	#define YYMIN 5400
#endif
//		<o>5角参数上限 WJMAX <1000-10000>
//		<i>default: 5600
#ifndef WJMAX
	#define WJMAX 5100
#endif
//		<o>5角参数下限 WJMIN <1000-10000>
//		<i>default: 5100
#ifndef WJMIN
	#define WJMIN 4600
#endif
//		<o>1角参数上限 YJMAX <1000-10000>
//		<i>default: 5600
#ifndef YJMAX
	#define YJMAX 5100
#endif
//		<o>1角参数下限 YJMIN <1000-10000>
//		<i>default: 5100
#ifndef YJMIN
	#define YJMIN 4600
#endif
// </h>

// <h>硬币标准直径参数配置（时间） 单位：0.1ms
//		<o>1元参数上限 YYTMAX <30-100>
//		<i>default: 70
#ifndef YYTMAX
	#define YYTMAX 70
#endif
//		<o>1元参数下限 YYTMIN <30-100>
//		<i>default: 63
#ifndef YYTMIN
	#define YYTMIN 63
#endif
//		<o>5角参数上限 WJTMAX <30-100>
//		<i>default: 54
#ifndef WJTMAX
	#define WJTMAX 54
#endif
//		<o>5角参数下限 WJTMIN <30-100>
//		<i>default: 47
#ifndef WJTMIN
	#define WJTMIN 47
#endif
//		<o>1角参数上限 YJTMAX <30-100>
//		<i>default: 46
#ifndef YJTMAX
	#define YJTMAX 46
#endif
//		<o>1角参数下限 YJTMIN <30-100>
//		<i>default: 40
#ifndef YJTMIN
	#define YJTMIN 40
#endif
// </h>


// ***********************<<< end of configuration section >>>************************

/***end of the file***/
