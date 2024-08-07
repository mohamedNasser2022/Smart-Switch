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
#include"Rte_Nvm_STD.h"

#include"LIB_ERROR.h"

#include"system_mode.h"
#include"DIO_config.h"
#include"RTE_Com_ServiceHost.h"
static volatile u32 system_time_ms;

Idt_Rec005 SSID;
Idt_Rec006 PASS;

static struct{
	volatile u8 System_Mode;
	volatile u8 Mode_Status;
	volatile u8 Nvm_State;

}System_Mode_Controller;

static volatile push_button_t Push_Button;

static volatile u8 WIFI_sequenc_status = 0;
static volatile u8 WIFI_Initialization_Sequence_Counter = 1;

void System_Init(void)
{
	System_Mode_Controller.System_Mode = INITIOLAZTION_MODE;

	Rte_Write_System_Mode(&System_Mode_Controller.System_Mode); /*Bypass*/

	Push_Button.Pin_ID = PIN_TO_RESET_SYSTEM_CONFIGRUTIONS;

	Push_Button.Button_Mode = BUTTON_NOT_PRESSED;
	Rte_PortControl_Pin_Init(Push_Button.Pin_ID,PULL_UP);

	MGPIO_voidSetPinDirection(Hardware_PIN16,OUTPUT_SPEED_2MHZ_PP); // Wifi Power Pin

	
	MGPIO_voidSetPinValue(Hardware_PIN16,1);
	MGPIO_voidSetPinValue(Hardware_PIN16,0);
	MSTK_voidSetBusyWait(1000000);


}

void system_Polling(void)
{




}

void system_Periodic(void)
{
	system_time_ms ++ ;
	Runnable_System_Read_Nvm_Data();
	if(system_time_ms % 10 == 0)
	{
		Push_Button_Task(); // Comes Each 10 ms

	}
	
	if(1 == System_Mode_Controller.Nvm_State)
	{
		Runnable_System_Mode_Wifi_Init();	
	}

	if(0 == system_time_ms % 500)
	{
		store_Wifi_data();  // check each 500 ms
	}

}

static void store_Wifi_data(void)
{
	Idt_Message_0x30_t Name;
	Idt_Message_0x31_t Password;
	if(Read_Done == Rte_Read_Message_0x31(&Password) && Read_Done == Rte_Read_Message_0x30(&Name))
	{
		Rte_Write_FD04(&Name); // Name
		Rte_Write_FD05(&Password); //Pass
	}

}

