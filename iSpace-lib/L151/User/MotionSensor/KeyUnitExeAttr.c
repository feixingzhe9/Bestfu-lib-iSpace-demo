/*******************************************************************************
**	文    件: Cube20ExeAttr.c
**  功    能：20面体属性命令接口
**  编    译：Keil uVision5 V5.10.0.2	
**  版    本：V1.0.0
**  编    写：Seven
**  创建日期：2014/05/26
**  修改日期：2014/05/26
**  说    明：
********************************************************************************/

#include "Unitcfg.h"	
#include "KeyUnitExeAttr.h"	

#include "Thread.h"	
#include "LowPower.h"	
#include "USART2.h"	
#include "Battery.h"
#include "ADC.h"
#include "wtc6216.h"
#include "m74hc595.h"
#include "keyunit.h"
#include "led_light.h"
#include "power.h"
//对属性读写的接口列表
const AttrExe_st Cube6AttrOperatTab[] = 
{
	{0x01, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x02, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x03, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x04, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x05, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x06, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x07, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x08, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x09, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0a, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0b, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0c, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0d, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0e, LEVEL_0, NULL					, Get_Touch_Attr  }

};


/*******************************************************************************
**函	数:  	Cube20Init()
**功	能:  	模块初始化
**参    数:  	unitID		--单元号
**返	回:  		
********************************************************************************/
void Cube6Init(INT8U unitID)
{
	WTC6216_Port_Init();
	POWER_PIN_INIT();
	POWER_ON();
	m74hc595_init();
		
	Thread_Login(FOREVER, 0, 1, &KeyScan);		
//	Thread_Login(FOREVER, 0, 1000, &CheckStandbyMode);		
	Thread_Login(FOREVER, 0, 1000, &Run_Led);	
	Upload();	
}
/*******************************************************************************
**函	数:  	Cube20EepromInit()
**功	能:  	模块所属 eeprom 初始化
**参    数:  	unitID		-单元号
**返	回:  		
********************************************************************************/
void Cube6EepromInit(INT8U unitID)
{
	
}


/*******************************************************************************
**函	数:  	Get_Cube20_Face_Attr()
**功	能:  	获取面值
**参    数:  	pdata[0]:   --单元号
				*rlen		--返回参数长度
				*rpara		--返回参数存放地址
**返	回:  	TRUE/FALSE
**说	明：	
********************************************************************************/
MsgResult_t Get_Touch_Attr(UnitPara_t *pdata, INT8U *rlen, INT8U *rpara)
{
	*rlen    = 1;
	rpara[0] = Touch_Value;
	return COMPLETE;
}


void Cube6Checking_Attr(void)
{
	
}
