#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"

#define PORT_ADC	GPIO_A
#define PIN_ADC		pin_4
#define ADC_CH		4 

#define PORT_ADC_SWITCH		GPIO_A
#define PIN_ADC_SWITCH		pin_5
	 	       									   
void  ADC_Init(void);
u8 Get_ADC(u16 *ADC_Result) ; 						//获得某个通道值 
u8 Get_ADC_Average(u8 times,u16 *Average_Voltage);	//得到某个通道10次采样的平均值 

#endif 















