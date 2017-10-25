//******************************************
//  档案名称： PRINT_STRING_BY_UART
//  版本    ： V...
//  功能    ： PRINT_STRING_BY_UART 使用函数
//  备注    ： 使用 UART 采字串方式传送给串口调试助手
//******************************************

#include "MQ6812.h"
#include "iApp.h"
#include "print_string_by_uart.h"
#include "uart_data.h"


// 依照程序使用之 UART 组数选择定义如下：
//----------------------
//#define TX_Data_Buf     TD0BUF.byte     // 定义使用芯片第 0 组 UART 之 TD0BUF
#define TX_Data_Buf     TD1BUF.byte     // 定义使用芯片第 1 组 UART 之 TD1BUF
//#define TX_Data_Buf     TD2BUF.byte     // 定义使用芯片第 2 组 UART 之 TD2BUF
//----------------------

//----------------------
//  备注：1. "\r\n" 占了 3 个字节，
//        2. 若有 ERROR: NOW_STR_LEN[]******* 时，之后芯片内部操作可能是异常的
//           此为传送字串已超过定义之长度，
//           请忽必修改程序后再重新调试，避免分析到错误的资料！
char  str_list[MAX_STR_LEN];
uchar str_len;
//----------------------
extern SENT_EVT sent_evt ;
extern REC_EVT 	rec_evt  ;

//*********************************************************************
// 函数名   :
// 函数功能 :
// 备注     :
//*********************************************************************
void printf_byUART(void)
{
//	字串最大数检查 ......
//  备注：1. "\r\n" 占了 3 个字节，
//        2. 若有 ERROR: NOW_STR_LEN[]******* 时，之后芯片内部操作可能是异常的
//           此为传送字串已超过定义之长度，
//           请忽必修改程序后再重新调试，避免分析到错误的资料！

//  若大于 MAX_STR_LEN，则传送 ERROR: > MAX_STR_LEN
    str_len = strlen(str_list);
    if( str_len >= MAX_STR_LEN )
    {
        sprintf(str_list, "\r\n");
        sprintf(str_list, "ERROR: NOW_STR_LEN[%d] > MAX_STR_LEN[%d]\r\n", str_len, MAX_STR_LEN);
        str_len = strlen(str_list);

    }
    start_trans();

}

//  主程序里直定好 UART 串口参数后，直接调用如下：
//  { sprintf(str_list, "************************\r\n");  printf_byUART(); }
//  { sprintf(str_list, "123 abc ABC\r\n");               printf_byUART(); }
//  { sprintf(str_list, "temp = %d:\r\n", temp);          printf_byUART(); }
//  { sprintf(str_list, "num = %d:\r\n", 555);            printf_byUART(); }
//  { sprintf(str_list, "char = %s:\r\n", "string");      printf_byUART(); }
            

//*********************************************************************
// 函数名   :
// 函数功能 :
// 备注     :
//*********************************************************************
void start_trans(void)
{
    uchar iloop=0;

    while( iloop < str_len )
    {
        TX_Data_Buf = str_list[iloop];
        while( UART1SR.bit.b0 )
        {
            WDCDR.byte = 0x4e;			// clear wdt
        }
        iloop++;
    }

}

void Print_Uart_Sent_Process(void)
{
	switch (sent_evt.sent_process)
	{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
		case UART_TX_IDLE : 
											sprintf(str_list, "UART_TX_IDLE\r\n");  
											break;
											
		case UART_SENDING_DATA:
											sprintf(str_list, "UART_SENDING_DATA\r\n");  
											break;
		
		case UART_WAITING_OK1:
											sprintf(str_list, "UART_WAITING_OK1\r\n");  
											break;
		
		case UART_REC_OK1:
											sprintf(str_list, "UART_REC_OK1\r\n");  
											break;
											
		case UART_SENT_SUCCESS:
											sprintf(str_list, "UART_SENT_SUCCESS\r\n");  
											break;
											
		case UART_SENT_TIME_OUT:
											sprintf(str_list, "UART_SENT_TIME_OUT\r\n");  
											break;
											
		case UART_SENT_FAIL:
											sprintf(str_list, "UART_SENT_FAIL\r\n");  
											break;
											
		case UART_REC_ERR:
											sprintf(str_list, "UART_REC_ERR\r\n");  
											break;
	}
	printf_byUART();
}
void Print_Uart_Receive_Process(void)
{
		switch(rec_evt.rec_process)
	{
			__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
		case UART_RX_IDLE: 
											sprintf(str_list, "UART_RX_IDLE\r\n");  
											break;
		case UART_REC_PACKAGE:
											sprintf(str_list, "UART_REC_PACKAGE\r\n");        
											break;
		case UART_ODD_PARITY:
											sprintf(str_list, "UART_ODD_PARITY\r\n");        
											break;
		case UART_SENDING_OK1:
											sprintf(str_list, "UART_SENDING_OK1\r\n");        
											break;
		case UART_SENDING_ERR:
											sprintf(str_list, "UART_SENDING_ERR\r\n");        
											break;
		case UART_WAITING_OK2:
						 					sprintf(str_list, "UART_WAITING_OK2\r\n");        
											break;
		case UART_REC_OK2:
											sprintf(str_list, "UART_REC_OK2\r\n");        
											break;
		case UART_REC_SUCCESS:
											sprintf(str_list, "UART_REC_SUCCESS\r\n");        

	}
	printf_byUART();
}

































