/*****************************************************************
;*         Sample SFR Header File for TLCS-870/C1 Series         *
;*               Memory Style: Within 64K byte                   *
;*---------------------------------------------------------------*
;*  (C)Copyright TOSHIBA CORPORATION 2008  All rights reserved   *
;*****************************************************************/

//****************************************************************/
#ifdef IO_MEM
/* This definition is for I/O variable and extern definition */
/* So please do not use the name "IO_MEM".*/
#define EXTERN
#else
#define EXTERN extern
#endif
//****************************************************************/
//****************************************************************
typedef struct {
	const unsigned char b7:1;
	const unsigned char b6:1;
	const unsigned char b5:1;
	const unsigned char b4:1;
	const unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
} BYTE_FIELD_FSCTRL;
typedef union {
	const unsigned char   byte;
	BYTE_FIELD_FSCTRL      bit;
} TYPE_BYTE_FSCTRL;
//****************************************************************/
typedef struct {
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
} BYTE_FIELD;
/*=======  BYTE IO ========*/
typedef union {
	unsigned char   byte;
	BYTE_FIELD      bit;
} TYPE_BYTE;

typedef struct {
	unsigned int b15:1;
	unsigned int b14:1;
	unsigned int b13:1;
	unsigned int b12:1;
	unsigned int b11:1;
	unsigned int b10:1;
	unsigned int b9:1;
	unsigned int b8:1;
	unsigned int b7:1;
	unsigned int b6:1;
	unsigned int b5:1;
	unsigned int b4:1;
	unsigned int b3:1;
	unsigned int b2:1;
	unsigned int b1:1;
	unsigned int b0:1;
} WORD_FIELD;
/*======= WORD IO ========*/
typedef union {
 	unsigned int    word;
 	unsigned char   byte[2];
 	WORD_FIELD      bit;
} TYPE_WORD;
typedef union {
 	unsigned int    word;
 	unsigned char   byte[2];
	TYPE_BYTE       TBYTE[2];
 	WORD_FIELD      bit;
} TYPE_WORD_EX;
/***[SFR1]******************************************************/
EXTERN TYPE_BYTE        __io(0x0000)    P0DR;            /* Port P0 output latch */
EXTERN TYPE_BYTE        __io(0x0001)    P1DR;            /* Port P1 output latch */
EXTERN TYPE_BYTE        __io(0x0002)    P2DR;            /* Port P2 output latch */ //unsupported for MQ6801
/*---   (0x0003)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0004)    P4DR;            /* Port P4 output latch */
/*---   (0x0006)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0007)    P7DR;            /* Port P7 output latch */
EXTERN TYPE_BYTE        __io(0x0008)    P8DR;            /* Port P8 output latch */
EXTERN TYPE_BYTE        __io(0x0009)    P9DR;            /* Port P9 output latch */
//EXTERN TYPE_BYTE        __io(0x000B)    PBDR;            /* Port PB output latch */	//unsupported for MQ6801
EXTERN TYPE_BYTE        __io(0x000D)    P0PRD;           /* Port P0 input data */
EXTERN TYPE_BYTE        __io(0x000E)    P1PRD;           /* Port P1 input data */
EXTERN TYPE_BYTE        __io(0x000F)    P2PRD;           /* Port P2 input data *///unsupported for MQ6801
/*---   (0x0010)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0011)    P4PRD;           /* Port P4 input data */
/*---   (0x0013)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0014)    P7PRD;           /* Port P7 input data */
EXTERN TYPE_BYTE        __io(0x0015)    P8PRD;           /* Port P8 input data */
EXTERN TYPE_BYTE        __io(0x0016)    P9PRD;           /* Port P9 input data */
/*---   (0x0017)    Reserved   ---*/
//EXTERN TYPE_BYTE        __io(0x0018)    PBPRD;           /* Port PB input data */
//EXTERN TYPE_BYTE        __io(0x001A)    UART0CR1;        /* UART0 control register 1 */
//EXTERN TYPE_BYTE        __io(0x001B)    UART0CR2;        /* UART0 control register 2 */
//EXTERN TYPE_BYTE    __io(0x001C)    UART0DR;         /* UART0 baud rate register */
//EXTERN TYPE_BYTE        __io(0x001D)    UART0SR;         /* UART0 status register */
//EXTERN TYPE_BYTE    __io(0x001E)    U0BF;
//#define TD0BUF U0BF                                 /* UART0 transmit data buffer */
//#define RD0BUF U0BF                                 /* UART0 receive data buffer */
EXTERN TYPE_BYTE        __io(0x001F)    SIO0CR;          /* Serial interface 0 control register */
EXTERN TYPE_BYTE        __io(0x0020)    SIO0SR;          /* Serial interface 0 status register */
EXTERN TYPE_BYTE    __io(0x0021)    SIO0BUF;         /* Serial interface 0 buffer register */
EXTERN TYPE_BYTE        __io(0x0022)    SBI0CR1;         /* Serial bus interface 0 control register 1 */
EXTERN TYPE_BYTE        __io(0x0023)    S0CS;
#define SBI0CR2 S0CS
                                /* Serial bus interface 0 control register 2 */
#define SBI0SR2 S0CS
                                /* Serial bus interface 0 status register 2 */
