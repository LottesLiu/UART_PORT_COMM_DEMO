//******************************************
//           This is a C Template file
//���ߣ�
//����
//����
//��ע
//******************************************
/*                            Pin Assignment
 *********************************************************************
 ............................32.VDD
 ............................31.P40/AIN0/KWI0
 ............................30.P41/AIN1/KWI1
 ............................29.P42/AIN2/KWI2
 ............................28.P43/AIN3/KWI3/VREF
 ............................27.P44/AIN4/KWI4/SEG11
 ............................26.P45/AIN5/KWI5/SEG10
 ............................25.P46/AIN6/KWI6/SEG9
 ...............................3 3 3 2 2 2 2 2.............................
 ...............................2 1 0 9 8 7 6 5.............................
 ..............................-----------------............................
 01.VSS......................01|O              |24...P47/AIN7/KWI7/SEG8
 02.P00/XIN..................02|               |23...P74/DVOB/AIN8/SI/KWI13/SEG7
 03.P01/XOUT.................03|     QFN-32    |22...P76/INT3/SCLK/KWI15/SEG6
 04.P10/RESETB...............04|    LQFP-32    |21...P70/TC00/PWM00B/SEG5
 05.P71/TC01/PWM01B..........05|               |20...P75/INT2/SO/KWI14/SEG4
 06.P90/TX/RX/COM0...........06|               |19...P77/INT4/SS/SEG3
 07.P91/RX/TX/COM1...........07|               |18...P27/RX/TX/KWI11/SEG2
 08.P80/TC02/PWM02B..........08|               |17...P26/TX/RX/KWI10/SEG1
 ..............................-----------------............................
 ...............................0 1 1 1 1 1 1 1.............................
 ...............................9 0 1 2 3 4 5 6.............................
 ............................09.P81/TC03/PWM03B
 ............................10.P72/TCA0/PPGA0B/COM2
 ............................11.P73/COM3/KWI12
 ............................12.P82/TC04/PWM04B/COM4
 ............................13.P83/TC05/PWM05B/COM5
 ............................14.P23/SDA/COM6
 ............................15.P24/SCL/KWI8/COM7
 ............................16.P25/KWI9/SEG0
 *********************************************************************/
//******************************************
//Stack Pointer    =    0x23f (If use mq6812_x_startup.asm)
//Ram range = 0x40~0x23f
//******************************************

//******************************************
//----------------------------------------//
//    Application Note
//    MQ6812/MQ6821 ʹ��SWITCH ָ��ע������
//----------------------------------------//
//    ��MQ6812/MQ6821ϵ�в�Ʒ��16KB flash������ϵ�в�Ʒ��ͬ���ڵ�·����϶�ʱ��(timing)��Ҫ��ϸߣ�
//    ָ�� ��JP gg(ע1)�� �ڼ��������¿����л��ʻ������һ�ű��޷���ȷ��ȡ֮״����Ϊ��������������
//    �����������¡����������޸�SWITCHָ��ķ�ʽ����˵�������г����׫д��
//
//    ע1: ����gg Ϊ16λͨ�û�����WA, BC, DE, HL, IX, IY��, ��ϸָ��˵����ο�TLCS-870/C1 Series Instruction Set��66ҳ)��
//
//    ��Ҫ���Ӵ�ָ���޸ĵĲ�Ʒ:
//    (1)    MQ6812ϵ�в�Ʒ��������Ʒ�ͺ�ΪMQ6812SP028HAER(SOP28��װ)��MQ6812SS028HAER(SSOP28��װ)��MQ6812LQ032HAER(LQFP32��װ)��MQ6812N4032HAER(QFN32��װ)��
//    (2)    MQ6821ϵ�в�Ʒ��������Ʒ�ͺ�ΪMQ6821SP020HAER(SOP20��װ)��MQ6821SS020HAER(SSOP20��װ)��MQ6821DP020HAER(DIP20��װ)��
//
//
//    MQ6812/MQ6821ϵ�в�Ʒ��SWITCHָ�����һ��CASE֮��������һ��NOPָ���������·�����
//    \\-->>        switch(variable)
//    \\-->>        {
//    \\-->>            __asm("NOP");                // switch ���һ�� case ֮������һ�� "NOP"���������� "JP gg" ָ�
//    \\-->>            case 0:
//    \\-->>                // Add your code here ......
//    \\-->>                break;
//  \\-->>
//    \\-->>            default:
//    \\-->>                // Add your code here ......
//    \\-->>                break;
//    \\-->>        }
//    �޸ĺ�, ʹ��MQ-Link����ʱ�����־��� I87C1-Warning-538, ��Ϊ��������, ����Դ���Ϣ��
//----------------------------------------//


