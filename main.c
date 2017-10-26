//******************************************
//           This is a C Template file
//作者：
//日期
//功能
//备注
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
//    MQ6812/MQ6821 使用SWITCH 指令注意事项
//----------------------------------------//
//    因MQ6812/MQ6821系列产品的16KB flash与其它系列产品不同，在电路设计上对时序(timing)的要求较高，
//    指令 ”JP gg(注1)” 在极端条件下可能有机率会出现下一脚本无法正确读取之状况。为避免此情况发生，
//    必须依照以下「三、建议修改SWITCH指令的方式」的说明来进行程序的撰写。
//
//    注1: 其中gg 为16位通用缓存器WA, BC, DE, HL, IX, IY等, 详细指令说明请参考TLCS-870/C1 Series Instruction Set的66页)。
//
//    需要增加此指令修改的产品:
//    (1)    MQ6812系列产品，包含产品型号为MQ6812SP028HAER(SOP28封装)、MQ6812SS028HAER(SSOP28封装)、MQ6812LQ032HAER(LQFP32封装)、MQ6812N4032HAER(QFN32封装)。
//    (2)    MQ6821系列产品，包含产品型号为MQ6821SP020HAER(SOP20封装)、MQ6821SS020HAER(SSOP20封装)、MQ6821DP020HAER(DIP20封装)。
//
//
//    MQ6812/MQ6821系列产品的SWITCH指令与第一个CASE之间必须插入一个NOP指令。请参阅如下范例：
//    \\-->>        switch(variable)
//    \\-->>        {
//    \\-->>            __asm("NOP");                // switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
//    \\-->>            case 0:
//    \\-->>                // Add your code here ......
//    \\-->>                break;
//  \\-->>
//    \\-->>            default:
//    \\-->>                // Add your code here ......
//    \\-->>                break;
//    \\-->>        }
//    修改后, 使用MQ-Link编译时将出现警告 I87C1-Warning-538, 此为正常现象, 请忽略此信息。
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
//    请由 <OPmode.h> 里设置外部晶振 (高速 or 低速), 并请参考以下说明：
//    外部晶振脚 HXTAL/LXTAL 使用相同 IO(P00/P01), 只能择一开启.
//.....................................................................................
//#undef    XTAL_High        // 定义外部高速晶振: #define(使用晶振) / #undef(不用晶振) :
//#undef    XTAL_Low        // 定义外部低速晶振: #define(使用晶振) / #undef(不用晶振) :
//            |........................................................................................
//            |---------> // 注意事项:
//            |---------> // 1. Enable LXtal: 需设定 FSCTRL.bit.b0 = 1; --> FSCTRL请使用单位元(bit operation)
//            |---------> // 2. 启动低速外部晶振需在烧录时, 搭配勾选 ext low OSC:
//            |---------> //    IDE烧录        : Project -> Pin Setting -> 勾选 ext low OSC
//            |---------> //    Writer烧录    : 点选Type -> 在IC type选项同一页面右方 -> 勾选 ext low OSC
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
    
    
    
    SYSTEM_INIT();        // IO, CGCR 初始化，及 P10/P40/P41 在仿真时之设定
    KWI_INIT();         // 停止模式唤醒脚初始化
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
// 函数名    : SYSTEM_INIT(void)
// 函数功能    : IO, CGCR 初始化，及 P10/P40/P41 在仿真时之设定
// 备注        :
//*********************************************************************
void SYSTEM_INIT(void)
{
#ifdef _DEBUG    //...  _DEBUG(仿真模式下): 用于仿真 ev board
    //------------------------------------------------------------------
    //    (系统默认): 仿真时将P10设定为Reset Pin，以避免影响仿真及烧录功能.
    //    SYSCR3.byte   = 0x00;    // SYSCR3.bit.b0=1: 将P10设定为一般IO口, SYSCR3.bit.b0=0(预设值): P10为 Reset Pin
    //    SYSCR4.byte   = 0xB2;    // 0xB2: 启动 SYSCR3.bit.b0 之设定值
    //------------------------------------------------------------------
    FSCTRL.bit.b0 = 0;        // 0为默认值，程序若有变更此位(bit)，在仿真模式下需手动初始化清为默认值 0
    //------------------------------------------------------------------
#else            //...  于一般上电跑程序(非仿真模式下)，将 P10(RESET) 脚位设置为一般 IO 口
    //------------------------------------------------------------------
    //-- 将P10设定为一般IO口 ------
    //SYSCR3.byte = 0x01;        // SYSCR3.bit.b0=1: 将P10设定为一般IO口, SYSCR3.bit.b0=0(预设值): P10为 Reset Pin
    //SYSCR4.byte = 0xB2;        // 0xB2: 启动 SYSCR3.bit.b0 之设定值
    //------------------------------------------------------------------
#endif
    
    
    
    //-- 初始化 IO 口 (仿真脚位设置)------
#ifdef _DEBUG    //...  _DEBUG: 用于仿真 ev board
    //------------------------------------------------------------------
    //    仿真采用 P10/P40/P41 进 Debug mode，在仿真时将其设定为输入，
    //    以避免影响仿真及烧录功能.
    P1DR.byte = 0x00;
    P1CR.byte = set8bit(11111110);        // 设置 P10 为输入
    P4DR.byte = 0x00;
    P4CR.byte = set8bit(01111100);        // 设置 P40/P41 为输入
    //------------------------------------------------------------------
#else            //...  于一般上电跑程序(非仿真模式下)
    //------------------------------------------------------------------
    P1DR.byte = 0x00;
    P1CR.byte = 0xff;
    P4DR.byte = 0x00;
    P4CR.byte = set8bit(01111111);
    //------------------------------------------------------------------
#endif
    
    //-- 初始化 IO 口 ------
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
    //    look_data(IRSTSR.byte);        // IRSTSR: 内部因素复位检测状态寄存器
    WDCDR.byte = 0x4e;            // clear wdt
    
    
    //    ============================================
    //    高速晶振除频设置：CGCR                    ;  fc = 16MHz
    //    ============================================
    //    CGCR.byte = 0x00;            // ==> fcgck = fc/4 =  4Mhz(系统默认)
    CGCR.byte = 0x01;            // ==> fcgck = fc/2 =  8Mhz
    //    CGCR.byte = 0x02;            // ==> fcgck = fc   = 16Mhz
    //    CGCR.byte = 0x03;            // ==> fcgck = fc/8 =  2Mhz
    //    ============================================
    //    *** 请不要在低速模式(SLOW1/SLOW2) 改变 CGCR<FCGCKSEL> 寄存器的值
    //    ============================================
    
    
    //--------------------------------------------------------------------------------------------------//
    //    请由 <OPmode.h> 里设置外部晶振 (高速 or 低速), 并请参考以下说明：
    //    外部晶振脚 HXTAL/LXTAL 使用相同 IO(P00/P01), 只能择一开启.
    //.....................................................................................
    //#undef    XTAL_High        // 定义外部高速晶振: #define(使用晶振) / #undef(不用晶振) :
    //#undef    XTAL_Low        // 定义外部低速晶振: #define(使用晶振) / #undef(不用晶振) :
    //            |........................................................................................
    //            |---------> // 注意事项:
    //            |---------> // 1. Enable LXtal: 需设定 FSCTRL.bit.b0 = 1; --> FSCTRL请使用单位元(bit operation)
    //            |---------> // 2. 启动低速外部晶振需在烧录时, 搭配勾选 ext low OSC:
    //            |---------> //    IDE烧录        : Project -> Pin Setting -> 勾选 ext low OSC
    //            |---------> //    Writer烧录    : 点选Type -> 在IC type选项同一页面右方 -> 勾选 ext low OSC
    //            .........................................................................................
    //--------------------------------------------------------------------------------------------------//
    //    呼叫函数以选择是否切换外部高速晶振
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
    P9CR.bit.b0 = 0x0;  // 设定P90输入
    P9CR.bit.b1 = 0x1;    // 设定P91输出
    P9FC.bit.b1 = 0x1;  // 切换P91为特殊功能脚
    UATCNG.bit.b1 = 1;  // 設定 P91為TX輸出, P90為RX輸入
    
    //=========================
    __asm("DI");
    POFFCR1.bit.b1 = 1;     // UART1EN
    
    ILE.bit.b7   = 0;
    ILE.bit.b6   = 0;
    EIRE.bit.b7  = 1;       // INTTXD1
    EIRE.bit.b6  = 1;       // INTRXD1
    __asm("EI");
    
    //------ Baud rate = 9600 @ 8MHz
    UART1CR2.byte = 0x20;    //RTSEL 100  17个时钟，RXDNC 00: 无噪声抑止  STOPBR 接收端结束位长度0: 1位
    UART1DR.byte  = 48;        //baud rate = 9600
    //------ Baud rate = 9600 @ 4MHz
    //    UART1CR2.byte = 0x20;    //RTSEL 100  17个时钟，RXDNC 00: 无噪声抑止  STOPBR 接收端结束位长度0: 1位
    //    UART1DR.byte  = 24;        //baud rate = 9600
    
    UART1CR1.byte = 0xc0;
}
//*********************************************************************
// 函数名   :
// 函数功能 :
// 备注     :
//*********************************************************************
void UART_INIT_P26P27(void)
{
    //=========================
    P2CR.bit.b6 = 0;        // 设定P26输入
    P2CR.bit.b7 = 1;        // 设定P27输出
    P2FC.bit.b7 = 1;        // 切换P27为特殊功能脚
    UATCNG.bit.b2 = 1;      // 1: 設定 P26 P27 為串口功能腳
    UATCNG.bit.b1 = 1;      // 1: 設定 P27為TX輸出, P26為RX輸入
    
    //=========================
    __asm("DI");
    POFFCR1.bit.b1 = 1;     // UART1EN
    
    ILE.bit.b7   = 0;
    ILE.bit.b6   = 0;
    EIRE.bit.b7  = 1;       // INTTXD1
    EIRE.bit.b6  = 1;       // INTRXD1
    __asm("EI");
    
    //------ Baud rate = 38400 @ 8MHz
    //     UART1CR2.byte = 0x00;    //RTSEL 100  17个时钟，RXDNC 00: 无噪声抑止  STOPBR 接收端结束位长度0: 1位
    //     UART1DR.byte  = 12;        //baud rate = 38400
    //------ Baud rate = 9600 @ 8MHz
    UART1CR2.byte = 0x20;    //RTSEL 100  17个时钟，RXDNC 00: 无噪声抑止  STOPBR 接收端结束位长度0: 1位
    UART1DR.byte  = 48;        //baud rate = 9600
    //------ Baud rate = 9600 @ 4MHz
    //    UART1CR2.byte = 0x20;    //RTSEL 100  17个时钟，RXDNC 00: 无噪声抑止  STOPBR 接收端结束位长度0: 1位
    //    UART1DR.byte  = 24;        //baud rate = 9600
    
    UART1CR1.byte = 0xc0;
}
//*********************************************************************
// 函数名   :
// 函数功能 :
// 备注     : 0: 选择 P90 P91 为 UART 串口功能脚
//            1: 选择 P26 P27 为 UART 串口功能脚
//*********************************************************************
void UART_Pin_Function_CHG(uchar sel_pin)
{
    
    while( UART1SR.bit.b1 == 1 ) WDCDR.byte = 0x4e;     // 确认 UART 传送状态是否已完成再切换 UART 功能脚
    
    if( sel_pin == 0 )
    {
        //=========================
        P9CR.bit.b0 = 0;                // 设定P90输入
        P9CR.bit.b1 = 1;                // 设定P91输出
        P9FC.bit.b1 = 1;                // 切换P91为特殊功能脚
        UATCNG.bit.b2 = 0;              // 0: 設定 P90 P91 為串口功能腳
        UATCNG.bit.b1 = 1;              // 1: 設定 P91為TX輸出, P90為RX輸入
    }
    else
    {
        
        //=========================
        P2CR.bit.b6 = 0;                // 设定P26输入
        P2CR.bit.b7 = 1;                // 设定P27输出
        P2FC.bit.b7 = 1;                // 切换P27为特殊功能脚
        UATCNG.bit.b2 = 1;              // 設定 P26 P27 為串口功能腳
        UATCNG.bit.b1 = 1;              // 設定 P27為TX輸出, P26為RX輸入
    }
}


