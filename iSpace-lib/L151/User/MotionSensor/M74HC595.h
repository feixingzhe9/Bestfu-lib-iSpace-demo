/*****************************************************************************
文件： m74hc595.h
说明： m74hc595操作函数头文件
编译： Keil uVision4 V4.54.0.0
版本： v1.0
编写： linwuzhang
日期： 2013.10.21
*****************************************************************************/

#ifndef __M74HC595_H
#define __M74HC595_H

#include "GPIO.h"

extern INT16U data_temp;

/*	  
              METHOD1 
M74HC595功能说明
1、2、3、4、5、6、7、15(Q0~Q7)---------- Data Outputs
9(QH‘)---------------------------------- serial data outputs
10（SCLR）------------------------------ Shift Register Clear Input
11(SCK)	-------------------------------- Shift Register Clock Input
13(G)----------------------------------- Output Enable Input
14(SI)---------------------------------- Serial Data Input
12(RCK)--------------------------------- Storage Register Clock Input

M74HC595 与STM32 引脚的链接
14<------------->PA5	串行数据输入引脚
12<------------->PA7	存储寄存器时钟输入，上升沿将移位寄存器状态值锁存到输出寄存器
11<------------->PB1	移位寄存器时钟输入， 上升沿移位
13<------------->PA6	输出使能
10<------------->PB0	清输入以为寄存器
*/

#define _SDA_PORT    GPIO_A    
#define _SDA_PIN     pin_12    

#define OUT_PORT    GPIO_A  
#define OUT_PIN     pin_11  
									
#define LOCK_PORT    GPIO_A  
#define LOCK_PIN     pin_10

#define SCK_PORT    GPIO_A 
#define SCK_PIN     pin_9

#define RST_PORT    GPIO_A   
#define RST_PIN     pin_8


#ifndef	IO_STATUS
#define IO_STATUS0(GPIOx, pin)  GPIOx_Rst(GPIOx, pin) //相应管脚置0
#define IO_STATUS1(GPIOx, pin)  GPIOx_Set(GPIOx, pin) //相应管脚置1) 
#endif

#define M74HC595_SDA(str)   IO_STATUS##str(_SDA_PORT, _SDA_PIN)		//数据线A
#define M74HC595_LATCH(str)	 IO_STATUS##str(LOCK_PORT, LOCK_PIN)		   //上升沿将移位寄存器状态值锁存到输出寄存器
#define M74HC595_RST(str)	 IO_STATUS##str(RST_PORT, RST_PIN)		   //清除移位寄存器
#define M74HC595_OUTPUT_EN(str)	 IO_STATUS##str(OUT_PORT, OUT_PIN)	   //低电平，输出状态值；高电平，输出高阻抗	str=0,输出
#define M74HC595_SCLK(str)	 IO_STATUS##str(SCK_PORT, SCK_PIN)		   //移位寄存器移位时钟信号，上升沿移位


/****************************************
函 数 名:  m74hc595_init(void);
功能说明:  初始化74hc595相关IO管脚
参    数:            
返 回 值:  
*****************************************/
extern void m74hc595_init(void);

/****************************************
函 数 名: void m74hc595_reset(unsigned short data);
功能说明: 清除M74HC595移位寄存器
参    数:            
返 回 值:  
*****************************************/
extern void m74hc595_reset(void);
void m74hc595_output(INT16U data,INT8U cmd);
void m74hc595_All(INT16U data);
#endif 

