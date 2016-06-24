/*******************************************************************
文	件：delay.h
说	明：使用SysTick的普通计数模式对延迟进行管理
编	译：Keil uVision4 V4.54.0.0
版	本：v1.0
编	写：Unarty
日	期：
********************************************************************/
#ifndef __LPM_H
#define __LPM_H 

#include "stm32l1xx.h"			   
#include "BF_type.h"
#include "core_cm3.h"

extern INT8U In_Lpm_Flag;


typedef enum
{
	SLEEP 			= 0,	//睡眠模式
	Low_Power_Run	= 1,
	Low_Power_Sleep = 2,
	Stop 			= 3,
	Standby 		= 4 	//待机模式
}Low_Power_Mode;  


void Low_Power_Select(INT8U LPM);
void LP_Run_Mode(void);
void Sleep_Mode(void);
void Stop_Mode(void);
void Standby_Mode(void);

void Close_device(void);


void CheckStandbyMode(void);
void WKUP_Port_Init(void);
void Get_WKUP_State(void);

#endif	//LPM.h end


/**************************FILE*END********************************/





























