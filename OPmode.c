//******************************************
//           This is a C Template file
//作者
//日期
//功能
//备注
//******************************************
#include "MQ6812.h"
#include "iApp.h"
#include "OPmode.h"


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
//*********************************************************************

//*********************************************************************
// 函数名	: OpMode_Change_to()
// 函数功能	: 工作模式切换
// 备注		: 选择要操作的工作模式至 (iNor1/iNor2/iSlow2/iSlow1) 其中之一
//	--------:----------------------------------------------------------
//#define	iNor1		1	<-----------------
//#define	iNor2		2	<--------------  |
//#define	iSlow2		3	<-----------  |  |
//#define	iSlow1		4              |  |  |
//#define	iSlow2_R	5	<= (8-3) ---  |  |
//#define	iNor2_R		6	<= (8-2) ------  |
//#define	iNor1_R		7	<= (8-1) ---------
//	--------:----------------------------------------------------------
//*********************************************************************
void OpMode_Change_to(uchar iMode)
{
	uchar nowMode;
	uchar TmpIMF;

	TmpIMF = EIRL.bit.b0;	// 暂存 IMF 设定值

//	**********************************************************************
//	check system clock: [SYSCR2.bit.b4]=> 0.Normal, 1.SLOW
//	Normal mode ----------------------------------------------------------
	if( SYSCR2.bit.b4 == 0 )			// [SYSCK]=0 as high-frequency
	{
		if( SYSCR2.bit.b5 == 1 )		// [XTEN]=1
			nowMode = iNor2;
		else
			nowMode = iNor1;
	}

//	SLOW mode ------------------------------------------------------------
	else								// [SYSCK]=1 as low-frequency
	{
		if( SYSCR2.bit.b6 == 1 )		// [XEN] HXTAL
			nowMode = iSlow2;
		else if( SYSCR2.bit.b7 == 1 )	// [OSCEN] HIRC
			nowMode = iSlow2;
		else
			nowMode = iSlow1;
	}
//	----------------------------------------------------------------------
	if( nowMode == iMode )	return;		// 相同模式，不作变更
	if( nowMode >  iMode )				// 往回切换模式
	{
 		iMode   = 8 - iMode;
 		nowMode = 8 - nowMode;
 	}
	nowMode++;							// 从下一模式开始切换
//	----------------------------------------------------------------------
//	**********************************************************************

	switch(nowMode)
	{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
	//----------------------------------------//
	//****** Entry Normal1 mode (高速晶振)****//
	//----------------------------------------//
		//case 1:
        //
		//	if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//------------------------
	//****** Entry Normal2 mode **************//	Normal1	--> Normal2
	//----------------------------------------//------------------------
		case 2:
	//	entry Normal2 by XTAL_Low ............
	#ifdef XTAL_Low		//... 定义外部低速晶振
		//	MQ6812外部晶振 HXTAL/LXTAL用相同IO(P00/P01), 只能择一开启.
			P0CR.bit.b0   = 0;		// P00:XIN
			P0CR.bit.b1   = 0;		// P01:XOUT
		//	__asm("DI");
			EIRL.bit.b0   = 0;		// __asm("DI");
			WUCCR.byte    = 0x0e;	// 0x0c + 0x02
									// WUCDIV: (0x00/0x04/0x08/0x0c) source clocd division (0/2/4/8)
									// WUCSEL: (0x00/0x01/0x02), (HIRC/HXtal/LIRC_LXtal)
			WUCDR.byte    = 0x66;
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 1;		// INTWUC enable
			P0FC.bit.b0   = 1;		// define P00 外部晶振
			FSCTRL.bit.b0 = 1;		// Enable LXtal: FSCTRL请使用单位元(bit operation)
									// MQ6812启动低速外部晶振需在烧录时, 搭配勾选 ext low OSC:
									// IDE烧录		: Project -> Pin Setting -> 勾选 ext low OSC
									// Writer烧录	: 点选Type -> 在IC type选项同一页面右方 -> 勾选 ext low OSC
			SYSCR2.bit.b5 = 1;		// enable start External osc(XTEN=1) and WUC start count
		#ifdef _DEBUG	//...  _DEBUG: 用于仿真 ev board
			delay_times(t_1ms, 1000);
		#else
			while( ILL.bit.b4 == 0 ){ WDCDR.byte = 0x4e; }	// 等待INTWUC
		#endif
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 0;		// INTWUC disable

	//	entry Normal2 by LIRC ............
	#else
		//	__asm("DI");
			EIRL.bit.b0   = 0;		// __asm("DI");
			WUCCR.byte    = 0x0e;	// 0x0c + 0x02
									// WUCDIV: (0x00/0x04/0x08/0x0c) source clocd division (0/2/4/8)
									// WUCSEL: (0x00/0x01/0x02), (HIRC/HXtal/LIRC_LXtal)
			WUCDR.byte    = 0x26;
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 1;		// INTWUC enable
			SYSCR2.bit.b5 = 1;		// enable start External osc(XTEN=1) and WUC start count
		#ifdef _DEBUG	//...  _DEBUG: 用于仿真 ev board
			delay_times(t_1ms, 10);
		#else
			while( ILL.bit.b4 == 0 ){ WDCDR.byte = 0x4e; }	// 等待INTWUC
		#endif
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 0;		// INTWUC disable
	#endif	//...  end for #ifdef XTAL_Low

			if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//------------------------
	//****** Entry SLOW2 mode ****************//	Normal2 --> SLOW2
	//----------------------------------------//------------------------
		case 3:
			SYSCR2.bit.b4 = 1;		// [SYSCK] select system clock as low-frequency
			__asm("NOP");			// Wait 2 machine cycles
			__asm("NOP");

			if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//------------------------
	//****** Entry SLOW1 mode ****************//	SLOW2 --> SLOW1
	//----------------------------------------//------------------------
		case 4:
	//	entry SLOW1 by XTAL_High ............
	#ifdef XTAL_High	//...  XTAL_High: 定义外部高速晶振
			SYSCR2.bit.b6 = 0;		// [XEN] disable HXTAL

	//	entry SLOW1 by HIRC ............
	#else
			SYSCR2.bit.b7 = 0;		// [OSCEN] disable HIRC
	#endif	//...  end for #ifdef XTAL_High

			if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//------------------------
	//****** Entry SLOW2 mode (return)********//	SLOW1 --> SLOW2
	//----------------------------------------//------------------------
		case 5:
	//	entry SLOW2 by XTAL_High ............
	#ifdef XTAL_High	//...  XTAL_High: 定义外部高速晶振
		//	MQ6812外部晶振 HXTAL/LXTAL用相同IO(P00/P01), 只能择一开启.
			P0CR.bit.b0   = 0;		// P00:XIN
			P0CR.bit.b1   = 0;		// P01:XOUT
		//	__asm("DI");
			EIRL.bit.b0   = 0;		// __asm("DI");
			WUCCR.byte    = 0x0d;	// 0x0c + 0x01
									// WUCDIV: (0x00/0x04/0x08/0x0c) source clocd division (0/2/4/8)
									// WUCSEL: (0x00/0x01/0x02), (HIRC/HXtal/LIRC_LXtal)
			WUCDR.byte    = 0x4c;
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 1;		// INTWUC enable
			P0FC.bit.b0   = 1;		// define P00 外部晶振
			SYSCR2.bit.b6 = 1;		// enable start External osc(XEN=1) and WUC start count
		#ifdef _DEBUG	//...  _DEBUG: 用于仿真 ev board
			delay_times(t_1ms, 10);
		#else
			while( ILL.bit.b4 == 0 ){ WDCDR.byte = 0x4e; }	// 等待INTWUC
		#endif
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 0;		// INTWUC disable

	//	entry SLOW2 by HIRC ............
	#else
		//	__asm("DI");
			EIRL.bit.b0   = 0;		// __asm("DI");
			WUCCR.byte    = 0x0c;	// 0x0c + 0x00
									// WUCDIV: (0x00/0x04/0x08/0x0c) source clocd division (0/2/4/8)
									// WUCSEL: (0x00/0x01/0x02), (HIRC/HXtal/LIRC_LXtal)
			WUCDR.byte    = 0x4c;
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 1;		// INTWUC enable
			SYSCR2.bit.b7 = 1;		// enable start HIRC(OSCEN=1) and WUC start count
		#ifdef _DEBUG	//...  _DEBUG: 用于仿真 ev board
			delay_times(t_1ms, 10);
		#else
			while( ILL.bit.b4 == 0 ){ WDCDR.byte = 0x4e; }	// 等待INTWUC
		#endif
			ILL.bit.b4    = 0;		// need clear interrupt latch first
			EIRL.bit.b4   = 0;		// INTWUC disable
	#endif	//...  end for #ifdef XTAL_High

			if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//------------------------
	//****** Entry Normal2 mode  (return)*****//	SLOW2 --> Normal2
	//----------------------------------------//------------------------
		case 6:
			SYSCR2.bit.b4 = 0;		// [SYSCK] select system clock as high-frequency
			__asm("NOP");			// Wait 2 machine cycles
			__asm("NOP");

			if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//------------------------
	//****** Entry Normal1 mode  (return)*****//	Normal2 --> Normal1
	//----------------------------------------//------------------------
		case 7:
			SYSCR2.bit.b5 = 0;		// disable External osc(XTEN=0)

			if( nowMode == iMode ) break;	else nowMode++;

	//----------------------------------------//
	//****** Without change mode *************//
	//----------------------------------------//
		default:	break;
	}
	EIRL.bit.b0 = TmpIMF;	// 复原 IMF 设定值

}


