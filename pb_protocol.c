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
#include "pb_protocol.h"
#include "pb_package.h"
#include "pb_comm.h"
#include "DeviceAttachDet.h"

MSG_ROLE pb_role;
uchar decode_result;
uchar pb_waiting_response_flag = 0;
uchar dev0_id[4] = {0};
CHANNEL_STA channel_sta = 0;

extern struct PB_MSG pb_sent_msg1, pb_sent_msg2;
extern struct PB_MSG pb_rec_msg1,  pb_rec_msg2;
extern uchar DEV_ATT_PRE ;
extern uchar DEV_ATT_CUR ;
extern uchar DEV_ATT_NXT ;

extern INFO_COMM_STA comm_pro;

extern IDENTIFY_PROCESS id_process ;
extern ID_RESULT id_res ;

extern uchar wich_side_chged ;
extern uchar rx_data[];
extern INFO_COMM_STA comm_pro;

extern uchar start_comm_info_flag;
//------------------------------------------- RECEIVE PROCESS -------------------------------------------//
void Receive_PB_Package(void)
{
	uchar side = 0;
	Rx_Rcv_Data();
	if(flag_rec_msg==0)	return;
	flag_rec_msg = 0;
	if(rx_data[1] != 0)
	{
			if(start_comm_info_flag==1)
			channel_sta = IDLE;
	if(channel_sta == IDLE || channel_sta == WAIT_REPLY )
		{
			channel_sta = RECEIVE;

			Buffer_To_Message();
			Analysis_PB_Package();
			
		}
	}
	
}
uchar wait_reply_cnt;
uchar Analysis_PB_Package(void)
{
 uchar dir=0;
uchar side = 0;
char type =0;
	/************  To see wether the package is legal or not  ************/
// 	if(DEV_ATT_CUR!=0)      // dont execute this at the very begining.
// 	{
// 		if(pb_rec_msg1.msg_dir + pb_sent_msg1.msg_dir != 1 )
// 		{
// 			decode_result = 0;
// 			return  decode_result ;  // fail, illegal message.
// 		}
// 	}
	
	if(channel_sta ==  IDLE)
	channel_sta = RECEIVE;
//	if(channel_sta ==  SENT )//&& pb_rec_msg1.msg_type == (pb_sent_msg1.msg_type + 1) )
//	channel_sta = WAIT_FOR_REPLY;
	
	
	if(channel_sta ==  RECEIVE || channel_sta == WAIT_REPLY|| channel_sta == IDLE)
	{
		type = pb_rec_msg1.msg_type;
		
		switch (pb_rec_msg1.msg_type)
		{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
			case SHOW_ID:	{
									wich_side_chged = Which_Side_Changed();
									if(wich_side_chged==0x01)
									dir = 2;
									if(wich_side_chged==0x10)
									dir=1;
									pb_role = PB_Protocol_Compare_Device_ID((uchar *)(pb_rec_msg1.msg_data));
									Sent_PB_Package(dir, pb_role, RETURN_ID);
									delay_times(t_1ms, 100); 
									Sent_PB_Package(dir, pb_role, RETURN_ID);
									delay_times(t_1ms, 100); 
									Sent_PB_Package(dir, pb_role, RETURN_ID);
									delay_times(t_1ms, 100); 
									Sent_PB_Package(dir, pb_role, RETURN_ID);
									
									/***********IDENTIFY****************/
									if(id_process == ON_ID)
									{
										if(pb_rec_msg1.msg_dir == DIR_BACK)
										id_res = PB_ON_FRONT;
										if(pb_rec_msg1.msg_dir == DIR_FRONT)
										id_res = PB_ON_BACK;
										//if(pb_rec_msg1.msg_dir == 0)
										//id_res = PB_ON_BACK;
										
										id_process = FINISH_ID;
									}
									/**********CHANNEL*****************/
									if(channel_sta == WAIT_REPLY|| channel_sta == RECEIVE)
									{
										channel_sta = IDLE;
									}
										delay_times(t_1ms, 100); 			

								}break;
								 
			case RETURN_ID: {	

									pb_role = PB_Protocol_Compare_Device_ID((uchar *)(pb_rec_msg1.msg_data));
									/***********IDENTIFY****************/
									if(id_process == ON_ID)
									{
										if(pb_rec_msg1.msg_dir == DIR_BACK)
										id_res = PB_ON_FRONT;
										if(pb_rec_msg1.msg_dir == DIR_FRONT)
										id_res = PB_ON_BACK;
										
										id_process = FINISH_ID;
									}
									/**********CHANNEL*****************/
									if(channel_sta == WAIT_REPLY || channel_sta == RECEIVE)
									{
										channel_sta = IDLE;
									}
	
								  }break;
																			 
			case ASK_FOR_INFO:			{
													comm_pro = REC_ASK;
												}break;
																			 
			case RETURN_INFO:           {
												    comm_pro = REC_ANS;
													if(channel_sta == WAIT_REPLY)
													{
														channel_sta = IDLE;
													}
	
			
												}break;

			
		}
	}
	
}