EXTERN TYPE_BYTE        __io(0x0024)    I2C0AR;          /* I2C bus address 0 register *///unsupported for MQ6801
EXTERN TYPE_BYTE 		__io(0x0025)    SBI0DBR;         /* Serial bus interface 0 data buffer register *///unsupported for MQ6801
EXTERN TYPE_BYTE        __io(0x002A)    T00MOD;          /* Timer counter 00 mode register */
EXTERN TYPE_BYTE        __io(0x002B)    T01MOD;          /* Timer counter 01 mode register */
EXTERN TYPE_BYTE        __io(0x002C)    T001CR;          /* Timer counter 001 control register */
//EXTERN TYPE_BYTE        __io(0x002D)    TA0DRAL;
//EXTERN TYPE_BYTE        __io(0x002E)    TA0DRAH;
//EXTERN TYPE_BYTE        __io(0x002F)    TA0DRBL;
//EXTERN TYPE_BYTE        __io(0x0030)    TA0DRBH;

EXTERN TYPE_WORD_EX        __io(0x002D)    TA0DRA;
//#define TA0DRA _TA0DRA.word
#define TA0DRAL TA0DRA.TBYTE[0]                           
/* Timer counter A0 register AL */
#define TA0DRAH TA0DRA.TBYTE[1]                          
 /* Timer counter A0 register AH */
EXTERN TYPE_WORD_EX        __io(0x002F)    TA0DRB;
//#define TA0DRB _TA0DRB.word
#define TA0DRBL TA0DRB.TBYTE[0]
                           /* Timer counter A0 register BL */
#define TA0DRBH TA0DRB.TBYTE[1] 
                           /* Timer counter A0 register BH */
EXTERN TYPE_BYTE        __io(0x0031)    TA0MOD;          /* Timer counter A0 mode register */
EXTERN TYPE_BYTE        __io(0x0032)    TA0CR;           /* Timer counter A0 control register */
EXTERN TYPE_BYTE        __io(0x0033)    TA0SR;           /* Timer counter A0 status register */
EXTERN TYPE_BYTE        __io(0x0034)    ADCCR1;          /* AD converter control register 1 */
EXTERN TYPE_BYTE        __io(0x0035)    ADCCR2;          /* AD converter control register 2 */
EXTERN TYPE_BYTE    	__io(0x0036)    ADCDRL;          /* AD converted value register (lower side) */
EXTERN TYPE_BYTE    	__io(0x0037)    ADCDRH;          /* AD converted value register (upper side) */
EXTERN TYPE_BYTE        __io(0x0038)    DVOCR;           /* Divider output control register */
EXTERN TYPE_BYTE        __io(0x0039)    TBTCR;           /* Time base timer control register */
EXTERN TYPE_BYTE        __io(0x003A)    EIRL;            /* Interrupt enable register (EIRL) */
EXTERN TYPE_BYTE        __io(0x003B)    EIRH;            /* Interrupt enable register (EIRH) */
EXTERN TYPE_BYTE        __io(0x003C)    EIRE;            /* Interrupt enable register (EIRE) */
EXTERN TYPE_BYTE        __io(0x003D)    EIRD;            /* Interrupt enable register (EIRD) */
/*---   (0x003E)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x003F)    PSW;             /* Program status word */