//*********************************************************************
// 函数名	: XTAL_High_Config()
// 函数功能	: HIGH XTAL Sequence
// 备注		:
//*********************************************************************
void XTAL_High_Config()
{
#ifdef XTAL_High	//...  XTAL_High: 定义外部高速晶振
	uchar TmpIMF;

	TmpIMF = EIRL.bit.b0;	// 暂存 IMF 设定值

//	MQ6812外部晶振 HXTAL/LXTAL用相同IO(P00/P01), 只能择一开启.
	P0CR.bit.b0   = 0;		// P00:XIN
	P0CR.bit.b1   = 0;		// P01:XOUT

//	__asm("DI");
	EIRL.bit.b0   = 0;		// __asm("DI");
	WUCCR.byte    = 0x0d;	// 0x0c + 0x01
							// WUCDIV: (0x00/0x04/0x08/0x0c) source clocd division (0/2/4/8)
							// WUCSEL: (0x00/0x01/0x02), (HIRC/HXtal/LIRC_LXtal)
	WUCDR.byte    = 0x4c;
	ILL.bit.b4    = 0;		// need clear interrupt latch first
	EIRL.bit.b4   = 1;		// INTWUC enable
	P0FC.bit.b0   = 1;		// define P00 外部晶振
	SYSCR2.bit.b6 = 1;		// enable start External osc(XEN=1) and WUC start count
#ifdef _DEBUG	//...  _DEBUG: 用于仿真 ev board
	delay_times(t_1ms, 10);
#else
	while( ILL.bit.b4 == 0 ){ WDCDR.byte = 0x4e; }	// 等待INTWUC
#endif
	ILL.bit.b4    = 0;		// need clear interrupt latch first
	EIRL.bit.b4   = 0;		// INTWUC disable
	SYSCR1.bit.b3 = 1;		// SYSCR1<OSCSEL>=1: Select the external high-frequency clock
	__asm("NOP");
	__asm("NOP");
	SYSCR2.bit.b7 = 0;		// SYSCR2<OSCHEN>=0: Stop the internal high-frequency clock.

	EIRL.bit.b0 = TmpIMF;	// 复原 IMF 设定值

#endif
}