void ADC_IO_INIT(void)
{
    //    本笵例采用 AIN5(P45) AIN6(P46)为 ADC 采样输入端
    P4FC.bit.b5 = 1;
    P4CR.bit.b5 = 0;
    P4FC.bit.b6 = 1;
    P4CR.bit.b6 = 0;
    
    //-----------------------------------
    //    执行一次，取得内部Vref 2V之实际值
    //    MQ6812:读取值为 ( 内部Vref 2V之实际值 * 1024 ), 单位为mV
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
    //開啟TC00 TC01 CLK SOURCE
    //    ILH.bit.b4 =0;
    //    EIRH.bit.b4=1;             //[-,INTTCA0,INTTC01,INTTC00    INTRTC,INTADC,INTLVD,-]
    //開啟INTTC00
    __asm("EI");
    T00MOD.byte=0xC3;        //[TFF0,DBE0,TCK0[3],-,TCM0]
    //<DBE0>=1,<TCK0>=’111’,<TCM0>=10 10位PWM模式
    
    //----------------------------------------//
    //    ...... 输出 0% 设定 ................
    //----------------------------------------//
    if( T1 == 0 )
    {
        P7DR.bit.b0     = 0;    // PPG00 = 0
        P7FC.bit.b0     = 0;    // disable PPG00
    }
    //----------------------------------------//
    //    ...... 输出 100% 设定 ..............
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
    T00PWML.byte  = (T1%0x0100);    // T1: 占空比
    T00PWMH.byte  = (T1/0x0100);    // T1: 占空比
    
    T001CR.bit.b0 = 1;         //start PPG00
}


