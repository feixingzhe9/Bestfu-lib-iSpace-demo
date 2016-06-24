/***************************Copyright BestFu ***********************************
**  文    件:   KeyExeAttr.c
**  功    能：  <<属性层>>摁键属性层接口
**  编    译：  Keil uVision5 V5.10
**  版    本：  V1.0.0
**  编    写：  Seven
**  创建日期：  2014/08/21
**  修改日期：  2014/08/21
**  说    明：
**  V1.0
    >> 摁键状态 : 0==无摁键   1==短摁键   2==长按键
*******************************************************************************/
#include "Unitcfg.h"
#include "KeyExeAttr.h" 
#include "BatteryExeAttr.h"
#include "Key.h"
#include "Thread.h"
#include "LowPower.h"
#include "ShowLED.h"
#include "USART2.h"
#include "ShakeMotor.h"
#include "OLED.h"
#include "74HC595.h"

/*属性读写的接口列表*/
const AttrExe_st KeyAttrTab[] =
{
    {0x01, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x02, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x03, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x04, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x05, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x06, LEVEL_1, NULL    , Get_TouchKey_Attr },
    {0x07, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x08, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x09, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x0A, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x0B, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x0C, LEVEL_1, NULL    , Get_TouchKey_Attr },  
    {0x0D, LEVEL_1, NULL    , Get_TouchKey_Attr },     

    {0xC8, LEVEL_1, NULL    , Get_PowerPercent_Attr },   //固定属性  获取电池电量
    //{0xC9, LEVEL_1, NULL    , Get_ChargeState_Attr  },   //固定属性  获取电池充电状态(充电锂电池才有)  
};

/*******************************************************************************
**函    数： KeyInit
**功    能： 初始化
**参    数： unitID      --单元号
**返    回： void
*******************************************************************************/
void KeyInit(u8 unitID)
{
    //ShakeMotor_Init();
    //Key_Init();
    Init_OLED();
    _74HC595_Init();
    ShowLED_OpenAll();
        
    Thread_Login(FOREVER, 0, 5 , &Key_Handle);           //8ms 按键
    Thread_Login(FOREVER, 0, 100, &LowPower_CheckTime);   //100ms*100 = 10s  睡眠
    Upload();
}

/*******************************************************************************
**函    数： KeyEepromInit
**功    能： 所属 eeprom 初始化
**参    数： unitID      --单元号
**返    回： void
*******************************************************************************/
void KeyEepromInit(u8 unitID)
{
    unitID = unitID;
}

/*******************************************************************************
**函    数： Get_TouchKey_Attr()
**功    能： 获取触摸摁键值
**参    数： *pData      --输入参数
             *rLen       --返回参数长度
             *rData      --返回参数存放地址
**返    回： TRUE/FALSE
********************************************************************************/
MsgResult_t Get_TouchKey_Attr(UnitPara_t *pData, u8 *rLen, u8 *rData)
{
    u8 ch = pData->cmd;
    
    *rLen    = 1;
    rData[0] = KeyCh[ch].Status;
    
    return COMPLETE;
}

/*******************************************************************************
**函    数:  KeyChecking_Attr()
**功    能:  验证设备
**参    数:  void
**返    回:  void
********************************************************************************/
void KeyChecking_Attr(void)
{
     Thread_Login(MANY, 4, 200 , &ShowLED_CheckDevice);
}

/***************************Copyright BestFu **********************************/

