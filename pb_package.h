//******************************************
//           This is a c File Head
//作者：   
//日期     
//功能
//备注
//******************************************   

#ifndef __PB_PACKAGE_H_
#define __PB_PACKAGE_H_

typedef enum
{
	SHOW_ID = 0,
	RETURN_ID,
	ASK_FOR_INFO,
	RETURN_INFO,
	STOP_COMM,
	START_CHA,
	START_DCHA,
	PAUSE_CMD
} MSG_TYPE;
typedef enum
{
	DIR_FRONT = 1,
	DIR_BACK
	
} MSG_DIR;
typedef enum
{
	ROLE_UNCLEAR=0,
	ROLE_MASTER,
	ROLE_SLAVE
} MSG_ROLE;

typedef void (*pb_protocal_rec_callback)(uchar * buffer);
struct PB_MSG
{
	MSG_DIR msg_dir;
	MSG_ROLE msg_role;
	MSG_TYPE msg_type;
	uchar msg_data[4];
	pb_protocal_rec_callback rec_cb;
	
};

void Message_To_Buffer(struct PB_MSG m);
uchar Buffer_To_Message(void);
uchar PB_Protocol_Compare_Device_ID(uchar* id);
void Get_Device_ID(void);


#endif

