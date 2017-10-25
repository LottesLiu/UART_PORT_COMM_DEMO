#include "MQ6812.h"
#include "iApp.h"
#include "FlashFunction.h"
#include "protocol.h"
#include "task.h"
#include "DeviceAttachDet.h"
#include "pb_comm.h"


extern uchar att_front_flag;
extern uchar att_back_flag;
extern uchar usb_adp_in_flag;

extern uchar DEV_ATT_CUR;
extern uchar dev0_id[];

extern uchar dev_0_att, dev_x_att;
extern uint   dev_0_bat, dev_x_bat;
DEV_POS dev_pos;
BAT_EVT bat_evt;
extern 	uchar	   dev_discharging_f ;
extern 	uchar		dev_charging_f ;

uchar touch_key_evt = 0;
uchar touch_key_occur = 0;

extern 	uchar	tkey_finish_self_switch_flag;
extern 	uchar	tkey_finish_sent_switch_flag ;
uchar bat_status_check_standard =0;
void PB_Task_Manager(void)
{	
	if(DEV_ATT_CUR==0)  return;
	dev_0_att = DEV_ATT_CUR;
	dev_0_bat = dev0_id[0];
	
	
	
	if((dev_0_att == 0x0B) && (dev_x_att == 0xB0) )
		dev_pos = PB0_PB1;
	if((dev_0_att == 0x0B) && (dev_x_att == 0xBF) )
		dev_pos = PB0_PB1_CHATAB;
	if((dev_0_att == 0xFB) && (dev_x_att == 0xB0) )
		dev_pos = CASE_PB0_PB1;
	if((dev_0_att == 0xFB) && (dev_x_att == 0xBF ))
		dev_pos = CASE_PB0_PB1_CHATAB;
	if((dev_0_att == 0xAB) && (dev_x_att == 0xB0 ))
		dev_pos = PB0_PB1;
	if((dev_0_att == 0xAB) && (dev_x_att == 0xBF ))
		dev_pos = ADP_PB0_PB1;
	if((dev_0_att == 0xB0) && (dev_x_att == 0x0B) )
		dev_pos = PB0_PB1;
	if((dev_0_att == 0xB0) && (dev_x_att == 0xFB) )
		dev_pos = CASE_PB1_PB0;
	if((dev_0_att == 0xB0) && (dev_x_att == 0xAB) )
		dev_pos = ADP_PB1_PB0;
	if((dev_0_att == 0xBF) && (dev_x_att == 0x0B) )
		dev_pos = PB1_PB0_CHATAB;
	if((dev_0_att == 0xBF) &&( dev_x_att == 0xFB) )
		dev_pos = CASE_PB1_PB0_CHATAB;
	if((dev_0_att == 0xBF) && (dev_x_att == 0xAB) )
		dev_pos = ADP_PB1_PB0_CHATAB;
	if(DEV_ATT_CUR == 0XF0)
	dev_pos = CASE_PB0;
	if(DEV_ATT_CUR == 0X0F)
	dev_pos = PB0_CHATAB;
	if(DEV_ATT_CUR == 0XA0)
	dev_pos = ADP_PB0;
// 	if(( DEV_ATT_CUR == 0XB0 )||( DEV_ATT_CUR == 0X0B ))
// 	dev_pos = PB0_PB1;
	if((dev_0_att == 0xBB) && ((dev_x_att == 0x0B) ||(dev_x_att == 0x0B)))
	{
		dev_pos = PB0_PB1_PB2;
	}
	if((dev_x_att == 0xBB) && ((dev_0_att == 0x0B) ||(dev_0_att == 0x0B)))
	{
		dev_pos = PB0_PB1_PB2;
	}
		
	if(dev_0_bat>dev_x_bat)
	{
		bat_evt = BAT0_LARGE;
	}
	else
	{
		bat_evt = BAT0_SMALL;
	}

    switch(dev_pos)
	{
		__asm("NOP");				// switch 与第一个 case 之间置入一行 "NOP"，避免编译出 "JP gg" 指令！
		case PB0_PB1: {
						
						if(bat_status_check_standard==0XCC||touch_key_occur%2==1)
						{
							if (bat_evt == BAT0_LARGE) 
							 PB_Ipwm_Discharge_Control();
							else if(bat_evt == BAT0_SMALL) 
							  PB_Ipwm_Charge_Control();
						}
						else
						{
							if (bat_evt == BAT0_LARGE) 
							 PB_Ipwm_Charge_Control();
								
							else if(bat_evt == BAT0_SMALL) 
							   PB_Ipwm_Discharge_Control();
						}
						
							} break;
							
		case PB0_PB1_CHATAB: {
							if(bat_evt == BAT0_LARGE )
								PB_Ipwm_Charge_Control();
							else if(bat_evt == BAT0_SMALL )
							    PB_Stay();
							} break;
							
		case CASE_PB0_PB1: {
							if(bat_evt == BAT0_LARGE )
								PB_Stay();
							else if(bat_evt == BAT0_SMALL )
								PB_Ipwm_Discharge_Control();
							} break;
							
		case CASE_PB0_PB1_CHATAB: {
							if(bat_evt == BAT0_LARGE )
								PB_Ipwm_Charge_Control();
							else if(bat_evt == BAT0_SMALL )
							    PB_Stay();
							} break;
							
		case ADP_PB0_PB1: {
							if(bat_evt == BAT0_LARGE )
								PB_Ipwm_Charge_Control();
							else if(bat_evt == BAT0_SMALL )
							    PB_Stay();
							} break;
							
		case ADP_PB0_PB1_CHATAB: {
							if(bat_evt == BAT0_LARGE )
								PB_Ipwm_Charge_Control();
							else if(bat_evt == BAT0_SMALL )
							    PB_Stay();
							} break;
							
		case CASE_PB1_PB0: {
							if(bat_evt == BAT0_LARGE )
								PB_Stay();
							else if(bat_evt == BAT0_SMALL )
							    PB_Ipwm_Discharge_Control();
							} break;
		case PB0_PB1_PB2:
							{
								PB_Stay();
								D1=0;D2=0;D3=0;D4=0;
							}
		case CASE_PB0: PB_Ipwm_Discharge_Control(); break;

		case PB0_CHATAB: PB_Ipwm_Charge_Control(); break;

		case ADP_PB0: PB_Ipwm_Charge_Control(); break;
 
	}
	
	
}
extern uchar keySLIP, keyPUSH, keySLIP_down, keySLIP_up;
uchar tkey_finish_self_switch_flag=0;
uchar tkey_finish_sent_switch_flag=0;
uchar touch_key_short_press =0;
extern uchar key_slip_up ;
extern uchar key_slip_down;
void Touch_Key_Manager(void)
{
	if(dev_charging_f==1)
	{
		if(key_slip_up==1)     // charge to discharge 
		{
			key_slip_up=0;
			touch_key_occur++;
		}
		
	}
	if(dev_discharging_f ==1)
	{
		if(key_slip_down==1) // discharge to charge
		{
			key_slip_down = 0;
			touch_key_occur++;
		}
		
	}
// 	if(touch_key_short_press ==1)
// 	{
// 		touch_key_short_press = 0;
// 		touch_key_occur++;
// 	}

}