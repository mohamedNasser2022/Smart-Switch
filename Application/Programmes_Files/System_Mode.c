/*
 * System_Mode.c
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */

#include"system_Main.h"
#include"STD_TYPES.h"
#include"Data_Structure.h"
#include"RTE.h"
#include"LIB_ERROR.h"

#include"system_mode.h"
#include"DIO_config.h"
static volatile u32 system_time_ms;

u8 SSID[] = "Thorn";
u8 PASS[] = "abdalaze0m1WMA19";

static volatile push_button_t Push_Button;
static volatile u8 WIFI_Trigger_Mode = 0;
static volatile u8 WIFI_sequenc_status = 0;
static volatile u8 WIFI_Initialization_Sequence_Counter = 1;
void System_Init(void)
{
	Push_Button.Pin_ID = PIN_TO_RESET_SYSTEM_CONFIGRUTIONS;
	Push_Button.Button_Mode = BUTTON_NOT_PRESSED;
	Rte_PortControl_Pin_Init(Push_Button.Pin_ID,PULL_UP);





}


void system_Polling(void)
{


	if(WIFI_Trigger_Mode == INITIOLAZTION_MODE )
	{
		System_Init_WIFI_Mode_Sequence();

	}
	else
	{

	}
	System_Fetch_Messages();
	System_Fetch_Shared_Variables();

}

void system_Periodic(void)
{
	system_time_ms ++ ;

	if(system_time_ms % 10 == 0)
	{
		Push_Button_Task(); // Comes Each 10 ms

	}

}

static void System_Init_WIFI_Mode_Sequence(void)
{


	switch(WIFI_Initialization_Sequence_Counter)
	{
	case  1:

		Rte_Write_Message_0x02(INITIOLAZTION_MODE);
		WIFI_Initialization_Sequence_Counter ++;
		WIFI_Initialization_Sequence_Counter +=50;

		break;

	case 2:

		Rte_Write_Message_0x01(NUMBER_RELAYS_ON_THIS_ECU,1,5);

		WIFI_Initialization_Sequence_Counter ++;
		WIFI_Initialization_Sequence_Counter +=50;

		break;
	case 3:

		Rte_Write_WIFI_Sequenc_Variable(SYSTEM_ENABLE_SEQUENCE);

		WIFI_Initialization_Sequence_Counter ++;
		WIFI_Initialization_Sequence_Counter +=50;

		break;
	case 4:

		Rte_Write_Message_0x02(STAND_BY_MODE);

		WIFI_Initialization_Sequence_Counter ++;
		WIFI_Initialization_Sequence_Counter +=50;
		break;
	case 5:

		Rte_Write_Message_0x20(SSID);
		Rte_Write_Message_0x21(PASS);
		WIFI_Initialization_Sequence_Counter ++;
		WIFI_Initialization_Sequence_Counter +=50;

		break;


	default :
		break;

	}

}

static void System_Fetch_Shared_Variables(void)
{
	if(Rte_Read_WIFI_Sequenc_Variable(&WIFI_sequenc_status))
	{
		if(WIFI_sequenc_status == OBJECT_FINISHED_SEQUENCE)
		{
			Rte_Write_WIFI_Sequenc_Variable(UNDEFINED);
			WIFI_Initialization_Sequence_Counter -=50;
		}
	}
	Rte_Read_System_Mode(&WIFI_Trigger_Mode);
}

static void System_Fetch_Messages(void)
{
	u8 Local_Array_Data[10];

	if(Read_Done == Rte_Read_Message_0x03(&Local_Array_Data[0],&Local_Array_Data[1]))
	{
		System_Mode_Message_0x03_Analize(Local_Array_Data);
	}
}

/*****************************************************Message Writing*******************************************************/


/*****************************************************Message Writing*****Ending**************************************************/

static void System_Mode_Message_0x03_Analize(u8* Pointer_Data)
{
	u8 Local_Check = 1;

	u8 Local_System_mode ;


	if(Pointer_Data[0] == WIFI_OK && Pointer_Data[1] == INITIOLAZTION_MODE)
	{

		Rte_Write_Status_ID(Pointer_Data[2]);
	}
	else if(Pointer_Data[0] == WIFI_OK && Pointer_Data[1] == NUMBER_RELAYS_ON_THIS_ECU)
	{

	}
	else if(Pointer_Data[0] == WIFI_OK && Pointer_Data[1] == STAND_BY_MODE)
	{
		//Rte_Write_System_Mode(STAND_BY_MODE);
		Rte_Write_WIFI_Sequenc_Variable(WIFI_FINISHED_SEQUENCE);

	}
	else if(Pointer_Data[0] == WIFI_OK && Pointer_Data[1] == WIFI_MODE)
	{
		Rte_Write_System_Mode(WIFI_MODE);

		WIFI_Initialization_Sequence_Counter -=100;

	}
	else
	{
		Local_Check = 0;
		//Rte_Write_System_Mode(STAND_BY_MODE);
	}

	if(Local_Check == 1 )
	{
		WIFI_Initialization_Sequence_Counter -=50;
	}
	else
	{

	}

}

static void Push_Button_Task(void)
{

	u8 Local_Read ;
	Rte_PortControl_Pin_Read(Push_Button.Pin_ID,&Local_Read);

	Push_Button.Button_Current_Status  = Local_Read;

	switch(Push_Button.Button_Mode)
	{

	case BUTTON_NOT_PRESSED:

		if(Push_Button.Button_Current_Status == BUTTON_PRESSED && Push_Button.Button_Pervious_Status == BUTTON_NOT_PRESSED)
		{
			// Button is pressed
			Push_Button.Button_Mode = BUTTON_PRESSED;
		}
		break;

	case BUTTON_PRESSED:

		Push_Button.Button_Time_Counter_ms += 10;

		if(Push_Button.Button_Time_Counter_ms == 300)
		{

			if(Push_Button.Button_Current_Status == BUTTON_PRESSED && Push_Button.Button_Pervious_Status == BUTTON_PRESSED)
			{
				Push_Button.Button_Mode = BUTTON_CONFIRMED_PRESSED;
			}
			else
			{
				Push_Button.Button_Mode = BUTTON_NOT_PRESSED;
				Push_Button.Button_Time_Counter_ms = 0;

			}
		}
		break;

	case BUTTON_CONFIRMED_PRESSED:

		Push_Button.Button_Time_Counter_ms += 10;  // Start count time

		if(Push_Button.Button_Current_Status == BUTTON_NOT_PRESSED && Push_Button.Button_Pervious_Status == BUTTON_PRESSED)
		{
			Push_Button.Button_Mode = BUTTON_NOT_PRESSED;
			if(Push_Button.Button_Time_Counter_ms >= 3000 && Push_Button.Button_Time_Counter_ms <= 7000)
			{
				Rte_Write_System_Mode(INITIOLAZTION_MODE); // Write this to start Init Sequenc for WIFI
			}
			else if(Push_Button.Button_Time_Counter_ms >= 10000 && Push_Button.Button_Time_Counter_ms <= 16000)
			{

			}
			else
			{

			}
			Push_Button.Button_Time_Counter_ms = 0;
		}

		break;

	}
	Push_Button.Button_Pervious_Status = Push_Button.Button_Current_Status;
}
