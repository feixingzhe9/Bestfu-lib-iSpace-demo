/*******************************************************************************
**	文    件: LowPower.c
**  功    能：STM32L151 低功耗驱动
**  编    译：Keil uVision5 V5.10
**	芯    片: STM32L151xx
**  版    本：V1.0.0
**  创建日期：2014.07.10
**  修改日期：2014.07.10
**  说    明：  
********************************************************************************/
#include "gpio.h"
#include "LowPower.h"
#include "Cube6.h"
#include "SysHard.h"

#define CR_VOS_MASK              ((uint32_t)0xFFFFE7FF)
#define PWR_VoltageScaling_Range1       PWR_CR_VOS_0
#define PWR_VoltageScaling_Range2       PWR_CR_VOS_1
#define PWR_VoltageScaling_Range3       PWR_CR_VOS

INT8U In_Lpm_Flag = 0;


void WKUP_Port_Init(void)
{
	GPIOx_Cfg(GPIO_A, pin_0, IN_DOWN);
}

void Get_WKUP_State(void)
{
	if( pin_0 == GPIOx_Get(GPIO_A, pin_0))	In_Lpm_Flag = 0;  // 睡眠等待时间重新计时
}

/*******************************************************************************
**函	数:  	RunAndCheck_StandbyMode()
**功	能:  	100ms 运行一次  计时15s 进入StandBy 模式
**参    数:  	no
**返	回:  	no
**说	明：	Seven modify 2014.04.04
********************************************************************************/
void CheckStandbyMode(void)
{
	if(In_Lpm_Flag++>=100)
	{
		In_Lpm_Flag = 0;
		#if (LPM_EN>0)
			Standby_Mode();
		#endif			
	}    
}

#if (LPM_EN > 0)

void Low_Power_Select(INT8U LPM)
{
//	WriteEepromPara((INT8U *)&g_stEeEx.Sys.Board.SerialNo,sizeof(g_stEeEx.Sys.Board.SerialNo));
	switch(LPM)
	{
		case 0://睡眠模式
			Sleep_Mode();
			break;
		case 1://低电压运行
			LP_Run_Mode();
			break;
		case 2://低电压睡眠模式
			
			break;
		case 3://停止模式
			Stop_Mode();
			break;
		case 4://待机模式
			Standby_Mode();
			break;
	}
}
void Sleep_Mode(void)
{
	Close_device();
	//LPM_IO_process();
	
	RCC->APB1ENR|=1<<28;    //使能电源时钟	
	PWR->CR &= ~(3<<0);		//清除PDDS 和LPDSR
	PWR->CR |= 1<<0;		//set LPDSR
	/* Clear SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
	__WFI();				 //执行WFI指令	
}
/* PWR_EnterLowPowerRunMode */
void LP_Run_Mode(void)
{
//	RCC->APB1ENR |= 1<<28;  //使能电源时钟
//	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range2);//1.5v
//	PWR->CR |= PWR_CR_LPSDSR;
//    PWR->CR |= PWR_CR_LPRUN;   	
}

void Stop_Mode(void)
{
//	/*关闭spi2 和tim3*/
//	Close_device();
//	/*IO模拟输入*/
//	LPM_IO_process();
//	
//	/*进入low power mode*/
//	LP_Run_Mode();
//	RCC->APB1ENR|=1<<28;     //使能电源时钟	

//	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range2);//1.5v
//	 
//	PWR->CR &= ~(3<<0);		//清除PDDS 和LPDSR
//	PWR->CR |= 1<<0;		//set LPDSR
//	/* Set SLEEPDEEP bit of Cortex System Control Register */
//	SCB->SCR |= SCB_SCR_SLEEPDEEP;
//	RCC->APB1ENR &= ~(1<<28);     /*关闭电源时钟*/	
//	__WFI();
//	/* Reset SLEEPDEEP bit of Cortex System Control Register */
//	SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);  	
}

//待机模式
void Standby_Mode(void)
{
	//关中断
	SysTick->CTRL = 0;					//Systick
	NVIC_DisableIRQ(EXTI15_10_IRQn);	//si4432中断	
	NVIC_DisableIRQ(USART1_IRQn);		//串口1中断
	DisableIRQ();						//禁止所有中断
	
	//Close_device();
	//LPM_IO_process();	
	RF_SWITCH_OFF; 			//433进入睡眠	
	SPI2->CR1  	 &= ~(1<<6); 	//关闭SPI2
	RCC->APB1ENR &= ~(1<<14);   //关闭SPI2时钟
	RCC->APB2ENR &= ~(1<<14);   //关闭USART1时钟
	RCC->AHBRSTR |= 1<<0;  		//Reset GPIOA
	
	
	RCC->APB1ENR|=1<<28;     //使能电源时钟	 
	/* Set SLEEPDEEP bit	: Select SleepDeep mode*/
	SCB->SCR|= SCB_SCR_SLEEPDEEP;	
	/* Set PDDS bit			: Select STANDBY mode */
	PWR->CR |= PWR_CR_PDDS; 
	/* Set CWUF bit			: Clear Wakeup flag */
	PWR->CR |= PWR_CR_CWUF; 	
	/* Set EWUP1 bit		: Enable EWUP pin 1 :PA0*/
	PWR->CSR|= PWR_CSR_EWUP1;
	/* Request Wait For Interrupt */
	__WFI();
}


void Close_device(void)
{
	TIM3->CR1  &= ~(1<<0);  
	SPI2->CR1  &= ~(1<<6); 
	WWDG->CR   &= ~(1<<7);		//关闭看门狗
	RCC->APB1ENR &= ~(1<<1);	//关闭TIM3时钟
	RCC->APB1ENR &= ~(1<<14);   //关闭SPI2时钟
	RCC->APB1ENR &= ~(1<<11);   //关闭SPI2时钟
}

void LPM_IO_process(void)
{	
#if 1 //standby
	RCC->AHBRSTR |= 1<<0;  //Reset GPIOA
#endif

}
/**
  * @brief  Configures the voltage scaling range.
  * @note   During voltage scaling configuration, the system clock is stopped 
  *         until the regulator is stabilized (VOSF = 0). This must be taken 
  *         into account during application developement, in case a critical 
  *         reaction time to interrupt is needed, and depending on peripheral 
  *         used (timer, communication,...).
  *             
  * @param  PWR_VoltageScaling: specifies the voltage scaling range.
  *   This parameter can be:
  *     @arg PWR_VoltageScaling_Range1: Voltage Scaling Range 1 (VCORE = 1.8V).
  *     @arg PWR_VoltageScaling_Range2: Voltage Scaling Range 2 (VCORE = 1.5V).
  *     @arg PWR_VoltageScaling_Range3: Voltage Scaling Range 3 (VCORE = 1.2V) 
  * @retval None
  */
void PWR_VoltageScalingConfig(uint32_t PWR_VoltageScaling)
{
  uint32_t tmp = 0;
  
  tmp = PWR->CR;

  tmp &= CR_VOS_MASK;
  tmp |= PWR_VoltageScaling;
  
  PWR->CR = tmp & 0xFFFFFFF3;

}
void EXTI0_IRQHandler(void)
{	
	EXTI->PR = 1<<0;  //清除LINE0上的中断标志位 
} 
#endif

void StandbyCountReset(void)
{
}





