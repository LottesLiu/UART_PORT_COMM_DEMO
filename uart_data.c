//******************************************
//           This is a C Template file
//作者：   
//日期     
//功能
//备注
//******************************************   

#include "MQ6812.h"
#include "iApp.h"
#include "uart_data.h"
#include "print_string_by_uart.h"

extern uchar rx_data[];
static uchar tx_data[10] = 	{0xAA, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xED};
static uchar ok2_data[10] =  {0xAA, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xED};
static uchar ok1_data[10] =  {0xAA, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xED};
static uchar err_data[10] = 	 {0xAA, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xED};





uchar rec_done_flag, rec_start, rec_cnt, uart_flag;
uchar TX_DATA,RX_DATA;
uchar rx_data_type = 100;


SENT_EVT sent_evt ;
REC_EVT 	rec_evt  ;
uchar ok1_time_cnt;
uchar ok2_time_cnt;

extern char cnt2_10ms;

void Tx_Send_Data( uchar data_type )
{
	uchar i;
	if( data_type == 0 )
	{
		for ( i=0; i<10; i++ )
		{
			TD1BUF.byte = *( tx_data+i );
			while( UART1SR.bit.b0 )
				{
					WDCDR.byte = 0x4e;			// clear wdt
				}
		}
	}
	else if( data_type == 1 )
	{
		for( i=0; i<10; i++ )
		{
			TD1BUF.byte = *( ok1_data+i );
			 while( UART1SR.bit.b0 )
				{
					WDCDR.byte = 0x4e;			// clear wdt
				}
		}

	}
	else if( data_type == 2 )
	{
		for ( i=0; i<10; i++ )
		{
			TD1BUF.byte = *( ok2_data+i );
			 while( UART1SR.bit.b0 )
				{
					WDCDR.byte = 0x4e;			// clear wdt
				}
		}

	}
	else if( data_type == 3 )
	{
		for ( i=0; i<10; i++ )
		{
			TD1BUF.byte = *( err_data+i );
				while( UART1SR.bit.b0 )
				{
					WDCDR.byte = 0x4e;			// clear wdt
				}
		}

	}

}
void Rx_Rcv_Data( void )
{
	uchar time_out_cnt = 0;
	uchar time_out_flag = 0;
	uchar i=0;
	if( rec_start == 0xaa )                  // uart port start receiving package 
	{
		while(1)
		{
			while( rec_done_flag==0 ) // in the process of receiving package 
			{
				// !!!! maybe needs to change it to 1ms interrupt !!!!
				if( cnt1_10ms==1 )
				{
					cnt1_10ms = 0;
					time_out_cnt++;
					if( time_out_cnt > 1 )
					{
						time_out_cnt=0;
						time_out_flag=1;
					}
				}
				if( time_out_flag==1 )
				{
					rec_done_flag=1;
					return;                               // time out during receiving 
				}
				WDCDR.byte = 0x4e;
			}

			if( rec_done_flag == 1 && time_out_flag ==0 )   // finish receiving the package
			{
				Check_Rx_Data_Type();       // checking package type
				break;
			}
		}
	}
}
void Check_Rx_Data_Type( void )
{
	char i;

	if( rx_data[1] == rx_data[2] && rx_data[1] == rx_data[3] )
	{
		if( rx_data[1] == 0x11 )
			rx_data_type = 1;
		else if( rx_data[1] == 0x22 )
			rx_data_type = 2;
		else if( rx_data[1] == 0xEE )
			rx_data_type = 3;
	}
	else
		rx_data_type = 0;               // package 
}
void Uart_Sent_Manager( void )
{
	uchar res;
	switch ( sent_evt.sent_process )
	{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
		case UART_TX_IDLE : 
		
											if( sent_evt.rpt_sent_times != 0 )
												sent_evt.rpt_sent_times = 0;
											if( sent_evt.wait_ok1_time_set != 0 )
												sent_evt.wait_ok1_time_set = 0;
											if( sent_evt.wait_ok1_time_cnt != 0 )
												sent_evt.wait_ok1_time_cnt = 0;
											break;
											
		case UART_SENDING_DATA:
		
											Tx_Send_Data( 0 );
											sent_evt.sent_process = UART_WAITING_OK1;
											break;
		
		case UART_WAITING_OK1:

											res = Uart_Wait_Ok1_Handler();
											if( res == 0 )
											sent_evt.sent_process = UART_REC_ERR;
											else if( res == 1 )
											sent_evt.sent_process = UART_REC_OK1;
											break;
		
		case UART_REC_OK1:
											
											Uart_Send_Ok2_Handler();
											sent_evt.sent_process = UART_SENT_SUCCESS;
											break;
											
		case UART_SENT_SUCCESS:
											
											//package_signed_flag = 1;
											sent_evt.sent_process = UART_TX_IDLE;
											break;
											
		case UART_SENT_TIME_OUT:
											
											//package_signed_flag = 2;
											sent_evt.sent_process = UART_TX_IDLE;
											break;
											
		case UART_SENT_FAIL:
											
											//package_signed_flag = 3;
											sent_evt.sent_process = UART_TX_IDLE;
											break;
											
		case UART_REC_ERR:
											
											sent_evt.rpt_sent_times ++;
											if( sent_evt.rpt_sent_times < 3 )
											sent_evt.sent_process = UART_SENDING_DATA;
											else
											sent_evt.sent_process = UART_SENT_FAIL;
		}

}

