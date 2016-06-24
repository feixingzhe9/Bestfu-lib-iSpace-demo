#ifndef __AT24C0X_H__
#define __AT24C0X_H__  

#include "stm32l1xx.h"
#include "BF_type.h"
#include "GPIO.h"

#define DEVICE_ADDR		0xD0	// MPU6050 PIN AD0 =0   : 1101 000x

//====================================================
//*******IIC Inteface STM32L151C8T6 I/O***************
#define GPIO_IIC_SCL		GPIOA
#define PORT_IIC_SCL		GPIO_A
#define  PIN_IIC_SCL		(1<<8)

#define GPIO_IIC_SDA		GPIOA
#define PORT_IIC_SDA		GPIO_A
#define  PIN_IIC_SDA		(1<<9)
#define  NUM_IIC_SDA		9
//=====================================================

#define	SCL1		GPIO_IIC_SCL->BSRRL |= PIN_IIC_SCL
#define SCL0		GPIO_IIC_SCL->BSRRH |= PIN_IIC_SCL

#define	SDA1		GPIO_IIC_SDA->BSRRL |= PIN_IIC_SDA
#define SDA0		GPIO_IIC_SDA->BSRRH |= PIN_IIC_SDA

#define SDA_IN()	GPIOx_Cfg(PORT_IIC_SDA, PIN_IIC_SDA, IN_UP)
#define SDA_OUT()	GPIOx_Cfg(PORT_IIC_SDA, PIN_IIC_SDA, OUT_PU_40M)

//#define SDA_IN()	GPIO_IIC_SDA->MODER &= ~(3<<(NUM_IIC_SDA<<1))		//输入模式 00
//#define SDA_OUT()	GPIO_IIC_SDA->MODER |=  (1<<(NUM_IIC_SDA<<1))		//输出模式 01

#define Get_SDA()	(GPIO_IIC_SDA->IDR & PIN_IIC_SDA)
//======================================================
void  IIC_Init_PORT(void);
void  IIC_Start(void);
void  IIC_Stop(void);

void  IIC_ACK(void); 
void  IIC_NACK(void); 
u8    IIC_WaitAck(void);

void  IIC_SendByte(u8 dat);
u8    IIC_GetByte(void);

void  IIC_WriteByte(u8 Addr,u8 data);
u8    IIC_ReadByte(u8 Addr);

void  IIC_WriteWord(u8 Addr,u16 data);
u16   IIC_ReadWord(u8 Addr);

void  IIC_WriteDataN(u8 Addr,u8 *pData ,u8 Number);
void  IIC_ReadDataN(u8 Addr,u8 *pData,u8 Number);


#endif
