#include "MQ6812.h"
#include "iApp.h"
#include "FlashFunction.h"
#include "protocol.h"
#include "ipwm.h"
#include "battery_detect.h"
#include "led.h"


char dev_start_dchg_flag =0;
char dev_start_chg_flag = 0;
char ipwm_temp = 0;
char ipwm_val = 0;
char led_blink_f = 0;

extern uchar bat_quan ;
uchar dev_discharging_f =0;
uchar dev_charging_f =0;
void PB_Ipwm_Discharge_Control(void)
{
	if(dev_start_dchg_flag==0)   // not in discharge mode
	{
		CE = 0;
		delay_times(t_1ms, 1);
		DIR=1;
		PPG00_INIT(50, 100);
		CE=1;
		dev_start_dchg_flag=1;
		dev_start_chg_flag=0;
		dev_discharging_f =1;
		dev_charging_f = 0;
	}
	//Get_Battery_Quantity();
 		D1 = 1;
		D2 = 1;
}
void PB_Ipwm_Charge_Control(void)
{
	if(dev_start_chg_flag==0)
	{
		CE = 0;
		delay_times(t_1ms, 1);
		DIR=0;
		PPG00_INIT(20, 100);
		CE=1;
		dev_start_chg_flag=1;
		dev_start_dchg_flag =0;
		dev_discharging_f =0;
		dev_charging_f = 1;
	}
	else
	{
		if(flag_1s==1)
		{
			pb_ipwm_dynamic_control();
			flag_1s=0;
		}
	}
}
void pb_ipwm_dynamic_control(void)
{
//		if(ipwm_temp<30)
//		{
//			ipwm_temp++;
//		}
//		PPG00_INIT(ipwm_temp, 100);
		
		PPG00_INIT(15, 100);
		
		D1 = 1;
		D2 = 1;
		D3 = 1;
		if(led_blink_f)
		{
			D4= 1;
			led_blink_f=0;
		}
		else
		{
			D4 = 0;
			led_blink_f=1;
		}
		
}
void PB_Stay(void)
{
	delay_times(t_1ms, 1);
	DIR=0;
	PPG00_INIT(0, 100);
			dev_start_dchg_flag=0;
		dev_start_chg_flag=0;
	CE=0;
}
