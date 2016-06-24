#ifndef __WTC6216_H
#define __WTC6216_H

#include "gpio.h"
#include "stdio.h"	 
#include "BF_type.h"	

extern INT8U LPM_KEY1;
extern INT8U LPM_KEY2;
extern u8 Touch_Value;

#define INT_PORT    GPIO_A     
#define INT_PIN     pin_0     

#define DATA0_PORT    GPIO_C      
#define DATA0_PIN    pin_3      
													    
#define DATA1_PORT    GPIO_C    
#define DATA1_PIN     pin_2     

#define DATA2_PORT    GPIO_C      
#define DATA2_PIN    pin_1       
													    
#define DATA3_PORT    GPIO_C      
#define DATA3_PIN     pin_0      





#define INT_READ                  GPIOx_Get(INT_PORT, INT_PIN)
#define DATA0_READ                GPIOx_Get(DATA0_PORT, DATA0_PIN)
#define DATA1_READ                GPIOx_Get(DATA1_PORT, DATA1_PIN)
#define DATA2_READ                GPIOx_Get(DATA2_PORT, DATA2_PIN)
#define DATA3_READ                GPIOx_Get(DATA3_PORT, DATA3_PIN)


void WTC6216_Port_Init(void);
void Get_Key(INT16U *Key_Temp);
void Set_Back_Led(INT16U *Lamp_Num);
void keytask(INT8U LPM);
INT8U Get_Key_LPM(INT8U *Key_Temp);
INT8U key_read(void);
void key_temp(INT8U *temp);

#endif	   
















