
#ifndef __OPmode_H_
#define __OPmode_H_

/*********************************************
****** ����ģʽת��֮������ʹ��ע������ ******
**********************************************

//	--------:----------------------------------------------------------
//	����ģʽ�л����̣�
//	Normal1	--> Normal2 --> SLOW2 --> SLOW1
//	SLOW1 --> SLOW2 --> Normal2 --> Normal1
//	--------:----------------------------------------------------------
//*********************************************************************
// 			: Each Mode Switch Sequence
//	Normal1	:----------------------------------------------------------
//			: --> Normal1
//			: --> IDLE0(INTTBT release)		--> Normal1
//			: --> IDLE1(Interrupt release)	--> Normal1
//			: --> STOP (�ȴ�����)			--> Normal1
//	Normal2	:----------------------------------------------------------
//			: --> Normal2
//			: --> IDLE2(�ȴ��ж�)			--> Normal2
//			: --> STOP (�ȴ�����)			--> Normal2
//	SLOW2	:----------------------------------------------------------
//			: --> SLOW2
//	SLOW1	:----------------------------------------------------------
//			: --> SLOW1
//			: --> SLEEP0(INTTBT release)	--> SLOW1
//			: --> SLEEP1(Interrupt release)	--> SLOW1
//			: --> STOP  (�ȴ�����)			--> SLOW1
//	--------:----------------------------------------------------------
**********************************************************************/





//--------------------------------------------------------------------------------------------------//
//	���� <OPmode.h> �������ⲿ���� (���� or ����), ����ο�����˵����
//	�ⲿ����� HXTAL/LXTAL ʹ����ͬ IO(P00/P01), ֻ����һ����.
//.....................................................................................
#undef	XTAL_High		// �����ⲿ���پ���: #define(ʹ�þ���) / #undef(���þ���) :
#undef	XTAL_Low		// �����ⲿ���پ���: #define(ʹ�þ���) / #undef(���þ���) :
//			|........................................................................................
//			|---------> // ע������:
//			|---------> // 1. Enable LXtal: ���趨 FSCTRL.bit.b0 = 1; --> FSCTRL��ʹ�õ�λԪ(bit operation)
//			|---------> // 2. ���������ⲿ����������¼ʱ, ���乴ѡ ext low OSC:
//			|---------> //    IDE��¼		: Project -> Pin Setting -> ��ѡ ext low OSC
//			|---------> //    Writer��¼	: ��ѡType -> ��IC typeѡ��ͬһҳ���ҷ� -> ��ѡ ext low OSC
//			.........................................................................................
//--------------------------------------------------------------------------------------------------//


//	Normal1	--> Normal2 --> SLOW2 --> SLOW1
//	SLOW1 --> SLOW2 --> Normal2 --> Normal1
#define	iNor1		1
#define	iNor2		2
#define	iSlow2		3
#define	iSlow1		4
//#define	iSlow2_R	5	// ���ɳ��������жϣ�
//#define	iNor2_R		6	// ���ɳ��������жϣ�
//#define	iNor1_R		7	// ���ɳ��������жϣ�

#define Active_IDLE0	SYSCR2.bit.b2 = 1		// TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
#define Active_SLEEP0	SYSCR2.bit.b2 = 1		// TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode

#define Active_IDLE1	SYSCR2.bit.b3 = 1		// IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
#define Active_IDLE2	SYSCR2.bit.b3 = 1		// IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
#define Active_SLEEP1	SYSCR2.bit.b3 = 1		// IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode

#define Active_STOP	{	SYSCR1.bit.b5 = 1; SYSCR1.bit.b6 = 1; SYSCR1.bit.b7 = 1; }
					//	SYSCR1.bit.b5 = 1;		// OUTEN=1, output hold at STOP mode
					//							// ��stop mode��ע�������λ���ܸ���, ��ĩʹ�ý�λ�趨Ϊ�����λ,
					//							// �����λ���ӻ����δ֪©��
					//	SYSCR1.bit.b6 = 1;		// RELM=1,  Level-sensitive release STOP mode
					//	SYSCR1.bit.b7 = 1;		// entry STOP mode


void OpMode_Change_to(uchar iMode);
//........................| iMode: iNor1/iNor2/iSlow2/iSlow1

void XTAL_High_Config();
void HIRC_ChangeTo_8MHz();

void INTTBT_Init_OP();
void Disable_INTTBT_OP();


#endif


















