/***************************Copyright BestFu 2014-05-14*************************
文	件：    SIGACTExeAttr.h
说	明：    单色调光器设备属性实现头文件
编	译：    Keil uVision4 V4.54.0.0
版	本：    v1.0
编	写：    linwuzhang
日	期：    2013.9.10
修　改：	暂无
*******************************************************************************/
#ifndef __SINACTEXEATTR_H
#define __SINACTEXEATTR_H

#include "UnitCfg.h"

#define SINGLE_POWER_ON_STATE_ADDR			(0x3000)	//开关执行器上电状态存储地址

typedef struct
{
	u8 state;
}SigPowerOn_t;	//单路执行器上电状态指示

extern const AttrExe_st SigActAttrTable[];

void SigActParaInit(u8 unitID);
void SigActEepromInit(u8 unitID);
u8 SigAct_UnitAttrNum(void);

void SigActInstruct(void);

MsgResult_t Set_SigActSwitch_Attr(UnitPara_t *pData);
MsgResult_t Get_SigActSwitch_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara);

MsgResult_t Set_SigActionTimer_Attr(UnitPara_t *pData);

MsgResult_t Set_SigPowerOnStatus_Attr(UnitPara_t *pData);
MsgResult_t Get_SigPowerOnStatus_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara);


#endif	 //end #if
/**************************Copyright BestFu 2014-05-14*************************/
