/*
 * Object_Controller.c
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */

#include"system_Main.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Data_Structure.h"
#include"DIO_config.h"
#include"RTE.h"
#include"object_Controller.h"

volatile u32 Object_SW_Time_In_ms;

Object_Data_Manger_t Object_Data_Manger;

Relay_t  Relays[NUMBER_RELAYS_ON_THIS_ECU];
Switch_t Switches[NUMBER_SWITCHS_ON_THIS_ECU];



static volatile u8 WIFI_Sequenc_Status;
static volatile u8 System_Mode;

void Object_Init(void)
{
	Object_Data_Manger.Object_App_Status = OBJECT_INTIOLIZATION_MODE;
	u8 Local_Return = NOT_DEFINE;

	if(Relay_Initilaizations(OBJECT_NO_1_ID_IN_LOCAL_ECU,OBJECT_NO_1_COMUNICATION_WIFI_ID,OBJECT_NO_1_RELAY,OBJECT_NO_1_SWITCH,OBJECT_NO_1_TIME) == SUCCESS && Local_Return != ERROR)
	{
		Local_Return = SUCCESS;
	}
	else
	{
		Local_Return = ERROR;
	}
	if(Relay_Initilaizations(OBJECT_NO_2_ID_IN_LOCAL_ECU,OBJECT_NO_2_COMUNICATION_WIFI_ID,OBJECT_NO_2_RELAY,OBJECT_NO_2_SWITCH,OBJECT_NO_2_TIME) == SUCCESS && Local_Return != ERROR)
	{
		Local_Return = SUCCESS;
	}
	else
	{
		Local_Return = ERROR;
	}

	if(Relay_Initilaizations(OBJECT_NO_3_ID_IN_LOCAL_ECU,OBJECT_NO_3_COMUNICATION_WIFI_ID,OBJECT_NO_3_RELAY,OBJECT_NO_3_SWITCH,OBJECT_NO_3_TIME) == SUCCESS && Local_Return != ERROR)
	{
		Local_Return = SUCCESS;
	}
	else
	{
		Local_Return = ERROR;
	}

	if(Local_Return == SUCCESS)
	{
		Object_Data_Manger.Object_App_Status = OBJECT_RUNNING_NORMAL;
	}
	else
	{
		Object_Data_Manger.Object_App_Status = OBJECT_ERROR;
	}

}

void Object_Polling(void)
{
	if(WIFI_Sequenc_Status == SYSTEM_ENABLE_SEQUENCE)
	{
		Object_Init_Objects_In_WIFI();
	}
	if(Object_Data_Manger.Object_App_Status == OBJECT_RUNNING_NORMAL)
	{

	}

	Object_Fetch_Message_From_Rte();
	Object_Fetch_Shared_Varaibles();

}

void Object_Periodic(void)
{
	Object_SW_Time_In_ms++;
	static volatile u16 should_be_Deleted = 400;

			if(Object_SW_Time_In_ms % should_be_Deleted == 0)  //50
			{
				if(System_Mode == WIFI_MODE)
				{

						Object_Status_Message_Send_Each_10ms();

				}
				else
				{

				}

			}

}

static u8 Relay_Initilaizations(u8 Object_ID_IN_Local_ECU,u8 Com_WIFI_ID,u8 Relay_Pin,u8 switch_Pin,u32 Time_to_Be_off_In_Seconds)
{
	u8 Local_Return = NOT_DEFINE;

	if(Object_Data_Manger.Relay_Counter <= NUMBER_RELAYS_ON_THIS_ECU && Object_Data_Manger.Switch_Counter <= NUMBER_SWITCHS_ON_THIS_ECU)
	{
		Relays[Object_Data_Manger.Relay_Counter].Object_WIFI_ID = Com_WIFI_ID;

		Relays[Object_Data_Manger.Relay_Counter].Object_Number_In_Status_Message = Object_ID_IN_Local_ECU;

		Relays[Object_Data_Manger.Relay_Counter].Output_PIN_ID = Relay_Pin;

		Relays[Object_Data_Manger.Relay_Counter].Timer_Referance = Time_to_Be_off_In_Seconds;

		Relays[Object_Data_Manger.Relay_Counter].Pointer_Switch = &Switches[Object_Data_Manger.Switch_Counter];

		Relays[Object_Data_Manger.Relay_Counter].Pointer_Switch->Input_PIN_ID = switch_Pin;

		Rte_PortControl_Pin_Init(Relay_Pin,0);
		Rte_PortControl_Pin_Level(Relay_Pin,0);
		//Rte_PortControl_Pin_Init(switch_Pin,PULL_UP);

		Object_Data_Manger.Relay_Counter++;

		Object_Data_Manger.Switch_Counter++;

		Local_Return = SUCCESS;
	}
	else
	{
		Local_Return = ERROR;
	}

	return Local_Return;

}

