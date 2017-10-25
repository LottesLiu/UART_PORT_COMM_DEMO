#include "MQ6812.h"
#include "iApp.h"
#include "FlashFunction.h"
#include "pb_protocol.h"
#include "task.h"
#include "pb_comm.h"
#include "pb_package.h"

extern uchar att_front_flag;
extern uchar att_back_flag;
extern uchar usb_adp_in_flag;

extern uchar DEV_ATT_PRE ;
extern uchar DEV_ATT_CUR ;
extern uchar DEV_ATT_NXT ;

extern struct PB_MSG pb_sent_msg1, pb_sent_msg2;
extern struct PB_MSG pb_rec_msg1,  pb_rec_msg2;

extern MSG_ROLE pb_role;

INFO_COMM_STA comm_pro;

uchar dev_0_att, dev_x_att;
uint dev_0_bat, dev_x_bat;
uchar start_comm_info_flag = 0;

extern uchar touch_key_evt;
extern 	uchar	touch_key_occur ;

uchar wait_reply_info_cnt=0;
uchar wait_reply_info_timeout_cnt=0;

extern uchar bat_status_check_standard;
void PB_Comm_Manager(void)
{
    uchar dir0 = 0;
	start_comm_info_flag=1;
	Receive_PB_Package();
	switch(comm_pro)
	{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
		case COMM_STOP: {  
									if(flag1_1s ==1&&pb_role==ROLE_MASTER)   //master and its time
									{   
										flag1_1s = 0;
										dir0 = Get_PB_Direction();
										Form_PB_Package(dir0, 1, 2);
										if(touch_key_occur%2==1)
										{
											pb_sent_msg1.msg_data[1]= 0xCC;
										}
										Message_To_Buffer(pb_sent_msg1);
	
										Tx_Send_Data();
										//comm_pro = SENT_ASK;
									}
										
								}break;
										
		case SENT_ASK:{
											//delay_times(t_1ms, 100); 	
											//Sent_PB_Package(dir0, ROLE_MASTER, ASK_FOR_INFO);
											
										}    break;
		
		case REC_ANS: {  
								dev_x_att =( pb_rec_msg1.msg_data[0]&0x00FF);
								dev_x_bat = (pb_rec_msg1.msg_data[2]<<8) +pb_rec_msg1.msg_data[3];
							    bat_status_check_standard =  pb_rec_msg1.msg_data[1];
								comm_pro = COMM_STOP;
							}   break;
							 
								   
		case WAIT_ANS:{;}break;
		
		case REC_ASK:{
							
							dev_x_att =  pb_rec_msg1.msg_data[0];
							bat_status_check_standard =  pb_rec_msg1.msg_data[1];
							dev_x_bat = (pb_rec_msg1.msg_data[2]<<8) +pb_rec_msg1.msg_data[3];
							
							//touch_key = ( pb_rec_msg1.msg_data[1]&0x00FF);
							
							comm_pro = SENT_ANS;
		
						}break;
		case SENT_ANS:{
		
										dir0 = Get_PB_Direction();
										Form_PB_Package(dir0, 1, 3);
										
										if(touch_key_occur%2==1)
										{
											pb_sent_msg1.msg_data[1]= 0xCC;
										}
										Message_To_Buffer(pb_sent_msg1);
										Tx_Send_Data();
										comm_pro = COMM_STOP;
		
		}    break;
	


	}
    
}
uchar Get_PB_Direction(void)
{  
	uchar dir0;
    if(DEV_ATT_CUR>>4 == 0x0B)    // PB ON FRONT
	{
		dir0 = 1;
	}
	if((DEV_ATT_CUR&0x0F) ==0x0B)    // PB ON BACK 
	{
		dir0 = 2;
	}
	
	return dir0;
}