//------------------------------------------- SENTING PROCESS -------------------------------------------//
uchar wait_reply_timeout_cnt=0;
void Sent_PB_Package(uchar dir0, uchar role0, uchar type0)
{
	uchar dir;


	if((channel_sta==RECEIVE) || (channel_sta==IDLE) || (channel_sta == WAIT_REPLY) )
	{
		Form_PB_Package(dir0, role0, type0);
		Message_To_Buffer(pb_sent_msg1);
		Tx_Send_Data();
	}
	if(channel_sta==IDLE)
	channel_sta =  SENT ;
	if(channel_sta ==  SENT )
	channel_sta = WAIT_REPLY;
	
//	if(start_comm_info_flag==1 )
//	channel_sta=IDLE;
	
	if(wich_side_chged==0x01)
	dir = 2;
	if(wich_side_chged==0x10)
	dir=1;
	
	while(channel_sta == WAIT_REPLY)
	{
		 Receive_PB_Package();
			if( flag2_50ms == 1)
			{
				flag2_50ms=0;
				wait_reply_cnt ++;
				if(wait_reply_cnt>1) // 100ms
				{
					wait_reply_timeout_cnt++;
					wait_reply_cnt = 0;
					Tx_Send_Data();
				}
			}
			if(wait_reply_timeout_cnt>2)
			{
				wait_reply_timeout_cnt=0;
				return;
			}
		
		
	}

	
}
void Form_PB_Package(uchar dir0, uchar role0, uchar type0)   // form device info into pb message type 
{
		pb_sent_msg1.msg_dir = dir0;
	    pb_sent_msg1.msg_role = role0;
		pb_sent_msg1.msg_type = type0;
		Payload_Unit_To_Package(type0);
}

void Payload_Unit_To_Package (uchar t)
{ 
	uchar i ;
	uint bat_qua;
	if(t == 0)   // show id 
	{
		Get_Device_ID();
		for(i = 0; i<4; i++)
		pb_sent_msg1.msg_data[i] = dev0_id[i];
	}
	if(t == 1) // return id
	{
		Get_Device_ID();
		for(i = 0; i<4; i++)
		pb_sent_msg1.msg_data[i] = dev0_id[i];
	}
	if(t == 2)  // ask for info
	{
		pb_sent_msg1.msg_data[0] = DEV_ATT_CUR;
		
		
		pb_sent_msg1.msg_data[1] = 0;
		bat_qua = Get_Battery_Quantity();
		pb_sent_msg1.msg_data[2] = (uchar)(bat_qua>>8);
		pb_sent_msg1.msg_data[3] = (uchar)bat_qua;
		
		
	}
	if(t == 3)  // return info
	{
		pb_sent_msg1.msg_data[0] = DEV_ATT_CUR;
		pb_sent_msg1.msg_data[1] = 0;
		bat_qua = Get_Battery_Quantity();
		pb_sent_msg1.msg_data[2] = (uchar)(bat_qua>>8);
		pb_sent_msg1.msg_data[3] = (uchar)bat_qua;
	}

}
//------------------------------------------- CHANNEL STATUS PROCESS -------------------------------------------//
uchar wait_reply_count = 0;
uchar time_out_flag = 0;
void PB_If_Channel_Status_Time_Out(void)
{
	if(channel_sta !=WAIT_REPLY )
		return;
	if(flag1_50ms==1)
	{
		flag1_50ms = 0;
		wait_reply_count++;
		if(wait_reply_count>50)
		{
			wait_reply_count++;
			channel_sta = TIME_OUT;
			time_out_flag = 1;
		}

		
	}
	if(time_out_flag==1)
	{
		time_out_flag=0;
		if(id_process == ON_ID)
		{
			if(pb_sent_msg1.msg_dir == DIR_FRONT)
			id_res = CASE_ON_FRONT;
			if(pb_sent_msg1.msg_dir == DIR_BACK)
			id_res = CHA_TAB_ON_BACK;
			id_process = FINISH_ID;
		}
		channel_sta = IDLE;
	}

	
}



