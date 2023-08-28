/*
 * DIO_Expander_Comunication_Layer.c
 *
 *  Created on: Jun 4, 2023
 *      Author: Mohamed Nasser
 */


#include"DIO_Expander_Private.h"
#include"DIO_Expander_Interface.h"
#include"DIO_Expander_Config.h"

#include"DIO_Expander_Comunication_Layer_interface.h"

#include"Queue_Interface.h"
#include"I2C_Interface.h"


/*----------Typedef----------------*/

struct
{
	u8 Expander_MODE:2;

}DIO_Expander_System_Mode;

enum
{
	Undefined,
	Normal,
	Reset,
	Faild,
	Wait,
	Busy,
	True,
	False,
}System_Mode;

static Nested_Queue_3 Buffer_Sending_Data;
volatile u32 DIO_Expander_System_Time_ms;


/*------------*/


void DIO_Expander_Com_Initialization(void)
{

	Nested_Queue3_Create(&Buffer_Sending_Data);
	DIO_Expander_System_Mode.Expander_MODE = Reset;
	MGPIO_voidSetPinDirection(Hardware_PIN28,OUTPUT_SPEED_2MHZ_PP);

}


void DIO_Expander_Com_Polling(void)
{

	DIO_Expander_Com_Check_If_Updates_Needed();
	DIO_Expander_Com_Check_Buffer_And_Send_Data_To_Physical_Layer();
	//test();
}

static void DIO_Reseting(void)
{
	static volatile u8 Local_Counter = 0;
	if(0 == Local_Counter)
	{
		MGPIO_voidSetPinValue(Hardware_PIN28,1);
		Local_Counter++;
	}
	else if(1 == Local_Counter)
	{
		MGPIO_voidSetPinValue(Hardware_PIN28,0);
		Local_Counter = 0;
		DIO_Expander_System_Mode.Expander_MODE = Normal;
	}



}


void DIO_Expander_Com_Time(void)
{
	DIO_Expander_System_Time_ms ++;
	if(Normal == DIO_Expander_System_Mode.Expander_MODE)
	{
		if(DIO_Expander_System_Time_ms % 10 == 0)
		{
			Request_of_Reading(Address_RegDataB,25);
		}
	}
	else if(Reset == DIO_Expander_System_Mode.Expander_MODE)
	{
		DIO_Reseting();
	}



}

/*-----------------------------------Private Functions------------------------------------------------------*/

static void DIO_Expander_Com_Check_If_Updates_Needed(void)
{
	Array_Of_Queue_3  Local_Data;
	Queue3_Create(&Local_Data);
//	Local_Data.Address =  DIO_Expander_ADDRESS;   // push Addresses here

	if(Flags.Flag_Updates != NO_UPDATES_NEEDED)
	{
		if(UPDATES_NEEDED == Flags.Flags_Update_Bit_Level.Set_Direction_Called)
		{

			Queue3_Push(&Local_Data,Address_RegDirB);
			Queue3_Push(&Local_Data,DIO_Registers_Data.RegDirB);
			Queue3_Push(&Local_Data,DIO_Registers_Data.RegDirA);

			if(Nested_Queue3_Full(&Buffer_Sending_Data) != 1)
			{
				Nested_Queue3_Push(&Buffer_Sending_Data,&Local_Data);
			}

			Queue3_Push(&Local_Data,Address_RegDebounceEnableB);
			Queue3_Push(&Local_Data,DIO_Registers_Data.RegDebounceEnableB);
			Queue3_Push(&Local_Data,DIO_Registers_Data.RegDebounceEnableA);

			if(Nested_Queue3_Full(&Buffer_Sending_Data) != 1)
			{
				Nested_Queue3_Push(&Buffer_Sending_Data,&Local_Data);
			}
			Flags.Flags_Update_Bit_Level.Set_Direction_Called = NO_UPDATES_NEEDED;
		}
		if(UPDATES_NEEDED == Flags.Flags_Update_Bit_Level.Set_Pin_Level_Called)
		{
			Queue3_Push(&Local_Data,Address_RegDataB);
			Queue3_Push(&Local_Data,DIO_Registers_Data.RegDataB);
			Queue3_Push(&Local_Data,DIO_Registers_Data.RegDataA);

			if(Nested_Queue3_Full(&Buffer_Sending_Data) != 1)
			{
				Nested_Queue3_Push(&Buffer_Sending_Data,&Local_Data);
			}

			Flags.Flags_Update_Bit_Level.Set_Pin_Level_Called = NO_UPDATES_NEEDED;

		}
	}
}

static void DIO_Expander_Com_Check_Buffer_And_Send_Data_To_Physical_Layer(void)
{
	Array_Of_Queue_3  Local_Data;
	Queue3_Create(&Local_Data);

	if(Nested_Queue3_Pop(&Buffer_Sending_Data,&Local_Data))
	{
		if(I2C_Request_Sent == Push_Data_to_I2C_Sending_Buffer_Perpherial_1(DIO_Expander_ADDRESS,&Local_Data))  /* You have to get address first */
		{

		}
		else
		{
			Nested_Queue3_Undo_Last_Pop(&Buffer_Sending_Data);
		}
	}





}

static u8 Request_of_Reading(u8 copy_Reading_Starting_from,u8 Lenght_of_Reading)
{
	volatile u8 Local_Return = 1;

	Array_Of_Queue_3  Local_Data;
	Queue3_Create(&Local_Data);

	if(0 == DIO_Expander_Reading_Controller.Reading_On_Going) // Make sure no reading flag on going
	{
		if(Reconfigure_Read_Pointer(copy_Reading_Starting_from))
		{
			Queue3_Push(&Local_Data,copy_Reading_Starting_from);
			if(0 != DIO_Expander_Reading_From_Chip(&Local_Data,Lenght_of_Reading,Notification_Handler_I2C))
			{
				DIO_Expander_Reading_Controller.Reading_On_Going = 1;
			}
		}
		else
		{

		}

	}
	else
	{

	}


}

static u8 Reconfigure_Read_Pointer(u8 Register_Address)
{
	u8 Local_Return = 1;

	if(Register_Address <= END_OF_ADDRESSES)
	{
		DIO_Expander_Reading_Controller.Read_Pointer = (&DIO_Registers_Data.RegInputDisableB + Register_Address);
	}
	else
	{
		Local_Return = 0;	//Do nothing
	}

	return Local_Return ;
}

static void Notification_Handler_I2C(void* ptr)
{
	u8 Local_Data ;
	if(1 == DIO_Expander_Reading_Controller.Reading_On_Going)
	{
		while(Queue3_Pop(ptr,&Local_Data))
		{
			*DIO_Expander_Reading_Controller.Read_Pointer = Local_Data;

			DIO_Expander_Reading_Controller.Read_Pointer++;
		}
		DIO_Expander_Reading_Controller.Reading_On_Going = 0;
	}
	else
	{

	}
}


/*-----------------------------------------------------------------------------------------------------*/
