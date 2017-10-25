//******************************************
//           This is a C Template file
//作者：   
//日期     
//功能
//备注
//******************************************   
// #include "MQ6812.h"
#include "iApp.h"
#include "ADC.h"
#include "FlashFunction.h"
#include "pb_protocol.h"
#include "task.h"
#include "pb_comm.h"
#include "pb_package.h"
#include "battery_detect.h"


uchar bat_qua =0;
extern uchar dev0_id[];

uint Get_Battery_Quantity(void)
{
	uint bat ;
	//bat = ADC_BAT_check(); 
	bat =dev0_id[0];
    return bat;
}









