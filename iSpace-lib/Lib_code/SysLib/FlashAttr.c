/***************************Copyright BestFu 2014-05-14*************************
��	����	FlaseAttr.c
˵	����	����ICFlash���ݲ����������
��	�룺	Keil uVision4 V4.54.0.0
��	����	v1.0
��	д��	Unarty
��	�ڣ�	2013-11-22
��  ��:     2014.12.25 Unarty ���ݲ�ͬ�洢��С��Flash,���·�������������пռ��С
*******************************************************************************/
#include "UnitCfg.h"
#include "FlashAttr.h"
#include "Updata.h" 
#include "Thread.h"
#include "SI4432.h"
#include "WDG.h"
#include "DevPartTab.h"
#include "Updata.h"


//Private function declaration
static MsgResult_t Get_DevUpgradeReady_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara);
static MsgResult_t Get_IAPPackCheck_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara);
static MsgResult_t Set_IAPDataCRC_Attr(UnitPara_t *data);

/*******************************************************************************
�� �� ���� 	Set_IAPReady_Attr 
����˵����  ��������׼������
��	  ��:   data[0]: Ŀ�굥Ԫ
			data[1]: ��������
�� �� ֵ��  ��Ϣִ�н��
*******************************************************************************/
MsgResult_t Set_IAPReady_Attr(UnitPara_t *pData)
{
	WDG_Feed();
	switch(pData->data[0])
	{
		case 0xF1:
		{		
			return (MsgResult_t)UpgradePreStage(pData);
		}
		case 0xF3:
		{		
			return Set_IAPDataCRC_Attr(pData);
		}
		default:
		{
			return PARA_MEANING_ERR;
		}
	}
}

/*******************************************************************************
�� �� ��:  	Get_IAPReady_Attr
����˵��:  	��ȡ�豸����׼��״̬
��    ��:  	data[0]: Ŀ�굥Ԫ
			data[1]: ��������
			rLen:	���ز�������
			rpara:	���ز�������
�� �� ֵ:  	��Ϣִ�н��
*******************************************************************************/
MsgResult_t Get_IAPReady_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara)
{
	WDG_Feed();
	switch(pData->data[0])
	{	
		case 0xF0:
		{		
			return (MsgResult_t)Get_DevUpgradeReady_Attr(pData, rlen, rpara);
		}
		case 0xF2:
		{
			return (MsgResult_t)Get_IAPPackCheck_Attr(pData, rlen, rpara);
		}
		default:
		{
			return PARA_MEANING_ERR;
		}	
	}	
}

/*******************************************************************************
�� �� ���� 	Set_IAPPackSave_Attr
����˵����  �������ݰ�����
��	  ��:   data[0]: Ŀ�굥Ԫ
			data[1]: ��������       
�� �� ֵ�� 	��Ϣִ�н��
*******************************************************************************/
MsgResult_t Set_IAPPackSave_Attr(UnitPara_t *pData)
{
	WDG_Feed();	
	if (0xF1 == UPDATA_LEVEL)
	{			
		return (MsgResult_t)Updata_PackProcess(*(u16*)&pData->data[0], pData->len - 2, (u8*)&pData->data[2]);//���ݰ�����
	}
	else if (0xF2 == UPDATA_LEVEL)
	{
		return COMPLETE;
	}
	else
	{
		UPDATA_LEVEL = 0;
	}	
	return UPGRADE_STATE_ERR;
}

/*******************************************************************************
�� �� ���� 	Get_DevUpgradeReady_Attr
����˵����  ��ȡ�豸����׼��״̬
��	  ��:   data[0]: Ŀ�굥Ԫ
			data[1]: ��������
			rLen:	���ز�������
			rpara:	���ز�������
�� �� ֵ:  	��Ϣִ�н��
*******************************************************************************/
static MsgResult_t Get_DevUpgradeReady_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara)
{
	DevPivotalSet_t* pDevPivotalSet = GetDevPivotalSet();
	Boot0Info_t* pBoot0Info = (Boot0Info_t*)(pDevPivotalSet->Boot0FlagAddr);
	Soft_t* pSoft = (Soft_t*)(pDevPivotalSet->DevSoftInfoAddr);
	Hard_t* pHard = (Hard_t*)(pDevPivotalSet->DevHardInfoAddr);
	
	if(UPGRADE_BOOTLOADER == pData->data[1])//����bootloader1
	{
		*rlen 			 = 11;
		UPDATA_LEVEL	 = 0xF0;
		UpgradeAim 		 = UPGRADE_BOOTLOADER;
		*(u16*)&rpara[0] = pSoft->deviceType;
		*(u32*)&rpara[2] = pHard->hardVer;
		*(u32*)&rpara[6] = pBoot0Info->SoftVer;
		*(u8*)&rpara[10] = pHard->chipType;
		return COMPLETE;
	}
	else if(UPGRADE_APP == pData->data[1])	//����App
	{
		if(BOOTLOADER_0_JUMP_FLAG == pBoot0Info->jumpFlag)
		{
			return BOOT_LOSE_ERR;	//����bootloader��ʧ�Ĵ�����
		}
		else
		{
			*rlen 			 = 11;
			UpgradeAim 		 = UPGRADE_APP;
			UPDATA_LEVEL 	 = 0xF0;
			*(u16*)&rpara[0] = pSoft->deviceType;
			*(u32*)&rpara[2] = pHard->hardVer;
			*(u32*)&rpara[6] = pSoft->SoftVer;
			*(u8*)&rpara[10]= pHard->chipType;
			return COMPLETE;						
		}
	}	
	return PARA_MEANING_ERR;
}

