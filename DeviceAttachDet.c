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
#include "DeviceAttachDet.h"

extern uchar DEV_ATT_PRE ;
extern uchar DEV_ATT_CUR ;
extern uchar DEV_ATT_NXT ;

extern uchar DEV_ATT_PRE0 ;
extern uchar DEV_ATT_CUR0 ;
extern uchar DEV_ATT_NXT0 ;

IDENTIFY_PROCESS id_process = 0;
ID_RESULT id_res = 0;

uchar att_back_in_cnt = 0;
uchar att_back_out_cnt = 0;
uchar att_front_in_cnt = 0;
uchar att_front_out_cnt = 0;
uchar usb_adp_in_flag = 0;

uchar att_back_pre = 0;
uchar att_back_cur = 0;
uchar att_back_nxt = 0;

uchar att_front_pre = 0;
uchar att_front_cur = 0;
uchar att_front_nxt = 0;

extern uchar pb_role;
extern uchar pb_waiting_response_flag;
extern struct PB_MSG pb_sent_msg1, pb_sent_msg2;
extern struct PB_MSG pb_rec_msg1,  pb_rec_msg2;

void Device_Attachment_Detect(void)
{
	if(WKUP_BACK==1)
	{	
		att_back_in_cnt++;
	}
	else
	{
		att_back_out_cnt++;
	}
	if(WKUP_FRONT==1)
	{
		att_front_in_cnt++;
	}
	else
	{
		att_front_out_cnt++;
	}
/*------------------------------------*/
	
	if(att_back_in_cnt>20)
	{
		att_back_nxt = 1;
		att_back_in_cnt=0;
		att_back_out_cnt=0;
	}
	if(att_back_out_cnt>30)
	{
		att_back_nxt = 0;
		att_back_in_cnt=0;
		att_back_out_cnt=0;
	}
	/*---------------------------*/
	if(att_front_in_cnt>25)
	{
		if(att_front_out_cnt>15)
		{
			att_front_nxt =2;
			att_front_in_cnt=0;
		    att_front_out_cnt=0;
		}
		else
		{
			att_front_nxt=1;
			att_front_in_cnt=0;
		    att_front_out_cnt=0;
		}
	}
	if(att_front_out_cnt>50)
	{
		att_front_nxt=0;
		att_front_in_cnt=0;
		att_front_out_cnt=0;
		
	}
	if(att_front_nxt!=att_front_cur)
	{
		att_front_pre = att_front_cur;
		att_front_cur = att_front_nxt;
		
		   	if(att_front_cur == 0)
			{
				DEV_ATT_NXT0 = DEV_ATT_CUR0 &  0X0F; 
			}
			   if(att_front_cur == 1)
			{
				DEV_ATT_NXT0 = DEV_ATT_CUR0 | 0XF0;
			}
				if(att_front_cur == 2)
			{
			  DEV_ATT_NXT0 = DEV_ATT_CUR0 & 0X0F;
			  DEV_ATT_NXT0 = DEV_ATT_NXT0 | 0XA0;
			}
	}
	
	if(att_back_nxt!=att_back_cur)
	{
		att_back_pre = att_back_cur;
		att_back_cur = att_back_nxt;
		
	   if(att_back_cur == 0)
		{
			DEV_ATT_NXT0 = DEV_ATT_CUR0 & 0XF0;
		}
	
		 if(att_back_cur == 1)
		{
			DEV_ATT_NXT0 = DEV_ATT_CUR0 | 0X0F;
		}
	}

	
}
uchar Which_Side_Changed(void)
{
	uchar res = 0; 
	uchar val = 0;
// 	val = DEV_ATT_NXT0 ^ DEV_ATT_CUR0 ;   // same = 1 , different = 0;
// 	if(val <= 0x0F)   // back side changed
// 	{
// 		res = 0x01;
// 	}
// 	else              // front side changed
// 	{
// 		res = 0x10;
// 	}

	if((DEV_ATT_NXT0 >>4) ==0x0F || (DEV_ATT_NXT0 >>4) ==0x0A  )
	res = 0x10;
	else
	res = 0x01;
	return res;
   
}
void Adv_Att_Identity(uchar side)
{

	if (side == 0x01) // back side has changed 
	{
		if(DEV_ATT_NXT0 & 0x0F ) 		// attached sth on
		{
// 			if((DEV_ATT_CUR | 0x0F == 0xBF)&&pb_role == 2 )     // before sent Identify package , check if theres a pb attached
// 			Sent_PB_Package(DIR_BACK,ROLE_SLAVE, PAUSE_CMD);// on the other side  and if it is master role , if so , sent PAUSE .
			
			Sent_PB_Package(2, 0,SHOW_ID);
			PB_If_Channel_Status_Time_Out();
		}
		else									//taken sth off
		{
			id_res = NONE_ON_BACK;
			id_process = 2;
		}
	}
	if(side ==  0x10)
	{		
			if(DEV_ATT_NXT0 & 0xF0 ) 		// attached sth on
				{
		// 			if((DEV_ATT_CUR | 0x0F == 0xBF)&&pb_role == 2 )     // before sent Identify package , check if theres a pb attached
		// 			Sent_PB_Package(DIR_FRONT,ROLE_SLAVE, PAUSE_CMD);// on the other side  and if it is master role , if so , sent PAUSE .
					if((DEV_ATT_NXT0>>4) == 0x0F)
					{
					delay_times(t_1ms, 99);
					Sent_PB_Package(1, 0,SHOW_ID);
					}
					else if((DEV_ATT_NXT0>>4 )== 0x0A)
					{
						id_res = ADP_ON_FRONT;
						id_process = 2;
					}
				}
				else									//taken sth off
				{
					id_res = NONE_ON_FRONT;
					id_process = 2;
				}	
		}
	
}
void Update_Attach_Status(ID_RESULT res)
{
	switch (res)
	{
	__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
	
		case NONE_ON_BACK: DEV_ATT_NXT = DEV_ATT_CUR & 0XF0; break;
		
		case NONE_ON_FRONT: DEV_ATT_NXT = DEV_ATT_CUR & 0X0F; break;
		
		case CHA_TAB_ON_BACK: {
										DEV_ATT_NXT = DEV_ATT_CUR & 0XF0; 
										DEV_ATT_NXT = DEV_ATT_NXT | 0X0F;
										}   break;
		case PB_ON_BACK:  		{
										DEV_ATT_NXT = DEV_ATT_CUR & 0XF0; 
										DEV_ATT_NXT = DEV_ATT_NXT | 0X0B;
										}   break;
		case PB_ON_FRONT:  		{
										DEV_ATT_NXT = DEV_ATT_CUR & 0X0F; 
										DEV_ATT_NXT = DEV_ATT_NXT | 0XB0;
										}   break;
		case CASE_ON_FRONT:   {
										DEV_ATT_NXT = DEV_ATT_CUR & 0X0F; 
										DEV_ATT_NXT = DEV_ATT_NXT | 0XF0;
										}   break;
		case ADP_ON_FRONT:   {
										DEV_ATT_NXT = DEV_ATT_CUR & 0X0F; 
										DEV_ATT_NXT = DEV_ATT_NXT | 0XA0;
										}   break;
	}
	DEV_ATT_PRE = DEV_ATT_CUR;
	DEV_ATT_CUR = DEV_ATT_NXT;
	DEV_ATT_PRE0 = DEV_ATT_CUR0;
	DEV_ATT_CUR0 = DEV_ATT_NXT0;
}