static void Object_Init_Objects_In_WIFI(void)
{
	static volatile u8 i = 0;

	if(Rte_Write_Message_0x14(Relays[i].Object_WIFI_ID,Relays[i].Object_Number_In_Status_Message))
	{

		if(i == (NUMBER_RELAYS_ON_THIS_ECU-1))
		{
			Rte_Write_WIFI_Sequenc_Variable(OBJECT_FINISHED_SEQUENCE);
		}
		i++;
	}

}

static void Object_Fetch_Shared_Varaibles(void)
{
	Rte_Read_WIFI_Sequenc_Variable(&WIFI_Sequenc_Status);
	Rte_Read_System_Mode(&System_Mode);
	Rte_Read_Status_ID(&Object_Data_Manger.Object_Status_ID);
}

static void Object_Fetch_Message_From_Rte(void)
{

	u8 Local_Array[10];

	if(Rte_Read_Message_0x10(Local_Array))
	{
		if(System_Mode == WIFI_MODE)
		{
			Object_Analize_Message_0x10(Local_Array);
		}
		else
		{

		}

	}


}



static void Object_Analize_Message_0x10(u8* Pointer_Data)
{
	/*Local Variables*/
	u8 Local_Data = 0;
	u8 Local_ID = 0 ;
	switch(Pointer_Data[1])
	{
	case OBJECT_TOGGLE:
		Local_ID = Pointer_Data[0];
		if(Get_Search_About_WIFI_ID(&Local_ID))
		{
			Rte_PortControl_Pin_Toggle(Local_ID);
		}
		break;
	case OBJECT_STATUS:
		/*
		if(Rte_PortControl_Pin_Read(Pointer_Data[0],&Local_Data))
		{

			if(Local_Data == 0)
			{
				Local_Data = OBJECT_OFF;

			}
			else
			{
				Local_Data = OBJECT_ON;
			}

			Object_Write_Message_0x11(Pointer_Data->Data[0],OBJECT_STATUS,Local_Data,0,0,0);
		}
		else
		{
			Object_Write_Message_0x11(Pointer_Data->Data[0],OBJECT_ERROR,OBJECT_ERROR,0,0,0);
		}
		 */
		break;

	case OBJECT_READING:

		break;

	default:

		break;
	}
}

static u8 Get_Search_About_WIFI_ID(u8 *Pointer_ID)
{
	u8 Local_Return = 0;
	for(u8 i=0 ; i < NUMBER_RELAYS_ON_THIS_ECU ;i++)
	{

		if(Relays[i].Object_WIFI_ID == *Pointer_ID)
		{
			*Pointer_ID = Relays[i].Output_PIN_ID;
			Local_Return = 1;
			break;
		}
		else
		{
			Local_Return = 0;
		}

	}
	return Local_Return;
}

static u8 Get_Object_Status(u8 *Pointer_Data)
{
	u8 Local_Data = 0;
	*Pointer_Data = 0;

	for(u8 i=0 ; i < NUMBER_RELAYS_ON_THIS_ECU ;i++)
	{

		Rte_PortControl_Pin_Read(Relays[i].Output_PIN_ID,&Local_Data);

		*Pointer_Data = (*Pointer_Data)|(Local_Data<<Relays[i].Object_Number_In_Status_Message);

	}
	return 1 ;
}

/********************Periodic Functions*****************************/
static void Object_Status_Message_Send_Each_10ms(void)
{
	u8 Local_Status = 0;
	if(Get_Object_Status(&Local_Status))
	{
		Rte_Write_Message_0x13(Local_Status,0,0,0,0,Object_Data_Manger.Object_Status_ID);
	}

}
/*************************************************/