#ifndef    IO_MEM
#define    IO_MEM
#endif
#include "MQ6812.h"
#include "iApp.h"
#include "OPmode.h"
#include "KWU.h"
#include "ExtINT.h"
#include "ADC.h"
#include "pb_protocol.h"
#include "ipwm.h"
#include "DeviceAttachDet.h"
#include "pb_comm.h"
#include "pb_package.h"
#include "uart_data.h"
//#include "pb_tkey.h"





//--------------------------------------------------------------------------------------------------//
//    ���� <OPmode.h> �������ⲿ���� (���� or ����), ����ο�����˵����
//    �ⲿ����� HXTAL/LXTAL ʹ����ͬ IO(P00/P01), ֻ����һ����.
//.....................................................................................
//#undef    XTAL_High        // �����ⲿ���پ���: #define(ʹ�þ���) / #undef(���þ���) :
//#undef    XTAL_Low        // �����ⲿ���پ���: #define(ʹ�þ���) / #undef(���þ���) :
//            |........................................................................................
//            |---------> // ע������:
//            |---------> // 1. Enable LXtal: ���趨 FSCTRL.bit.b0 = 1; --> FSCTRL��ʹ�õ�λԪ(bit operation)
//            |---------> // 2. ���������ⲿ����������¼ʱ, ���乴ѡ ext low OSC:
//            |---------> //    IDE��¼        : Project -> Pin Setting -> ��ѡ ext low OSC
//            |---------> //    Writer��¼    : ��ѡType -> ��IC typeѡ��ͬһҳ���ҷ� -> ��ѡ ext low OSC
//            .........................................................................................
//--------------------------------------------------------------------------------------------------//


void SYSTEM_INIT(void);
void KWI_INIT(void);
void UART_INIT(void);
void UART_INIT_P26P27(void);
void UART_Pin_Function_CHG(uchar sel_pin);
void ADC_IO_INIT(void);
void PPG00_INIT(uint T1, uint T2);
void PPG00_adj(uint T1, uint T2);
void ExtINT_INIT(void);
void TIMER_TCA0(void);
void Ext_INIT(void);
void key_active_check(void);



void STOP_for_RESET(void);
void test_IO(void);
void test_UART(void);
void test_AD(void);





uchar cnt1_10ms, cnt2_10ms, cnt1_50ms,cnt2_50ms,cnt_1s;
uchar keySLIP, keyPUSH, keySLIP_down, keySLIP_up;
uchar temp_bit, temp2_bit;
extern char  str_list[];
uchar s1_counter =0;


uchar print_permit_flag =0;

extern SENT_EVT sent_evt ;
extern REC_EVT     rec_evt  ;
extern uchar TX_DATA, RX_DATA;
extern uchar rec_done_flag, rec_start, rec_cnt, uart_flag;
SENT_EVT_STA   tx_sta_cur = 0;
SENT_EVT_STA   tx_sta_nxt = 0;

REC_EVT_STA     rx_sta_cur = 0;
REC_EVT_STA     rx_sta_nxt = 0;

uchar UART_CUR = 0;

