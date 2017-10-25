//******************************************
//           This is a C Template file
//作者：   
//日期     
//功能
//备注
//******************************************   
#include "MQ6812.h"
#include "FlashFunction.h"




//==============================================================================
//函式名称	:FlashWriteByte 
//回传值		:void
//参数		:<addr>	指定写入地址，建议使用于数据FLASH内存区块(0x7E80~0x7EFF)。
//          		数据FLASH内存区块是专用于芯片程序運行時，紀錄參數、數據使用。在烧
//          		录代码至芯片时，不会使用此区块。若有特殊需求也可使用于程序FLASH
//          		内存区块(0xc000~0xffff)，但需注意该地址有无代码，以免写入后修改程序结构。
//     		 <data>	欲写入FLASH的资料，长度为1BYTE
//功能		:从addr地址开始，写入长度为1BYTE的指定data
//==============================================================================
void FlashWriteByte(unsigned int addr,unsigned char data)
{	
	FLSCR1.byte = 0xa0;		
	FLSCR2.byte = 0xd5;			//enable flash command
	__asm("ld (0xf555),0xaa");
	__asm("ld (0xfaaa),0x55");
	__asm("ld (0xf555),0xa0");
	*(unsigned char* )(addr) = data;      

	FLSCR1.byte = 0x40;
	FLSCR2.byte = 0xd5;			//disable flash command
}




//==============================================================================
//函式名称	:FlashReadSequence
//回传值		:void
//参数		:<addr> 从FLASH读取的起始地址
//     		 <data> 阵列指标，函式会从FLASG读取资料，写入阵列
//     		 <length>函式从FLASH里读取的长度(BYTE数)
//功能		:从addr地址开始，读取FLASH里指定长度length的资料，存至data阵列里
//==============================================================================
void FlashReadSequence(unsigned int addr,unsigned char* data,unsigned int length)
{
	unsigned char *p_addr = (unsigned char *)addr;
	unsigned int i;
	for(i=0;i<length;i++)
	{
		data[i] = *(p_addr+i);
		WDCDR.byte=0x4e; 		//clear wdt
	}
	
}




//==============================================================================
//函式名称	:FlashReadByte 
//回传值		:unsigned char
//参数		:<addr>	从FLASH读取的地址
//功能		:于指定地址addr读取资料后回传
//==============================================================================
unsigned char FlashReadByte(unsigned int addr)
{	
	return *((unsigned char *)addr);
}




//==============================================================================
//函式名称	:FlashSectionErase 
//回传值		:void
//参数		:<addr> 函式会擦除包含指定地址addr的section
//功能		:输入指定地址addr,系统依此地址自动判断、擦除包含指定地址addr的section(128 Bytes)
//     
//     		例: 若addr =0x7e80 則section:0x7e80~0x7eff 包含0x7e80  所以系统会擦除0x7e80~0x7eff  (128 Bytes)
//         		若addr =0x7e99 則section:0x7e80~0x7eff 包含0x7e99  所以系统会擦除0x7e80~0x7eff  (128 Bytes)
//         		若addr =0x7eff 則section:0x7e80~0x7eff 包含0x7eff  所以系统会擦除0x7e80~0x7eff  (128 Bytes) 
//         		若addr =0xf000 則section:0xf000~0xf07f 包含0xf000  所以系统会擦除0xf000~0xf07f  (128 Bytes)
//         		若addr =0xefff 則section:0xef80~0xefff 包含0xefff  所以系统会擦除0xef80~0xefff  (128 Bytes)
// 
//         section规则:0xXX00~0xXX7f , 0xXX80~0xXXff
// 
// 		   数据FLASH内存区块:
//         		<section>0x7e80~0x7eff
//  	   程序FLASH内存区块:
//         		<section>0xc000~0xc07f 
//         		<section>0xe080~0xe0ff 
//         		<section>0xe100~0xe17f 
//         		<section>0xe180~0xe1ff
//                         :
//                         :						  
//         		<section>0xff00~0xff7f 
//         		<section>0xff80~0xffff
//==============================================================================
void FlashSectionErase(unsigned int addr)
{
	FLSCR1.byte = 0xa0;		
	FLSCR2.byte = 0xd5;			//enable flash command
	__asm("ld (0xf555),0xaa");
	__asm("ld (0xfaaa),0x55");
	__asm("ld (0xf555),0x80");
	__asm("ld (0xf555),0xaa");
	__asm("ld (0xfaaa),0x55");
		
	*(unsigned char* )(addr) = 0x20;
	FLSCR1.byte = 0x40;
	FLSCR2.byte = 0xd5;			//disable flash command
	
}