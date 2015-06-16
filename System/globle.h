/****************************************************************************************
																								globle.h
																				designed for the project
																					2014-08-30 16:55:51
																							by lunanting

*****************************************************************************************/
#ifndef __GLOBLE_H
#define __GLOBLE_H

#include "module.h"

/***全局宏定义***/
#ifdef NM_VALUE_GLOBLE
#define NM_VALUE_EXT
#else
#define NM_VALUE_EXT	extern
#endif


/***定义常量***/

typedef struct {
	u16 yy;
	u16 wj;
	u16 yj;
	u16 jb;
} COIN;

extern COIN	refresh;
#endif
//end of the file
