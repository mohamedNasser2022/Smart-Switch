/*
 * I2C_Manger.c
 *
 *  Created on: Jan 25, 2023
 *      Author: Mohamed Nasser
 */

#include"Data_Structure.h"
#include"I2C_Manger.h"
#include"Queue_Interface.h"

#define SUCCESS  1
#define ERROR    0

static Comuncation_Manger_Interface_Nested Buffer_I2C_Data_to_be_Send;

void I2C_Manger_Init(void)
{
	Nested_Queue0_Create(&Buffer_I2C_Data_to_be_Send);
	I2C_Init();
}

void I2C_Manger_Polling(void)
{

	I2C1_Polling();
}


u8 Comuncation_Manger_Send_Data_to_I2C_Buffer(Comuncation_Manger_Interface* Pointer_To_Data)
{
	u8 Local_Return = 0;
	if(Nested_Queue0_Push(&Buffer_I2C_Data_to_be_Send,Pointer_To_Data))
	{
		Local_Return =  SUCCESS;

	}
	else
	{
		Local_Return = ERROR;
	}
	return Local_Return;
}



static void I2C_Manger_Send_Data_to_I2C_Hardware(void)
{
	u8 Fetch_Local_Addresses = 0;
	u8 Comuncation_Destine = 0;
	Comuncation_Manger_Interface Local_Queue;
	Queue0_Create(&Local_Queue);

	Nested_Queue0_Pop(&Buffer_I2C_Data_to_be_Send,&Local_Queue);

	Queue0_Pop(&Local_Queue,&Fetch_Local_Addresses);
	Queue0_Pop(&Local_Queue,&Comuncation_Destine);

	I2C_Push_Data_To_Buffer(Comuncation_Destine,Fetch_Local_Addresses,&Local_Queue); // Log is Wrong



}