/***[SFR3]******************************************************/
/*---   (0x0E40)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0E40)    LCDBUF00;     
EXTERN TYPE_BYTE        __io(0x0E41)    LCDBUF01;     
EXTERN TYPE_BYTE        __io(0x0E42)    LCDBUF02;     
EXTERN TYPE_BYTE        __io(0x0E43)    LCDBUF03;     
EXTERN TYPE_BYTE        __io(0x0E44)    LCDBUF04;     
EXTERN TYPE_BYTE        __io(0x0E45)    LCDBUF05;     
EXTERN TYPE_BYTE        __io(0x0E46)    LCDBUF06;     
EXTERN TYPE_BYTE        __io(0x0E47)    LCDBUF07;  
EXTERN TYPE_BYTE        __io(0x0E48)    LCDBUF08;     
EXTERN TYPE_BYTE        __io(0x0E49)    LCDBUF09;     
EXTERN TYPE_BYTE        __io(0x0E4A)    LCDBUF10;     
EXTERN TYPE_BYTE        __io(0x0E4B)    LCDBUF11;       

EXTERN TYPE_BYTE        __io(0x0E7C)    LCDCR1;   
EXTERN TYPE_BYTE        __io(0x0E7D)    LCDCR2;   
EXTERN TYPE_BYTE        __io(0x0E7E)    LCDCR3;   
EXTERN TYPE_BYTE        __io(0x0E7F)    LCDCR4;   
EXTERN TYPE_BYTE        __io(0x0E80)    LCDCR5;   
/*---   (0x0E41)    Reserved   ---*/
/*---   (0x0E42)    Reserved   ---*/
/*---   (0x0E43)    Reserved   ---*/
/*---   (0x0E44)    Reserved   ---*/
/*---   (0x0E45)    Reserved   ---*/
/*---   (0x0E46)    Reserved   ---*/
/*---   (0x0E47)    Reserved   ---*/
/*---   (0x0E48)    Reserved   ---*/
/*---   (0x0E49)    Reserved   ---*/
/*---   (0x0E4A)    Reserved   ---*/
/*---   (0x0E4B)    Reserved   ---*/
/*---   (0x0E4C)    Reserved   ---*/
/*---   (0x0E4D)    Reserved   ---*/
/*---   (0x0E4E)    Reserved   ---*/
/*---   (0x0E4F)    Reserved   ---*/
/*---   (0x0E50)    Reserved   ---*/
/*---   (0x0E51)    Reserved   ---*/
/*---   (0x0E52)    Reserved   ---*/
/*---   (0x0E53)    Reserved   ---*/
/*---   (0x0E54)    Reserved   ---*/
/*---   (0x0E55)    Reserved   ---*/
/*---   (0x0E56)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0E57)    UATCNG;     
EXTERN TYPE_BYTE        __io(0x0EE7)    ADCVRF;           
EXTERN TYPE_BYTE_FSCTRL        __io(0x0EED)    FSCTRL;           

EXTERN TYPE_BYTE        __io(0x0EF6)    MULCTR;           
/*---   (0x0E58)    Reserved   ---*/
/*---   (0x0E59)    Reserved   ---*/
/*---   (0x0E5A)    Reserved   ---*/
/*---   (0x0E5B)    Reserved   ---*/
/*---   (0x0E5C)    Reserved   ---*/
/*---   (0x0E5D)    Reserved   ---*/
/*---   (0x0E5E)    Reserved   ---*/
/*---   (0x0E5F)    Reserved   ---*/
/*---   (0x0E60)    Reserved   ---*/
/*---   (0x0E61)    Reserved   ---*/
/*---   (0x0E62)    Reserved   ---*/
/*---   (0x0E63)    Reserved   ---*/
/*---   (0x0E64)    Reserved   ---*/
/*---   (0x0E65)    Reserved   ---*/
/*---   (0x0E66)    Reserved   ---*/
/*---   (0x0E67)    Reserved   ---*/
/*---   (0x0E68)    Reserved   ---*/
/*---   (0x0E69)    Reserved   ---*/
/*---   (0x0E6A)    Reserved   ---*/
/*---   (0x0E6B)    Reserved   ---*/
/*---   (0x0E6C)    Reserved   ---*/
/*---   (0x0E6D)    Reserved   ---*/
/*---   (0x0E6E)    Reserved   ---*/
/*---   (0x0E6F)    Reserved   ---*/
/*---   (0x0E70)    Reserved   ---*/
/*---   (0x0E71)    Reserved   ---*/
/*---   (0x0E72)    Reserved   ---*/
/*---   (0x0E73)    Reserved   ---*/
/*---   (0x0E74)    Reserved   ---*/
/*---   (0x0E75)    Reserved   ---*/
/*---   (0x0E76)    Reserved   ---*/
/*---   (0x0E77)    Reserved   ---*/
/*---   (0x0E78)    Reserved   ---*/
/*---   (0x0E79)    Reserved   ---*/
/*---   (0x0E7A)    Reserved   ---*/
/*---   (0x0E7B)    Reserved   ---*/
/*---   (0x0E7C)    Reserved   ---*/
/*---   (0x0E7D)    Reserved   ---*/
/*---   (0x0E7E)    Reserved   ---*/
/*---   (0x0E7F)    Reserved   ---*/
/*---   (0x0E80)    Reserved   ---*/
/*---   (0x0E81)    Reserved   ---*/
/*---   (0x0E82)    Reserved   ---*/
/*---   (0x0E83)    Reserved   ---*/
/*---   (0x0E84)    Reserved   ---*/
/*---   (0x0E85)    Reserved   ---*/
/*---   (0x0E86)    Reserved   ---*/
/*---   (0x0E87)    Reserved   ---*/
/*---   (0x0E88)    Reserved   ---*/
/*---   (0x0E89)    Reserved   ---*/
/*---   (0x0E8A)    Reserved   ---*/
/*---   (0x0E8B)    Reserved   ---*/
/*---   (0x0E8C)    Reserved   ---*/
/*---   (0x0E8D)    Reserved   ---*/
/*---   (0x0E8E)    Reserved   ---*/
/*---   (0x0E8F)    Reserved   ---*/
/*---   (0x0E90)    Reserved   ---*/
/*---   (0x0E91)    Reserved   ---*/
/*---   (0x0E92)    Reserved   ---*/
/*---   (0x0E93)    Reserved   ---*/
/*---   (0x0E94)    Reserved   ---*/
/*---   (0x0E95)    Reserved   ---*/
/*---   (0x0E96)    Reserved   ---*/
/*---   (0x0E97)    Reserved   ---*/
/*---   (0x0E98)    Reserved   ---*/
/*---   (0x0E99)    Reserved   ---*/
/*---   (0x0E9A)    Reserved   ---*/
/*---   (0x0E9B)    Reserved   ---*/
/*---   (0x0E9C)    Reserved   ---*/
/*---   (0x0E9D)    Reserved   ---*/
/*---   (0x0E9E)    Reserved   ---*/
/*---   (0x0E9F)    Reserved   ---*/
/*---   (0x0EA0)    Reserved   ---*/
/*---   (0x0EA1)    Reserved   ---*/
/*---   (0x0EA2)    Reserved   ---*/
/*---   (0x0EA3)    Reserved   ---*/
/*---   (0x0EA4)    Reserved   ---*/
/*---   (0x0EA5)    Reserved   ---*/
/*---   (0x0EA6)    Reserved   ---*/
/*---   (0x0EA7)    Reserved   ---*/
/*---   (0x0EA8)    Reserved   ---*/
/*---   (0x0EA9)    Reserved   ---*/
/*---   (0x0EAA)    Reserved   ---*/
/*---   (0x0EAB)    Reserved   ---*/
/*---   (0x0EAC)    Reserved   ---*/
/*---   (0x0EAD)    Reserved   ---*/
/*---   (0x0EAE)    Reserved   ---*/
/*---   (0x0EAF)    Reserved   ---*/
/*---   (0x0EB0)    Reserved   ---*/
/*---   (0x0EB1)    Reserved   ---*/
/*---   (0x0EB2)    Reserved   ---*/
/*---   (0x0EB3)    Reserved   ---*/
/*---   (0x0EB4)    Reserved   ---*/
/*---   (0x0EB5)    Reserved   ---*/
/*---   (0x0EB6)    Reserved   ---*/
/*---   (0x0EB7)    Reserved   ---*/
/*---   (0x0EB8)    Reserved   ---*/
/*---   (0x0EB9)    Reserved   ---*/
/*---   (0x0EBA)    Reserved   ---*/
/*---   (0x0EBB)    Reserved   ---*/
/*---   (0x0EBC)    Reserved   ---*/
/*---   (0x0EBD)    Reserved   ---*/
/*---   (0x0EBE)    Reserved   ---*/
/*---   (0x0EBF)    Reserved   ---*/
/*---   (0x0EC0)    Reserved   ---*/
/*---   (0x0EC1)    Reserved   ---*/
/*---   (0x0EC2)    Reserved   ---*/
/*---   (0x0EC3)    Reserved   ---*/
/*---   (0x0EC4)    Reserved   ---*/
/*---   (0x0EC5)    Reserved   ---*/
/*---   (0x0EC6)    Reserved   ---*/
/*---   (0x0EC7)    Reserved   ---*/
/*---   (0x0EC8)    Reserved   ---*/
/*---   (0x0EC9)    Reserved   ---*/
/*---   (0x0ECA)    Reserved   ---*/
/*---   (0x0ECB)    Reserved   ---*/
/*---   (0x0ECC)    Reserved   ---*/
/*---   (0x0ECD)    Reserved   ---*/
/*---   (0x0ECE)    Reserved   ---*/
/*---   (0x0ECF)    Reserved   ---*/
/*---   (0x0ED0)    Reserved   ---*/
/*---   (0x0ED1)    Reserved   ---*/
/*---   (0x0ED2)    Reserved   ---*/
/*---   (0x0ED3)    Reserved   ---*/
/*---   (0x0ED4)    Reserved   ---*/
/*---   (0x0ED5)    Reserved   ---*/
/*---   (0x0ED6)    Reserved   ---*/
/*---   (0x0ED7)    Reserved   ---*/
/*---   (0x0ED8)    Reserved   ---*/
/*---   (0x0ED9)    Reserved   ---*/
/*---   (0x0EDA)    Reserved   ---*/
/*---   (0x0EDB)    Reserved   ---*/
/*---   (0x0EDC)    Reserved   ---*/
/*---   (0x0EDD)    Reserved   ---*/
/*---   (0x0EDE)    Reserved   ---*/
/*---   (0x0EDF)    Reserved   ---*/
/*---   (0x0EE0)    Reserved   ---*/
/*---   (0x0EE1)    Reserved   ---*/
/*---   (0x0EE2)    Reserved   ---*/
/*---   (0x0EE3)    Reserved   ---*/
/*---   (0x0EE4)    Reserved   ---*/
/*---   (0x0EE5)    Reserved   ---*/
/*---   (0x0EE6)    Reserved   ---*/
/*---   (0x0EE7)    Reserved   ---*/
/*---   (0x0EE9)    Reserved   ---*/
/*---   (0x0EEA)    Reserved   ---*/
/*---   (0x0EEB)    Reserved   ---*/
/*---   (0x0EEC)    Reserved   ---*/
/*---   (0x0EED)    Reserved   ---*/
/*---   (0x0EEE)    Reserved   ---*/
/*---   (0x0EEF)    Reserved   ---*/
/*---   (0x0EF0)    Reserved   ---*/
/*---   (0x0EF1)    Reserved   ---*/
/*---   (0x0EF2)    Reserved   ---*/
/*---   (0x0EF3)    Reserved   ---*/
  /*---   (0x0EF4)    Reserved   ---*/
  /*---   (0x0EF5)    Reserved   ---*/
  /*---   (0x0EF6)    Reserved   ---*/
  /*---   (0x0EF7)    Reserved   ---*/