static void Runnable_System_Mode_Wifi_Init(void)
{
	volatile u8 Local_Array_Data[2];

	Rte_Read_System_Mode(&System_Mode_Controller.System_Mode);
	Idt_Message_0x03_t Local_Read_Message_0x03;
	Idt_Message_0x01_t Local_Write_Message_0x01;
	switch (System_Mode_Controller.System_Mode)
	{
	case INITIOLAZTION_MODE: /*Shall send Message 0x01 and wait Respond*/

		if (System_Mode_Controller.Mode_Status == UNDEFINED)
		{
			Local_Write_Message_0x01.Number_of_Relays = NUMBER_OF_RELAYS_INTERNAL_ON_CHIP;
			Local_Write_Message_0x01.Length_of_Status_Message = LENGHT_STATUS_OBJECT_ON_SYSTEM;
			Rte_Write_Message_0x01(&Local_Write_Message_0x01);
			
			System_Mode_Controller.Mode_Status = Sys_OnGoing;
		}
		else if(Sys_OnGoing == System_Mode_Controller.Mode_Status)
		{
			

			if(Read_Done == Rte_Read_Message_0x03(&Local_Read_Message_0x03))
			{
				if(Local_Read_Message_0x03.Respond == WIFI_OK && Local_Read_Message_0x03.System_Mode == INITIOLAZTION_MODE)
				{
					System_Mode_Controller.Mode_Status = Sys_Done;
				}
				else
				{
					System_Mode_Controller.Mode_Status = Sys_Faild;
				}

			}

		}
		else if(System_Mode_Controller.Mode_Status == Sys_Done)
		{
			System_Mode_Controller.System_Mode = SYSTEM_ENABLE_SEQUENCE;
			Rte_Write_System_Mode(&System_Mode_Controller.System_Mode);
			System_Mode_Controller.Mode_Status = UNDEFINED;

		}
		else if(System_Mode_Controller.Mode_Status == Sys_Faild)
		{

		}
		else
		{

		}
		break;
	case SYSTEM_ENABLE_SEQUENCE: 

		if(System_Mode_Controller.Mode_Status  == UNDEFINED)
		{
			WIFI_sequenc_status = SYSTEM_ENABLE_SEQUENCE;
			Rte_Write_WIFI_Sequenc_Variable(&WIFI_sequenc_status);
			System_Mode_Controller.Mode_Status = Sys_OnGoing;

		}
		else if(System_Mode_Controller.Mode_Status  == Sys_OnGoing)
		{
			if(Rte_Read_WIFI_Sequenc_Variable(&WIFI_sequenc_status))
			{
				if(WIFI_DONE == WIFI_sequenc_status)
				{
					
					System_Mode_Controller.Mode_Status = Sys_Done;
				}
				else
				{

				}

			}

		}
		else if(System_Mode_Controller.Mode_Status  == Sys_Done)
		{
			System_Mode_Controller.System_Mode = STAND_BY_MODE;
			Rte_Write_System_Mode(&System_Mode_Controller.System_Mode);
			System_Mode_Controller.Mode_Status = UNDEFINED;
			
		}
		else
		{

		}
		break;
	case STAND_BY_MODE:

		if(System_Mode_Controller.Mode_Status  == UNDEFINED)
		{
			
			Rte_Write_Message_0x20(&SSID);
			Rte_Write_Message_0x21(&PASS);
			System_Mode_Controller.Mode_Status = Sys_OnGoing;

		}
		else if(Sys_OnGoing == System_Mode_Controller.Mode_Status)
		{
			

			if(Read_Done == Rte_Read_Message_0x03(&Local_Read_Message_0x03))
			{
				if(Local_Read_Message_0x03.Respond == WIFI_OK && Local_Read_Message_0x03.System_Mode == WIFI_MODE_Stand_by)
				{
					System_Mode_Controller.Mode_Status = Sys_Done;
				}
				else
				{
					System_Mode_Controller.Mode_Status = Sys_Faild;
				}

			}
		}
		else if(System_Mode_Controller.Mode_Status  == Sys_Done)
		{
			System_Mode_Controller.System_Mode = WIFI_MODE_Stand_by;
			Rte_Write_System_Mode(&System_Mode_Controller.System_Mode);
			System_Mode_Controller.Mode_Status = UNDEFINED;

		}

		break;

		case WIFI_MODE_Stand_by:

			
			if(Read_Done == Rte_Read_Message_0x03(&Local_Read_Message_0x03))
			{
				if(Local_Read_Message_0x03.Respond == WIFI_OK && Local_Read_Message_0x03.System_Mode == WIFI_MODE)
				{
					System_Mode_Controller.System_Mode = WIFI_MODE;
					Rte_Write_System_Mode(&System_Mode_Controller.System_Mode);
				}
				else
				{
					
				}

			}
		

			break;

		case WIFI_MODE:

			

			if(Read_Done == Rte_Read_Message_0x03(&Local_Read_Message_0x03))
			{
				if(Local_Read_Message_0x03.Respond == WIFI_OK && Local_Read_Message_0x03.System_Mode == WIFI_MODE_Stand_by)
				{
					System_Mode_Controller.System_Mode = WIFI_MODE_Stand_by;
					Rte_Write_System_Mode(&System_Mode_Controller.System_Mode);
				}
				else
				{
					
				}

			}
		

			break;
	
	default:
		break;
	}


}

static void Runnable_System_Read_Nvm_Data(void)
{
	if(0 == System_Mode_Controller.Nvm_State)
	{
		if(Read_Done == Rte_Read_FD04(&SSID) && Read_Done ==  Rte_Read_FD05(&PASS))
		{
			System_Mode_Controller.Nvm_State = 1;
		}
		else
		{

		}
		
	}
}


/*****************************************************Message Writing*******************************************************/


/*****************************************************Message Writing*****Ending**************************************************/


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
				//Rte_Write_System_Mode(INITIOLAZTION_MODE); // Write this to start Init Sequenc for WIFI
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
