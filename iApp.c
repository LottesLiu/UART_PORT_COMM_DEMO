
#include "MQ6812.h"
#include "iApp.h"


//	delay_times(t_1ms, 800);				// 用于 Normal mode, 不适用Slow mode
//void delay_times(uchar tBase, uint x);	// 用于 Normal mode, 不适用Slow mode
//.....................|...........| x: 设定延迟时间变数
//.....................| tBase: 设定延迟单位: t_1ms/t_100us 等...
//#define t_1ms		0
//#define t_100us	1



//*********************************************************************
// 函数名	: delay_times(uchar tBase, uint x)
// 函数功能	: 延时函数
// 备注		: ==> t_1ms   = 0;
// 			: ==> t_100us = 1;
// 			: ...
//*********************************************************************
void delay_times(uchar tBase, uint x)
{
	uint  i, cgcrT;

//	uchar cgcrF[4]={ 2, 4,  8, 1 };	// HIRC =>  8MHz
	uchar cgcrF[4]={ 4, 8, 16, 2 };	// HIRC => 16MHz

//	...... ...... ...... delay for HIRC ...... ...... ......
	if( SYSCR2.bit.b4 == 0 )
	{
		cgcrT = cgcrF[CGCR.byte];		//0:fc/4, 1:fc/2, 2:fc/1, 3:fc/8
		switch(tBase){
			__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
			case 0:		// t_1ms
				cgcrT *= 110;
				for(; x>0; x--)
					for(i=0; i<cgcrT; i++){}
				break;
			case 1:		// t_100us
				cgcrT *= 11;
				for(; x>0; x--)
					for(i=0; i<cgcrT; i++){}
				break;
		}
	}
//	...... ...... ...... delay for LIRC ...... ...... ......
	else for(; x>0; x--){}

	WDCDR.byte=0x4e; 			//clear wdt
}


































