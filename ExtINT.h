
#ifndef __ExtINT_H_
#define __ExtINT_H_



// Input define: External Interrupt Pins
//#define INT_00_Input	{ P9CR.bit.b2 = 0; }
//#define INT_01_Input	{ P9CR.bit.b3 = 0; }
#define INT_02_Input	{ P7CR.bit.b5 = 0; }
#define INT_03_Input	{ P7CR.bit.b6 = 0; }
#define INT_04_Input	{ P7CR.bit.b7 = 0; }
//#define INT_05_Input	{ P2CR.bit.b5 = 0; }

// Interrupt define: Interrupt POFFCRx/Latch/Enable Register...
//#define INT_00_set		{ POFFCR3.bit.b0 = 1; ILE.bit.b0 = 0; EIRE.bit.b0 = 1; }
//#define INT_01_set		{ POFFCR3.bit.b1 = 1; ILE.bit.b1 = 0; EIRE.bit.b1 = 1; }
#define INT_02_set		{ POFFCR3.bit.b2 = 1; ILE.bit.b2 = 0; EIRE.bit.b2 = 1; }
#define INT_03_set		{ POFFCR3.bit.b3 = 1; ILE.bit.b3 = 0; EIRE.bit.b3 = 1; }
#define INT_04_set		{ POFFCR3.bit.b4 = 1; ILE.bit.b4 = 0; EIRE.bit.b4 = 1; }
//#define INT_05_set		{ POFFCR3.bit.b5 = 1; ILE.bit.b5 = 0; EIRE.bit.b5 = 1; }

//#define INT_00_dis		{ POFFCR3.bit.b0 = 0; ILE.bit.b0 = 0; EIRE.bit.b0 = 0; }
//#define INT_01_dis		{ POFFCR3.bit.b1 = 0; ILE.bit.b1 = 0; EIRE.bit.b1 = 0; }
#define INT_02_dis		{ POFFCR3.bit.b2 = 0; ILE.bit.b2 = 0; EIRE.bit.b2 = 0; }
#define INT_03_dis		{ POFFCR3.bit.b3 = 0; ILE.bit.b3 = 0; EIRE.bit.b3 = 0; }
#define INT_04_dis		{ POFFCR3.bit.b4 = 0; ILE.bit.b4 = 0; EIRE.bit.b4 = 0; }
//#define INT_05_dis		{ POFFCR3.bit.b5 = 0; ILE.bit.b5 = 0; EIRE.bit.b5 = 0; }




//.............................................................................................
//#define d_ExtINT_00_Rising	{ INT_00_Input; INT_00_set; EINTCR0.byte = 0x00 | 0x00; }
//#define d_ExtINT_00_Falling	{ INT_00_Input; INT_00_set; EINTCR0.byte = 0x04 | 0x00; }
//#define d_ExtINT_00_Both	{ INT_00_Input; INT_00_set; EINTCR0.byte = 0x08 | 0x00; }
//#define d_ExtINT_00_High	{ INT_00_Input; INT_00_set; EINTCR0.byte = 0x0C | 0x00; }
//
////.............................................................................................
//#define d_ExtINT_05_Rising	{ INT_05_Input; INT_05_set; EINTCR5.byte = 0x00 | 0x00; }
//#define d_ExtINT_05_Falling	{ INT_05_Input; INT_05_set; EINTCR5.byte = 0x04 | 0x00; }
//#define d_ExtINT_05_Both	{ INT_05_Input; INT_05_set; EINTCR5.byte = 0x08 | 0x00; }
//#define d_ExtINT_05_High	{ INT_05_Input; INT_05_set; EINTCR5.byte = 0x0C | 0x00; }
//
////.............................................................................................
//#define d_ExtINT_01_Rising	{ INT_01_Input; INT_01_set; EINTCR1.byte = 0x00 | 0x00; }
//#define d_ExtINT_01_Falling	{ INT_01_Input; INT_01_set; EINTCR1.byte = 0x04 | 0x00; }
//#define d_ExtINT_01_Both	{ INT_01_Input; INT_01_set; EINTCR1.byte = 0x08 | 0x00; }
//#define d_ExtINT_01_High	{ INT_01_Input; INT_01_set; EINTCR1.byte = 0x0C | 0x00; }

//.............................................................................................
#define d_ExtINT_02_Rising	{ INT_02_Input; INT_02_set; EINTCR2.byte = 0x00 | 0x00; }
#define d_ExtINT_02_Falling	{ INT_02_Input; INT_02_set; EINTCR2.byte = 0x04 | 0x00; }
#define d_ExtINT_02_Both	{ INT_02_Input; INT_02_set; EINTCR2.byte = 0x08 | 0x00; }
#define d_ExtINT_02_High	{ INT_02_Input; INT_02_set; EINTCR2.byte = 0x0C | 0x00; }

//.............................................................................................
#define d_ExtINT_03_Rising	{ INT_03_Input; INT_03_set; EINTCR3.byte = 0x00 | 0x00; }
#define d_ExtINT_03_Falling	{ INT_03_Input; INT_03_set; EINTCR3.byte = 0x04 | 0x00; }
#define d_ExtINT_03_Both	{ INT_03_Input; INT_03_set; EINTCR3.byte = 0x08 | 0x00; }
#define d_ExtINT_03_High	{ INT_03_Input; INT_03_set; EINTCR3.byte = 0x0C | 0x00; }

//.............................................................................................
#define d_ExtINT_04_Rising	{ INT_04_Input; INT_04_set; EINTCR4.byte = 0x00 | 0x00; }
#define d_ExtINT_04_Falling	{ INT_04_Input; INT_04_set; EINTCR4.byte = 0x04 | 0x00; }
#define d_ExtINT_04_Both	{ INT_04_Input; INT_04_set; EINTCR4.byte = 0x08 | 0x00; }
#define d_ExtINT_04_High	{ INT_04_Input; INT_04_set; EINTCR4.byte = 0x0C | 0x00; }
//...................................................................|......| Noise Canceller: |   Normal    |  SLOW
//...................................................................|......|------------------------------------------
//...................................................................|......| 0x00:            | fcgck       |  fs/4
//...................................................................|......| 0x01:            | fcgck/2^2   |  fs/4
//...................................................................|......| 0x02:            | fcgck/2^3   |  fs/4
//...................................................................|......| 0x03:            | fcgck/2^4   |  fs/4
//...................................................................|(0x00/0x04/0x08/0x0C) <==> Rising/Falling/Both/High


// Disable setting..............................................
//#define d_ExtINT_00_Dis		{ INT_00_dis; }
//#define d_ExtINT_01_Dis		{ INT_01_dis; }
#define d_ExtINT_02_Dis		{ INT_02_dis; }
#define d_ExtINT_03_Dis		{ INT_03_dis; }
#define d_ExtINT_04_Dis		{ INT_04_dis; }
//#define d_ExtINT_05_Dis		{ INT_05_dis; }




#endif















