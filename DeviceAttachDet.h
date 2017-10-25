//******************************************
//           This is a c File Head
//作者：   
//日期     
//功能
//备注
//******************************************   

#ifndef __DeviceAttachDet_H_
#define __DeviceAttachDet_H_

typedef enum
{
    NONE_ON_BACK = 0,
	NONE_ON_FRONT,
	CHA_TAB_ON_BACK,
	PB_ON_BACK,
	PB_ON_FRONT,
	CASE_ON_FRONT,
	ADP_ON_FRONT
}ID_RESULT;

typedef enum
{
    STOP_ID =0,
	ON_ID,
	FINISH_ID
}IDENTIFY_PROCESS;




void Device_Attachment_Detect(void);
void Device_Attachment_State_Update(void);
uchar Which_Side_Changed(void);
void Update_Attach_Status(ID_RESULT res);
#endif