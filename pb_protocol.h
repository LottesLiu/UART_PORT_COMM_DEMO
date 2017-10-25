//******************************************
//           This is a c File Head
//作者：   
//日期     
//功能
//备注
//******************************************   

#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

typedef enum
{
	IDLE = 0,
	SENT,
	WAIT_REPLY,
	TIME_OUT,
	RECEIVE,
	ERROR
} CHANNEL_STA;

uchar Analysis_PB_Package(void);
//------------------------------------------- SENTING PROCESS -------------------------------------------//
void Sent_PB_Package(uchar dir0, uchar role0, uchar type0);
void Form_PB_Package(uchar dir0, uchar role0, uchar type0); // form device info into pb message type 
void Payload_Unit_To_Package (uchar t);


#endif

