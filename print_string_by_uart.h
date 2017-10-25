//******************************************
//  档案名称： PRINT_STRING_BY_UART
//  版本    ： V...
//  功能    ： PRINT_STRING_BY_UART 头文件
//  备注    ： 使用 UART 采字串方式传送给串口调试助手
//******************************************
#ifndef _PRINT_STRING_BY_UART_H__
#define _PRINT_STRING_BY_UART_H__


#include "stdio.h"

#define MAX_STR_LEN     50              // 定义最大传送字节数
//----------------------
//  备注：1. "\r\n" 占了 3 个字节，
//        2. 若有 ERROR: NOW_STR_LEN[]******* 时，之后芯片内部操作可能是异常的
//           此为传送字串已超过定义之长度，
//           请忽必修改程序后再重新调试，避免分析到错误的资料！
extern char  str_list[MAX_STR_LEN];
extern uchar str_len;



void printf_byUART(void);
void start_trans(void);
void Print_Uart_Receive_Process(void);
void Print_Uart_Sent_Process(void);


#endif








