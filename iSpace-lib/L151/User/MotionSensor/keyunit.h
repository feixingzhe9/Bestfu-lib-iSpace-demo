#ifndef __KEYUNIT_H
#define __KEYUNIT_H

#include "gpio.h"
#include "stdio.h"	 
#include "BF_type.h"	

#define KEY_UPLOAD			1	//按键实时上报使能标记

#define KEY_MAX_CHN  	14
#define KEY_START_NUM 	1

#define  KEY_SHORT              1
//#define  KEY_SHORT_END          2
#define  KEY_LONG_BEGIN         3
#define  KEY_LONG_KEEP          4
#define  KEY_LONG_END           5
#define  KEY_LONG_3S            6      
#define  KEY_LONG               2





typedef struct
{
	u8  KeyLvl;    // 按键电平，1表示有效，0表示无效
	u8  Lstartf;   // 长按开始标志，1表示开始，0表示没开始
	u16  Time;      // 时间计数器，用于确定短按或是长按
	u16  LTimecnt;  // 长按保持，触发间隔
	u8 KeyLOCK;
	u16 count;
}KeyItem;

typedef struct
{
	KeyItem   key[KEY_MAX_CHN];
}KeyTable;

extern KeyTable keypara;

#define  KEY_VALID_LVL             1          // 按键有效电平，即按钮按下的实际信号
#define  KEY_INVALID_LVL    !KEY_VALID_LVL    // 按键无效电平，无按键时的电平状态

#define KEY_LOCK 1
#define KEY_UNLOCK !KEY_LOCK 
#define LOCK_TIME 150  

void KeyDeal(u16 key, u16 keytmp);
void KeyTimeCnt(void);
void KeyScan(void);



#endif	   
















