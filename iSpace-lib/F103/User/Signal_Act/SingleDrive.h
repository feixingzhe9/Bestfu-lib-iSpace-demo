/***************************Copyright BestFu 2014-05-14*************************
文	件：    singleUnit.c
说	明：    单路执行器驱动实现文件
编	译：    Keil uVision4 V4.54.0.0
版	本：    v1.0
编	写：    Unarty
日	期：    2014.08.20
修　改：	暂无
*******************************************************************************/
#ifndef __SINGLEDRIVE_H
#define __SINGLEDRIVE_H

#include "BF_type.h"
#include "GPIO.h"


#define SIG_PORT		GPIO_B
#define SIG_PIN			pin_9

#define SIG_ON			GPIOx_Set(SIG_PORT, SIG_PIN)
#define SIG_OFF			GPIOx_Rst(SIG_PORT, SIG_PIN)
#define SIG_RVRS		GPIOx_Rvrs(SIG_PORT, SIG_PIN)
#define SIG_STATUS		GPIOx_Get(SIG_PORT, SIG_PIN)

void SingleDrive_Init(void);

#endif
/**************************Copyright BestFu 2014-05-14*************************/
