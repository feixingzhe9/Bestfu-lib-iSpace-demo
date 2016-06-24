/*****************************************************************************
文件： m74hc595.c
说明： m74hc595操作函数实现文件
编译： Keil uVision4 V4.54.0.0
版本： v1.0
编写： linwuzhang
日期： 2013.10.21
*****************************************************************************/

#include "m74hc595.h"

#include "sys.h"
#include "delay.h"
INT16U data_temp = 0;
/****************************************
函 数 名:  m74hc595_init(void);
功能说明:  初始化74hc595相关IO管脚
参    数:            
返 回 值:  
*****************************************/
void m74hc595_init(void)
{
	GPIOx_Cfg(_SDA_PORT,  _SDA_PIN,  OUT_PP_2M);
	GPIOx_Cfg(OUT_PORT,  OUT_PIN,  	 OUT_PP_2M);
	GPIOx_Cfg(LOCK_PORT, LOCK_PIN, 	 OUT_PP_2M);
	GPIOx_Cfg(SCK_PORT,  SCK_PIN,  	 OUT_PP_2M);
	GPIOx_Cfg(RST_PORT,  RST_PIN, 	 OUT_PP_2M);
//	M74HC595_OUTPUT_EN(1);	//高阻抗，关闭所有LED
//	M74HC595_RST(0);		//清除寄存器值
//	M74HC595_LATCH(0);
//	delay_us(10);
//	M74HC595_LATCH(1);
}

/****************************************
函 数 名: void m74hc595_output(unsigned short data);
功能说明: 将data通过m74hc595输出
参    数: data表示595级联的16个IO输出。data的第15位驱动第16个LED灯，data的第0位驱动第1个LED灯
		  对应位置0，点亮LED，如LED=0x4001,    表示点亮第14个和第1个LED灯      
返 回 值:  
*****************************************/
void m74hc595_output(INT16U data,INT8U cmd)
{
	INT8U i;
	
//	M74HC595_OUTPUT_EN(1);	//高阻抗，关闭所有LED
	M74HC595_LATCH(0);		//输出状态寄存器保持
    M74HC595_RST(1);	
	if(cmd)
	{
		data_temp |= 1<<data;
	}
	else
	{
		data_temp &= ~(1<<data);
	}
	
	for(i=16;i>0;i--)
	{
		M74HC595_SCLK(0);
		if(data_temp&(1<<(i-1)))
		{
			M74HC595_SDA(1);
		}
		else
		{
			M74HC595_SDA(0);	
		}
		M74HC595_SCLK(1);
	}
	M74HC595_LATCH(1);		 //将移位寄存器的值锁存到输出寄存器中
	M74HC595_OUTPUT_EN(0);	//输出有效，点亮LED灯
}
void m74hc595_All(INT16U data)
{
	INT8U i;
//	M74HC595_OUTPUT_EN(1);	//高阻抗，关闭所有LED
	M74HC595_LATCH(0);		//输出状态寄存器保持
	
    M74HC595_RST(1);	
	for(i=16;i>0;i--)
	{
		M74HC595_SCLK(0);
		if(data&(1<<(i-1)))
		{
			M74HC595_SDA(1);
		}
		else
		{
			M74HC595_SDA(0);	
		}
		M74HC595_SCLK(1);
	}
	M74HC595_LATCH(1);		 //将移位寄存器的值锁存到输出寄存器中
	M74HC595_OUTPUT_EN(0);	//输出有效，点亮LED灯
}
/****************************************
函 数 名: void m74hc595_reset(unsigned short data);
功能说明: 清除M74HC595移位寄存器
参    数:            
返 回 值:  
*****************************************/
void m74hc595_reset(void)
{
	M74HC595_RST(0);
	delay_us(1);
	M74HC595_RST(1);
}