uchar  Uart_Wait_Ok1_Handler(void)
{
	uchar i,	res;
	while( ! (rec_done_flag == 1 && (rx_data_type == 1 || rx_data_type == 3) ) )
	{ 
		WDCDR.byte = 0x4e;				// clear wdt
		
		Rx_Rcv_Data();
		
		if( cnt2_10ms >= 1 )
		{
			cnt2_10ms=0;
			ok1_time_cnt++;
			if( ok1_time_cnt > 2 )
			{
				ok1_time_cnt=0;
				ok1_expiry_flag = 1;
				return 0 ;
			}
		}
	}
	//------receive sth-----------//
	if( rec_done_flag == 1 && (rx_data_type == 1 || rx_data_type == 3) )   // OK1 OR ERROR
	{
		flag_rec_msg = 0;
		rx_data_type = 100;
   		for( i=1; i<9; i++ )
		{
			if( rx_data[i] == ok1_data[i] )
				res = 1;
			else
				res = 0;                                 // not ok1 comfirm package                         			
		}
	}

	
}
void Uart_Send_Ok2_Handler(void)
{
	Tx_Send_Data(2);
}
//*************************************** RECEIVE PROCESS ************************************************************//
void Uart_Receive_Manager(void)
{
	switch(rec_evt.rec_process)
	{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
		case UART_RX_IDLE: 
											
											if( rec_evt.wait_ok2_time_set != 0 )
											rec_evt.wait_ok2_time_set = 0; 
											if( rec_evt.wait_ok2_time_cnt != 0 )
											rec_evt.wait_ok2_time_cnt = 0;
											if( rec_done_flag==1 && rx_data_type==0 )      // package type is data package 
											{
												flag_rec_msg=0;
												rx_data_type= 100;
												rec_evt.rec_process = UART_REC_PACKAGE;
											}
											break;
											
		case UART_REC_PACKAGE:
											
											rec_evt.rec_process = UART_ODD_PARITY;
											break;
											
		case UART_ODD_PARITY:
											
											Uart_Odd_Parity_Handler();
											break;
											
		case UART_SENDING_OK1:
											
											Uart_Send_Ok1_Handler();
											rec_evt.rec_process = UART_WAITING_OK2;
											break;
		
		case UART_SENDING_ERR:
											
											Uart_Send_Error_Handler();
											rec_evt.rec_process = UART_RX_IDLE;
											break;
			
		case UART_WAITING_OK2:
											
											Uart_Waiting_Ok2_Handler();
											
											break;
											
		case UART_REC_OK2:
											
											rec_evt.rec_process = UART_REC_SUCCESS;
											break;
		case UART_WAITING_OK2_TIME_OUT:
											
											rec_evt.rec_process = UART_REC_SUCCESS;
											break;
											
		case UART_REC_SUCCESS:
											
											rec_evt.rec_process = UART_RX_IDLE;
											//package_uncode_permit_flag = 1;
											break;
											
	}

}

void Uart_Odd_Parity_Handler(void)
{
	uchar i;
	uchar cnt = 0;
	
	for( i=1; i<9; i++ )
	{
		if( rx_data[i] % 2 ==0 )
		{
			cnt++;
		}
	}
	if( cnt % 2 ==0 )    // odd partity pass
		rec_evt.rec_process = UART_SENDING_OK1;
	else
		rec_evt.rec_process = UART_SENDING_ERR;

	
}
void Uart_Send_Ok1_Handler(void)
{
	Tx_Send_Data(1);
}

void Uart_Send_Error_Handler(void)
{
	Tx_Send_Data(3);
}
void Uart_Waiting_Ok2_Handler(void)
{

	uchar i,	res;
	while( ! ( rec_done_flag == 1 && rx_data_type == 2 ) )
	{
		WDCDR.byte = 0x4e;				// clear wdt
		
		Rx_Rcv_Data();
		
		if( cnt2_10ms>=1 )
		{
			cnt2_10ms=0;
			ok2_time_cnt++;
			if( ok2_time_cnt>2 )
			{
				ok2_time_cnt=0;
				ok2_expiry_flag = 1;
				rec_evt.rec_process = UART_WAITING_OK2_TIME_OUT;
				return;
			}
		}
	}
	//------receive sth-----------//
	if( rec_done_flag == 1 && rx_data_type == 2 )
	{
		flag_rec_msg = 0;
		rx_data_type = 100;
   		for( i=1; i<9; i++ )
		{
			if( rx_data[i] == ok2_data[i] )
				res = 1;
			else
				res = 0;                                 // not ok1 comfirm package                         			
		}
		if( res ==0 )
		rec_evt.rec_process = UART_REC_FAIL;
		else
		rec_evt.rec_process = UART_REC_OK2;
	}

}