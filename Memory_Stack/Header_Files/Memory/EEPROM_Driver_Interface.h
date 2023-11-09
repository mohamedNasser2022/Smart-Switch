/*
 * EEPROM_Driver_Interface.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Mohamed Nasser
 */
#include"Queue_Interface.h"
#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_INTERFACE_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_INTERFACE_H_

typedef Array_Of_Queue_3 EEROM_Queue;
#define EEPROM_Queue_Pop(QUEUE_POINTER,POINTER_DATA)  Queue3_Pop(QUEUE_POINTER,POINTER_DATA)
#define EEPROM_Queue_Push(QUEUE_POINTER,DATA)  		Queue3_Push(QUEUE_POINTER,DATA)
#define EEPROM_Queue_Create(QUEUE_POINTER) 			 Queue3_Create(QUEUE_POINTER)

enum
{
	Undefined,
	Writing,
	Reading,
	Normal,
	Erasing,
	Wait,
	Busy,
	On_Progress,
	True,
	OK_EEPROM,
	Faild_EEPROM,
}EEPROM_Modes;

void EEPROM_Driver_Time(void);
void EEPROM_Driver_Polling(void);
void EEPROM_Driver_Initialization(void);
u8 EEPROM_Driver_Read(u16 copy_Reading_Starting_from,u8 Lenght_of_Reading,void (*Pointer_Function)(void*));
u8 EEPROM_Driver_Write(u16 WordAddress,EEROM_Queue *Pointer_To_Queue);
u8 EEPROM_Driver_Set_Call_Back_Writing(void (*Pointer_Function)(void*));
u8 EEPROM_Requested_Erase_ALL(void);
#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_INTERFACE_H_ */