void main()
{
    cnt1_10ms=0;
    cnt2_10ms=0;
    cnt1_50ms = 0;
    
    
    
    SYSTEM_INIT();        // IO, CGCR ��ʼ������ P10/P40/P41 �ڷ���ʱ֮�趨
    KWI_INIT();         // ֹͣģʽ���ѽų�ʼ��
    UART_INIT();
    UART_Pin_Function_CHG(0);         // selected P90 P91 as UART FUNCTION PORT
    ADC_IO_INIT();
    TIMER_TCA0();
    PPG00_INIT(0, 100);
    Ext_INIT();
    WDCDR.byte = 0x4e;                // clear wdt
    //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    delay_times(t_1ms, 10);
    BAT_EN = 1;    // mcu wake up bat_en = 1 , mcu go to sleep bat_en = 0;
    
    //-*-*-*-*-*-*-*-*-*-*-*  IMITATE TEST  *-*-*-*-*-*-*-*-*-*-*-*-*-*-
    
    
    //-*-*-*-*-*-*-*-*-*-*-*  IMITATE TEST  *-*-*-*-*-*-*-*-*-*-*-*-*-*-
    D1=1;
    
    //sprintf(str_list, "HW INIT ...\r\n");
    // printf_byUART();
    
    while(1)
    {
        WDCDR.byte = 0x4e;            // clear wdt
        Rx_Rcv_Data();
        
        Uart_Sent_Manager();
        Uart_Receive_Manager();
        
        //         if(flag1_1s==1)
        //         {
        //             flag1_1s = 0;
        //             s1_counter++;
        //             if(s1_counter>10)
        //             {
        //                 s1_counter = 0;
        //                 if(UART_CUR==0)
        //                 {
        //                      UART_Pin_Function_CHG(1);
        //                      UART_CUR = 1;
        //                      D4=1;
        //                 }
        //                 else
        //                 {
        //                      UART_Pin_Function_CHG(0);
        //                      UART_CUR = 0;
        //                       D4=0;
        //                 }
        //             }
        //
        //         }
        
        
        
    }
    //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
}




