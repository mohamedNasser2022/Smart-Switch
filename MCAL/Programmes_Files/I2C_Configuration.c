/*
 * I2C_Configuration.c
 *
 *  Created on: Dec 21, 2022
 *      Author: Mohamed Nasser
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"I2C_config.h"

#include"I2C_Configuration.h"


I2C_Configuration_Struct I2C_cf_1;

void I2C_Set_Values(void)
{
	I2C_cf_1.I2C_No = I2C_PERPHEIAL_1;
	I2C_cf_1.I2C_Frequency = 200000; /**/
	I2C_cf_1.I2C_Interrupt_Enable_Buffer = I2C1_INTERRUPT_AT_BUFFER;
	I2C_cf_1.I2C_Interrupt_Enable_Event  = I2C1_INTERRUPT_AT_EVENT;
	I2C_cf_1.I2C_Interrupt_Enable_Error  =I2C1_INTERRUPT_AT_ERROR;
	I2C_cf_1.I2C_Bus_Mode = I2C1_BUS_MODE;
	I2C_cf_1.I2C_General_Call_Enable = I2C1_GENERALL_CALL;
	I2C_cf_1.I2C_ACK_Enable = I2C1_ACK;
	I2C_cf_1.I2C_ADDMODE = ADDRESS_LENGTH;
	I2C_cf_1.I2C_DualMode_ADD = ADDRESS_MODE;

/*------------------------------------------------------------------*/
#if ADDRESS_MODE == DUAL_ADDRESSES
	I2C_cf_1.I2C_Address_2=10;
#endif

#if ADDRESS_LENGTH == BIT10_ADDRESS
	I2C_cf_1.I2C_Address_1 = 10;
#else
	I2C_cf_1.I2C_Address_1 = 10;
#endif
/*--------------------------------------------------------------*/
};
