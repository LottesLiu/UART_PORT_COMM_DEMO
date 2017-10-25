#include "MQ6812.h"
#include "iApp.h"
#include "FlashFunction.h"
#include "protocol.h"
#include "wkup_det.h"
extern uchar cur_dev_sta;
extern uchar pre_dev_sta;
extern uchar nxt_dev_sta;
uchar wkup_back_in_cnt = 0;
uchar wkup_back_out_cnt = 0;
uchar wkup_front_in_cnt = 0;
uchar wkup_front_out_cnt = 0;
uchar usb_adp_in_flag = 0;

uchar wkup_back_flag = 0;
uchar wkup_front_flag = 0;

void WKUP_Detect(void)
{
	if(WKUP_BACK==1)
	{	
		wkup_back_in_cnt++;
	}
	else
	{
		wkup_back_out_cnt++;
	}
	if(WKUP_FRONT==1)
	{
		wkup_front_in_cnt++;
	}
	else
	{
		wkup_front_out_cnt++;
	}
	
	if(wkup_back_in_cnt>10)
	{
		wkup_back_flag = 1;
		wkup_back_in_cnt=0;
		wkup_back_out_cnt=0;
	}
	if(wkup_back_out_cnt>10)
	{
		wkup_back_flag = 1;
		wkup_back_in_cnt=0;
		wkup_back_out_cnt=0;
	}
	if(wkup_front_in_cnt>10)
	{
		if(wkup_front_out_cnt>6)
		{
			usb_adp_in_flag =1;
			wkup_front_in_cnt=0;
		    wkup_front_out_cnt=0;
		}
		else
		{
			usb_adp_in_flag =0;
			wkup_front_flag=1;
			wkup_front_in_cnt=0;
		    wkup_front_out_cnt=0;
		}
	}
	if(wkup_front_out_cnt>9)
	{
		if(wkup_front_in_cnt ==0)
		{
			wkup_front_flag=0;
			wkup_front_in_cnt=0;
		    wkup_front_out_cnt=0;
		}
	}
    WKUP_Update_Device_State();
	
}
void WKUP_Update_Device_State(void)
{
	if(wkup_back_flag==1)
	{
		nxt_dev_sta |= 0x04;
	}
	else
	{
	    nxt_dev_sta &= 0xfb;
	}
	if(wkup_front_flag==1)
	{
		nxt_dev_sta |= 0x08;
	}
	else
	{
	    nxt_dev_sta &= 0xf7;
	}
	if(usb_adp_in_flag==1)
	{
		nxt_dev_sta |= 0x10;
	} 
	else
	{
	    nxt_dev_sta &= 0xef;
	} 
}
