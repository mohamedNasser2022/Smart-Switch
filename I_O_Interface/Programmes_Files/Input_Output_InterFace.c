/*
 * Input_Output_InterFace.c
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */
#include"system_Main.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Data_Structure.h"


#include"RTE.h"
#include"DIO_Expander_Interface.h"
#include"DIO_interface.h"

#include "Input_Output_Private.h"
#include"Input_Output_Configuration.h"
#include"Input_Output_Interface.h"

struct
{
	u8 Access_request:1;
	u8 PIN_ID;
	u8 PORT;
}I_O_Controller;


volatile u8 X ;

void I_O_Interface_Initialization(void)
{
	DIO_Expander_Initialization();


}

void I_O_Interface_Polling(void)
{
	DIO_Expander_Polling();
}

void I_O_Interface_Periodic(void)
{
	DIO_Expander_Time();
}

u8 I_O_Interface_Init_Pin(u8 copy_Pin_ID,u8 copy_Pin_Mode)
{
	u8 Local_Return = 1;

	if(I_O_Controller.Access_request == 0)
	{
		I_O_Controller.Access_request = 1;

		if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_ON_BOARD )
		{

			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				MGPIO_voidSetPinDirection(I_O_Controller.PORT,I_O_Controller.PIN_ID,copy_Pin_Mode);
			}
			else
			{
				Local_Return = 0;
			}

		}
		else if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_EXPANDER_BOARD)
		{
			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				DIO_Expander_Set_Pin_Mode(I_O_Controller.PIN_ID,copy_Pin_Mode);
			}
			else
			{
				Local_Return = 0;
			}

		}
		else
		{
			Local_Return = 0;
		}
		I_O_Controller.Access_request = 0;
	}
	else
	{
		Local_Return = 0;
	}


	return Local_Return;
}



u8 I_O_Interface_set_Pin_Level(u8 copy_Pin_ID,u8 copy_Pin_Level)
{
	u8 Local_Return = 1;

	if(I_O_Controller.Access_request == 0)
	{
		I_O_Controller.Access_request = 1;

		if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_ON_BOARD )
		{

			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				MGPIO_voidSetPinValue(I_O_Controller.PORT,I_O_Controller.PIN_ID,copy_Pin_Level);
			}
			else
			{
				Local_Return = 0;
			}



		}
		else if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_EXPANDER_BOARD)
		{
			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				DIO_Expander_Set_Pin_Level(I_O_Controller.PIN_ID,copy_Pin_Level);
			}
			else
			{
				Local_Return = 0;
			}

		}
		else
		{
			Local_Return = 0;
		}
		I_O_Controller.Access_request = 0;
	}
	else
	{
		Local_Return = 0;
	}


	return Local_Return;
}


u8 I_O_Interface_Read_Pin_Level(u8 copy_Pin_ID,u8* Location_of_Pin_State_Level_Save)
{

	u8 Local_Return = 1;

	if(I_O_Controller.Access_request == 0)
	{
		I_O_Controller.Access_request = 1;

		if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_ON_BOARD )
		{

			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				*Location_of_Pin_State_Level_Save = MGPIO_u8GetPinValue(I_O_Controller.PORT,I_O_Controller.PIN_ID);
			}
			else
			{
				Local_Return = 0;
			}



		}
		else if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_EXPANDER_BOARD)
		{
			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				*Location_of_Pin_State_Level_Save	= DIO_Expander_Read_Pin(I_O_Controller.PIN_ID);
			}
			else
			{
				Local_Return = 0;
			}

		}
		else
		{
			Local_Return = 0;
		}
		I_O_Controller.Access_request = 0;
	}
	else
	{
		Local_Return = 0;
	}


	return Local_Return;
}

u8 I_O_Interface_Toggle_Pin(u8 copy_Pin_ID)
{
	u8 Local_Return = 1;

	if(I_O_Controller.Access_request == 0)
	{
		I_O_Controller.Access_request = 1;

		if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_ON_BOARD )
		{
			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				MGPIO_voidTogglePin(I_O_Controller.PORT,I_O_Controller.PIN_ID);
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(copy_Pin_ID <= MAX_NUMBER_OF_DIO_EXPANDER_BOARD)
		{
			if(IO_Hardware_Switching_on_Input_Number(copy_Pin_ID))
			{
				DIO_Expander_Toggle(I_O_Controller.PIN_ID);
			}
			else
			{
				Local_Return = 0;
			}

		}
		else
		{
			Local_Return = 0;
		}
		I_O_Controller.Access_request = 0;
	}
	else
	{
		Local_Return = 0;
	}
	return Local_Return;
}

static u8 IO_Hardware_Switching_on_Input_Number(u8 copy_Pin_ID)
{
	u8 Local_Return = 1;
	switch(copy_Pin_ID)
	{
		case VIRTUAL_PIN_0:
			Splite_into_ports_and_Pins(INPUT_OUTPUT_PIN_0_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_1:
			Splite_into_ports_and_Pins(INPUT_OUTPUT_PIN_1_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_2:
			Splite_into_ports_and_Pins(INPUT_OUTPUT_PIN_2_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_3:
			Splite_into_ports_and_Pins(INPUT_OUTPUT_PIN_3_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_4:
			Splite_into_ports_and_Pins(INPUT_OUTPUT_PIN_4_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_5:
			Splite_into_ports_and_Pins(INPUT_OUTPUT_PIN_5_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_6:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_6_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_7:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_7_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_8:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_8_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_9:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_9_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_10:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_10_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_11:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_11_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_12:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_12_DIO_PHYSICAL);
		break;
		case VIRTUAL_PIN_13:
			Splite_into_ports_and_Pins(PORTS_DONT_CARE,INPUT_OUTPUT_PIN_13_DIO_PHYSICAL);
		break;
		}
	return Local_Return;
}

static void Splite_into_ports_and_Pins(u8 copy_Port,u8 copy_ID)
{
	I_O_Controller.PIN_ID = copy_ID;
	I_O_Controller.PORT = copy_Port;
}
