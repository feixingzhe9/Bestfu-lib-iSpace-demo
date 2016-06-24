#ifndef _POWER_H
#define _POWER_H

#include "sys.h"
#include "GPIO.h"

#ifndef TRUE	
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef INT8U 
#define INT8U unsigned char
#endif

#ifndef INT16U 
#define INT16U unsigned short int
#endif

#ifndef INT32U 
#define INT32U unsigned int
#endif



#define RF_POWER_PORT    GPIO_D   
#define RF_POWER_PIN     pin_2     

#define LED_POWER_PORT    GPIO_C   
#define LED_POWER_PIN     pin_15   
									
#define VOICE_POWER_PORT    GPIO_C   
#define VOICE_POWER_PIN     pin_15   
									
#define TFT_POWER_PORT    GPIO_C   
#define TFT_POWER_PIN     pin_9   


#define RF_POWER_OUT                 GPIOx_Cfg(RF_POWER_PORT,  RF_POWER_PIN,  OUT_PP_400K)
#define LED_POWER_OUT                GPIOx_Cfg(LED_POWER_PORT, LED_POWER_PIN, OUT_PP_400K)
#define VOICE_POWER_OUT                GPIOx_Cfg(VOICE_POWER_PORT, VOICE_POWER_PIN, OUT_PP_400K)
#define TFT_POWER_OUT                GPIOx_Cfg(TFT_POWER_PORT, TFT_POWER_PIN, OUT_PP_400K)


#ifndef	POWER_POWER_IO_STATUS
#define POWER_IO_STATUS0(GPIOx, pin)  GPIOx_Rst(GPIOx, pin) //相应管脚置0
#define POWER_IO_STATUS1(GPIOx, pin)  GPIOx_Set(GPIOx, pin) //相应管脚置1) 
#endif

#define RF_POWER(str)   POWER_IO_STATUS##str(RF_POWER_PORT, RF_POWER_PIN)		   //数据线A
#define LED_POWER(str)  POWER_IO_STATUS##str(LED_POWER_PORT, LED_POWER_PIN)		   //数据线A
#define VOICE_POWER(str)  POWER_IO_STATUS##str(VOICE_POWER_PORT, VOICE_POWER_PIN)		   //数据线A
#define TFT_POWER(str)  POWER_IO_STATUS##str(TFT_POWER_PORT, TFT_POWER_PIN)		   //数据线A


extern void POWER_PIN_INIT(void);
extern void POWER_ON(void);
extern void POWER_OFF(void);



#endif

