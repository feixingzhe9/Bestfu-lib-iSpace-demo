#ifndef __TIMER_H
#define __TIMER_H
#include "BF_TYPE.H"
#include "stm32l1xx.h"

extern volatile u8 TIM2_FLAG;
void Init_TIMx(TIM_TypeDef *TIMx,u16 psc,u16 arr);
void TIMx_Start(TIM_TypeDef *TIMx,u16 arr);
u32 TIMx_Stop(TIM_TypeDef *TIMx);


#endif

