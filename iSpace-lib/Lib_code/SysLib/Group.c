/***************************Copyright BestFu 2016-06-24*************************
��	����    Group.c
˵	��:	    iSpace���鴦��
��	�룺    Keil uVision4 V4.54.0.0
��	����    v1.0
��	д��    xjx
��	�ڣ�    2016-06-24
��  ��:     ����
*******************************************************************************/

#include "Group.h"
#include "SysHard.h"
#include "EEPROM.h"

GroupManage_t groupManage;
GroupManage_t *pGroupManage = &groupManage;



/*******************************************************************************
�� �� ��:  	GroupNumExist
����˵��:  	�жϷ�����Ƿ��Ѿ�����
��    ��:  	groupNum:�����
�� �� ֵ:  	����0:���ڣ�
			0:������
*******************************************************************************/
u8 GroupNumExist(u32 groupNum,u8 unit)
{
	u8 i = 0;
	for(i = 0; i < pGroupManage->cnt; i++)
	{
		if((groupNum == pGroupManage->group[i].groupNum) && (unit == pGroupManage->group[i].unit))
		{
			return (i + 1);//
		}
	}
	
	return 0;
}

/*******************************************************************************
�� �� ��:  	DelOneGroupNum
����˵��:  	ɾ��һ�������(�ǳ���)
��    ��:  	groupNum:�����
			unit	:��Ԫ��
�� �� ֵ:  	
			
*******************************************************************************/
u8 DelOneGroupNum(u32 groupNum, u8 unit)
{
	u8 i = 0;
	
	i = GroupNumExist(groupNum,unit);
	
	if(i > 0)//����
	{

		if(i == pGroupManage->cnt)//��Ҫɾ���ķ����������棬ֱ��ɾ��
		{
//			pGroupManage->group[pGroupManage->cnt - 1].groupNum = 0;
//			pGroupManage->group[pGroupManage->cnt - 1].unit = 0;
			
			pGroupManage->cnt--;					
		}
		else		//��Ҫɾ���ķ���Ų�������棬�������ķ���Ÿ��ǵ�Ҫɾ����λ��
		{
			pGroupManage->group[i - 1].groupNum = pGroupManage->group[pGroupManage->cnt - 1].groupNum;
			pGroupManage->group[i - 1].unit = pGroupManage->group[pGroupManage->cnt - 1].unit;//�����һ������Ű�Ҫɾ���ķ���Ÿ���
//			pGroupManage->group[pGroupManage->cnt - 1].groupNum = 0;
//			pGroupManage->group[pGroupManage->cnt - 1].unit = 0;
			
			pGroupManage->cnt--;
			
			WriteDataToEEPROM(GROUP_START_ADDR + 1 + (i - 1) * ONE_GROUP_SPACE, ONE_GROUP_SPACE,(u8*)&pGroupManage->group[i - 1]);
		}
		WriteDataToEEPROMEx(GROUP_START_ADDR, 1, pGroupManage->cnt);
	}
	return 1;
}


/*******************************************************************************
�� �� ��:  	Set_Scene_Attr
����˵��:  	���ó���
��    ��:  	data[0]: Ŀ�굥Ԫ
			data[1]: ��������
�� �� ֵ:  	��Ϣִ�н��
*******************************************************************************/
MsgResult_t Set_New_Group_Attr(UnitPara_t *pData)
{
	u8 num = 0;
	u8 i = 0;
	u8 j = 0;
	u32 groupNum = 0;
	u8 unit = 0;
	u8 flag = 0;//
	u8 eepromWriteStartPos = pGroupManage->cnt;//��¼���� �����ӡ� ������ʼд��EEPROM��λ��
	u8 eepromWriteCnt = 0;//��¼���� �����ӡ� ����д��EEPROM�ķ���ŵ�����
	Group_t buf[GROUP_ONECE_SET_MAX] = {0};
	
//	if(pGroupManage->cnt > 0)
//	{
//		eepromWriteStartPos = pGroupManage->cnt;
//	}
	
	if((pData->len < 6) || (pData->len > (2+ (GROUP_ONECE_SET_MAX << 2) ) ) || ((pData->len - 2) % 4))//�����ж�
	{
		return PARA_LEN_ERR;
	}
	
	num = (pData->len - 2) >> 2;
	unit = pData->data[0];
	
	if(1 == pData->data[1])//����
	{
		if(pGroupManage->cnt + num > GROUP_NUM_MAX)//ʣ��ռ��ж�
		{
			return DATA_SAVE_OVER;
		}
		for(i = 0; i < num; i++)
		{
			groupNum = (u32)pData->data[2 + (i<<2)];
			if(0 == GroupNumExist(groupNum,unit))//�÷���Ų����ڣ���д��
			{
				flag = 1;
				pGroupManage->group[pGroupManage->cnt].groupNum = groupNum;
				pGroupManage->group[pGroupManage->cnt].unit = unit;			//д���ڴ�
				pGroupManage->cnt++;
				
				buf[eepromWriteCnt].groupNum = groupNum;
				buf[eepromWriteCnt].unit = unit;
				eepromWriteCnt++;
			}
		}
		if(1 == flag)//˵������Ҫ���ӵķ����
		{
			WriteDataToEEPROMEx(GROUP_START_ADDR ,1,pGroupManage->cnt);
			WriteDataToEEPROM(GROUP_START_ADDR + 1 + (eepromWriteStartPos * ONE_GROUP_SPACE),\
										eepromWriteCnt * ONE_GROUP_SPACE, (u8*)buf);
		}	
	}
	else if(2 == pData->data[1])		//�޸�
	{
		if(pData->len != 10)		//�޸Ĳ��������ݳ��ȹ̶�Ϊ10
		{
			return PARA_LEN_ERR;
		}
		
		groupNum = (u32)pData->data[2];//�ɵķ����
		i = GroupNumExist(groupNum,unit);
		if(0 == i)					//�Ҳ����ɵķ����
		{
			return PARA_MEANING_ERR;
		}
		else
		{
//			i -= 1;
			
			pGroupManage->group[i - 1].groupNum = (u32)pData->data[6];//��ֵ�µķ����
			pGroupManage->group[i - 1].unit = unit;
			
			WriteDataToEEPROM(GROUP_START_ADDR + 1 + (i - 1) * ONE_GROUP_SPACE, ONE_GROUP_SPACE,(u8*)&pGroupManage->group[i - 1]);
		}
	}
	else if(3 == pData->data[1])		//ɾ��
	{
		for(j = 0; j < num; j++)
		{
			groupNum = (u32)pData->data[2 + (j<<2)];
			DelOneGroupNum(groupNum,unit);
		}
		WriteDataToEEPROMEx(GROUP_START_ADDR, 1, pGroupManage->cnt);		
	}
	
	return COMPLETE;
}

/**************************Copyright BestFu 2014-05-14*************************/

