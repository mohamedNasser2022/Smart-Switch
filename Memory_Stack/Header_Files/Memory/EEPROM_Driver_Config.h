/*
 * EEPROM_Driver_Config.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Mohamed Nasser
 */

#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_CONFIG_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_CONFIG_H_

#define EEPROM_ADDRESSES   0xA0
#define EEPROM_PAGES   	   64
#define EEPROM_PAGE_SIZE   16

#define EEPROM_Driver_Interface_With_I2C(WORD_ADDRESS,QUEUE_DATA)  									  Push_Data_to_I2C_Sending_Buffer_Perpherial_1_With_Notification((u8)((EEPROM_ADDRESSES | (WORD_ADDRESS >> 7) & (0xFE))),QUEUE_DATA,Notification_Handler_I2C)
#define EEPROM_Driver_Read_From_Hardware(WORD_ADDRESS,QUEUE_DATA,NUMBER_OF_BYTE_TO_READ)			  Reading_From_I2C_Perpherial_1((u8)((EEPROM_ADDRESSES | (WORD_ADDRESS >> 6) & (0xFE))),QUEUE_DATA,NUMBER_OF_BYTE_TO_READ,Notification_Handler_I2C)
#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_EEPROM_DRIVER_CONFIG_H_ */