//*********************************************************************
// ������    : SYSTEM_INIT(void)
// ��������    : IO, CGCR ��ʼ������ P10/P40/P41 �ڷ���ʱ֮�趨
// ��ע        :
//*********************************************************************
void SYSTEM_INIT(void)
{
#ifdef _DEBUG    //...  _DEBUG(����ģʽ��): ���ڷ��� ev board
    //------------------------------------------------------------------
    //    (ϵͳĬ��): ����ʱ��P10�趨ΪReset Pin���Ա���Ӱ����漰��¼����.
    //    SYSCR3.byte   = 0x00;    // SYSCR3.bit.b0=1: ��P10�趨Ϊһ��IO��, SYSCR3.bit.b0=0(Ԥ��ֵ): P10Ϊ Reset Pin
    //    SYSCR4.byte   = 0xB2;    // 0xB2: ���� SYSCR3.bit.b0 ֮�趨ֵ
    //------------------------------------------------------------------
    FSCTRL.bit.b0 = 0;        // 0ΪĬ��ֵ���������б����λ(bit)���ڷ���ģʽ�����ֶ���ʼ����ΪĬ��ֵ 0
    //------------------------------------------------------------------
#else            //...  ��һ���ϵ��ܳ���(�Ƿ���ģʽ��)���� P10(RESET) ��λ����Ϊһ�� IO ��
    //------------------------------------------------------------------
    //-- ��P10�趨Ϊһ��IO�� ------
    //SYSCR3.byte = 0x01;        // SYSCR3.bit.b0=1: ��P10�趨Ϊһ��IO��, SYSCR3.bit.b0=0(Ԥ��ֵ): P10Ϊ Reset Pin
    //SYSCR4.byte = 0xB2;        // 0xB2: ���� SYSCR3.bit.b0 ֮�趨ֵ
    //------------------------------------------------------------------
#endif
    
    
    
    //-- ��ʼ�� IO �� (�����λ����)------
#ifdef _DEBUG    //...  _DEBUG: ���ڷ��� ev board
    //------------------------------------------------------------------
    //    ������� P10/P40/P41 �� Debug mode���ڷ���ʱ�����趨Ϊ���룬
    //    �Ա���Ӱ����漰��¼����.
    P1DR.byte = 0x00;
    P1CR.byte = set8bit(11111110);        // ���� P10 Ϊ����
    P4DR.byte = 0x00;
    P4CR.byte = set8bit(01111100);        // ���� P40/P41 Ϊ����
    //------------------------------------------------------------------
#else            //...  ��һ���ϵ��ܳ���(�Ƿ���ģʽ��)
    //------------------------------------------------------------------
    P1DR.byte = 0x00;
    P1CR.byte = 0xff;
    P4DR.byte = 0x00;
    P4CR.byte = set8bit(01111111);
    //------------------------------------------------------------------
#endif
    
    //-- ��ʼ�� IO �� ------
    P0DR.byte = 0x00;
    P0CR.byte = 0xff;
    //    P1DR.byte = 0x00;
    //    P1CR.byte = 0xff;
    P2DR.byte = 0x00;
    P2CR.byte = 0x00;
    P4DR.byte = 0x00;
    P4CR.byte = 0xff;
    P7DR.byte = 0x00;
    P7CR.byte = set8bit(00010111); // wakeup front is p73 ???
    P8DR.byte = 0x00;
    P8CR.byte = 0xff;
    P9DR.byte = 0x00;
    P9CR.byte = 0xff;
    //    look_data(IRSTSR.byte);        // IRSTSR: �ڲ����ظ�λ���״̬�Ĵ���
    WDCDR.byte = 0x4e;            // clear wdt
    
    
    //    ============================================
    //    ���پ����Ƶ���ã�CGCR                    ;  fc = 16MHz
    //    ============================================
    //    CGCR.byte = 0x00;            // ==> fcgck = fc/4 =  4Mhz(ϵͳĬ��)
    CGCR.byte = 0x01;            // ==> fcgck = fc/2 =  8Mhz
    //    CGCR.byte = 0x02;            // ==> fcgck = fc   = 16Mhz
    //    CGCR.byte = 0x03;            // ==> fcgck = fc/8 =  2Mhz
    //    ============================================
    //    *** �벻Ҫ�ڵ���ģʽ(SLOW1/SLOW2) �ı� CGCR<FCGCKSEL> �Ĵ�����ֵ
    //    ============================================
    
    
    //--------------------------------------------------------------------------------------------------//
    //    ���� <OPmode.h> �������ⲿ���� (���� or ����), ����ο�����˵����
    //    �ⲿ����� HXTAL/LXTAL ʹ����ͬ IO(P00/P01), ֻ����һ����.
    //.....................................................................................
    //#undef    XTAL_High        // �����ⲿ���پ���: #define(ʹ�þ���) / #undef(���þ���) :
    //#undef    XTAL_Low        // �����ⲿ���پ���: #define(ʹ�þ���) / #undef(���þ���) :
    //            |........................................................................................
    //            |---------> // ע������:
    //            |---------> // 1. Enable LXtal: ���趨 FSCTRL.bit.b0 = 1; --> FSCTRL��ʹ�õ�λԪ(bit operation)
    //            |---------> // 2. ���������ⲿ����������¼ʱ, ���乴ѡ ext low OSC:
    //            |---------> //    IDE��¼        : Project -> Pin Setting -> ��ѡ ext low OSC
    //            |---------> //    Writer��¼    : ��ѡType -> ��IC typeѡ��ͬһҳ���ҷ� -> ��ѡ ext low OSC
    //            .........................................................................................
    //--------------------------------------------------------------------------------------------------//
    //    ���к�����ѡ���Ƿ��л��ⲿ���پ���
    XTAL_High_Config();
    
}


void KWI_INIT(void)
{
    //    disable all Key-On Wakeup setting
    d_KWU_all_disable;                //    disable all Key-On Wakeup setting
    
    //    Key-On Wakeup setting
    d_KWU_10_EnH;
    d_KWU_12_EnH;
    //......|..| EnL/EnH/Dis: stop mode release level, or Disable
    //......| 00~15: KWU00~KWU15
}


