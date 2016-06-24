/***************************Copyright BestFu 2014-05-14*************************
��	����	Group.h
˵	����	iSpace�������ͷ�ļ�
��	�룺	Keil uVision4 V4.54.0.0
��	����	v1.0
��	д��	xjx
��	�ڣ�	2016-06-24
*******************************************************************************/
#ifndef __GROUP_H
#define __GROUP_H


#include "UnitCfg.h"

#define GROUP_NUM_MAX			150	//����������(��������������)
#define GROUP_SCENE_NUM_MAX		256	//��󳡾���������

#define GROUP_ONECE_SET_MAX		40	//һ�����÷�����������

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

