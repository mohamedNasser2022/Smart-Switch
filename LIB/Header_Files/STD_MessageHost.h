#include"STD_TYPES.h"
#ifndef	STD_MESSAGE_H_
#define	STD_MESSAGE_H_

#define MESSAGE_0x01        0x01
#define MESSAGE_LENGTH_0x01 3
typedef struct
{
	u8 Number_of_Relays;
	u8 Length_of_Status_Message;
	u8 Reserver[1];
}Idt_Message_0x01_t;

#define MESSAGE_0x11        0x11
#define MESSAGE_LENGTH_0x11 3
typedef struct
{
	u8 Object_ID;
	u8 Command;
	u8 Time_In_Mins;
}Idt_Message_0x11_t;

#define MESSAGE_0x13        0x13
#define MESSAGE_LENGTH_0x13 8
typedef struct
{
	u8 Object_status_1;
	u8 Object_status_2;
	u8 Object_status_3;
	u8 Object_status_4;
	u8 Object_status_5;
	u8 Object_status_6;
	u8 Object_status_7;
	u8 Object_status_8;
}Idt_Message_0x13_t;

#define MESSAGE_0x14        0x14
#define MESSAGE_LENGTH_0x14 6
typedef struct
{
	u8 Object_ID;
	u8 Object_Number_In_Status_Message;
	u8 Reserver[4];
}Idt_Message_0x14_t;

#define MESSAGE_0x20        0x20
#define MESSAGE_LENGTH_0x20 20
typedef struct
{
	u8 Data[20];
}Idt_Message_0x20_t;

#define MESSAGE_0x21        0x21
#define MESSAGE_LENGTH_0x21 40
typedef struct
{
	u8 Data[40];
}Idt_Message_0x21_t;

#define MESSAGE_0x03        0x03
#define MESSAGE_LENGTH_0x03 6
typedef struct
{
	u8 Respond;
	u8 System_Mode;
	u8 Reserver[4];
}Idt_Message_0x03_t;

#define MESSAGE_0x10        0x10
#define MESSAGE_LENGTH_0x10 3
typedef struct
{
	u8 Object_ID;
	u8 Command;
	u8 Time_In_Mins;
}Idt_Message_0x10_t;

#define MESSAGE_0x30        0x30
#define MESSAGE_LENGTH_0x30 20
typedef struct
{
	u8 Data[20];
}Idt_Message_0x30_t;

#define MESSAGE_0x31        0x31
#define MESSAGE_LENGTH_0x31 40
typedef struct
{
	u8 Data[40];
}Idt_Message_0x31_t;

#define MESSAGE_0x15        0x15
#define MESSAGE_LENGTH_0x15 2
typedef struct
{
	u8 Object_ID;
	u8 Object_Data;
}Idt_Message_0x15_t;


#endif