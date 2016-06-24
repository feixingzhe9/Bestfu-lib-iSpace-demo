#include "wtc6216.h"

#include "delay.h"

#include "sys.h"
#include "usart.h"
#include "LowPower.h"

u8 Touch_Value;

INT8U LPM_KEY1;
INT8U LPM_KEY2;

void WTC6216_Port_Init(void)
{
	GPIOx_Cfg(INT_PORT,INT_PIN, IN_DOWN);
	GPIOx_Cfg(DATA0_PORT, DATA0_PIN, IN_DOWN);
	GPIOx_Cfg(DATA1_PORT, DATA1_PIN, IN_DOWN);
	GPIOx_Cfg(DATA2_PORT, DATA2_PIN, IN_DOWN);
	GPIOx_Cfg(DATA3_PORT, DATA3_PIN, IN_DOWN);
}
void Get_Key(INT16U *Key_Temp)   
{
	INT8U KEY1 = 0x9f,KEY2 = 0x8f;
	static INT8U KEY0=0xff,Scan_Time=0,Step=0;	
	switch(Step)
	{
		case 0:
			if(INT_READ==1)
			{
				In_Lpm_Flag = 0;
				Scan_Time++;
				if(Scan_Time==1)
				{
					KEY0 = key_read();
				}
				if(Scan_Time==15)
				{
					if(INT_READ==1)
					{
						KEY1 = key_read();
						if(KEY0==KEY1)
						{
							Step = 1;
							Scan_Time = 0;
						}
						else
						{
							Scan_Time = 0;
							Step = 0;
							*Key_Temp = 0;
							KEY0 = 0xff;
						}
						
					}
					else
					{
						Scan_Time = 0;
						Step = 0;
						KEY0 = 0xff;
						*Key_Temp = 0;
					}
				}
			}
			else
			{
				*Key_Temp = 0;
				Step = 0;
				Scan_Time = 0;
				KEY0 = 0xff;
			}
			break;
		case 1:
			if(INT_READ==1)
			{
				KEY2 = key_read();
				In_Lpm_Flag = 0;
				if(KEY0==KEY2)
				{
					key_temp(&KEY2);
					*Key_Temp = 1<<KEY2;//获取到正确的按键值
				}
				else
				{
					Step = 0;
					Scan_Time = 0;
					*Key_Temp = 0;
					KEY0 = 0xff;
				}
			}	
			else 
			{
				Step = 0;
				Scan_Time = 0;
				*Key_Temp = 0;
				KEY0 = 0xff;
				
			}
			break;	
		default:
		{
			*Key_Temp = 0;
			Step = 0;
			Scan_Time = 0;
			KEY0 = 0xff;
		}
	}	
}


INT8U Get_Key_LPM(INT8U *Key_Temp)   
{
	INT8U Key=0;
//	In_Lpm_Flag = 0;
	if(INT_READ==1)
	{
		*Key_Temp = key_read();
		key_temp(Key_Temp);
		Key = 1<<*Key_Temp;
	}
	return Key;
}
void keytask(INT8U LPM)
{
	if(LPM)
	{
//		PropEventFifo(1, LPM_KEY1+1, SRCEVENT, KEY_SHORT); 
//		PropChangeScanAndExe();
//		keypara.key[LPM_KEY1].KeyLOCK =KEY_LOCK;
	}
}
INT8U key_read(void)
{
	INT8U get_key=0;
	if(DATA0_READ !=0)
	{
		get_key |= (INT8U)(1<<0);
	}
	else
	{
		get_key &= ~(INT8U)((1<<0));
	}
	
	if(DATA1_READ !=0)
	{
		get_key |= (INT8U)(1<<1);
	}
	else
	{
		get_key &= ~(INT8U)(1<<1);
	}
	
	if(DATA2_READ !=0)
	{
		get_key |= (INT8U)(1<<2);
	}
	else
	{
		get_key &= ~(INT8U)(1<<2);
	}
	
	if(DATA3_READ !=0)
	{
		get_key |= (INT8U)(1<<3);
	}
	else
	{
		get_key &= ~(INT8U)(1<<3);
	}
	
	return get_key;
	
}
void key_temp(INT8U *temp)
{
	if(*temp==0x0A)
	{
		*temp = 0;
	}
	else if(*temp==0x0B)
	{
		*temp = 1;
	}
	else if(*temp==0x0C)
	{
		*temp = 2;
	}
	else if(*temp==0x0D)
	{
		*temp = 3;
	}
	else if(*temp==0x0E)
	{
		*temp = 4;
	}
	else if(*temp==0x0F)
	{
		*temp = 5;
	}
	else if(*temp==0x02)
	{
		*temp = 6;
	}
	else if(*temp==0x03)
	{
		*temp = 7;
	}
	else if(*temp==0x04)
	{
		*temp = 8;
	}
	else if(*temp==0x05)
	{
		*temp = 9;
	}
	else if(*temp==0x06)
	{
		*temp = 10;
	}
	else if(*temp==0x07)
	{
		*temp = 11;
	}
	else if(*temp==0x08)
	{
		*temp = 12;
	}
	else if(*temp==0x09)
	{
		*temp = 13;
	}
	else if(*temp==0x01)
	{
		*temp = 14;
	}
	else
	{
		*temp = 100;
	}

}




