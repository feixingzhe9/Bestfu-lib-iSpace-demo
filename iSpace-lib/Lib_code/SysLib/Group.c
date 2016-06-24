/***************************Copyright BestFu 2016-06-24*************************
文	件：    Group.c
说	明:	    iSpace分组处理
编	译：    Keil uVision4 V4.54.0.0
版	本：    v1.0
编	写：    xjx
日	期：    2016-06-24
修  改:     暂无
*******************************************************************************/

#include "Group.h"
#include "SysHard.h"
#include "EEPROM.h"

GroupManage_t groupManage;
GroupManage_t *pGroupManage = &groupManage;



/*******************************************************************************
函 数 名:  	GroupNumExist
功能说明:  	判断分组号是否已经存在
参    数:  	groupNum:分组号
返 回 值:  	大于0:存在，
			0:不存在
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
函 数 名:  	DelOneGroupNum
功能说明:  	删除一个分组号(非场景)
参    数:  	groupNum:分组号
			unit	:单元号
返 回 值:  	
			
*******************************************************************************/
u8 DelOneGroupNum(u32 groupNum, u8 unit)
{
	u8 i = 0;
	
	i = GroupNumExist(groupNum,unit);
	
	if(i > 0)//存在
	{

		if(i == pGroupManage->cnt)//需要删除的分组号在最后面，直接删除
		{
//			pGroupManage->group[pGroupManage->cnt - 1].groupNum = 0;
//			pGroupManage->group[pGroupManage->cnt - 1].unit = 0;
			
			pGroupManage->cnt--;					
		}
		else		//需要删除的分组号不在最后面，把最后面的分组号覆盖到要删除的位置
		{
			pGroupManage->group[i - 1].groupNum = pGroupManage->group[pGroupManage->cnt - 1].groupNum;
			pGroupManage->group[i - 1].unit = pGroupManage->group[pGroupManage->cnt - 1].unit;//用最后一个分组号把要删除的分组号覆盖
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
函 数 名:  	Set_Scene_Attr
功能说明:  	设置场景
参    数:  	data[0]: 目标单元
			data[1]: 参数长度
返 回 值:  	消息执行结果
*******************************************************************************/
MsgResult_t Set_New_Group_Attr(UnitPara_t *pData)
{
	u8 num = 0;
	u8 i = 0;
	u8 j = 0;
	u32 groupNum = 0;
	u8 unit = 0;
	u8 flag = 0;//
	u8 eepromWriteStartPos = pGroupManage->cnt;//记录本次 “增加” 操作开始写入EEPROM的位置
	u8 eepromWriteCnt = 0;//记录本次 “增加” 操作写入EEPROM的分组号的数量
	Group_t buf[GROUP_ONECE_SET_MAX] = {0};
	
//	if(pGroupManage->cnt > 0)
//	{
//		eepromWriteStartPos = pGroupManage->cnt;
//	}
	
	if((pData->len < 6) || (pData->len > (2+ (GROUP_ONECE_SET_MAX << 2) ) ) || ((pData->len - 2) % 4))//参数判断
	{
		return PARA_LEN_ERR;
	}
	
	num = (pData->len - 2) >> 2;
	unit = pData->data[0];
	
	if(1 == pData->data[1])//增加
	{
		if(pGroupManage->cnt + num > GROUP_NUM_MAX)//剩余空间判断
		{
			return DATA_SAVE_OVER;
		}
		for(i = 0; i < num; i++)
		{
			groupNum = (u32)pData->data[2 + (i<<2)];
			if(0 == GroupNumExist(groupNum,unit))//该分组号不存在，则写入
			{
				flag = 1;
				pGroupManage->group[pGroupManage->cnt].groupNum = groupNum;
				pGroupManage->group[pGroupManage->cnt].unit = unit;			//写入内存
				pGroupManage->cnt++;
				
				buf[eepromWriteCnt].groupNum = groupNum;
				buf[eepromWriteCnt].unit = unit;
				eepromWriteCnt++;
			}
		}
		if(1 == flag)//说明有需要增加的分组号
		{
			WriteDataToEEPROMEx(GROUP_START_ADDR ,1,pGroupManage->cnt);
			WriteDataToEEPROM(GROUP_START_ADDR + 1 + (eepromWriteStartPos * ONE_GROUP_SPACE),\
										eepromWriteCnt * ONE_GROUP_SPACE, (u8*)buf);
		}	
	}
	else if(2 == pData->data[1])		//修改
	{
		if(pData->len != 10)		//修改操作的数据长度固定为10
		{
			return PARA_LEN_ERR;
		}
		
		groupNum = (u32)pData->data[2];//旧的分组号
		i = GroupNumExist(groupNum,unit);
		if(0 == i)					//找不到旧的分组号
		{
			return PARA_MEANING_ERR;
		}
		else
		{
//			i -= 1;
			
			pGroupManage->group[i - 1].groupNum = (u32)pData->data[6];//赋值新的分组号
			pGroupManage->group[i - 1].unit = unit;
			
			WriteDataToEEPROM(GROUP_START_ADDR + 1 + (i - 1) * ONE_GROUP_SPACE, ONE_GROUP_SPACE,(u8*)&pGroupManage->group[i - 1]);
		}
	}
	else if(3 == pData->data[1])		//删除
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

