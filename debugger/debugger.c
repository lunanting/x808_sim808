/******************************************************************************************************************

																								         debugger.c
																								designed for debugging  test C code
																								     2014-10-13 11:34:45
																								         by lunanting

******************************************************************************************************************/

#include "stdarg.h"
#include "module.h"

/***可变参数设计代码原型***/
/*
函数功能说明：可变参数类型的函数可以实现不定个数形参函数；
形参格式：type 形参，...；
功能：在做多参数调用同一个函数一次性便捷实现，或实现可变形参的实现；

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
		执行代码
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
// 		执行代码
// 		****/
// 		nArgValue=va_arg(arg_ptr,TIM_TypeDef);
// 		memcpy(nArgValue,va_arg(arg_ptr,TIM_TypeDef),sizeof(TIM_TypeDef));
// 	}
// 	while(nArgValue!=-1);
// 	return;
// }



/***end of the file***/