/*---   (0x0EF8)    Reserved   ---*/
/*---   (0x0EF9)    Reserved   ---*/
/*---   (0x0EFA)    Reserved   ---*/
/*---   (0x0EFB)    Reserved   ---*/
/*---   (0x0EFC)    Reserved   ---*/
/*---   (0x0EFD)    Reserved   ---*/
/*---   (0x0EFE)    Reserved   ---*/
/*---   (0x0EFF)    Reserved   ---*/

/***[SFR2]******************************************************/
EXTERN TYPE_BYTE        __io(0x0F00)    P0PD;            /* Port P0 input/output control */
EXTERN TYPE_BYTE        __io(0x0F01)    P1PD;            /* Port P1 input/output control */
EXTERN TYPE_BYTE        __io(0x0F02)    P2PD;            /* Port P2 input/output control */
EXTERN TYPE_BYTE        __io(0x0F04)    P4PD;            /* Port P4 input/output control */
EXTERN TYPE_BYTE        __io(0x0F07)    P7PD;            /* Port P7 input/output control */
EXTERN TYPE_BYTE        __io(0x0F08)    P8PD;            /* Port P8 input/output control */
EXTERN TYPE_BYTE        __io(0x0F09)    P9PD;            /* Port P9 input/output control */

/*---   (0x0F00)    Reserved   ---*/
/*---   (0x0F01)    Reserved   ---*/
/*---   (0x0F02)    Reserved   ---*/
/*---   (0x0F03)    Reserved   ---*/
/*---   (0x0F04)    Reserved   ---*/
/*---   (0x0F05)    Reserved   ---*/
/*---   (0x0F06)    Reserved   ---*/
/*---   (0x0F07)    Reserved   ---*/
/*---   (0x0F08)    Reserved   ---*/
/*---   (0x0F09)    Reserved   ---*/
/*---   (0x0F0A)    Reserved   ---*/
/*---   (0x0F0B)    Reserved   ---*/
/*---   (0x0F0C)    Reserved   ---*/
/*---   (0x0F0D)    Reserved   ---*/
/*---   (0x0F0E)    Reserved   ---*/
/*---   (0x0F0F)    Reserved   ---*/
/*---   (0x0F10)    Reserved   ---*/
/*---   (0x0F11)    Reserved   ---*/
/*---   (0x0F12)    Reserved   ---*/
/*---   (0x0F13)    Reserved   ---*/
/*---   (0x0F14)    Reserved   ---*/
/*---   (0x0F15)    Reserved   ---*/
/*---   (0x0F16)    Reserved   ---*/
/*---   (0x0F17)    Reserved   ---*/
/*---   (0x0F18)    Reserved   ---*/
/*---   (0x0F19)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F1A)    P0CR;            /* Port P0 input/output control */
EXTERN TYPE_BYTE        __io(0x0F1B)    P1CR;            /* Port P1 input/output control */
EXTERN TYPE_BYTE        __io(0x0F1C)    P2CR;            /* Port P2 input/output control *///unsupported for MQ6801
/*---   (0x0F1D)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F1E)    P4CR;            /* Port P4 input/output control */
/*---   (0x0F20)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F21)    P7CR;            /* Port P7 input/output control */
EXTERN TYPE_BYTE        __io(0x0F22)    P8CR;            /* Port P8 input/output control */
EXTERN TYPE_BYTE        __io(0x0F23)    P9CR;            /* Port P9 input/output control */
//EXTERN TYPE_BYTE        __io(0x0F25)    PBCR;            /* Port PB input/output control *///unsupported for MQ6801
EXTERN TYPE_BYTE        __io(0x0F27)    P0PU;            /* Port P0 built-in pull-up resistor control */
EXTERN TYPE_BYTE        __io(0x0F28)    P1PU;            /* Port P1 built-in pull-up resistor control */
EXTERN TYPE_BYTE        __io(0x0F29)    P2PU;            /* Port P2 built-in pull-up resistor control *///unsupported for MQ6801
/*---   (0x0F2A)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F2B)    P4PU;            /* Port P4 built-in pull-up resistor control */
  /*---   (0x0F2C)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F2E)    P7PU;            /* Port P7 built-in pull-up resistor control */
