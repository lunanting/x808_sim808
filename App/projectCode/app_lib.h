/*****************************************************************************************************
app_lib.h
designed for the application
2015-03-09 13:41:09
by lunanting
*****************************************************************************************************/

#ifndef __APP_LIB_H__
#define __APP_LIB_H__

#include "app.h"
/***应用程序库函数申明***/
extern u8 signal_state(u8 state);
extern u8 sys_state(u8 state);
extern void key_get(u8 *state,u8 *key);
extern void app_spi(u8 dac,u16 data);
extern void key_led(u8 led,u8 state);
extern void sound_control(u8 state);
extern void power_down(u8 time);
extern u8 app_io(u8 io,u8 state,u16 pin);
extern void test_io(void);
extern void send_485(char *s);
extern void analyze_485(void);

/**/
#endif
/***end of the file***/
