/*******************************************************************
文	件：    Battery.c
说	明：    Voltage逻辑代码
编	译：    Keil uVision4 V4.54.0.0
版	本：    v1.0
编	写：    Seven
日	期：    2014.07.10

锂电池电压范围：  3.0V ~ 4.2V

放电电压至 3.5V  能量释放 95%


********************************************************************/
#include "gpio.h"
#include "Unitcfg.h"
#include "Battery.h"
#include "adc.h"
                     // 90   80  70  60  50  40  30  20  10  1  %
const u16 VoltageTab[]={403,397,390,383,378,373,369,365,362,340};

//电压保存值
u8 BattVoltageLev;


//读取电压值
u8 Battery_GetVoltage(u16 *Voltage)
{
	u16 ADC_Value;
	u32 tmp_voltage=0;
	GPIOx_Set(PORT_ADC_SWITCH, PIN_ADC_SWITCH);	
	if(!Get_ADC_Average(10,&ADC_Value))
	{
		//Voltage = ADC_Result *330 / 4096
		tmp_voltage = ADC_Value*132;		//扩大200倍    0——330   分压电阻 1/2
		*Voltage    = tmp_voltage/819;
		GPIOx_Rst(PORT_ADC_SWITCH, PIN_ADC_SWITCH);		
		return 0;
	}
	GPIOx_Rst(PORT_ADC_SWITCH, PIN_ADC_SWITCH);		
	return 1;
}
//电压分级
u8 Battery_GetPower(u8 * VoltageLev)
{
	u16  vtg=0;
	u8	 precent=0;
	if(!Battery_GetVoltage(&vtg))
	{
		if(vtg>=VoltageTab[0])		//90%
		{
			precent=90;
		}
		else if(vtg>=VoltageTab[1])//80%
		{
			precent=80;
		}
		else if(vtg>=VoltageTab[2])//70%
		{
			precent=70;
		}
		else if(vtg>=VoltageTab[3])//60%
		{
			precent=60;
		}
		else if(vtg>=VoltageTab[4])//50%
		{
			precent=50;
		}
		else if(vtg>=VoltageTab[5])//40%
		{
			precent=40;
		}
		else if(vtg>=VoltageTab[6])//30%
		{
			precent=30;
		}
		else if(vtg>=VoltageTab[7])//20%
		{
			precent=20;
		}
		else if(vtg>=VoltageTab[8])//10%
		{
			precent=10;
		}
		else if(vtg>=VoltageTab[9])//1%
		{
			precent=1;
		}
		*VoltageLev = precent;
		return  0;
	}
	else return 1;
}

//INT8U VoltageExeCmd(MsgCmd_st *str)
//{
//    
//	INT8U  flag;
//	switch (str->Cmd)
//	{
//		case 0xFF:	flag = Voltage_Get_Attr(str);
//					break;
//		default:	str->ucDataLen = 0;
//					flag = FALSE;
//					break;
//	}
//	return flag;
//}

/*******************************************************************
函 数 名： 	IAP_Ready_Attr  
功能说明：  升级准备属性
参	  数:   *str--命令执行参数       
返 回 值：  TRUE/FALSE
********************************************************************/
//INT8U Voltage_Get_Attr(MsgCmd_st *str)
//{
//	if(Battery_Power_Instruct())
//	{
//		return TRUE;
//	}
//	return FALSE;
//}

u8 Battery_Power_Instruct(void)
{
	
//	COM_STR Battery_Power_CMD;
//	if(!Battery_GetPower(&BattVoltageLev))
//	{
//		Battery_Power_CMD.Version              = PROTOCOL_VER; 			// 版本号
//		*(u32*)&Battery_Power_CMD.ClientNum    = *(u32*)&g_stEeEx.Sys.Board.ClientNum;	// 用户号
//		Battery_Power_CMD.DesObjectType        = 0x01; 			// 目标类型
//		*(u32*)&Battery_Power_CMD.DesObjectID  = 0x00000000; 	// 目标地址
//		Battery_Power_CMD.DesObjectTypeID      = 0xFF; 			// 广播类型号
//		*(u32*)&Battery_Power_CMD.SrcObjectID  = *(u32*)&g_var.DeviceID; // 源地址
//		Battery_Power_CMD.SerialNum            = 0x00;       	// 流水号
//		Battery_Power_CMD.MsgTypeNum           = WRITEWITHACK; 	// 消息类型码
//		Battery_Power_CMD.UnitID               = 0x00;     		// 单元ID
//		Battery_Power_CMD.Cmd                  = 0xFF;			// 命令码
//		Battery_Power_CMD.DataLength           = 0x01;     		// 参数长度
//		Battery_Power_CMD.Parameter[0] = BattVoltageLev; 		    //参数
//		AnswerCommand(&Battery_Power_CMD, 1);
//	}
//	else 
//	{
//		return 0;
//	}
	return 1;
}
void Battery_Power_Instruct_success(void)
{
	static u8 Get_voltage_success = 1;
	if(Get_voltage_success )
		{
			if(Battery_Power_Instruct())
			{
				Get_voltage_success =0;
			}
		}
}

