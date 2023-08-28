/*
 * EEPROM_Driver_Interface.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Mohamed Nasser
 */

#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_INTERFACE_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_INTERFACE_H_

enum
{
	Undefined,
	Writing,
	Reading,
	Normal,
	Erasing,
	Faild,
	Wait,
	Busy,
	On_Progress,
	True,
	False,
}EEPROM_Modes;

void EEPROM_Driver_Time(void);
void EEPROM_Driver_Polling(void);
void EEPROM_Driver_Initialization(void);
u8 EEPROM_Driver_Read(u16 copy_Reading_Starting_from,u8 Lenght_of_Reading);
u8 EEPROM_Driver_Write(u16 WordAddress,Comuncation_Manger_Interface *Pointer_To_Queue);
u8 EEPROM_Requested_Erase_ALL(void);
#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_INTERFACE_H_ */
