
#ifndef __OPmode_H_
#define __OPmode_H_

/*********************************************
****** 工作模式转换之建议与使用注意事项 ******
**********************************************

//	--------:----------------------------------------------------------
//	工作模式切换流程：
//	Normal1	--> Normal2 --> SLOW2 --> SLOW1
//	SLOW1 --> SLOW2 --> Normal2 --> Normal1
//	--------:----------------------------------------------------------
//*********************************************************************
// 			: Each Mode Switch Sequence
//	Normal1	:----------------------------------------------------------
//			: --> Normal1
//			: --> IDLE0(INTTBT release)		--> Normal1
//			: --> IDLE1(Interrupt release)	--> Normal1
//			: --> STOP (等待唤醒)			--> Normal1
//	Normal2	:----------------------------------------------------------
//			: --> Normal2
//			: --> IDLE2(等待中断)			--> Normal2
//			: --> STOP (等待唤醒)			--> Normal2
//	SLOW2	:----------------------------------------------------------
//			: --> SLOW2
//	SLOW1	:----------------------------------------------------------
//			: --> SLOW1
//			: --> SLEEP0(INTTBT release)	--> SLOW1
//			: --> SLEEP1(Interrupt release)	--> SLOW1
//			: --> STOP  (等待唤醒)			--> SLOW1
//	--------:----------------------------------------------------------
**********************************************************************/





//--------------------------------------------------------------------------------------------------//
//	请由 <OPmode.h> 里设置外部晶振 (高速 or 低速), 并请参考以下说明：
//	外部晶振脚 HXTAL/LXTAL 使用相同 IO(P00/P01), 只能择一开启.
//.....................................................................................
#undef	XTAL_High		// 定义外部高速晶振: #define(使用晶振) / #undef(不用晶振) :
#undef	XTAL_Low		// 定义外部低速晶振: #define(使用晶振) / #undef(不用晶振) :
//			|........................................................................................
//			|---------> // 注意事项:
//			|---------> // 1. Enable LXtal: 需设定 FSCTRL.bit.b0 = 1; --> FSCTRL请使用单位元(bit operation)
//			|---------> // 2. 启动低速外部晶振需在烧录时, 搭配勾选 ext low OSC:
//			|---------> //    IDE烧录		: Project -> Pin Setting -> 勾选 ext low OSC
//			|---------> //    Writer烧录	: 点选Type -> 在IC type选项同一页面右方 -> 勾选 ext low OSC
//			.........................................................................................
//--------------------------------------------------------------------------------------------------//


//	Normal1	--> Normal2 --> SLOW2 --> SLOW1
//	SLOW1 --> SLOW2 --> Normal2 --> Normal1
#define	iNor1		1
#define	iNor2		2
#define	iSlow2		3
#define	iSlow1		4
//#define	iSlow2_R	5	// 此由程序自行判断，
//#define	iNor2_R		6	// 此由程序自行判断，
//#define	iNor1_R		7	// 此由程序自行判断，

#define Active_IDLE0	SYSCR2.bit.b2 = 1		// TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
#define Active_SLEEP0	SYSCR2.bit.b2 = 1		// TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode

#define Active_IDLE1	SYSCR2.bit.b3 = 1		// IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
#define Active_IDLE2	SYSCR2.bit.b3 = 1		// IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
#define Active_SLEEP1	SYSCR2.bit.b3 = 1		// IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode

#define Active_STOP	{	SYSCR1.bit.b5 = 1; SYSCR1.bit.b6 = 1; SYSCR1.bit.b7 = 1; }
					//	SYSCR1.bit.b5 = 1;		// OUTEN=1, output hold at STOP mode
					//							// 进stop mode需注意输入脚位不能浮接, 或将末使用脚位设定为输出脚位,
					//							// 输入脚位浮接会造成未知漏电
					//	SYSCR1.bit.b6 = 1;		// RELM=1,  Level-sensitive release STOP mode
					//	SYSCR1.bit.b7 = 1;		// entry STOP mode


void OpMode_Change_to(uchar iMode);
//........................| iMode: iNor1/iNor2/iSlow2/iSlow1

void XTAL_High_Config();
void HIRC_ChangeTo_8MHz();

void INTTBT_Init_OP();
void Disable_INTTBT_OP();


#endif


















