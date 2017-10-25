//******************************************
//  �������ƣ� PRINT_STRING_BY_UART
//  �汾    �� V...
//  ����    �� PRINT_STRING_BY_UART ʹ�ú���
//  ��ע    �� ʹ�� UART ���ִ���ʽ���͸����ڵ�������
//******************************************

#include "MQ6812.h"
#include "iApp.h"
#include "print_string_by_uart.h"
#include "uart_data.h"


// ���ճ���ʹ��֮ UART ����ѡ�������£�
//----------------------
//#define TX_Data_Buf     TD0BUF.byte     // ����ʹ��оƬ�� 0 �� UART ֮ TD0BUF
#define TX_Data_Buf     TD1BUF.byte     // ����ʹ��оƬ�� 1 �� UART ֮ TD1BUF
//#define TX_Data_Buf     TD2BUF.byte     // ����ʹ��оƬ�� 2 �� UART ֮ TD2BUF
//----------------------

//----------------------
//  ��ע��1. "\r\n" ռ�� 3 ���ֽڣ�
//        2. ���� ERROR: NOW_STR_LEN[]******* ʱ��֮��оƬ�ڲ������������쳣��
//           ��Ϊ�����ִ��ѳ�������֮���ȣ�
//           ������޸ĳ���������µ��ԣ������������������ϣ�
char  str_list[MAX_STR_LEN];
uchar str_len;
//----------------------
extern SENT_EVT sent_evt ;
extern REC_EVT 	rec_evt  ;

//*********************************************************************
// ������   :
// �������� :
// ��ע     :
//*********************************************************************
void printf_byUART(void)
{
//	�ִ��������� ......
//  ��ע��1. "\r\n" ռ�� 3 ���ֽڣ�
//        2. ���� ERROR: NOW_STR_LEN[]******* ʱ��֮��оƬ�ڲ������������쳣��
//           ��Ϊ�����ִ��ѳ�������֮���ȣ�
//           ������޸ĳ���������µ��ԣ������������������ϣ�

//  ������ MAX_STR_LEN������ ERROR: > MAX_STR_LEN
    str_len = strlen(str_list);
    if( str_len >= MAX_STR_LEN )
    {
        sprintf(str_list, "\r\n");
        sprintf(str_list, "ERROR: NOW_STR_LEN[%d] > MAX_STR_LEN[%d]\r\n", str_len, MAX_STR_LEN);
        str_len = strlen(str_list);

    }
    start_trans();

}

//  ��������ֱ���� UART ���ڲ�����ֱ�ӵ������£�
//  { sprintf(str_list, "************************\r\n");  printf_byUART(); }
//  { sprintf(str_list, "123 abc ABC\r\n");               printf_byUART(); }
//  { sprintf(str_list, "temp = %d:\r\n", temp);          printf_byUART(); }
//  { sprintf(str_list, "num = %d:\r\n", 555);            printf_byUART(); }
//  { sprintf(str_list, "char = %s:\r\n", "string");      printf_byUART(); }
            

//*********************************************************************
// ������   :
// �������� :
// ��ע     :
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
		__asm("NOP");				// switch ���һ�� case ֮������һ�� "NOP"���������� "JP gg" ָ�
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
			__asm("NOP");				// switch ���һ�� case ֮������һ�� "NOP"���������� "JP gg" ָ�
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

