EXTERN TYPE_BYTE        __io(0x0F2F)    P8PU;            /* Port P8 built-in pull-up resistor control */
EXTERN TYPE_BYTE        __io(0x0F30)    P9PU;            /* Port P9 built-in pull-up resistor control */
/*---   (0x0F31)    Reserved   ---*/
/*---   (0x0F32)    Reserved   ---*/
/*---   (0x0F33)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F34)    P0FC;            /* Port P0 function control */
/*---   (0x0F35)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F36)    P2FC;            /* Port P2 function control *///unsupported for MQ6801
/*---   (0x0F37)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F38)    P4FC;            /* Port P4 function control */
/*---   (0x0F3A)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F3B)    P7FC;            /* Port P7 function control */
EXTERN TYPE_BYTE        __io(0x0F3C)    P8FC;            /* Port P8 function control */
EXTERN TYPE_BYTE        __io(0x0F3D)    P9FC;            /* Port P9 function control */
/*---   (0x0F3E)    Reserved   ---*/
//EXTERN TYPE_BYTE        __io(0x0F3F)    PBFC;            /* Port PB function control *///unsupported for MQ6801
/*---   (0x0F40)    Reserved   ---*/
/*---   (0x0F41)    Reserved   ---*/
/*---   (0x0F42)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F43)    P2OUTCR;         /* Port P2 output control */
/*---   (0x0F44)    Reserved   ---*/
/*---   (0x0F45)    Reserved   ---*/
/*---   (0x0F46)    Reserved   ---*/
/*---   (0x0F47)    Reserved   ---*/
/*---   (0x0F48)    Reserved   ---*/
/*---   (0x0F49)    Reserved   ---*/
//EXTERN TYPE_BYTE        __io(0x0F4A)    P9OUTCR;         /* Port P9 output control */
/*---   (0x0F4B)    Reserved   ---*/
//EXTERN TYPE_BYTE        __io(0x0F4C)    PBOUTCR;         /* Port PB output control *///unsupported for MQ6801
/*---   (0x0F4D)    Reserved   ---*/
/*---   (0x0F4E)    Reserved   ---*/
/*---   (0x0F4F)    Reserved   ---*/
/*---   (0x0F50)    Reserved   ---*/
/*---   (0x0F51)    Reserved   ---*/
/*---   (0x0F52)    Reserved   ---*/
/*---   (0x0F53)    Reserved   ---*/
EXTERN TYPE_BYTE    __io(0x0F54)    UART1CR1;        /* UART1 control register 1 *///unsupported for MQ6801
EXTERN TYPE_BYTE    __io(0x0F55)    UART1CR2;        /* UART1 control register 2 *///unsupported for MQ6801
EXTERN TYPE_BYTE    __io(0x0F56)    UART1DR;         /* UART1 baud rate register *///unsupported for MQ6801
EXTERN TYPE_BYTE    __io(0x0F57)    UART1SR;         /* UART1 status register *///unsupported for MQ6801
EXTERN TYPE_BYTE    __io(0x0F58)    U1BF;
#define TD1BUF U1BF                                 
/* UART1 transmit data buffer */
#define RD1BUF U1BF                                 
/* UART1 receive data buffer */
/*---   (0x0F59)    Reserved   ---*/
//EXTERN TYPE_BYTE    __io(0x0F5A)    UART2CR1;        /* UART2 control register 1 *///unsupported for MQ6801
//EXTERN TYPE_BYTE    __io(0x0F5B)    UART2CR2;        /* UART2 control register 2 *///unsupported for MQ6801
//EXTERN TYPE_BYTE    __io(0x0F5C)    UART2DR;         /* UART2 baud rate register *///unsupported for MQ6801
//EXTERN TYPE_BYTE    __io(0x0F5D)    UART2SR;         /* UART2 status register *///unsupported for MQ6801
//EXTERN TYPE_BYTE    __io(0x0F5E)    U2BF;
//#define TD2BUF U2BF                                 
/* UART1 transmit data buffer */
//#define RD2BUF U2BF                                 
/* UART1 receive data buffer */
/*---   (0x0F5F)    Reserved   ---*/
/*---   (0x0F60)    Reserved   ---*/
/*---   (0x0F61)    Reserved   ---*/
/*---   (0x0F62)    Reserved   ---*/
/*---   (0x0F63)    Reserved   ---*/
  /*---   (0x0F64)    Reserved   ---*/
