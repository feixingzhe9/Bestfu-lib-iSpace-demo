#ifndef __USART1_H
#define __USART1_H

#include <stdio.h>	
#include "BF_type.h"

#define EN_USART1_RX 			0		//使能串口1接收
#define USART1_SUPPORT_PRINTF	0		//使能串口1支持printf()函数
	  	

extern void USART1_Init(u32 pclk2,u32 bound);
extern void USART1_SendByte(u8 ch);

#endif	   

