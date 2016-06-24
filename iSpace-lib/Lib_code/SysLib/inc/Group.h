/***************************Copyright BestFu 2014-05-14*************************
文	件：	Group.h
说	明：	iSpace分组操作头文件
编	译：	Keil uVision4 V4.54.0.0
版	本：	v1.0
编	写：	xjx
日	期：	2016-06-24
*******************************************************************************/
#ifndef __GROUP_H
#define __GROUP_H


#include "UnitCfg.h"

#define GROUP_NUM_MAX			150	//最大分组数量(不包括场景分组)
#define GROUP_SCENE_NUM_MAX		256	//最大场景分组数量

#define GROUP_ONECE_SET_MAX		40	//一次设置分组的最大数量

#define GROUP_START_ADDR		(0x200)
#define ONE_GROUP_SPACE				(sizeof(Group_t))


typedef struct
{
	u8  unit;	//
	u32 groupNum;
}Group_t;

typedef struct
{
	u8 cnt;
	Group_t group[GROUP_NUM_MAX];
}GroupManage_t;




typedef struct
{
	u8  unit;
	u8  addr;
	u32 groupSceneNum;
}GroupSceneIndex_t;



typedef struct
{
	u8 cnt;
	GroupSceneIndex_t groupScene[GROUP_SCENE_NUM_MAX];
}GroupSceneManage_t;



#endif
/**************************Copyright BestFu 2014-05-14*************************/