/*---   (0x0F65)    Reserved   ---*/
/*---   (0x0F66)    Reserved   ---*/
/*---   (0x0F67)    Reserved   ---*/
/*---   (0x0F68)    Reserved   ---*/
/*---   (0x0F69)    Reserved   ---*/
/*---   (0x0F6A)    Reserved   ---*/
/*---   (0x0F6B)    Reserved   ---*/
/*---   (0x0F6C)    Reserved   ---*/
/*---   (0x0F6D)    Reserved   ---*/
/*---   (0x0F6E)    Reserved   ---*/
/*---   (0x0F6F)    Reserved   ---*/
/*---   (0x0F73)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F74)    POFFCR0;         /* Low power consumption register 0 */
EXTERN TYPE_BYTE        __io(0x0F75)    POFFCR1;         /* Low power consumption register 1 */
EXTERN TYPE_BYTE        __io(0x0F76)    POFFCR2;         /* Low power consumption register 2 */
EXTERN TYPE_BYTE        __io(0x0F77)    POFFCR3;         /* Low power consumption register 3 */
/*---   (0x0F78)    Reserved   ---*/
/*---   (0x0F79)    Reserved   ---*/
/*---   (0x0F7A)    Reserved   ---*/
/*---   (0x0F7B)    Reserved   ---*/
/*---   (0x0F7C)    Reserved   ---*/
/*---   (0x0F7D)    Reserved   ---*/
/*---   (0x0F7E)    Reserved   ---*/
/*---   (0x0F7F)    Reserved   ---*/
/*---   (0x0F80)    Reserved   ---*/
/*---   (0x0F81)    Reserved   ---*/
/*---   (0x0F82)    Reserved   ---*/
/*---   (0x0F83)    Reserved   ---*/
/*---   (0x0F84)    Reserved   ---*/
/*---   (0x0F85)    Reserved   ---*/
/*---   (0x0F86)    Reserved   ---*/
/*---   (0x0F87)    Reserved   ---*/

EXTERN TYPE_BYTE        __io(0x0F8C)    T02MOD;          /* Timer counter 02 mode register */
EXTERN TYPE_BYTE        __io(0x0F8D)    T03MOD;          /* Timer counter 03 mode register */
EXTERN TYPE_BYTE        __io(0x0F8E)    T023CR;          /* Timer counter 023 control register */
/*---   (0x0F8F)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0F90)    T00CNTL;
EXTERN TYPE_BYTE        __io(0x0F91)    T00CNTH;
EXTERN TYPE_BYTE        __io(0x0F92)    T01CNTL;
EXTERN TYPE_BYTE        __io(0x0F93)    T01CNTH;
EXTERN TYPE_BYTE        __io(0x0F94)    T02CNTL;
EXTERN TYPE_BYTE        __io(0x0F95)    T02CNTH;
EXTERN TYPE_BYTE        __io(0x0F96)    T03CNTL;
EXTERN TYPE_BYTE        __io(0x0F97)    T03CNTH;
/*---   (0x0F94)    Reserved   ---*/
/*---   (0x0F95)    Reserved   ---*/
/*---   (0x0F96)    Reserved   ---*/
/*---   (0x0F97)    Reserved   ---*/
/*---   (0x0F98)    Reserved   ---*/
/*---   (0x0F99)    Reserved   ---*/
/*---   (0x0F9A)    Reserved   ---*/
/*---   (0x0F9B)    Reserved   ---*/
EXTERN TYPE_BYTE    __io(0x0F9C)    T00REGL;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0F9D)    T00REGH;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0F9E)    T01REGL;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0F9F)    T01REGH;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0FA0)    T00PWML;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0FA1)    T00PWMH;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0FA2)    T01PWML;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0FA3)    T01PWMH;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0FA4)    T02REGL;          /* Timer register 02 */
EXTERN TYPE_BYTE    __io(0x0FA5)    T02REGH;          /* Timer register 02 */
EXTERN TYPE_BYTE    __io(0x0FA6)    T03REGL;          /* Timer register 03 */
EXTERN TYPE_BYTE    __io(0x0FA7)    T03REGH;          /* Timer register 03 */
EXTERN TYPE_BYTE    __io(0x0FA8)    T02PWML;          /* Timer register 02 */
EXTERN TYPE_BYTE    __io(0x0FA9)    T02PWMH;          /* Timer register 02 */
EXTERN TYPE_BYTE    __io(0x0FAA)    T03PWML;          /* Timer register 03 */
EXTERN TYPE_BYTE    __io(0x0FAB)    T03PWMH;          /* Timer register 03 */


