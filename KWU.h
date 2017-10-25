
#ifndef __KWU_H_
#define __KWU_H_



#define d_KWU_all_disable		\
		{						\
			KWUCR0.byte = 0x00;	\
			KWUCR1.byte = 0x00;	\
			KWUCR2.byte = 0x00;	\
			KWUCR3.byte = 0x00;	\
		}

//..KWI 0.......................
#define d_KWU_00_Dis	{                  P4PU.bit.b0 = 0; P4PD.bit.b0 = 0;	                   KWUCR0.bit.b0 = 0; }
#define d_KWU_00_EnL	{ P4CR.bit.b0 = 0; P4PU.bit.b0 = 1; P4PD.bit.b0 = 0;	KWUCR0.bit.b1 = 0; KWUCR0.bit.b0 = 1; }
#define d_KWU_00_EnH	{ P4CR.bit.b0 = 0; P4PU.bit.b0 = 0; P4PD.bit.b0 = 1;	KWUCR0.bit.b1 = 1; KWUCR0.bit.b0 = 1; }
//............................................................................................|..................| 1: enable, 0: disable
//............................................................................................| (0:Low, 1:high) level release stop mode

//.........................
#define d_KWU_01_Dis	{                  P4PU.bit.b1 = 0; P4PD.bit.b1 = 0;	                   KWUCR0.bit.b2 = 0; }
#define d_KWU_01_EnL	{ P4CR.bit.b1 = 0; P4PU.bit.b1 = 1; P4PD.bit.b1 = 0;	KWUCR0.bit.b3 = 0; KWUCR0.bit.b2 = 1; }
#define d_KWU_01_EnH	{ P4CR.bit.b1 = 0; P4PU.bit.b1 = 0; P4PD.bit.b1 = 1;	KWUCR0.bit.b3 = 1; KWUCR0.bit.b2 = 1; }

//.........................
#define d_KWU_02_Dis	{                  P4PU.bit.b2 = 0; P4PD.bit.b2 = 0;	                   KWUCR0.bit.b4 = 0; }
#define d_KWU_02_EnL	{ P4CR.bit.b2 = 0; P4PU.bit.b2 = 1; P4PD.bit.b2 = 0;	KWUCR0.bit.b5 = 0; KWUCR0.bit.b4 = 1; }
#define d_KWU_02_EnH	{ P4CR.bit.b2 = 0; P4PU.bit.b2 = 0; P4PD.bit.b2 = 1;	KWUCR0.bit.b5 = 1; KWUCR0.bit.b4 = 1; }

//.........................
#define d_KWU_03_Dis	{                  P4PU.bit.b3 = 0; P4PD.bit.b3 = 0;	                   KWUCR0.bit.b6 = 0; }
#define d_KWU_03_EnL	{ P4CR.bit.b3 = 0; P4PU.bit.b3 = 1; P4PD.bit.b3 = 0;	KWUCR0.bit.b7 = 0; KWUCR0.bit.b6 = 1; }
#define d_KWU_03_EnH	{ P4CR.bit.b3 = 0; P4PU.bit.b3 = 0; P4PD.bit.b3 = 1;	KWUCR0.bit.b7 = 1; KWUCR0.bit.b6 = 1; }

//.........................
#define d_KWU_04_Dis	{                  P4PU.bit.b4 = 0; P4PD.bit.b4 = 0;	                   KWUCR1.bit.b0 = 0; }
#define d_KWU_04_EnL	{ P4CR.bit.b4 = 0; P4PU.bit.b4 = 1; P4PD.bit.b4 = 0;	KWUCR1.bit.b1 = 0; KWUCR1.bit.b0 = 1; }
#define d_KWU_04_EnH	{ P4CR.bit.b4 = 0; P4PU.bit.b4 = 0; P4PD.bit.b4 = 1;	KWUCR1.bit.b1 = 1; KWUCR1.bit.b0 = 1; }

//.........................
#define d_KWU_05_Dis	{                  P4PU.bit.b5 = 0; P4PD.bit.b5 = 0;	                   KWUCR1.bit.b2 = 0; }
#define d_KWU_05_EnL	{ P4CR.bit.b5 = 0; P4PU.bit.b5 = 1; P4PD.bit.b5 = 0;	KWUCR1.bit.b3 = 0; KWUCR1.bit.b2 = 1; }
#define d_KWU_05_EnH	{ P4CR.bit.b5 = 0; P4PU.bit.b5 = 0; P4PD.bit.b5 = 1;	KWUCR1.bit.b3 = 1; KWUCR1.bit.b2 = 1; }

//.........................
#define d_KWU_06_Dis	{                  P4PU.bit.b6 = 0; P4PD.bit.b6 = 0;	                   KWUCR1.bit.b4 = 0; }
#define d_KWU_06_EnL	{ P4CR.bit.b6 = 0; P4PU.bit.b6 = 1; P4PD.bit.b6 = 0;	KWUCR1.bit.b5 = 0; KWUCR1.bit.b4 = 1; }
#define d_KWU_06_EnH	{ P4CR.bit.b6 = 0; P4PU.bit.b6 = 0; P4PD.bit.b6 = 1;	KWUCR1.bit.b5 = 1; KWUCR1.bit.b4 = 1; }

//.........................
#define d_KWU_07_Dis	{                  P4PU.bit.b7 = 0; P4PD.bit.b7 = 0;	                   KWUCR1.bit.b6 = 0; }
#define d_KWU_07_EnL	{ P4CR.bit.b7 = 0; P4PU.bit.b7 = 1; P4PD.bit.b7 = 0;	KWUCR1.bit.b7 = 0; KWUCR1.bit.b6 = 1; }
#define d_KWU_07_EnH	{ P4CR.bit.b7 = 0; P4PU.bit.b7 = 0; P4PD.bit.b7 = 1;	KWUCR1.bit.b7 = 1; KWUCR1.bit.b6 = 1; }