//*********************************************************************
// 函数名	: HIRC_ChangeTo_8MHz()
// 函数功能	: HIRC 16MHz change to 8MHz
// 备注		: 改变内部高速时钟 (fosc) 频率 (FOSCCKS), 需在低速1模式下进行, 系统默认为16MHz
//*********************************************************************
void HIRC_ChangeTo_8MHz()
{
//	1. FSCTRL请使用单位元(bit operation)
//	2. 欲改变内部高速时钟 (fosc) 频率 (FOSCCKS),
//	   需在低速1模式下进行.
	FSCTRL.bit.b2 = 0;		// ......
	FSCTRL.bit.b1 = 0;		// FSCTRL<FOSCCKS> => FSCTRL<2:1>:
							// 00:  8MHz,
							// 01: 16MHz,(系统默认)
							// 10: reserved
							// 11: reserved
}



//*********************************************************************
// 函数名	: INTTBT_Init()
// 函数功能	: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
// 备注		:
//*********************************************************************
void INTTBT_Init_OP()
{
							// -----|-------------|----------|----------|
							//      |          Normal        |   SLOW   |
							// -----|-------------|----------|----------|
							//      |   DV9CK=0   | DV9CK=1  |----------|
							// -----|-------------|----------|----------|
							// 000: | fcgck/2^22  | fs/2^15  | fs/2^15  |
							// 001: | fcgck/2^20  | fs/2^13  | fs/2^13  |
							// 010: | fcgck/2^15  | fs/2^8   | Reserved |
							// 011: | fcgck/2^13  | fs/2^6   | Reserved |
							// 100: | fcgck/2^12  | fs/2^5   | Reserved |
							// 101: | fcgck/2^11  | fs/2^4   | Reserved |
							// 110: | fcgck/2^10  | fs/2^3   | Reserved |
							// 111: | fcgck/2^8   | Reserved | Reserved |
							// -----|-------------|----------|----------|
	TBTCR.byte    = 0x00;	// TBTCR[2:0]<TBTCK>: 0~7, default=0
//	SYSCR1.bit.b4 = 0;		// DV9CK: 0.fcgck, 1.fs/4
//..........................................................................................
//--> 如果进入 IDLE0/SLEEP0 将由 INTTBT 唤醒, 如不想执行 TBT 中断程序, 则不执行下列几行程序(开始点)
	__asm("DI");
	ILL.bit.b5    = 0;		// need clear interrupt latch first
	EIRL.bit.b5   = 1;		// INTTBT enable
	TBTCR.bit.b3  = 1;		// start TBT
	__asm("EI");
//<-- 如果进入 IDLE0/SLEEP0 将由 INTTBT 唤醒, 如不想执行 TBT 中断程序, 则不执行上列几行程序(结束点)
//..........................................................................................
}


//*********************************************************************
// 函数名	: Disable_INTTBT()
// 函数功能	: Disable INTTBT
// 备注		:
//*********************************************************************
void Disable_INTTBT_OP()
{
	__asm("DI");
	ILL.bit.b5    = 0;		// need clear interrupt latch first
	EIRL.bit.b5   = 0;		// INTTBT disable
	TBTCR.bit.b3  = 0;		// stop TBT
	__asm("EI");
}



