EXTERN TYPE_BYTE    __io(0x0FB0)    T04REGL;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0FB1)    T04REGH;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0FB2)    T05REGL;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0FB3)    T05REGH;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0FB4)    T04PWML;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0FB5)    T04PWMH;          /* Timer register 00 */
EXTERN TYPE_BYTE    __io(0x0FB6)    T05PWML;          /* Timer register 01 */
EXTERN TYPE_BYTE    __io(0x0FB7)    T05PWMH;          /* Timer register 01 */
EXTERN TYPE_BYTE        __io(0x0FB8)    T04MOD;          /* Timer counter 04 mode register */
EXTERN TYPE_BYTE        __io(0x0FB9)    T05MOD;          /* Timer counter 05 mode register */
EXTERN TYPE_BYTE        __io(0x0FBA)    T045CR;          /* Timer counter 045 control register */
EXTERN TYPE_BYTE        __io(0x0FBB)    T04CNTL;
EXTERN TYPE_BYTE        __io(0x0FBC)    T04CNTH;
EXTERN TYPE_BYTE        __io(0x0FBD)    T05CNTL;
EXTERN TYPE_BYTE        __io(0x0FBE)    T05CNTH;
/*---   (0x0F9C)    Reserved   ---*/
/*---   (0x0F9D)    Reserved   ---*/
/*---   (0x0F9E)    Reserved   ---*/
/*---   (0x0F9F)    Reserved   ---*/
/*---   (0x0FA0)    Reserved   ---*/
/*---   (0x0FA1)    Reserved   ---*/
/*---   (0x0FA2)    Reserved   ---*/
/*---   (0x0FA3)    Reserved   ---*/
/*---   (0x0FA4)    Reserved   ---*/
/*---   (0x0FA5)    Reserved   ---*/
/*---   (0x0FA6)    Reserved   ---*/
/*---   (0x0FA7)    Reserved   ---*/
//EXTERN TYPE_BYTE        __io(0x0FA8)    TA1DRAL;//unsupported for MQ6801
//EXTERN TYPE_BYTE        __io(0x0FA9)    TA1DRAH;//unsupported for MQ6801
//EXTERN TYPE_BYTE        __io(0x0FAA)    TA1DRBL;//unsupported for MQ6801
//EXTERN TYPE_BYTE        __io(0x0FAB)    TA1DRBH;//unsupported for MQ6801
//#define TA1DRA _TA1DRA.word
//#define TA1DRAL TA1DRA.byte[0]                           /* Timer counter A1 register AL */
//#define TA1DRAH TA1DRA.byte[1]                           /* Timer counter A1 register AH */
//EXTERN TYPE_WORD        __io(0x0FAA)    _TA1DRB;
//#define TA1DRB _TA1DRB.word
//#define TA1DRBL TA1DRB.byte[0]                           /* Timer counter A1 register BL */
//#define TA1DRBH TA1DRB.byte[1]                           /* Timer counter A1 register BH */
//EXTERN TYPE_BYTE        __io(0x0FAC)    TA1MOD;          /* Timer counter A1 mode register *///unsupported for MQ6801
//EXTERN TYPE_BYTE        __io(0x0FAD)    TA1CR;           /* Timer counter A1 control register *///unsupported for MQ6801
//EXTERN TYPE_BYTE        __io(0x0FAE)    TA1SR;           /* Timer counter A1 status register *///unsupported for MQ6801
/*---   (0x0FAF)    Reserved   ---*/
/*---   (0x0FB0)    Reserved   ---*/
/*---   (0x0FB1)    Reserved   ---*/
/*---   (0x0FB2)    Reserved   ---*/
/*---   (0x0FB3)    Reserved   ---*/
/*---   (0x0FB4)    Reserved   ---*/
/*---   (0x0FB5)    Reserved   ---*/
/*---   (0x0FB6)    Reserved   ---*/
/*---   (0x0FB7)    Reserved   ---*/
/*---   (0x0FB8)    Reserved   ---*/
/*---   (0x0FB9)    Reserved   ---*/
/*---   (0x0FBA)    Reserved   ---*/
/*---   (0x0FBB)    Reserved   ---*/
/*---   (0x0FBC)    Reserved   ---*/
/*---   (0x0FBD)    Reserved   ---*/
/*---   (0x0FBE)    Reserved   ---*/
/*---   (0x0FC0)    Reserved   ---*/
/*---   (0x0FC1)    Reserved   ---*/
/*---   (0x0FC2)    Reserved   ---*/
/*---   (0x0FC3)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0FC4)    KWUCR0;          /* Key-on wakeup control register 0 */
EXTERN TYPE_BYTE        __io(0x0FC5)    KWUCR1;          /* Key-on wakeup control register 1 */
EXTERN TYPE_BYTE        __io(0x0FC6)    VDCR1;           /* Voltage detection control register 1 */
EXTERN TYPE_BYTE        __io(0x0FC7)    VDCR2;           /* Voltage detection control register 2 */
EXTERN TYPE_BYTE        __io(0x0FC8)    RTCCR;           /* Real time clock control register */
/*---   (0x0FC9)    Reserved   ---*/
EXTERN TYPE_BYTE        __io(0x0FCA)    KWUCR2;          /* Key-on wakeup control register 2 */
EXTERN TYPE_BYTE        __io(0x0FCB)    KWUCR3;          /* Key-on wakeup control register 3 */
EXTERN TYPE_BYTE        __io(0x0FCC)    IRSTSR;          /* Internal factor reset detection status register *///unsupported for MQ6801
EXTERN TYPE_BYTE        __io(0x0FCD)    WUCCR;           /* Warm-up counter control register */
EXTERN TYPE_BYTE    __io(0x0FCE)    WUCDR;           /* Warm-up counter data register */
EXTERN TYPE_BYTE        __io(0x0FCF)    CGCR;            /* Clock gear control register */
EXTERN TYPE_BYTE        __io(0x0FD0)    FLSCR1;          /* Flash memory control register 1 */
EXTERN TYPE_BYTE        __io(0x0FD1)    FLCM;
#define FLSCR2 FLCM                                
 /* Flash memory control register 2 */
