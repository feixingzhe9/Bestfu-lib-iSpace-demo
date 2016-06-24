/***************************************************************
**	文    件: Cube20ExeAttr.c
**  平    台：MDK V5.10	
**  作    者：Seven
**  创建日期：2014/05/26
**  修改日期：2014/05/26
**  版    本：V1.0
**  描    述：20面体应用层接口
***************************************************************/
#ifndef		_CUBE20_EXE_ATTR_H_
#define		_CUBE20_EXE_ATTR_H_

#include "BF_type.h"
#include "UnitCfg.h"

extern const AttrExe_st Cube6AttrOperatTab[];

void  Cube6Init(INT8U unitID);
void  Cube6EepromInit(INT8U unitID);


MsgResult_t Get_Touch_Attr(UnitPara_t *pdata, INT8U *rlen, INT8U *rpara);

void Cube6Checking_Attr(void);

#endif