void UART_INIT(void)
{
    //=========================
    P9CR.bit.b0 = 0x0;  // �趨P90����
    P9CR.bit.b1 = 0x1;    // �趨P91���
    P9FC.bit.b1 = 0x1;  // �л�P91Ϊ���⹦�ܽ�
    UATCNG.bit.b1 = 1;  // �O�� P91��TXݔ��, P90��RXݔ��
    
    //=========================
    __asm("DI");
    POFFCR1.bit.b1 = 1;     // UART1EN
    
    ILE.bit.b7   = 0;
    ILE.bit.b6   = 0;
    EIRE.bit.b7  = 1;       // INTTXD1
    EIRE.bit.b6  = 1;       // INTRXD1
    __asm("EI");
    
    //------ Baud rate = 9600 @ 8MHz
    UART1CR2.byte = 0x20;    //RTSEL 100  17��ʱ�ӣ�RXDNC 00: ��������ֹ  STOPBR ���ն˽���λ����0: 1λ
    UART1DR.byte  = 48;        //baud rate = 9600
    //------ Baud rate = 9600 @ 4MHz
    //    UART1CR2.byte = 0x20;    //RTSEL 100  17��ʱ�ӣ�RXDNC 00: ��������ֹ  STOPBR ���ն˽���λ����0: 1λ
    //    UART1DR.byte  = 24;        //baud rate = 9600
    
    UART1CR1.byte = 0xc0;
}
//*********************************************************************
// ������   :
// �������� :
// ��ע     :
//*********************************************************************
void UART_INIT_P26P27(void)
{
    //=========================
    P2CR.bit.b6 = 0;        // �趨P26����
    P2CR.bit.b7 = 1;        // �趨P27���
    P2FC.bit.b7 = 1;        // �л�P27Ϊ���⹦�ܽ�
    UATCNG.bit.b2 = 1;      // 1: �O�� P26 P27 �鴮�ڹ����_
    UATCNG.bit.b1 = 1;      // 1: �O�� P27��TXݔ��, P26��RXݔ��
    
    //=========================
    __asm("DI");
    POFFCR1.bit.b1 = 1;     // UART1EN
    
    ILE.bit.b7   = 0;
    ILE.bit.b6   = 0;
    EIRE.bit.b7  = 1;       // INTTXD1
    EIRE.bit.b6  = 1;       // INTRXD1
    __asm("EI");
    
    //------ Baud rate = 38400 @ 8MHz
    //     UART1CR2.byte = 0x00;    //RTSEL 100  17��ʱ�ӣ�RXDNC 00: ��������ֹ  STOPBR ���ն˽���λ����0: 1λ
    //     UART1DR.byte  = 12;        //baud rate = 38400
    //------ Baud rate = 9600 @ 8MHz
    UART1CR2.byte = 0x20;    //RTSEL 100  17��ʱ�ӣ�RXDNC 00: ��������ֹ  STOPBR ���ն˽���λ����0: 1λ
    UART1DR.byte  = 48;        //baud rate = 9600
    //------ Baud rate = 9600 @ 4MHz
    //    UART1CR2.byte = 0x20;    //RTSEL 100  17��ʱ�ӣ�RXDNC 00: ��������ֹ  STOPBR ���ն˽���λ����0: 1λ
    //    UART1DR.byte  = 24;        //baud rate = 9600
    
    UART1CR1.byte = 0xc0;
}
//*********************************************************************
// ������   :
// �������� :
// ��ע     : 0: ѡ�� P90 P91 Ϊ UART ���ڹ��ܽ�
//            1: ѡ�� P26 P27 Ϊ UART ���ڹ��ܽ�
//*********************************************************************
void UART_Pin_Function_CHG(uchar sel_pin)
{
    
    while( UART1SR.bit.b1 == 1 ) WDCDR.byte = 0x4e;     // ȷ�� UART ����״̬�Ƿ���������л� UART ���ܽ�
    
    if( sel_pin == 0 )
    {
        //=========================
        P9CR.bit.b0 = 0;                // �趨P90����
        P9CR.bit.b1 = 1;                // �趨P91���
        P9FC.bit.b1 = 1;                // �л�P91Ϊ���⹦�ܽ�
        UATCNG.bit.b2 = 0;              // 0: �O�� P90 P91 �鴮�ڹ����_
        UATCNG.bit.b1 = 1;              // 1: �O�� P91��TXݔ��, P90��RXݔ��
    }
    else
    {
        
        //=========================
        P2CR.bit.b6 = 0;                // �趨P26����
        P2CR.bit.b7 = 1;                // �趨P27���
        P2FC.bit.b7 = 1;                // �л�P27Ϊ���⹦�ܽ�
        UATCNG.bit.b2 = 1;              // �O�� P26 P27 �鴮�ڹ����_
        UATCNG.bit.b1 = 1;              // �O�� P27��TXݔ��, P26��RXݔ��
    }
}


