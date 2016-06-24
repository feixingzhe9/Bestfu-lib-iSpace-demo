#include "led_light.h"
#include "keyunit.h"
#include "m74hc595.h"
#include "Thread.h"	

INT8U led_flag = 0;
INT8U Led_num = 50;
void led_light_scan(void)
{
	INT8U i;	
	for(i=0;i<KEY_MAX_CHN;i++)
	{
		if(keypara.key[i].KeyLOCK == KEY_LOCK)
		{
			Led_num	= i;
			Thread_Login(MANY, 4, 90, &led_scan);
			keypara.key[i].KeyLOCK =KEY_UNLOCK;				
		}
	}	
	
}
void led_scan(void)
{
	if(Led_num != 50)
	{		
		LED_F(&Led_num);
	}
	else
	{
		led_flag = 0;
		data_temp &= 3<<9;
		m74hc595_All(data_temp);
	}

}
void LED_F(INT8U *NUM)
{
	switch(*NUM)
	{
		case 0:
		{
			LED_Status_Turn_Over(11);
			break;
		}
		case 1:
		{
			LED_Status_Turn_Over(12);
			break;

		}
		case 2:
		{
			LED_Status_Turn_Over(13);
			break;
		}
		case 3:
		{
			LED_Status_Turn_Over(14);				
			break;
		}
		case 4:
		{
			LED_Status_Turn_Over(15);
			break;
		}
		case 5:
		{
			LED_Status_Turn_Over(9);
			break;

		}
		case 6:
		{
			LED_Status_Turn_Over(7);
			break;

		}
		case 7:
		{
			LED_Status_Turn_Over(6);
			break;
		}
		case 8:
		{
			LED_Status_Turn_Over(5);
			break;
		}
		case 9:
		{
			LED_Status_Turn_Over(4);
			break;
		}
		case 10:
		{
			LED_Status_Turn_Over(3);
			break;
		}
		case 11:
		{
			LED_Status_Turn_Over(2);
			break;
		}
		case 12:
		{
			LED_Status_Turn_Over(1);
			break;

		}
		case 13:
		{
			LED_Status_Turn_Over(0);
			break;
		}
		default:
		{
			led_flag = 0;
			data_temp &= 3<<9;
			m74hc595_All(data_temp);
			break;
		}
	}
}
void LED_Double_light(INT8U *NUM,INT8U Local)
{
	keypara.key[*NUM].count++; 
	if(led_flag<2)
	{
		if(keypara.key[*NUM].count==1)
		{
			m74hc595_output(Local,1); //关闭     
		}  
		else if(keypara.key[*NUM].count==LOCK_TIME/2)
		{
			m74hc595_output(Local,0); //点亮
		}
		else if(keypara.key[*NUM].count==LOCK_TIME)
		{
			led_flag++;
			keypara.key[*NUM].count = 0;//开始第二次
		}
	}
	else
	{	
		keypara.key[*NUM].KeyLOCK =KEY_UNLOCK;		
		keypara.key[*NUM].count = 0;			
		data_temp &= 3<<9;
		m74hc595_All(data_temp);
		*NUM = 50;
	}
}
void LED_Status_Turn_Over(INT8U Local)
{
	
	static INT8U led_status = 0,count = 0;
	led_status = ~led_status;
	count++;
	if(led_status)
	{
		m74hc595_output(Local,1); //关闭  
	}
	else
	{
		m74hc595_output(Local,0); //点亮  
	}
	if(count==4)
	{
		Led_num = 50;
		count = 0;
		data_temp &= 3<<9;
		m74hc595_All(data_temp);		
	}
}
/******************************************************************************
** 函数名称: void Run_Led(void)
** 功能描述: 运行灯闪烁功能。
** 输　入:   无
** 输　出  : 无
******************************************************************************/
void Run_Led(void)
{
	static INT8U flag = 0;
	flag = ~flag;
	if(flag)
	{
		m74hc595_output(9,0);
		m74hc595_output(10,1);
	}
	else
	{
		m74hc595_output(9,1);
		m74hc595_output(10,0);
	}	
}
