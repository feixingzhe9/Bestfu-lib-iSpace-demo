

#include "sys.h"
#include "TIMx.h"
#include "middle_led.h"
#include "adc.h"
#include "UnitCfg.h"

volatile u16 TIM2_MS=0;
/*******************************************************************************
**函	数:  	Init_TIMx()
**功	能:  	通用定时器TIM2/TIM3/TIM4/TIM5 初始化
**参    数:  	TIMx	-- TIM2/TIM3/TIM4/TIM5
**				psc		-- 预分频值
**				arr		-- 自动重装值
**返	回:  	null
**说	明：	Init_TIMx(TIM2,31,Count);	//1us 单位
				默认向上计数
********************************************************************************/
void Init_TIMx(TIM_TypeDef *TIMx,u16 psc,u16 arr)
{
	u8 x=0;

	x = ((u32)TIMx - TIM2_BASE)/(0x0400);
	RCC->APB1ENR |= (1<<x);	

 	TIMx->ARR  = arr;  			//自动重装值
	TIMx->PSC  = psc;  			//预分配器    CK_CNT = fck_psc/(psc+ 1) = 32M/(psc+1)	
								// 100Khz = 10us  : psc = 320
	TIMx->CR2 &= ~(0xF<<4);		//清主模式
	TIMx->CR2 |= 4<<4;			//

	TIMx->DIER|=1<<0; 			//使能中断	
    MY_NVIC_Init(2,3,TIM2_IRQn,2);	
	
	TIMx->CNT  = 0;				//清计数器	
    //TIMx->CR1 |= 1<<0;   		//使能定时器
}

void TIMx_Start(TIM_TypeDef *TIMx,u16 arr)
{
	TIM2_MS = 0;
 	TIMx->ARR  = arr;  			//自动重装值
	TIMx->CNT  = 0;				//清计数器	
    TIMx->CR1 |= 1<<0;   		//使能定时器	
}

u32 TIMx_Stop(TIM_TypeDef *TIMx)
{
	u32 count=0;
	count = TIMx->CNT;
	TIMx->CR1 &=~(1<<0);   		//关闭定时器
	count += TIM2_MS*1000;
	return  count;
}
/******************************************************************************
** 函数名称: TIM2_IRQHandler
** 功能描述: 定时器2中断服务程序
** 输　入:   ferq: 用户设置的输出频率值
** 返  回:   无
******************************************************************************/
void TIM2_IRQHandler(void)
{   
	if(TIM2->SR&0X0001)
	{	
		TIM2_MS++;
		//TIM2->CR1 &=~(1<<0);   		//关闭定时器
	}				   
	TIM2->SR&=~(1<<0);
}
void TIM3_IRQHandler(void)
{   
	if(TIM3->SR&0X0001)
	{	
		
	}				   
	TIM3->SR&=~(1<<0);
}
void TIM4_IRQHandler(void)
{   
	if(TIM4->SR&0X0001)
	{	
		
	}				   
	TIM4->SR&=~(1<<0);
}
void TIM5_IRQHandler(void)
{   
	if(TIM5->SR&0X0001)
	{	
		
	}				   
	TIM5->SR&=~(1<<0);
}

/**************************FILE*END********************************/

