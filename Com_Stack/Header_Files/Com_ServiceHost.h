#include"STD_TYPES.h"
#ifndef	COM_SERVICE_H_
#define	COM_SERVICE_H_

void Gate_Way(u8* Message_Data);
void Runnable_Read_Messages_1ms(void);
static void Message_Read_0x01(void);
static void Message_Read_0x11(void);
static void Message_Read_0x13(void);
static void Message_Read_0x14(void);
static void Message_Read_0x20(void);
static void Message_Read_0x21(void);
static void Message_Read_0x15(void);

#endif