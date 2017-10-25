//******************************************
//           This is a c File Head
//作者：   
//日期     
//功能
//备注
//******************************************   

#ifndef __TASK_H_
#define __TASK_H_

typedef enum 
{
	PB0_PB1 = 1,
	PB0_PB1_CHATAB,
	CASE_PB0_PB1,
	CASE_PB0_PB1_CHATAB,
	ADP_PB0_PB1,
	ADP_PB0_PB1_CHATAB,
	CASE_PB1_PB0,
	ADP_PB1_PB0,
	PB1_PB0_CHATAB,
	CASE_PB1_PB0_CHATAB,
	ADP_PB1_PB0_CHATAB,
	PB0_PB1_PB2,
	PB0_CAHTAB,
	CASE_PB0,
	ADP_PB0,
	PB0_CHATAB
	
} DEV_POS;
typedef enum 
{
	BAT0_LARGE = 1,
	BAT0_SMALL,
	BAT0_LOW,
	BAT1_LOW
	
} BAT_EVT;

#endif