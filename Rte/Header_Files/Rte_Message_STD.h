

#include"STD_TYPES.h"

#ifndef  RTE_MESSAGE_STD_H
#define  RTE_MESSAGE_STD_H


typedef struct 
{
    u8 Data[LENGHT_STATUS_OBJECT_ON_SYSTEM];
   
}Idt_Message_0x13_t;

#define MESSAGE_0x10	  0x10
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x10 6
typedef struct
{
	
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x10];
	

}Idt_Message_0x10_t;

#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x11 6
typedef struct
{
	
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x11];
	

}Idt_Message_0x11_t;




#endif
