//******************************************
//           This is a C Template file
//作者：   
//日期     
//功能
//备注
//******************************************   

#include "MQ6812.h"
#include "iApp.h"
#include "FlashFunction.h"
#include "protocol.h"
#include "ipwm.h"
// uchar rx_data[8] = {0};
// uchar tx_data[8] = {0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 
// 
// 
// extern uchar dev0_id[4];
// 
// struct PB_MSG pb_sent_msg1, pb_sent_msg2;
// struct PB_MSG pb_rec_msg1,  pb_rec_msg2;
// 
// uchar UART_OCUP_SENT_FLAG = 0;
// uchar UART_OCUP_REC_FLAG = 0;
// 
// void PB_Protocol_Rcv_Manager(void)
// {
// 	uchar rec_buf[8] = {0};
// 	uchar i ;
//     Rx_Rcv_Data();
// 	if(flag_rec_msg==0 )//|| UART_OCUP_REC_FLAG==0 && UART_OCUP_SENT_FLAG ==0)   
// 		return;
// 	for(i=0;i<8;i++)
// 	{
// 		rec_buf[i] = rx_data[i];
// 	}
// 	
// // 	switch(head)
// //    	{
// // 	 	__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
// // 		case 0xaa:  PB_Ipwm_Charge_Control();         	break;
// // 		case 0xbb:  PB_Ipwm_Discharge_Control();     	break;
// // 		case 0xdd:  PB_Protocol_Compare_Device_ID();	break;
// // 		case 0x11:  PB_Protocol_Sent_Stop_Comm();   	break;
// // 	}
// 
// 	//decode
// 	Decode_PB_Message();
// 	// ignore??
// 
// 	if(UART_OCUP_REC_FLAG==1)
// 	{
// 		 // form reply message
// 	}
// 	if(UART_OCUP_SENT_FLAG == 1 )
// 	{
// 		// UPDATED DEVICE STATUS AND EXE TASKS 
// 	}
// 	 
// 	flag_rec_msg = 0;
// }
// void PB_Sent_Manager(void)
// {
// 		Encode_PB_Message(pb_sent_msg1);
// 		Tx_Send_Data((uchar*)tx_data);
// }
// void Encode_PB_Message(struct PB_MSG m)
// {
// 	uchar i;
// 	uchar buff_temp[8]={0};
// 	buff_temp[1] = m.msg_dir;
// 	buff_temp[2] = m.msg_role;
// 	buff_temp[3] = m.msg_type;
// 	for(i=0; i<4; i++)
// 	{
// 		buff_temp[i+4] =m.msg_data[i];
// 	}
// 		tx_data[i] = buff_temp[i];
// 	
// }
// uchar Decode_PB_Message(void)
// {
// 	uchar i, decode_result =0 ;
// 	pb_rec_msg1.msg_dir = rx_data[1] ;
// 	pb_rec_msg1.msg_role = rx_data[2];
// 	pb_rec_msg1.msg_type= rx_data[3];
// 	for(i=0; i<4; i++)
// 	{
// 		pb_rec_msg1.msg_data[i] = rx_data[i+4];
// 	}
// 	
// 	/************************/
// 	if(pb_rec_msg1.msg_dir + pb_sent_msg1.msg_dir != 3 )
// 	{
// 	    decode_result = 0;
// 		return  decode_result ;  // fail, illegal message.
// 	}
// 	
// }
// void Encode_UART_Message(uchar dir0, uchar role0, uchar type0)
// {
// 		pb_sent_msg1.msg_dir = dir0;
// 	    pb_sent_msg1.msg_role = role0;
// 		pb_sent_msg1.msg_type = type0;
// 		Load_Data_To_Message(type0);
// }
// void Load_Data_To_Message (uchar t)
// { 
// 	uchar i ;
// 	if(t == 0)   // show id 
// 	{
// 		Get_Device_ID();
// 		for(i = 0; i<4; i++)
// 		pb_sent_msg1.msg_data[i] = dev0_id[i];
// 	}
// }
// 
// 
// void Tx_Send_Data(uchar *tx_data)
// {
// 	uchar i;
// 	for (i=0; i<8; i++)
// 	{
// 		TD1BUF.byte = *(dev0_id+i);
// 		delay_times(t_1ms, 10);
// 	}
// }// 
// 
// 
// void PB_Protocol_Compare_Device_ID(void)
// {
// 	uchar dev1_id[4] = {0} ;
// 	uchar i ;
// 	for (i=0; i<4; i++ )
// 	{
// 		dev1_id[i] =  rx_data[i+1];
// 	}
// 	Get_Device_ID();
// 	
// 	if(dev1_id[0]%2==0)
// 	{
// 		//PB_Protocol_Set_Device_Master();
// 	}
// 	else
// 	{
// 		//PB_Protocol_Set_Device_Slave();
// 	}
// }
// void Get_Device_ID(void)
// {
// 	FlashReadSequence(0x7e43, dev0_id, 4);
// }
