#include "keyunit.h"
#include "UnitCfg.h"
#include "wtc6216.h"
#include "m74hc595.h"
#include "led_light.h"

#if KEY_UPLOAD
#include "MsgPackage.h"
#endif

KeyTable keypara;


/*****************************************************************************
函 数 名:  void KeyScan(void)
功能说明:  按键扫描，获取到当前的按键值并与上一次比较，如果不一致说明有变化，处理。
参    数:  无
返 回 值:  无
*****************************************************************************/
void KeyScan(void)
{
	INT16U key=0,keytmp=0;
	static INT16U keyold=0;
	Get_Key(&key);
	keytmp = key^ keyold; 		//异或为1的位说明是有按键按下的或者是释放
	if(keytmp)
	{
		KeyDeal(key, keytmp);
	}
	keyold = key;
	KeyTimeCnt();
	led_light_scan();
}

/*****************************************************************************
函 数 名:  void KeyTimeCnt(void)
功能说明:  按键计时，每路按键独立增计数，在每10毫秒一次计时中调用。
参    数:  无
返 回 值:  无
*****************************************************************************/
void KeyTimeCnt(void)
{
	INT8U i,j;
	for(i=0;i<KEY_MAX_CHN;i++)
	{
		if(keypara.key[i].KeyLvl == KEY_VALID_LVL)//有按键按下
		{
			if(keypara.key[i].Lstartf)// 长按开始标志，1表示开始，0表示没开始
			{
				if((++keypara.key[i].LTimecnt % 1000) == 0) 
				{
					PropEventFifo(1, i+1, 1, KEY_LONG_BEGIN);
#if  KEY_UPLOAD	
					Touch_Value = KEY_LONG_BEGIN;
					Msg_Upload(1, i +1, 1, &Touch_Value);
#endif
					data_temp = 0;
					m74hc595_All(0);
					for(j=0;j<KEY_MAX_CHN;j++)
					{
						if(j==i)
						{
							keypara.key[j].KeyLOCK = KEY_LOCK;
							led_flag = 0;
						}
						else
						{
							keypara.key[j].KeyLOCK = KEY_UNLOCK;						
						}				
					}

				}
				if(keypara.key[i].LTimecnt == 2000)
				{
//					PropEventFifo(KEY_START_NUM, i+1, SRCEVENT, KEY_LONG_3S);

				}
			}
			else
			{
				if(++keypara.key[i].Time >= 500)//有按键按下一直计时，直到断开
				{
					//产生长按开始事件
					PropEventFifo(1, i+1, 1, KEY_LONG_BEGIN);
#if  KEY_UPLOAD					
					Touch_Value = KEY_LONG_BEGIN;			
					Msg_Upload(1, i +1, 1, &Touch_Value);
#endif						
					keypara.key[i].LTimecnt   = 0;//长按保持触发计数器清0
					keypara.key[i].Lstartf    = 1;
					keypara.key[i].KeyLOCK = KEY_LOCK;
					data_temp = 0;
					m74hc595_All(0);
					for(j=0;j<KEY_MAX_CHN;j++)
					{
						if(j==i)
						{
							keypara.key[j].KeyLOCK = KEY_LOCK;
							led_flag=0;
						}
						else
						{
							keypara.key[j].KeyLOCK = KEY_UNLOCK;						
						}				
					}
					
				}
			}
		}
		else//没有按键按下，按键计时清零
		{
			keypara.key[i].Time = 0;
			
		}
	}
}
/*****************************************************************************
函 数 名:  void KeyDeal(INT8U key, INT8U keytmp)
功能说明:  按键处理，每路单元独立判断，短按长按等状态。
参    数:  key-当前每路按键状态值，组合成字节
           keytmp-每路按键是否有变化值，组合成两个字节
返 回 值:  无
*****************************************************************************/
void KeyDeal(INT16U key, INT16U keytmp)
{
	INT8U i,j;
	for(i=0;i<KEY_MAX_CHN;i++)//KEY_MAX_CHN按键通道数
	{
		if(keytmp & (1<<i))
		{
			if(keypara.key[i].KeyLvl == KEY_VALID_LVL)                // 按键有效电平，即按钮按下的实际信号
			{
				//释放
				if(keypara.key[i].Time < 500 && keypara.key[i].Time > 0)
				{
					//产生短按和短按释放事件
				data_temp &= 3<<9;
				m74hc595_All(data_temp);
				for(j=0;j<KEY_MAX_CHN;j++)
				{
					if(j==i)
					{
						keypara.key[j].KeyLOCK = KEY_LOCK;
						led_flag=0;
					}
					else
					{
						keypara.key[j].KeyLOCK = KEY_UNLOCK;						
					}				
				}
//				PropEventFifo(KEY_START_NUM, i+1, SRCEVENT, KEY_SHORT); //KEY_START_NUM        0 // 按键单元开始号码
				PropEventFifo(1, i+1, 1, KEY_SHORT);
#if  KEY_UPLOAD					
				Touch_Value = KEY_SHORT;
				Msg_Upload(1, i +1, 1, &Touch_Value);
#endif			
				}
				if(keypara.key[i].Lstartf)
				{
					//产生长按释放事件
					PropEventFifo(1, i+1, 1, KEY_LONG_END);
#if  KEY_UPLOAD						
					Touch_Value = KEY_LONG_END;
					Msg_Upload(1, i +1, 1, &Touch_Value);
#endif				
					keypara.key[i].LTimecnt   = 0;//长按保持触发计数器清0
					keypara.key[i].Lstartf    = 0;	
				}
				keypara.key[i].KeyLvl = KEY_INVALID_LVL;   //KEY_INVALID_LVL    !KEY_VALID_LVL    // 按键无效电平，无按键时的电平状态
			}
			else
			{
				//闭合
				keypara.key[i].KeyLvl = KEY_VALID_LVL;
				keypara.key[i].Time   = 0;
				
			}
			break;
		}
	}
}

