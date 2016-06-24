/***************************Copyright BestFu 2014-05-14*************************
文	件：    singleUnit.c
说	明：    单路执行器驱动实现文件
编	译：    Keil uVision4 V4.54.0.0
版	本：    v2.0
编	写：    Unart
日	期：    2014.08.20
修　改：	暂无
*******************************************************************************/
#ifndef __SINGLEUNIT_H
#define __SINGLEUNIT_H

#include "BF_type.h"

#define SINGLE_OPEN 0x01
#define SINGLE_CLOSE 0x00

typedef struct
{
	void *fun;			//开始状态函数
	u32 firstTime;
	u32 secondTime;
	u8  cycleFlag;		//循环标记
}SigActTime_t;

extern SigActTime_t gSigActTime;

void SingleUnit_Init(u8 unit);
void Single_ON(void);
void Single_OFF(void);
void Single_Rvrs(void);
u8 Single_State(void);
void Single_DelayClr(void);
void Single_DelayOpt1(void);
void Single_DelayOpt2(void);

#endif
/**************************Copyright BestFu 2014-05-14*************************/
