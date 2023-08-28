/*
 * EEPROM_Driver_Private.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Mohamed Nasser
 */

#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_PRIVATE_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_PRIVATE_H_

#define PADGES_NUMBER   16
#define SIZE_OF_EEPROM  1024


static void Notification_Handler_I2C(void* Pointer);
static u8 EEPROM_Driver_Test_Address(void);
static void EEPROM_Driver_Write_on_Physical(void);
static void EEPROM_Erasing_ALL(void);

#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_PRIVATE_H_ */
