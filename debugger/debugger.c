/******************************************************************************************************************

																								         debugger.c
																								designed for debugging  test C code
																								     2014-10-13 11:34:45
																								         by lunanting

******************************************************************************************************************/

#include "stdarg.h"
#include "module.h"

/***�ɱ������ƴ���ԭ��***/
/*
��������˵�����ɱ�������͵ĺ�������ʵ�ֲ��������βκ�����
�βθ�ʽ��type �βΣ�...��
���ܣ��������������ͬһ������һ���Ա��ʵ�֣���ʵ�ֿɱ��βε�ʵ�֣�

*/
void va_func(int start,...)
{
	va_list arg_ptr;
	int nArgValue=start;
	int nArgCout=0;
	va_start(arg_ptr,start);
	do
	{
		++nArgCout;
		/****
		ִ�д���
		****/
		nArgValue=va_arg(arg_ptr,int);
	}
	while(nArgValue!=-1);
	return;
}
/***end***/

// void TIM_init(TIM_TypeDef* TIMx,...)
// {
// 	va_list arg_ptr;
// 	TIM_TypeDef* nArgValue=TIMx;
// 	TIM_TypeDef* nArgCout=0;
// 	va_start(arg_ptr,TIMx);
// 	do
// 	{
// 		++nArgCout;
// 		/****
// 		ִ�д���
// 		****/
// 		nArgValue=va_arg(arg_ptr,TIM_TypeDef);
// 		memcpy(nArgValue,va_arg(arg_ptr,TIM_TypeDef),sizeof(TIM_TypeDef));
// 	}
// 	while(nArgValue!=-1);
// 	return;
// }



/***end of the file***/