/*******************************************************************************
�� �� ��:  	Get_IAPPackCheck_Attr
����˵��:  	��ȡ�豸����
��    ��:  	data[0]: Ŀ�굥Ԫ
			data[1]: ��������
			rLen:	���ز�������
			rpara:	���ز�������
�� �� ֵ:  	��Ϣִ�н��
*******************************************************************************/
static MsgResult_t Get_IAPPackCheck_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara)
{
	WDG_Feed();
    if (0xF1 == UPDATA_LEVEL)
	{
		if (Updata_PackCheck(rlen, (u16*)rpara))
		{	//û�е���	
			UPDATA_LEVEL = 0xF2;
		}
		return COMPLETE;
	}
	else if (0xF2 == UPDATA_LEVEL)
	{
		return COMPLETE;	
	}
	else
	{
		UPDATA_LEVEL = 0;
	}
	return UPGRADE_STATE_ERR;
}

/*******************************************************************************
�� �� ��:  	Set_IAPDataCRC_Attr
����˵��:  	��ȡ��������У����
��    ��:  	data[0]: Ŀ�굥Ԫ
			data[1]: ��������
			rLen:	���ز�������
			rpara:	���ز�������
�� �� ֵ:  	��Ϣִ�н��
*******************************************************************************/
static MsgResult_t Set_IAPDataCRC_Attr(UnitPara_t *pData)
{
	WDG_Feed();
	if (0xF2 == UPDATA_LEVEL)
	{
		*(u8*)&pData->data[5] ^= *(u8*)&pData->data[6];
		*(u8*)&pData->data[6] ^= *(u8*)&pData->data[5];
		*(u8*)&pData->data[5] ^= *(u8*)&pData->data[6];

		if (Updata_Calibrate(*(u32*)&pData->data[1], *(u16*)&pData->data[5]) == TRUE)
		{
			if (Updata_Flag())
			{
				UPDATA_LEVEL = 0xF3;				
				WDG_FeedOFF();	
				return COMPLETE;
			} 	
		}
	}
	else if (0xF3 == UPDATA_LEVEL){	
		return COMPLETE;
	}
	UPDATA_LEVEL = 0;
	return CMD_EXE_ERR;
}

/*******************************************************************************
�� �� ���� 	Set_433Channel_Attr
����˵����  ����433�ŵ�����
��	  ��:   data[0]: Ŀ�굥Ԫ
			data[1]: ��������       
�� �� ֵ��  ��Ϣִ�н��
*******************************************************************************/
MsgResult_t Set_433Channel_Attr(UnitPara_t *pData)
{
	if ((pData->len != 1))	//���������Ȳ��Ϸ�
	{
		return PARA_LEN_ERR;
	}
	else if (pData->data[0] < CHANNEL_MIN     //���������ݲ��Ϸ�
		|| pData->data[0] > CHANNEL_MAX
		)
	{
		return PARA_MEANING_ERR;
	}
	
	if (pData->data[0]  != Channel_Get())
	{
		if (Updata_Channel(pData->data[0]) == FALSE)	//�����ŵ�ʧ��
		{		
			return CMD_EXE_ERR;
		}
		Thread_Login(ONCEDELAY, 0, 800, &Si4432_Init);	//�ر�ι�����豸�Զ���������
	}

	return COMPLETE;
}

/*******************************************************************************
�� �� ��:  	Get_433Channel_Attr
����˵��:  	��ȡ433�ŵ�����
��    ��:  	data[0]: Ŀ�굥Ԫ
			data[1]: ��������
			rLen:	���ز�������
			rpara:	���ز�������
�� �� ֵ:  	��Ϣִ�н��
*******************************************************************************/
MsgResult_t Get_433Channel_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara)
{
	*rpara = Channel_Get();		//�ŵ�ֵ
	*rlen = 1;
	
	return COMPLETE;
}

/**************************Copyright BestFu 2014-05-14*************************/