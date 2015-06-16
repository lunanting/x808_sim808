/***********************************************************************************************************************

																												project_config.c
																										designed for the project
																											2014-10-13 10:37:27
																												 by lunanting

***********************************************************************************************************************/
/***project_config.c�ļ�˵��**************************************
�������ļ���Ҫ���ڹ��̲���������
��Ҫ���������棺1.�����Ǿ�������� 
								2.���̱�׼����������
								
�������ļ�ʹ����configuration wirzard��ʽ��д��
��ֱ��ʹ������ҳ��������á�
***************end***********************************************/

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

// <h>Ӳ�ұ�׼��ѹ��������  ��λ��mv
//		<o>1Ԫ�������� YYMAX <1000-10000>
//		<i>default: 6300
#ifndef YYMAX
	#define YYMAX 6050
#endif
//		<o>1Ԫ�������� YYMIN <1000-10000>
//		<i>default: 5700
#ifndef YYMIN
	#define YYMIN 5400
#endif
//		<o>5�ǲ������� WJMAX <1000-10000>
//		<i>default: 5600
#ifndef WJMAX
	#define WJMAX 5100
#endif
//		<o>5�ǲ������� WJMIN <1000-10000>
//		<i>default: 5100
#ifndef WJMIN
	#define WJMIN 4600
#endif
//		<o>1�ǲ������� YJMAX <1000-10000>
//		<i>default: 5600
#ifndef YJMAX
	#define YJMAX 5100
#endif
//		<o>1�ǲ������� YJMIN <1000-10000>
//		<i>default: 5100
#ifndef YJMIN
	#define YJMIN 4600
#endif
// </h>

// <h>Ӳ�ұ�׼ֱ���������ã�ʱ�䣩 ��λ��0.1ms
//		<o>1Ԫ�������� YYTMAX <30-100>
//		<i>default: 70
#ifndef YYTMAX
	#define YYTMAX 70
#endif
//		<o>1Ԫ�������� YYTMIN <30-100>
//		<i>default: 63
#ifndef YYTMIN
	#define YYTMIN 63
#endif
//		<o>5�ǲ������� WJTMAX <30-100>
//		<i>default: 54
#ifndef WJTMAX
	#define WJTMAX 54
#endif
//		<o>5�ǲ������� WJTMIN <30-100>
//		<i>default: 47
#ifndef WJTMIN
	#define WJTMIN 47
#endif
//		<o>1�ǲ������� YJTMAX <30-100>
//		<i>default: 46
#ifndef YJTMAX
	#define YJTMAX 46
#endif
//		<o>1�ǲ������� YJTMIN <30-100>
//		<i>default: 40
#ifndef YJTMIN
	#define YJTMIN 40
#endif
// </h>


// ***********************<<< end of configuration section >>>************************

/***end of the file***/
