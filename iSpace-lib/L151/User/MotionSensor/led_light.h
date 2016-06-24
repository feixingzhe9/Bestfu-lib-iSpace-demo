#ifndef __LED_LIGHT_H
#define __LED_LIGHT_H

#include "gpio.h"
#include "stdio.h"	 
#include "BF_type.h"	

extern INT8U led_flag;
void led_light_scan(void);
void LED_F(INT8U *NUM);
void LED_Double_light(INT8U *NUM,INT8U Local);
void Run_Led(void);
void LED_Status_Turn_Over(INT8U Local);
void led_scan(void);
#endif	   
















