//******************************************
//  �������ƣ� PRINT_STRING_BY_UART
//  �汾    �� V...
//  ����    �� PRINT_STRING_BY_UART ͷ�ļ�
//  ��ע    �� ʹ�� UART ���ִ���ʽ���͸����ڵ�������
//******************************************
#ifndef _PRINT_STRING_BY_UART_H__
#define _PRINT_STRING_BY_UART_H__


#include "stdio.h"

#define MAX_STR_LEN     50              // ����������ֽ���
//----------------------
//  ��ע��1. "\r\n" ռ�� 3 ���ֽڣ�
//        2. ���� ERROR: NOW_STR_LEN[]******* ʱ��֮��оƬ�ڲ������������쳣��
//           ��Ϊ�����ִ��ѳ�������֮���ȣ�
//           ������޸ĳ���������µ��ԣ������������������ϣ�
extern char  str_list[MAX_STR_LEN];
extern uchar str_len;



void printf_byUART(void);
void start_trans(void);
void Print_Uart_Receive_Process(void);
void Print_Uart_Sent_Process(void);


#endif








