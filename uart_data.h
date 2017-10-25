//******************************************
//           This is a c File Head
//作者：   
//日期     
//功能
//备注
//******************************************   

#ifndef __UART_DATA_H_
#define __UART_DATA_H_

typedef enum
{
	UART_TX_IDLE = 0,
	UART_SENDING_DATA,
	UART_WAITING_OK1,
	UART_REC_OK1, 
	UART_SENDING_OK2,
	UART_SENT_SUCCESS,
	UART_REC_ERR,
	UART_SENT_TIME_OUT,
	UART_SENT_FAIL
}SENT_EVT_STA;

typedef struct
{
	SENT_EVT_STA			sent_process;
	uchar 						rpt_sent_times;
	uchar 						wait_ok1_time_set;
	uchar 						wait_ok1_time_cnt;
}SENT_EVT;




typedef enum 
{
	UART_RX_IDLE = 0,
	UART_REC_PACKAGE,
	UART_ODD_PARITY,
	UART_SENDING_OK1,
	UART_SENDING_ERR,
	UART_WAITING_OK2,
	UART_WAITING_OK2_TIME_OUT,
	UART_REC_OK2,
	UART_REC_SUCCESS,
	UART_REC_FAIL
}REC_EVT_STA ;
typedef struct
{
	REC_EVT_STA	        rec_process;
	uchar 						rpt_rec_times;	
	uchar 						wait_ok2_time_set;
	uchar 						wait_ok2_time_cnt;
}REC_EVT;

//*************************************** UART DATA PROCESS ********************************************************//

void Tx_Send_Data(uchar data_type);
void Rx_Rcv_Data(void);
void Check_Rx_Data_Type(void);


//*************************************** RECEIVE PROCESS ************************************************************//

void Uart_Sent_Manager(void);

uchar  Uart_Wait_Ok1_Handler(void);

void Uart_Send_Ok2_Handler(void);

//*************************************** RECEIVE PROCESS ************************************************************//
void Uart_Receive_Manager(void);

void Uart_Odd_Parity_Handler(void);

void Uart_Send_Ok1_Handler(void);

void Uart_Send_Error_Handler(void);

void Uart_Waiting_Ok2_Handler(void);




#endif

