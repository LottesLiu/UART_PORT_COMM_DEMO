/*****************************************************************
;*        Sample SFR/Vector File for TLCS-870/C1 Series          *
;*               Memory Style: Within 64K byte                   *
;*---------------------------------------------------------------*
;*  (C)Copyright TOSHIBA CORPORATION 2008  All rights reserved   *
;*****************************************************************/
//#define IO_MEM    1


#include "MQ6812.h"
#include "iApp.h"
#include "ExtINT.h"

extern uchar keySLIP, keyPUSH, keySLIP_down, keySLIP_up;
extern uchar cnt1_10ms, cnt2_10ms, cnt1_50ms, cnt2_50ms, cnt_1s;
extern uchar rec_done_flag, rec_start, rec_cnt, uart_flag;
extern uchar TX_DATA, RX_DATA;

char rx_data[10] = {0};

void startup(void);	//defined by startup.asm
/*========================================================
  [ Declare interrupt function ]
  ========================================================*/
void __interrupt Int2(void); 
void __interrupt Int3(void); 
void __interrupt Int4(void); 
void __interrupt IntTC00(void); 
void __interrupt IntTC01(void);
void __interrupt IntTC02(void);
void __interrupt IntTC03(void);
void __interrupt IntTC04(void);
void __interrupt IntTC05(void);
void __interrupt IntTCA0(void);
void __interrupt IntRTC(void);
void __interrupt IntADC(void);
void __interrupt IntVLTD(void);
void __interrupt IntRXD1(void);
void __interrupt IntTXD1(void);
void __interrupt IntSBI(void);
void __interrupt IntSIO0(void);
void __interrupt IntTBT(void);
void __interrupt IntWUC(void);
void __interrupt_n IntWDT(void);  
void __interrupt_n IntSWI(void);  


/*========================================================
  [ Dummy function for interrupt ]
  ========================================================*/
void __interrupt		Int_dummy(void){ }
void __interrupt_n		Int_n_dummy(void){ }

/*========================================================
  [ Implement interrupt function]
  ========================================================*/