//.........................
#define d_KWU_08_Dis	{                  P2PU.bit.b4 = 0; P2PD.bit.b4 = 0;	                   KWUCR2.bit.b0 = 0; }
#define d_KWU_08_EnL	{ P2CR.bit.b4 = 0; P2PU.bit.b4 = 1; P2PD.bit.b4 = 0;	KWUCR2.bit.b1 = 0; KWUCR2.bit.b0 = 1; }
#define d_KWU_08_EnH	{ P2CR.bit.b4 = 0; P2PU.bit.b4 = 0; P2PD.bit.b4 = 1;	KWUCR2.bit.b1 = 1; KWUCR2.bit.b0 = 1; }

//.........................
#define d_KWU_09_Dis	{                  P2PU.bit.b5 = 0; P2PD.bit.b5 = 0;	                   KWUCR2.bit.b2 = 0; }
#define d_KWU_09_EnL	{ P2CR.bit.b5 = 0; P2PU.bit.b5 = 1; P2PD.bit.b5 = 0;	KWUCR2.bit.b3 = 0; KWUCR2.bit.b2 = 1; }
#define d_KWU_09_EnH	{ P2CR.bit.b5 = 0; P2PU.bit.b5 = 0; P2PD.bit.b5 = 1;	KWUCR2.bit.b3 = 1; KWUCR2.bit.b2 = 1; }

//.........................
#define d_KWU_10_Dis	{                  P2PU.bit.b6 = 0; P2PD.bit.b6 = 0;	                   KWUCR2.bit.b4 = 0; }
#define d_KWU_10_EnL	{ P2CR.bit.b6 = 0; P2PU.bit.b6 = 1; P2PD.bit.b6 = 0;	KWUCR2.bit.b5 = 0; KWUCR2.bit.b4 = 1; }
#define d_KWU_10_EnH	{ P2CR.bit.b6 = 0; P2PU.bit.b6 = 0; P2PD.bit.b6 = 1;	KWUCR2.bit.b5 = 1; KWUCR2.bit.b4 = 1; }

//.........................
#define d_KWU_11_Dis	{                  P2PU.bit.b7 = 0; P2PD.bit.b7 = 0;	                   KWUCR2.bit.b6 = 0; }
#define d_KWU_11_EnL	{ P2CR.bit.b7 = 0; P2PU.bit.b7 = 1; P2PD.bit.b7 = 0;	KWUCR2.bit.b7 = 0; KWUCR2.bit.b6 = 1; }
#define d_KWU_11_EnH	{ P2CR.bit.b7 = 0; P2PU.bit.b7 = 0; P2PD.bit.b7 = 1;	KWUCR2.bit.b7 = 1; KWUCR2.bit.b6 = 1; }

//.........................
#define d_KWU_12_Dis	{                  P7PU.bit.b3 = 0; P7PD.bit.b3 = 0;	                   KWUCR3.bit.b0 = 0; }
#define d_KWU_12_EnL	{ P7CR.bit.b3 = 0; P7PU.bit.b3 = 1; P7PD.bit.b3 = 0;	KWUCR3.bit.b1 = 0; KWUCR3.bit.b0 = 1; }
#define d_KWU_12_EnH	{ P7CR.bit.b3 = 0; P7PU.bit.b3 = 0; P7PD.bit.b3 = 1;	KWUCR3.bit.b1 = 1; KWUCR3.bit.b0 = 1; }

//.........................
#define d_KWU_13_Dis	{                  P7PU.bit.b4 = 0; P7PD.bit.b4 = 0;	                   KWUCR3.bit.b2 = 0; }
#define d_KWU_13_EnL	{ P7CR.bit.b4 = 0; P7PU.bit.b4 = 1; P7PD.bit.b4 = 0;	KWUCR3.bit.b3 = 0; KWUCR3.bit.b2 = 1; }
#define d_KWU_13_EnH	{ P7CR.bit.b4 = 0; P7PU.bit.b4 = 0; P7PD.bit.b4 = 1;	KWUCR3.bit.b3 = 1; KWUCR3.bit.b2 = 1; }

//.........................
#define d_KWU_14_Dis	{                  P7PU.bit.b5 = 0; P7PD.bit.b5 = 0;	                   KWUCR3.bit.b4 = 0; }
#define d_KWU_14_EnL	{ P7CR.bit.b5 = 0; P7PU.bit.b5 = 1; P7PD.bit.b5 = 0;	KWUCR3.bit.b5 = 0; KWUCR3.bit.b4 = 1; }
#define d_KWU_14_EnH	{ P7CR.bit.b5 = 0; P7PU.bit.b5 = 0; P7PD.bit.b5 = 1;	KWUCR3.bit.b5 = 1; KWUCR3.bit.b4 = 1; }

//.........................
#define d_KWU_15_Dis	{                  P7PU.bit.b6 = 0; P7PD.bit.b6 = 0;	                   KWUCR3.bit.b6 = 0; }
#define d_KWU_15_EnL	{ P7CR.bit.b6 = 0; P7PU.bit.b6 = 1; P7PD.bit.b6 = 0;	KWUCR3.bit.b7 = 0; KWUCR3.bit.b6 = 1; }
#define d_KWU_15_EnH	{ P7CR.bit.b6 = 0; P7PU.bit.b6 = 0; P7PD.bit.b6 = 1;	KWUCR3.bit.b7 = 1; KWUCR3.bit.b6 = 1; }


#endif















