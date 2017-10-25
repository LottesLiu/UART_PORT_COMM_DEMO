
#ifndef __FLASHFUNCTION_H_
#define __FLASHFUNCTION_H_



void FlashWriteByte(unsigned int addr,unsigned char data);
void FlashReadSequence(unsigned int addr,unsigned char* data,unsigned int length);
unsigned char FlashReadByte(unsigned int addr);
void FlashSectionErase(unsigned int addr);



#endif





