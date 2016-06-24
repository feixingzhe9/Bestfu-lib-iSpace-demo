#ifndef __USART2_H
#define __USART2_H

#include <stdio.h>	
#include "BF_type.h"

#define EN_USART2_RX 			0		//使能串口2接收
#define USART2_SUPPORT_PRINTF	1		//使能串口2支持printf()函数

extern void USART2_Init(u32 pclk2,u32 bound);
extern void USART2_SendByte(u8 ch);

#endif	   