void __interrupt Int2(void)
{
//if(1){D4 = 1;delay_times(t_1ms, 50);D4 = 0;return;}

    d_ExtINT_02_Dis;
    keyPUSH = 1;
    // TCH3                 // P7PRD.bit.b5
    if( keySLIP >= 1 )
    {
        keySLIP_down = 1;
        d_ExtINT_02_Dis;
        d_ExtINT_03_Dis;
        d_ExtINT_04_Dis;
    }
    else
    {
        delay_times(t_1ms, 20);
        if( (TCH1 == 1) || (TCH2 == 1) )
        {
            keyPUSH = 100;
            d_ExtINT_02_Dis;
            d_ExtINT_03_Dis;
            d_ExtINT_04_Dis;
        }
        else
        {
            keySLIP = 1;
            d_ExtINT_03_Dis;
        }
    }
}    
void __interrupt Int3(void)
{
//if(1){D2=D3 = 1;delay_times(t_1ms, 50);D2=D3 = 0;return;}

    d_ExtINT_03_Dis;
    keyPUSH = 1;
    // TCH2                 // P7PRD.bit.b6
    if( keySLIP >= 1 )
    {
    //    delay_times(t_1ms, 10);
    }
    else
    {
        delay_times(t_1ms, 20);
        if( (TCH1 == 1) || (TCH3 == 1) )
        {
            keyPUSH = 100;
            d_ExtINT_02_Dis;
            d_ExtINT_03_Dis;
            d_ExtINT_04_Dis;
        }
        else
        {
            keySLIP = 1;
        }
    }
}   
void __interrupt Int4(void)
{
//if(1){D1 = 1;delay_times(t_1ms, 50);D1 = 0;return;}

    d_ExtINT_04_Dis;
    keyPUSH = 1;
    // TCH1                 // P7PRD.bit.b7
    if( keySLIP >= 1 )
    {
        keySLIP_up = 1;
        d_ExtINT_02_Dis;
        d_ExtINT_03_Dis;
        d_ExtINT_04_Dis;
    }
    else
    {
        delay_times(t_1ms, 20);
        if( (TCH2 == 1) || (TCH3 == 1) )
        {
            keyPUSH = 100;
            d_ExtINT_02_Dis;
            d_ExtINT_03_Dis;
            d_ExtINT_04_Dis;
        }
        else
        {
            keySLIP = 1;
            d_ExtINT_03_Dis;
        }
    }
}   
void __interrupt IntTC00(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntTC01(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntTC02(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntTC03(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntTC04(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntTC05(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntTCA0(void)
{
    cnt1_10ms++;
	cnt2_10ms++;

    if( cnt1_10ms >= 5 )
    {
        cnt1_10ms = 0;
        cnt1_50ms++;
		cnt2_50ms++;
        flag1_50ms = 1;
		flag2_50ms = 1;
		flag3_50ms = 1;
    }
	 if( cnt2_50ms >= 4 )
    {
        cnt2_50ms = 0;
        flag_200ms  = 1;
    }
    if( cnt1_50ms >= 20 )
    {
        cnt1_50ms = 0;
		cnt_1s++;
        flag_1s  = 1;
		flag1_1s = 1;
		flag2_1s = 1;
    }
    if( cnt_1s >= 3 )
    {
        cnt_1s = 0;
        flag_3s  = 1;
    }
	 if( keyPUSH ) keyPUSH++;
	//Add your interrupt handler code here
}   
void __interrupt IntRTC(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntADC(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntVLTD(void)
{
	//Add your interrupt handler code here
}   

void __interrupt IntRXD1(void)
{

	uart_flag = UART1SR.byte;	//get flag data [PERR,   FERR,  OERR,  -,     RBSY,  RBFL,   TBSY,   TBFL]
								//   PERR	奇偶校验错误标帜	0: 无奇偶校验错误
								// 							1: 发生奇偶校验错误
								//	 RFERR	收发框错误标帜	0: 无收发框错误
								// 							1: 发生收发框错误
								//	 OERR	溢出错误标帜		0: 无溢出错误
								// 							1: 发生溢出错误
								// 	 RBSY	接收忙碌标帜		0: 接收前或接收工作结束
								// 							1: 接收中
								// 	 RBFL	接收缓存器已满标帜	0: 接收缓存器为空
								// 								1: 接收缓存器已满
								// 	 TBSY	发送忙碌标帜		0: 发送前或发送工作结束
								// 							1: 发送中
								// 	 TBFL	发送缓存器已满标帜	0: 发送缓存器为空
								// 								1: 发送缓存器已满

	RX_DATA = RD1BUF.byte;		//get Rx data and clear flag

if( rec_start == 0x00 && RX_DATA == 0xaa)
{
	rec_start = 0xaa;
	rec_done_flag = 0;
	rec_cnt=0;
	rx_data[rec_cnt] = RX_DATA;
}
else if( rec_start == 0xaa )
{
	 rec_cnt++;
	 rx_data[rec_cnt] = RX_DATA;
	 
	 if( RX_DATA==0XED)
	 {
	 	rec_start = 0x00;
		rec_cnt = 0;
		rec_done_flag = 1;
	 }
	 
}
	//Add your interrupt handler code here
}   
void __interrupt IntTXD1(void)
{
	//Add your interrupt handler code here
}    
void __interrupt IntSBI(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntSIO0(void)
{
	//Add your interrupt handler code here
}    
void __interrupt IntTBT(void)
{
	//Add your interrupt handler code here
}   
void __interrupt IntWUC(void)
{
	//Add your interrupt handler code here
}   
void __interrupt_n IntWDT(void)
{
	//Add your interrupt handler code here
}    
void __interrupt_n IntSWI(void)
{
	//Add your interrupt handler code here
	unsigned char tmp; 
	tmp =*(unsigned char*)(0xf000);
	while(tmp != *(unsigned char*)(0xf000))
	{
		tmp =*(unsigned char*)(0xf000);
		
	}	
	SYSCR2.byte=0x10;	//system clock reset
}      
/*============================================
  [ Define interrupt table ]
    This part must be rewrite.
  ============================================*/
#pragma section const INT_VECTOR1
void * const IntTbl1[] = {
	IntTC05,			/* 0xffc4 : IntTC05 */
    IntTC04,			/* 0xffc6 : IntTC04 */
	(void *)0xffff,		/* 0xffc8 : Reserved */
    (void *)0xffff,		/* 0xffca : Reserved */
    IntTC03,			/* 0xffcc : IntTC03 */
    IntTC02,			/* 0xffce : IntTC02 */
    IntTXD1,			/* 0xffd0 : IntTXD1 */
    IntRXD1,			/* 0xffd2 : IntRXD1 */
    Int_dummy,			/* 0xffd4 : Reserved */	
    Int4,				/* 0xffd6 : Int4 */
    Int3,				/* 0xffd8 : Int3 */
    Int2,				/* 0xffda : Int2 */
    Int_dummy,			/* 0xffdc : Reserved */
    Int_dummy,			/* 0xffde : Reserved */
    IntSBI,				/* 0xffe0 : IntSBI */
    IntTCA0,			/* 0xffe2 : IntTCA0  */
    IntTC01,			/* 0xffe4 : IntTC01 */
    IntTC00,			/* 0xffe6 : IntTC00 */
    IntRTC,				/* 0xffe8 : IntRTC */
    IntADC,				/* 0xffea : IntADC */
    IntVLTD,			/* 0xffec : IntVLTD */
    Int_dummy,			/* 0xffee : Reserved */
    Int_dummy,			/* 0xfff0 : Reserved */
    IntSIO0,			/* 0xfff2 : IntSIO0 */
    IntTBT,				/* 0xfff4 : IntTBT */
    IntWUC,	    		/* 0xfff6 : IntWUC */
    IntWDT,				/* 0xfff8 : IntWDT */
    (void *)0xffff,		/* 0xfffa : Reserved */
    IntSWI,	   			/* 0xfffc : IntSWI/INTUNDEF */     
    startup		    	/* 0xfffe : RESET */					
};
#pragma section const   /* return to default */
