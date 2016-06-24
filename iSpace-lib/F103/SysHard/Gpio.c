/***************************Copyright BestFu 2014-05-14*************************
��	����	GPIO.c
˵	����	GPIO�˿������ļ�
��	�룺	Keil uVision4 V4.54.0.0
��	����	v1.0
��	д��	Unarty
��	�ڣ�	2013-08-09
�ޡ��ģ�	����
*******************************************************************************/
																						
#include "GPIO.h"
#include "stm32f10x.h"


/*******************************************************************************
�� �� ����	void GPIOx_Cfg(GPIO_Port GPIOx, u16 pin, GPIO_Mode mode)
����˵���� 	����GPIO����״̬
��	  ���� 	GPIOx: ��Ӧ��GPIO_(A~G)
			pin	 : �ܽ�pin_(0~15)
			mode :  ����(IN/OUT/AF)_����((IN_/ /UP|DOWN/FLOATING)
			(OUT/AF_(OP(��©)/PP(����)))_�ٶ�(2M/10M/50M) 
			�磺�����������ģʽ50M: AF_PP_50M
�� �� ֵ��	��
*******************************************************************************/
void GPIOx_Cfg(GPIO_Port GPIOx, u16 pin, GPIO_Mode mode)
{
	u32 i;
	GPIO_TypeDef *p = (GPIO_TypeDef*)(GPIO_BASE + (GPIOx<<10)); //ָ���ӦGPIO�Ļ�ַ��ַ
	 
	RCC->APB2ENR |= (1<<(GPIOx+2));	   //GPIO��ʱ��ʹ��
	
	for (i = 0; pin > 0; i++)
	{
		if (pin&0x01)  //��Ӧpin��Ҫ����
		{
            *(&p->CRL + (i>>3)) &= ~(0x0f<<((i&0x07)<<2));  //ģʽ��λ 	
			*(&p->CRL + (i>>3)) |= (mode<<((i&0x07)<<2));  //ģʽ���� 	
		}
		pin >>= 1; 
	}
}

/*******************************************************************************
�� �� ����	GPIOx_Set
����˵���� 	�����������״̬
��	  ���� 	GPIOx: ��Ӧ��GPIO_(A~G)
			pin	 : �ܽ�pin_(0~15)
�� �� ֵ��	���ú�GPIO ����Ĵ���ֵ 
ע    ��:   ��pin = 0xffff; ʱ���Դ˶˿ڵ��������Ž�����1
            ��pin = 0x0000; ����ֵ��Ϊ��ǰ����Ĵ����ڵ�ֵ
*******************************************************************************/
u16 GPIOx_Set(GPIO_Port GPIOx, u16 pin)
{
    GPIO_TypeDef *p = (GPIO_TypeDef*)(GPIO_BASE + (GPIOx<<10)); //ָ���ӦGPIO�Ļ�ַ��ַ

    p->ODR |= pin;

    return p->ODR;
}

/*******************************************************************************
�� �� ����	void GPIOx_Rst(GPIO_Port GPIOx, u16 pin)
����˵���� 	��λ�������״̬
��	  ���� 	GPIOx: ��Ӧ��GPIO_(A~G)
			pin	 : �ܽ�pin_(0~15)
�� �� ֵ��	��
ע    ��:   ��pin = 0xffff; ʱ���Դ˶˿ڵ��������Ž�����0
*******************************************************************************/
void GPIOx_Rst(GPIO_Port GPIOx, u16 pin)
{
    GPIO_TypeDef *p = (GPIO_TypeDef*)(GPIO_BASE + (GPIOx<<10)); //ָ���ӦGPIO�Ļ�ַ��ַ

    p->ODR &= ~pin;
}

/*******************************************************************************
�� �� ����	void GPIOx_Rvrs(GPIO_Port GPIOx, u16 pin)
����˵���� 	ȡ���������״̬(reverse)
��	  ���� 	GPIOx: ��Ӧ��GPIO_(A~G)
			pin	 : �ܽ�pin_(0~15)
�� �� ֵ��	��
ע    ��:   ��pin = 0xffff; ʱ���Դ˶˿ڵ��������Ž���ȡ��
*******************************************************************************/
void GPIOx_Rvrs(GPIO_Port GPIOx, u16 pin)
{
    GPIO_TypeDef *p = (GPIO_TypeDef*)(GPIO_BASE + (GPIOx<<10)); //ָ���ӦGPIO�Ļ�ַ��ַ

    p->ODR ^= pin;
}

/*******************************************************************************
�� �� ����	void GPIOx_Set(GPIO_Port GPIOx)
����˵���� 	��ȡ��Ӧ�˿ڸ����ŵ�����״ֵ̬
��	  ���� 	GPIOx: ��Ӧ��GPIO_(A~G)
			pin	 : �ܽ�pin_(0~15)
�� �� ֵ��	һ��16λ�������ݣ�ÿһλ��Ӧ���͵�����
ע    ��: 	��pin = 0xffff; �����������Ŷ�Ӧ��״ֵ̬
*******************************************************************************/
u16 GPIOx_Get(GPIO_Port GPIOx, u16 pin)
{
    GPIO_TypeDef *p = (GPIO_TypeDef*)(GPIO_BASE + (GPIOx<<10)); //ָ���ӦGPIO�Ļ�ַ��ַ

    return (u16)(p->IDR&pin);
}

/*******************************************************************************
�� �� ����	u32 GPIOx_Lock(GPIO_Port GPIOx, u16 pin)
����˵���� 	����Ӧ�˿��������������
��	  ���� 	GPIOx: ��Ӧ��GPIO_(A~G)
            pin	 : �ܽ�pin_(0~15)
            sta  :  LOCK/UNLOCK
�� �� ֵ��	0/(!0) : 0 FAIL, !0 OK 
ע    ��:   ����ӦGPIO�ڵ��������������´��ϵ縴λǰ�������ڸ��ĵ���������
			�˹��ܴ�������
*******************************************************************************/
//u32 GPIOx_Lock(GPIO_Port GPIOx, u16 pin, INT8U sta)
//{
//    GPIO_TypeDef *p = (GPIO_TypeDef*)(GPIO_BASE + (GPIOx<<10)); //ָ���ӦGPIO�Ļ�ַ��ַ
//
//    p->LCKR &= ~(1<<16); //����λ����
//
//    if (sta)
//    {
//        p->LCKR |= pin;
//    }
//    else
//    {
//        p->LCKR &= ~(pin);
//    }
//
//    /*GPIO������ʱ��*/
//    p->LCKR |= (1<<16);
//    p->LCKR &= ~(1<<16);
//    p->LCKR |= (1<<16);
//    if (!(p->LCKR & (1<<16)))
//    {
//        return (p->LCKR & (1<<16));
//    }
//    
//    return 0;
//}
/**************************Copyright BestFu 2014-05-14*************************/
