/***************************Copyright BestFu 2014-05-14*************************
文	件：    SIGACTExeAttr.c
说	明：    单色调光器设备属性实现文件
编	译：    Keil uVision4 V4.54.0.0
版	本：    v1.0
编	写：    linwuzhang
日	期：    2013.9.10
修　改：	暂无
*******************************************************************************/
#include "SigActExeAttr.h"
#include "bf_type.h"
#include "SingleUnit.h"
#include "SigActExeAttr.h"
#include "Thread.h"

u8 SigAct_Status = SINGLE_CLOSE;

//对属性读写的接口列表
const AttrExe_st SigActAttrTable[] =
{
	{0x01, LEVEL_1, Set_SigActSwitch_Attr       , Get_SigActSwitch_Attr        	},
	{0x02, LEVEL_0, Set_SigActionTimer_Attr		, NULL							},
	{0x08, LEVEL_0, Set_SigPowerOnStatus_Attr	, Get_SigPowerOnStatus_Attr		},
};

/*******************************************************************************
函 数 名:  SigAct_UnitAttrNum
功能说明:  计算开关单元属性数量
参    数:  无
返 回 值:  无
*******************************************************************************/
u8 SigAct_UnitAttrNum(void)
{
	return ((sizeof(SigActAttrTable)/sizeof(SigActAttrTable[0])));
}

/*******************************************************************************
函 数 名:  void SigActParaInit(u8 unitID)
功能说明:  执行器单元的初始化
参    数:  unitID-单元号
返 回 值:  无
*******************************************************************************/
void SigActParaInit(u8 unitID)
{
	SingleUnit_Init(unitID);
	Single_ON();	
	Thread_Login(ONCEDELAY, 0, 2000, &Single_OFF);
}

/*******************************************************************************
函 数 名:  void SigActEepromInit(u8 unitID)
功能说明:  调光单元EEPROM参数的默认值
参    数:  unitID-单元号
返 回 值:  无
*******************************************************************************/
void SigActEepromInit(u8 unitID)
{
}

/*******************************************************************************
函 数 名:  u8 Set_SigActSwitch_Attr(u8 *pData)
功能说明:  设置单路执行器开关
参    数:   pData->unit: 	单元号，
			pData->cmd:	  	属性号
            pData->len:     为参数长度
            pData->data:	为参数值(0为关闭，非0为开启)
返 回 值:  	操作结果
*******************************************************************************/
MsgResult_t Set_SigActSwitch_Attr(UnitPara_t *pData)
{
	if (pData->data[0])
	{
		Single_ON();
	}
	else
	{
		Single_OFF();
	}
	Single_DelayClr();
	Upload();
	
	return COMPLETE;
}

/*******************************************************************************
函 数 名:  	u8 Get_SigActSwitch_Attr(u8 *pData)
功能说明:  	设置RGB开关
参    数:  	pData->unit: 	单元号，
			pData->cmd:	  	属性号
            pData->len:     为参数长度
            pData->data:	为参数值(0为关闭，非0为开启)
			*rlen-返回参数长度
			*rpara-返回参数存放地址
返 回 值:  	1表示成功，0表示失败
*******************************************************************************/
MsgResult_t Get_SigActSwitch_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara)
{

	*rlen = 1;
	*rpara = Single_State();
	
    return COMPLETE;
}

/*******************************************************************************
函 数 名:  	Set_SigActionTimer_Attr
功能说明:  	设置开关动作属性
参    数:   pData->unit: 	单元号，
			pData->cmd:	  	属性号
            pData->len:     为参数长度
            pData->data:	为参数值(0为关闭，非0为开启)
返 回 值:  	操作结果
*******************************************************************************/
MsgResult_t Set_SigActionTimer_Attr(UnitPara_t *pData)
{
	if (pData->len < 8)
	{
		return PARA_LEN_ERR;
	}
	
	gSigActTime.firstTime = ((*(u32*)&pData->data[1])) * 1000;
	gSigActTime.secondTime = ((*(u32*)&pData->data[5])) * 1000;
	gSigActTime.cycleFlag = pData->data[9];
	gSigActTime.fun = (pData->data[0] == 0 ? &Single_OFF : & Single_ON);
	
	Thread_Login(ONCEDELAY, 0, 	gSigActTime.firstTime, &Single_DelayOpt1);
	
	return COMPLETE;
}

/*******************************************************************************
函 数 名:  	Set_SigPowerOnStatus_Attr
功能说明:  	设置单路执行器上电状态
参    数:   pData->unit: 	单元号，
			pData->cmd:	  	属性号
            pData->len:     为参数长度
            pData->data:	为参数值(0为关闭，非0为开启)
返 回 值:  	操作结果
*******************************************************************************/
MsgResult_t Set_SigPowerOnStatus_Attr(UnitPara_t *pData)
{
	SigPowerOn_t powerOn;
	
	if (1 == pData->len)	//参数长度正确
	{
		powerOn.state = pData->data[0];
		return EEPROM_Write(SINGLE_POWER_ON_STATE_ADDR, sizeof(SigPowerOn_t), (u8*)&powerOn);
	}		
	
	return PARA_MEANING_ERR;
}

/*******************************************************************************
函 数 名:  	Get_SigPowerOnStatus_Attr
功能说明:  	获取单路执行器上电状态
参    数:  	pData->unit: 	单元号，
			pData->cmd:	  	属性号
            pData->len:     为参数长度
            pData->data:	为参数值(0为关闭，非0为开启)
			*rlen-返回参数长度
			*rpara-返回参数存放地址
返 回 值:  	1表示成功，0表示失败
*******************************************************************************/
MsgResult_t Get_SigPowerOnStatus_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara)
{
	SigPowerOn_t powerOn;
	MsgResult_t result;
	
	result = EEPROM_Read(SINGLE_POWER_ON_STATE_ADDR, sizeof(SigPowerOn_t), (u8*)&powerOn);
	if (COMPLETE == result)
	{
		*rlen = sizeof(SigPowerOn_t);
		memcpy(rpara, &powerOn, *rlen);
	}
	
    return result;
}

/*******************************************************************************
函 数 名:  	SigActInstruct
功能说明:  	调光单元指示
参    数:  	unit:	对应的指示单元
返 回 值:  	无
注    意:	当unit = 0 时设备恢复到非提示状态
*******************************************************************************/
void SigActInstruct(void)
{
	Single_OFF();
	Thread_Login(MANY, 4, 500, &Single_Rvrs);
}

/**************************Copyright BestFu 2014-05-14*************************/