#define FLSCRM FLCM                                 
/* Flash memory control register 1 monitor */
EXTERN TYPE_BYTE        __io(0x0FD2)    FLSSTB;          /* Flash memory standby control register */
EXTERN TYPE_BYTE        __io(0x0FD3)    SPCR;            /* Port input control register */
EXTERN TYPE_BYTE        __io(0x0FD4)    WDCTR;           /* Watchdog timer control register */
EXTERN TYPE_BYTE    __io(0x0FD5)    WDCDR;           /* Watchdog timer control code register */
EXTERN TYPE_BYTE    __io(0x0FD6)    WDCNT;           /* 8-bit up counter monitor */
EXTERN TYPE_BYTE        __io(0x0FD7)    WDST;            /* Watchdog timer status */
//EXTERN TYPE_BYTE        __io(0x0FD8)    EINTCR1;         /* External interrupt control register 1 *///unsupported for MQ6801
EXTERN TYPE_BYTE        __io(0x0FD9)    EINTCR2;         /* External interrupt control register 2 */
EXTERN TYPE_BYTE        __io(0x0FDA)    EINTCR3;         /* External interrupt control register 3 */
EXTERN TYPE_BYTE        __io(0x0FDB)    EINTCR4;         /* External interrupt control register 4 */
EXTERN TYPE_BYTE        __io(0x0FDC)    SYSCR1;          /* System control register 1 */
EXTERN TYPE_BYTE        __io(0x0FDD)    SYSCR2;          /* System control register 2 */
EXTERN TYPE_BYTE        __io(0x0FDE)    SYSCR3;          /* System control register 3 */
EXTERN TYPE_BYTE        __io(0x0FDF)    SYS4;
	#define SYSCR4 SYS4
	#define SYSSR4 SYS4
EXTERN TYPE_BYTE    __io(0x0FE0)    ILL;             /* Interrupt latch (ILL) */
EXTERN TYPE_BYTE    __io(0x0FE1)    ILH;             /* Interrupt latch (ILH) */
EXTERN TYPE_BYTE    __io(0x0FE2)    ILE;             /* Interrupt latch (ILE) */
EXTERN TYPE_BYTE    __io(0x0FE3)    ILD;             /* Interrupt latch (ILD) */
/*---   (0x0FE4)    Reserved   ---*/
/*---   (0x0FE5)    Reserved   ---*/
/*---   (0x0FE6)    Reserved   ---*/
/*---   (0x0FE7)    Reserved   ---*/
/*---   (0x0FE8)    Reserved   ---*/
/*---   (0x0FE9)    Reserved   ---*/
/*---   (0x0FEA)    Reserved   ---*/
/*---   (0x0FEB)    Reserved   ---*/
/*---   (0x0FEC)    Reserved   ---*/
/*---   (0x0FED)    Reserved   ---*/
/*---   (0x0FEE)    Reserved   ---*/
/*---   (0x0FEF)    Reserved   ---*/
//EXTERN TYPE_BYTE        __io(0x0FF0)    ILRSL;          /*  */
//EXTERN TYPE_BYTE        __io(0x0FF1)    ILRSH;          /*  */
//EXTERN TYPE_BYTE        __io(0x0FF2)    ILRSE;          /*  */
//EXTERN TYPE_BYTE        __io(0x0FF3)    ILRSD;          /*  */
//EXTERN TYPE_BYTE        __io(0x0FF4)    ILPRS5;          /*  */
//EXTERN TYPE_BYTE        __io(0x0FF5)    ILPRS6;          /*  */
//EXTERN TYPE_BYTE        __io(0x0FF6)    ILPRS7;          /*  */
/*---   (0x0FF6)    Reserved   ---*/
/*---   (0x0FF7)    Reserved   ---*/
/*---   (0x0FF8)    Reserved   ---*/
/*---   (0x0FF9)    Reserved   ---*/
/*---   (0x0FFA)    Reserved   ---*/
/*---   (0x0FFB)    Reserved   ---*/
/*---   (0x0FFC)    Reserved   ---*/
/*---   (0x0FFD)    Reserved   ---*/
/*---   (0x0FFE)    Reserved   ---*/
/*---   (0x0FFF)    Reserved   ---*/

/*-eof-*/

//===========================

	
//===========================