void ADC_IO_INIT(void)
{
    //    ���D������ AIN5(P45) AIN6(P46)Ϊ ADC ���������
    P4FC.bit.b5 = 1;
    P4CR.bit.b5 = 0;
    P4FC.bit.b6 = 1;
    P4CR.bit.b6 = 0;
    
    //-----------------------------------
    //    ִ��һ�Σ�ȡ���ڲ�Vref 2V֮ʵ��ֵ
    //    MQ6812:��ȡֵΪ ( �ڲ�Vref 2V֮ʵ��ֵ * 1024 ), ��λΪmV
    iReal_Vref2V = GetVref();
    //-----------------------------------
}


void PPG00_INIT(uint T1, uint T2)
{
    //============================================
    // setting and start TCQ00
    //============================================
    P7DR.bit.b0    =0;            //set P70 output
    P7CR.bit.b0    =1;            //set P70 output
    __asm("DI");
    POFFCR0.bit.b4=1;         //[-.TC045EN,TC023EN,TC001EN    -,-,-,TCA0EN]
    //�_��TC00 TC01 CLK SOURCE
    //    ILH.bit.b4 =0;
    //    EIRH.bit.b4=1;             //[-,INTTCA0,INTTC01,INTTC00    INTRTC,INTADC,INTLVD,-]
    //�_��INTTC00
    __asm("EI");
    T00MOD.byte=0xC3;        //[TFF0,DBE0,TCK0[3],-,TCM0]
    //<DBE0>=1,<TCK0>=��111��,<TCM0>=10 10λPWMģʽ
    
    //----------------------------------------//
    //    ...... ��� 0% �趨 ................
    //----------------------------------------//
    if( T1 == 0 )
    {
        P7DR.bit.b0     = 0;    // PPG00 = 0
        P7FC.bit.b0     = 0;    // disable PPG00
    }
    //----------------------------------------//
    //    ...... ��� 100% �趨 ..............
    //----------------------------------------//
    else if( T1 == T2 )
    {
        P7DR.bit.b0     = 1;    // PPG00 = 1
        P7FC.bit.b0     = 0;    // disable PPG00
    }
    //----------------------------------------//
    else
    {
        P7FC.bit.b0     = 1;    // enable PPG00
    }
    
    T00REGL.byte  = (T2%0x0100);    // T2: cycle
    T00REGH.byte  = (T2/0x0100);    // T2: cycle
    T00PWML.byte  = (T1%0x0100);    // T1: ռ�ձ�
    T00PWMH.byte  = (T1/0x0100);    // T1: ռ�ձ�
    
    T001CR.bit.b0 = 1;         //start PPG00
}


