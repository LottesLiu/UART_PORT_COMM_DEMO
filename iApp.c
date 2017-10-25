
#include "MQ6812.h"
#include "iApp.h"


//	delay_times(t_1ms, 800);				// ���� Normal mode, ������Slow mode
//void delay_times(uchar tBase, uint x);	// ���� Normal mode, ������Slow mode
//.....................|...........| x: �趨�ӳ�ʱ�����
//.....................| tBase: �趨�ӳٵ�λ: t_1ms/t_100us ��...
//#define t_1ms		0
//#define t_100us	1



//*********************************************************************
// ������	: delay_times(uchar tBase, uint x)
// ��������	: ��ʱ����
// ��ע		: ==> t_1ms   = 0;
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
			__asm("NOP");				// switch ���һ�� case ֮������һ�� "NOP"���������� "JP gg" ָ�
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


































