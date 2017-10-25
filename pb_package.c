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
#include "pb_package.h"
#include "uart_data.h"

extern uchar rx_data[8];
extern uchar tx_data[8];



extern uchar dev0_id[4];

extern uchar pb_waiting_response_flag;

struct PB_MSG pb_sent_msg1, pb_sent_msg2;
struct PB_MSG pb_rec_msg1,  pb_rec_msg2;

void Message_To_Buffer(struct PB_MSG m)
{
	uchar i;
	uchar buff_temp[8]={0};
	buff_temp[1] = m.msg_dir;
	buff_temp[2] = m.msg_role;
	buff_temp[3] = m.msg_type;
	for(i=0; i<4; i++)
	{
		buff_temp[i+4] =m.msg_data[i];
	}
	for(i=1; i<8; i++)
		tx_data[i] = buff_temp[i];
	
}
uchar Buffer_To_Message(void)
{
	uchar i, decode_result =0 ;
	pb_rec_msg1.msg_dir = rx_data[1] ;
	pb_rec_msg1.msg_role = rx_data[2];
	pb_rec_msg1.msg_type= rx_data[3];
	for(i=0; i<4; i++)
	{
		pb_rec_msg1.msg_data[i] = rx_data[i+4];
	}
	
}

uchar PB_Protocol_Compare_Device_ID(uchar* id)
{
	uchar dev1_id[4] = {0} ;
	uchar i , res;
	for (i=0; i<4; i++ )
	{
		dev1_id[i] =  id[i+1];
	}
	Get_Device_ID();
	
	if(dev1_id[0]<dev0_id[0])
	{
		res = 2;		// slave
	}
	else
	{
		res = 1;		// master
	}
}
void Get_Device_ID(void)
{
	FlashReadSequence(0x7e43, dev0_id, 4);
}
