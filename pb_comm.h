//******************************************
//           This is a c File Head
//作者：   
//日期     
//功能
//备注
//******************************************   

#ifndef __PB_COMM_H_
#define __PB_COMM_H_

typedef enum
{
	COMM_STOP = 0,
	SENT_ASK,
	REC_ANS,
	WAIT_ANS,
	REC_ASK,
	SENT_ANS
} INFO_COMM_STA;


uchar Get_PB_Direction(void);
void PB_Comm_Manager(void);


#endif