
#ifndef __iApp_H_
#define __iApp_H_


//-- 重定义函数变量 --//
#ifndef	uchar
#define uchar unsigned char
#endif
#ifndef	uint
#define uint  unsigned int
#endif
#ifndef	ulong
#define ulong unsigned long
#endif


//****************************************************
//	在 C 语里以二进制的方式给值：***********************
//****************************************************
#define Define2Bin(n)        \
(                            \
	( ( n >> 21 ) & 0x80 ) | \
	( ( n >> 18 ) & 0x40 ) | \
	( ( n >> 15 ) & 0x20 ) | \
	( ( n >> 12 ) & 0x10 ) | \
	( ( n >>  9 ) & 0x08 ) | \
	( ( n >>  6 ) & 0x04 ) | \
	( ( n >>  3 ) & 0x02 ) | \
	( ( n       ) & 0x01 )   \
)
#define set8bit(n)  Define2Bin(0x##n##L)

//	程序里即可用二进制写值：
//	tempVAR = set8bit(10101010);   <==>   temp = 0xAA;
//****************************************************




//****************************************************
extern uchar cnt1_10ms, cnt1_50ms, cnt_1s;
extern uchar temp_bit, temp2_bit;
extern uchar ReadID[8];



#define   flag_3s			(((BYTE_FIELD*)&temp_bit)->b7)
#define   flag_1s			(((BYTE_FIELD*)&temp_bit)->b6)
#define   flag1_50ms		(((BYTE_FIELD*)&temp_bit)->b5)
#define   flag_rec_msg	(((BYTE_FIELD*)&temp_bit)->b4)
#define   flag1_1s			(((BYTE_FIELD*)&temp_bit)->b3)
#define   flag2_50ms			(((BYTE_FIELD*)&temp_bit)->b2)
#define   flag3_50ms			(((BYTE_FIELD*)&temp_bit)->b1)
#define   tVar_0			(((BYTE_FIELD*)&temp_bit)->b0)

#define   ok1_expiry_flag			(((BYTE_FIELD*)&temp2_bit)->b7)
#define   ok2_expiry_flag			(((BYTE_FIELD*)&temp2_bit)->b6)
#define   flag2_1s			(((BYTE_FIELD*)&temp2_bit)->b5)
#define   flag_200ms			(((BYTE_FIELD*)&temp2_bit)->b4)
#define   t2Var_3			(((BYTE_FIELD*)&temp2_bit)->b3)
#define   t2Var_2			(((BYTE_FIELD*)&temp2_bit)->b2)
#define   t2Var_1			(((BYTE_FIELD*)&temp2_bit)->b1)
#define   t2Var_0			(((BYTE_FIELD*)&temp2_bit)->b0)
//****************************************************




//	delay_times(t_1ms, 800);			// 用于 Normal mode, 不适用Slow mode
void delay_times(uchar tBase, uint x);	// 用于 Normal mode, 不适用Slow mode
//...................|...........| x: 设定延迟时间变数
//...................| tBase: 设定延迟单位: t_1ms/t_100us 等...
#define t_1ms		0
#define t_100us		1



// define input
#define	WKUP_BACK		P7PRD.bit.b3
#define	WKUP_FRONT	P2PRD.bit.b6
#define	TCH1				P7PRD.bit.b7
#define	TCH2				P7PRD.bit.b6
#define	TCH3				P7PRD.bit.b5

// define output
#define	Vout				P0DR.bit.b0
#define	Dock_EN			P7DR.bit.b1
#define	BAT_EN			P7DR.bit.b2
#define	DIR				P4DR.bit.b7
#define	CE					P7DR.bit.b4
#define	D1					P8DR.bit.b0
#define	D2					P8DR.bit.b1
#define	D3					P8DR.bit.b2
#define	D4					P8DR.bit.b3


#endif










