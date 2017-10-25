//******************************************
//           This is a C Template file
//���ߣ�   
//����     
//����
//��ע
//******************************************   
#include "MQ6812.h"
#include "FlashFunction.h"




//==============================================================================
//��ʽ����	:FlashWriteByte 
//�ش�ֵ		:void
//����		:<addr>	ָ��д���ַ������ʹ��������FLASH�ڴ�����(0x7E80~0x7EFF)��
//          		����FLASH�ڴ�������ר����оƬ�����\�Еr���o䛅���������ʹ�á�����
//          		¼������оƬʱ������ʹ�ô����顣������������Ҳ��ʹ���ڳ���FLASH
//          		�ڴ�����(0xc000~0xffff)������ע��õ�ַ���޴��룬����д����޸ĳ���ṹ��
//     		 <data>	��д��FLASH�����ϣ�����Ϊ1BYTE
//����		:��addr��ַ��ʼ��д�볤��Ϊ1BYTE��ָ��data
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
//��ʽ����	:FlashReadSequence
//�ش�ֵ		:void
//����		:<addr> ��FLASH��ȡ����ʼ��ַ
//     		 <data> ����ָ�꣬��ʽ���FLASG��ȡ���ϣ�д������
//     		 <length>��ʽ��FLASH���ȡ�ĳ���(BYTE��)
//����		:��addr��ַ��ʼ����ȡFLASH��ָ������length�����ϣ�����data������
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
//��ʽ����	:FlashReadByte 
//�ش�ֵ		:unsigned char
//����		:<addr>	��FLASH��ȡ�ĵ�ַ
//����		:��ָ����ַaddr��ȡ���Ϻ�ش�
//==============================================================================
unsigned char FlashReadByte(unsigned int addr)
{	
	return *((unsigned char *)addr);
}




//==============================================================================
//��ʽ����	:FlashSectionErase 
//�ش�ֵ		:void
//����		:<addr> ��ʽ���������ָ����ַaddr��section
//����		:����ָ����ַaddr,ϵͳ���˵�ַ�Զ��жϡ���������ָ����ַaddr��section(128 Bytes)
//     
//     		��: ��addr =0x7e80 �tsection:0x7e80~0x7eff ����0x7e80  ����ϵͳ�����0x7e80~0x7eff  (128 Bytes)
//         		��addr =0x7e99 �tsection:0x7e80~0x7eff ����0x7e99  ����ϵͳ�����0x7e80~0x7eff  (128 Bytes)
//         		��addr =0x7eff �tsection:0x7e80~0x7eff ����0x7eff  ����ϵͳ�����0x7e80~0x7eff  (128 Bytes) 
//         		��addr =0xf000 �tsection:0xf000~0xf07f ����0xf000  ����ϵͳ�����0xf000~0xf07f  (128 Bytes)
//         		��addr =0xefff �tsection:0xef80~0xefff ����0xefff  ����ϵͳ�����0xef80~0xefff  (128 Bytes)
// 
//         section����:0xXX00~0xXX7f , 0xXX80~0xXXff
// 
// 		   ����FLASH�ڴ�����:
//         		<section>0x7e80~0x7eff
//  	   ����FLASH�ڴ�����:
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