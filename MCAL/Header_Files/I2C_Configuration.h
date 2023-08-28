/*
 * I2C_Configuaration.h
 *
 *  Created on: Dec 21, 2022
 *      Author: Mohamed Nasser
 */


#include"I2C_config.h"

#ifndef I2C_CONFIGUARATION_H_
#define I2C_CONFIGUARATION_H_

typedef struct
{
	volatile u8 I2C_No:1;
	volatile u32 I2C_Frequency;
	volatile u8 I2C_Interrupt_Enable_Event:1;
	volatile u8 I2C_Interrupt_Enable_Buffer:1;
	volatile u8 I2C_Interrupt_Enable_Error:1;
	volatile u8 I2C_ACK_Enable:1;
	volatile u8 I2C_General_Call_Enable:1;
	volatile u8 I2C_Bus_Mode:1;
	volatile u8 I2C_ADDMODE:1;
	volatile u8 I2C_DualMode_ADD:1;

#if ADDRESS_MODE == DUAL_ADDRESSES
	volatile u8 I2C_Address_2;
#endif

#if ADDRESS_LENGTH == BIT10_ADDRESS
	volatile u16 I2C_Address_1;
#else
	volatile u8 I2C_Address_1;
#endif



}I2C_Configuration_Struct;

#define I2C_PERPHEIAL_1 0
#define I2C_PERPHEIAL_2 1


#endif /* I2C_CONFIGUARATION_H_ */