void PPG00_adj(uint T1, uint T2)
{
    //----------------------------------------//
    //    ...... ��� 0% �趨 ................
    //----------------------------------------//
    if( T1 == 0 )
    {
        P7DR.bit.b0     = 0;    // PPG00 = 0
        P7FC.bit.b0     = 0;    // disable PPG00
        return;
    }
    //----------------------------------------//
    //    ...... ��� 100% �趨 ..............
    //----------------------------------------//
    else if( T1 == T2 )
    {
        P7DR.bit.b0     = 1;    // PPG00 = 1
        P7FC.bit.b0     = 0;    // disable PPG00
        return;
    }
    //----------------------------------------//
    else
    {
        P7FC.bit.b0     = 1;    // enable PPG00
    }
    
    //    T00REGL.byte  = (T2%0x0100);    // T2: cycle
    //    T00REGH.byte  = (T2/0x0100);    // T2: cycle
    T00PWML.byte  = (T1%0x0100);    // T1: ռ�ձ�
    T00PWMH.byte  = (T1/0x0100);    // T1: ռ�ձ�
}

void ExtINT_INIT(void)
{
    __asm("DI");
    d_ExtINT_02_Rising;
    //.........|...| (Rising/Falling/Both/High)
    //.........| 02/03/04: INT2~INT4
    
    d_ExtINT_03_Falling;
    
    d_ExtINT_04_High;
    __asm("EI");
}


void TIMER_TCA0(void)
{
    __asm("DI");
    POFFCR0.bit.b0 = 1;     // TCA0
    ILH.bit.b6 = 1;
    EIRH.bit.b6 = 1;
    __asm("EI");
    TA0CR.byte   = 0xC0; //enable overflow interrupt,TFF=1,no noise canceller,enable auto capture
    TA0MOD.byte  = 0x80; //double buffer,source clk=fcgck/2^10,Timer mode
    
    TA0DRAL.byte = 78;   // 78 * 128us = * 9.984ms
    TA0DRAH.byte = 0x00; //counting register = 0x0201
    TA0CR.bit.b0 = 1;     //start Timer Counter
}
void Ext_INIT(void)
{
    keyPUSH      = 0;
    keySLIP      = 0;
    keySLIP_down = 0;
    keySLIP_up   = 0;
    
    d_ExtINT_02_Rising;
    d_ExtINT_03_Rising;
    d_ExtINT_04_Rising;
}


void key_active_check(void)
{
    
    //  ��������������
    if( keyPUSH >= 30 )
    {
        delay_times(t_1ms, 100);        D1=D2=D3=D4=1;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=0;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=1;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=0;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=1;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=0;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=1;
        delay_times(t_1ms, 100);        D1=D2=D3=D4=0;
        
        Ext_INIT();
    }
    else if( keySLIP >= 1 )
    {
        //  �����������»�
        if( keySLIP_down == 1 )
        {
            delay_times(t_1ms, 200);        D1=1;
            delay_times(t_1ms, 200);        D2=1;
            delay_times(t_1ms, 200);        D3=1;
            delay_times(t_1ms, 200);        D4=1;
            delay_times(t_1ms, 200);        D1=D2=D3=D4=0;
            //key_slip_down = 1;
            Ext_INIT();
        }
        //  �����������ϻ�
        else if( keySLIP_up == 1 )
        {
            delay_times(t_1ms, 200);        D4=1;
            delay_times(t_1ms, 200);        D3=1;
            delay_times(t_1ms, 200);        D2=1;
            delay_times(t_1ms, 200);        D1=1;
            delay_times(t_1ms, 200);        D1=D2=D3=D4=0;
            //    key_slip_up = 1;
            Ext_INIT();
        }
    }
    
    
    
}


void STOP_for_RESET(void)
{
    __asm("NOP");
    Active_STOP;
    __asm("NOP");
    SYSCR2.byte = 0x10;     // system clock reset
    __asm("NOP");
}


void test_IO(void)
{
    while(1)
    {
        WDCDR.byte = 0x4e;                // clear wdt
        if( TCH1 == 0 ) Vout = 0;     else Vout = 1;
        if( TCH2 == 0 ) DIR  = 0;     else DIR  = 1;
        if( TCH3 == 0 ) D2   = 0;    else D2   = 1;
    }
}