void PPG00_adj(uint T1, uint T2)
{
    //----------------------------------------//
    //    ...... 输出 0% 设定 ................
    //----------------------------------------//
    if( T1 == 0 )
    {
        P7DR.bit.b0     = 0;    // PPG00 = 0
        P7FC.bit.b0     = 0;    // disable PPG00
        return;
    }
    //----------------------------------------//
    //    ...... 输出 100% 设定 ..............
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
    T00PWML.byte  = (T1%0x0100);    // T1: 占空比
    T00PWMH.byte  = (T1/0x0100);    // T1: 占空比
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
    
    //  触摸按键：按下
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
        //  触摸按键：下滑
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
        //  触摸按键：上滑
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
    //****** Power on 后为 Normal1 mode ******//
    //----------------------------------------//
    
    //    Normal1 entry stop mode ............
    __asm("CPL (_P8DR).1");
    Active_STOP;                    // 此范例采用 KWI5 唤醒 STOP mode
    __asm("CPL (_P8DR).1");
    
    //    Normal1 entry IDLE0 mode ............
    __asm("CPL (_P8DR).0");
    INTTBT_Init_OP();                // initial TBT timer setting
    // 此范例采用 TBT 唤醒 IDLE1/IDLE2/SLEEP1 mode
    Active_IDLE0;                    // TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P8DR).0");
    
    //    Normal1 entry IDLE1 mode ............
    __asm("CPL (_P9DR).1");
    INTTBT_Init_OP();                // initial TBT timer setting
    // 此范例采用 TBT 唤醒 IDLE1/IDLE2/SLEEP1 mode
    Active_IDLE1;                    // IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P9DR).1");
    
    //----------------------------------------//
    //****** Entry Normal2 mode **************//
    //----------------------------------------//
    //    MQ6812 LIRC 一上电为启动状态，
    //    但仍必需 change to Normal2 mode, 避免系统造成不预期 reset
    OpMode_Change_to(iNor2);        // 选择要操作的工作模式至 (iNor1/iNor2/iSlow2/iSlow1) 其中之一
    
    //    Normal2 entry stop mode ............
    __asm("CPL (_P8DR).1");
    Active_STOP;                    // 此范例采用 KWI5 唤醒 STOP mode
    __asm("CPL (_P8DR).1");
    
    //    Normal2 entry IDLE2 mode ............
    __asm("CPL (_P9DR).1");
    INTTBT_Init_OP();                // initial TBT timer setting
    // 此范例采用 TBT 唤醒 IDLE1/IDLE2/SLEEP1 mode
    Active_IDLE2;                    // IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P9DR).1");
    
    //----------------------------------------//
    //****** Entry SLOW2 mode ****************//
    //----------------------------------------//
    OpMode_Change_to(iSlow2);        // 选择要操作的工作模式至 (iNor1/iNor2/iSlow2/iSlow1) 其中之一
    
    //----------------------------------------//
    //****** Entry SLOW1 mode ****************//
    //----------------------------------------//
    OpMode_Change_to(iSlow1);        // 选择要操作的工作模式至 (iNor1/iNor2/iSlow2/iSlow1) 其中之一
    
    //    SLOW1 entry stop mode ............
    __asm("CPL (_P8DR).1");
    Active_STOP;                    // 此范例采用 KWI5 唤醒 STOP mode
    __asm("CPL (_P8DR).1");
    
    //    SLOW1 entry SLEEP0 mode ............
    __asm("CPL (_P8DR).0");
    INTTBT_Init_OP();                // initial TBT timer setting
    // 此范例采用 TBT 唤醒 IDLE1/IDLE2/SLEEP1 mode
    Active_SLEEP0;                    // TGHALT: (Normal1->IDLE0) / (SLOW1->SLEEP0) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P8DR).0");
    
    //    SLOW1 entry SLEEP1 mode ............
    __asm("CPL (_P9DR).1");
    INTTBT_Init_OP();                // initial TBT timer setting
    // 此范例采用 TBT 唤醒 IDLE1/IDLE2/SLEEP1 mode
    Active_SLEEP1;                    // IDLE: (Normal1->IDLE1) / (Normal2->IDLE2) / (SLOW1->SLEEP1) mode
    Disable_INTTBT_OP();            // clear INTTBT setting after release IDLE0/SLEEP0 mode
    __asm("CPL (_P9DR).1");
    //----------------------------------------//
    //----------------------------------------//
}