void test_UART(void)
{
    rec_done_flag = 0;
    while( rec_done_flag==0) WDCDR.byte = 0x4e;            // clear wdt
    TX_DATA = RX_DATA;
    TD1BUF.byte = TX_DATA;
    delay_times(t_1ms, 1);
}


void test_AD(void)
{
    
    TD1BUF.byte = (ADC_Code_READ>>8) & 0x03;
    delay_times(t_1ms, 999);
    
    TD1BUF.byte = (ADC_Code_READ) & 0xff;
    delay_times(t_1ms, 999);
}


void all_operation_mode_seq(void)
{
    //----------------------------------------//
    //****** Power on ��Ϊ Normal1 mode ******//
    //----------------------------------------//
    
    //    Normal1 entry stop mode ............
    __asm("CPL (_P8DR).1");
    Active_STOP;                    // �˷������� KWI5 ���� STOP mode
    __asm("CPL (_P8DR).1");
    
    //    Normal1 entry IDLE0 mode ............
    __asm("CPL (_P8DR).0");
    INTTBT_Init_OP();                // initial TBT timer setting
    // �˷������� TBT ���� IDLE1/IDLE2/SLEEP1 mode
    Active_IDLE0;                    // TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P8DR).0");
    
    //    Normal1 entry IDLE1 mode ............
    __asm("CPL (_P9DR).1");
    INTTBT_Init_OP();                // initial TBT timer setting
    // �˷������� TBT ���� IDLE1/IDLE2/SLEEP1 mode
    Active_IDLE1;                    // IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P9DR).1");
    
    //----------------------------------------//
    //****** Entry Normal2 mode **************//
    //----------------------------------------//
    //    MQ6812 LIRC һ�ϵ�Ϊ����״̬��
    //    ���Ա��� change to Normal2 mode, ����ϵͳ��ɲ�Ԥ�� reset
    OpMode_Change_to(iNor2);        // ѡ��Ҫ�����Ĺ���ģʽ�� (iNor1/iNor2/iSlow2/iSlow1) ����֮һ
    
    //    Normal2 entry stop mode ............
    __asm("CPL (_P8DR).1");
    Active_STOP;                    // �˷������� KWI5 ���� STOP mode
    __asm("CPL (_P8DR).1");
    
    //    Normal2 entry IDLE2 mode ............
    __asm("CPL (_P9DR).1");
    INTTBT_Init_OP();                // initial TBT timer setting
    // �˷������� TBT ���� IDLE1/IDLE2/SLEEP1 mode
    Active_IDLE2;                    // IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P9DR).1");
    
    //----------------------------------------//
    //****** Entry SLOW2 mode ****************//
    //----------------------------------------//
    OpMode_Change_to(iSlow2);        // ѡ��Ҫ�����Ĺ���ģʽ�� (iNor1/iNor2/iSlow2/iSlow1) ����֮һ
    
    //----------------------------------------//
    //****** Entry SLOW1 mode ****************//
    //----------------------------------------//
    OpMode_Change_to(iSlow1);        // ѡ��Ҫ�����Ĺ���ģʽ�� (iNor1/iNor2/iSlow2/iSlow1) ����֮һ
    
    //    SLOW1 entry stop mode ............
    __asm("CPL (_P8DR).1");
    Active_STOP;                    // �˷������� KWI5 ���� STOP mode
    __asm("CPL (_P8DR).1");
    
    //    SLOW1 entry SLEEP0 mode ............
    __asm("CPL (_P8DR).0");
    INTTBT_Init_OP();                // initial TBT timer setting
    // �˷������� TBT ���� IDLE1/IDLE2/SLEEP1 mode
    Active_SLEEP0;                    // TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P8DR).0");
    
    //    SLOW1 entry SLEEP1 mode ............
    __asm("CPL (_P9DR).1");
    INTTBT_Init_OP();                // initial TBT timer setting
    // �˷������� TBT ���� IDLE1/IDLE2/SLEEP1 mode
    Active_SLEEP1;                    // IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P9DR).1");
    //----------------------------------------//
    //----------------------------------------//
}

