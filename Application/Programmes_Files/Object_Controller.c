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

#include"RTE_Com_ServiceHost.h"

#include"object_Controller.h"

volatile u32 Object_SW_Time_In_ms;

Object_Data_Manger_t Object_Data_Manger;

volatile Relay_t  Relays[NUMBER_OF_RELAYS_INTERNAL_ON_CHIP];
volatile Switch_t Switches[NUMBER_OF_RELAYS_INTERNAL_ON_CHIP];

/*-------------------------------------------------------------------*/

static volatile u8 Local_Relays_Status[8];
static volatile u8 Local_Switches_Status[8];
static u8 Struct_Status_Write_Valus(u8 *Struct_Pointer,u16 copy_Bit_ID,u8 copy_Level);
static u8 Struct_Status_Get_Valus(u8 *Struct_Pointer,u16 copy_Bit_ID,u8 *Pointer_Value);
/*-------------------------------------------------------------------*/




static volatile u8 WIFI_Sequenc_Status;
static volatile u8 System_Mode;

void Object_Init(void)
{
	Object_Data_Manger.Object_App_Status = OBJECT_INTIOLIZATION_MODE;
	u8 Local_Return = SUCCESS;


	Local_Return = Object_Relays_Switches_Initialization();

	if(Local_Return == SUCCESS)
	{
		Object_Data_Manger.Object_App_Status = Nvm_Read_Mode;
	}
	else
	{
		Object_Data_Manger.Object_App_Status = OBJECT_ERROR;
	}

}

void Object_Polling(void)
{


}

void Object_Periodic(void)
{
	Object_SW_Time_In_ms++;
	static  u16 should_be_Deleted = 400;
	switch (Object_Data_Manger.Object_App_Status)
	{
	case OBJECT_RUNNING_NORMAL  :

		if(Object_SW_Time_In_ms % 10 == 0)  //50
		{
			Runnable_Object_Update_Relays_And_Switch_Status_10ms();
		}
		if(Object_SW_Time_In_ms % 5 == 0)
		{
			Runnable_Object_Message_0x10_5ms();
		}
		if(Object_SW_Time_In_ms % 10 == 0)
		{
			Runnable_Object_Time_Data_Update();
		}

		break;
	case Nvm_Read_Mode :

		Runnable_Load_Nvm_Data();
		break;
	default:
		break;
	}
	
	if(Object_SW_Time_In_ms % 10 == 0)
	{
		Runnable_Object_Init_Objects_In_WIFI_10ms();
		Runnable_Object_Read_Inputs_Pins_And_Update_Output_Each_10ms();
	}
	if(Object_SW_Time_In_ms % 50 == 0)
	{
		Runnable_Object_Auto_Off_50ms();
	}
	
}

u8 Relay_Initilaizations(u8 Object_ID_IN_Local_ECU,u8 Com_WIFI_ID,u8 Relay_Pin,u8 switch_Pin,u32 Time_to_Be_off_In_Seconds)
{
	u8 Local_Return = NOT_DEFINE;

	if(Object_Data_Manger.Relay_Counter <= NUMBER_OF_RELAYS_INTERNAL_ON_CHIP && Object_Data_Manger.Switch_Counter <= NUMBER_OF_RELAYS_INTERNAL_ON_CHIP)
	{
		Relays[Object_Data_Manger.Relay_Counter].Object_WIFI_ID = Com_WIFI_ID;

		Relays[Object_Data_Manger.Relay_Counter].Object_Number_In_Status_Message = Object_ID_IN_Local_ECU;

		Relays[Object_Data_Manger.Relay_Counter].Output_PIN_ID = Relay_Pin;

		Relays[Object_Data_Manger.Relay_Counter].Timer_Referance_Mins = Time_to_Be_off_In_Seconds;

		Relays[Object_Data_Manger.Relay_Counter].Pointer_Switch = &Switches[Object_Data_Manger.Switch_Counter];

		Relays[Object_Data_Manger.Relay_Counter].Pointer_Switch->Input_PIN_ID = switch_Pin;

		Rte_PortControl_Pin_Init(Relay_Pin,OUTPUT_SPEED_2MHZ_PP);
		Rte_PortControl_Pin_Level(Relay_Pin,GPIO_LOW);
		Rte_PortControl_Pin_Init(switch_Pin,PULL_UP);

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

/**
 * WI-2006
 * Description : Runnable_Object_Time_Data_Update 
 * this function shall called each 10 ms and update timeoff for each object in system to report it to WIFI Module 
 * function call : periodic each 10 ms
*/

static void Runnable_Object_Time_Data_Update(void)
{	
	static u8 counter = 0;

	Idt_Message_0x15_t Local_Message;

	Rte_Read_System_Mode(&System_Mode);  /* Reading system mode */

	if(WIFI_MODE == System_Mode)
	{
		
		
		Local_Message.Object_ID   = Relays[counter].Object_WIFI_ID;
		Local_Message.Object_Data = Relays[counter].Timer_Referance_Mins;
		Rte_Write_Message_0x15(&Local_Message);
		counter ++;

		if(counter == NUMBER_OF_RELAYS_INTERNAL_ON_CHIP)
		{
			counter = 0;
		}
		else
		{

		}

		

	}

}

static void Runnable_Object_Init_Objects_In_WIFI_10ms(void)
{
	static volatile u8 i = 0;
	Rte_Read_WIFI_Sequenc_Variable(&WIFI_Sequenc_Status);

	if(WIFI_Sequenc_Status == SYSTEM_ENABLE_SEQUENCE)
	{
		Idt_Message_0x14_t Local_Message_0x14;
		Local_Message_0x14.Object_ID = Relays[i].Object_WIFI_ID;
		Local_Message_0x14.Object_Number_In_Status_Message = Relays[i].Object_Number_In_Status_Message;

		if(Write_Done == Rte_Write_Message_0x14(&Local_Message_0x14))
		{
			if(i == (NUMBER_OF_RELAYS_INTERNAL_ON_CHIP-1))
			{
				WIFI_Sequenc_Status = OBJECT_FINISHED_SEQUENCE;
				Rte_Write_WIFI_Sequenc_Variable(&WIFI_Sequenc_Status);
			}
			i++;
		}
	}
	else if(WIFI_Sequenc_Status == OBJECT_FINISHED_SEQUENCE)
	{
		
		Idt_Message_0x03_t Local_Message_0x03; 
		if(Read_Done == Rte_Read_Message_0x03(&Local_Message_0x03))
		{
			if(WIFI_OK == Local_Message_0x03.Respond && 0x14 == Local_Message_0x03.System_Mode)
			{
				WIFI_Sequenc_Status = WIFI_DONE;
				Rte_Write_WIFI_Sequenc_Variable(&WIFI_Sequenc_Status);
			}
			else if(WIFI_ERROR == Local_Message_0x03.Respond && 0x14 == Local_Message_0x03.System_Mode)
			{
				WIFI_Sequenc_Status = WIFI_ERROR;
				Rte_Write_WIFI_Sequenc_Variable(&WIFI_Sequenc_Status);
			}
			else
			{
				WIFI_Sequenc_Status = UNDEFINED;
				Rte_Write_WIFI_Sequenc_Variable(&WIFI_Sequenc_Status);
			}

		}

	}
	else
	{

	}




}

static void Runnable_Object_Auto_Off_50ms(void)
{
	/* 
		this runnables comes each 50 ms and check and count time for each relay
		Rte Interface : Rte_PortControl_Pin_Read()
						Rte_PortControl_Pin_Level()
	 */

	u8 Local_Relay_State;

	for(u8 i=0 ; i < NUMBER_OF_RELAYS_INTERNAL_ON_CHIP ;i++)
	{
		if( 0 != Relays[i].Timer_Referance_Mins )
		{
			Rte_PortControl_Pin_Read(Relays[i].Output_PIN_ID,&Local_Relay_State);

			if(1 == Local_Relay_State)
			{
				u32 Local_Time_Compare_in_Second = Relays[i].Timer_Referance_Mins * 60000; //Time Referance in mins covert to msecond
				Relays[i].Time_Counter += 50;

				if(Relays[i].Time_Counter >= Local_Time_Compare_in_Second)
				{
					Rte_PortControl_Pin_Level(Relays[i].Output_PIN_ID,0); 
					Relays[i].Time_Counter = 0;
				}
				else
				{
					//Relays[i].Time_Counter = 0;
				}

			}

		}
	}
}

static void Runnable_Load_Nvm_Data(void)
{
	/*
	This Runnable using to load last data to each object
	*/


	u8 Local_Relay_Struct[8];
	u8 Local_Switch_Struct[8];
	u8 Local_Relay_Status;
	u8 Local_Switch_Status;
	u8 Local_Current_Switch_Status;

	if(E_OK == Rte_Read_FD02(&Local_Relay_Struct) && E_OK == Rte_Read_FD03(&Local_Switch_Struct))
	{
		for(u8 i=0 ; i < NUMBER_OF_RELAYS_INTERNAL_ON_CHIP ;i++)
		{
			Struct_Status_Get_Valus(&Local_Relay_Struct,Relays[i].Object_Number_In_Status_Message,&Local_Relay_Status);
			Struct_Status_Get_Valus(&Local_Switch_Struct,Relays[i].Object_Number_In_Status_Message,&Local_Switch_Status);

			Relays[i].Pointer_Switch->Last_State_Pin = Local_Switch_Status; /* Restor Last Status*/

			Rte_PortControl_Pin_Read(Relays[i].Pointer_Switch->Input_PIN_ID,&Local_Current_Switch_Status);

			if(Local_Switch_Status != Local_Current_Switch_Status && 1 == Local_Relay_Status)
			{
				
				Rte_PortControl_Pin_Level(Relays[i].Output_PIN_ID,0);  // Off if there isn't equal

				Relays[i].Pointer_Switch->Current_State_Pin = Local_Current_Switch_Status;
				Relays[i].Pointer_Switch->Last_State_Pin = Local_Current_Switch_Status;
			}
			else if(1 == Local_Relay_Status)
			{
				Rte_PortControl_Pin_Level(Relays[i].Output_PIN_ID,1); // On if there isn't equal
			}
			else
			{
				Rte_PortControl_Pin_Level(Relays[i].Output_PIN_ID,0); 
			}

		}

		Object_Data_Manger.Object_App_Status = OBJECT_RUNNING_NORMAL;

	}

}

/*
 *	Runnable_Object_Message_0x10_5ms(void)
 *	WI #022 
*/

static void Runnable_Object_Message_0x10_5ms(void)
{
	/*Local Variables*/
	

	volatile u8 Local_Pin_State = 0;
	volatile Relay_t* Local_Relay;
	volatile Idt_Message_0x10_t Local_Message_0x10;
	if(Read_Done == Rte_Read_Message_0x10(&Local_Message_0x10))
	{
		switch(Local_Message_0x10.Command)
		{
		case Toggle_Command:



			/*Data[0] contain Wi-Fi ID of object*/
			if(Get_Search_About_WIFI_ID(Local_Message_0x10.Object_ID,&Local_Relay))
			{
				Rte_PortControl_Pin_Toggle(Local_Relay->Output_PIN_ID);
				Rte_PortControl_Pin_Read(Local_Relay->Output_PIN_ID,&Local_Pin_State);

				if(0 == Local_Pin_State)
				{
					/*this means object become off*/
					Local_Relay->Time_Counter = 0;
				}
			}
			break;
		case Request_Status:

			break;

		case Request_Reading:

			break;
		case Request_Time_Ref_Read:
			// WI #013 
			if(Get_Search_About_WIFI_ID(Local_Message_0x10.Object_ID,&Local_Relay))
			{
				Idt_Message_0x11_t Local_Message_0x11;

				volatile u8 Local_Time_Ref_Data = Local_Relay->Timer_Referance_Mins; 

				Local_Message_0x11.Object_ID = Local_Message_0x10.Object_ID; /*Object ID*/
				Local_Message_0x11.Command = Respond_Message;
				Local_Message_0x11.Time_In_Mins = ((u8) Local_Time_Ref_Data) ;
				
				Rte_Write_Message_0x11(&Local_Message_0x11);


			}

			break;
		case Time_Change:
			if(Get_Search_About_WIFI_ID(Local_Message_0x10.Object_ID,&Local_Relay))
			{

				 Local_Relay->Timer_Referance_Mins = Local_Message_0x10.Time_In_Mins ;
				 								

			}
			break;

		default:

			break;
		}

	}

}

static u8 Get_Search_About_WIFI_ID(u8 copy_ID,Relay_t** Pointer_Relay)
{
	volatile u8 Local_Return = 0;

	for(u8 i=0 ; i < NUMBER_OF_RELAYS_INTERNAL_ON_CHIP ;i++)
	{

		if(Relays[i].Object_WIFI_ID == copy_ID)
		{
			*Pointer_Relay = &Relays[i];
			Local_Return= 1 ;

			break;
		}
		else
		{
			Local_Return = 0;
		}

	}
	return Local_Return;
}


static void Runnable_Object_Read_Inputs_Pins_And_Update_Output_Each_10ms(void)
{	/*

	this Runnable read input pins which control certain relay based on configuration 
	and depend on reading this runnable will make relay on/off
	Rte interface : Rte_PortControl_Pin_Read(PIN_ID,POINTER) 
					Rte_PortControl_Pin_Level(PIN_ID,LEVEL)

 */
	u8 Local_Data = 0;

	for(u8 i = 0;i <NUMBER_OF_RELAYS_INTERNAL_ON_CHIP;i++)
	{
		Rte_PortControl_Pin_Read(Relays[i].Pointer_Switch->Input_PIN_ID,&Local_Data);
		Relays[i].Pointer_Switch->Current_State_Pin = Local_Data;

		if((1 == Relays[i].Pointer_Switch->Current_State_Pin) && (0 == Relays[i].Pointer_Switch->Last_State_Pin))
		{
			/*Rising edge detected  -> switch object off */
			Rte_PortControl_Pin_Level(Relays[i].Output_PIN_ID,0); /*Write Low*/
			Relays[i].Time_Counter = 0;
			Relays[i].Pointer_Switch->Last_State_Pin = Relays[i].Pointer_Switch->Current_State_Pin; /*store current in previous */
		}
		else if((0 == Relays[i].Pointer_Switch->Current_State_Pin) && (1 == Relays[i].Pointer_Switch->Last_State_Pin))
		{
			/*falling edge detected  -> switch object On */
			Rte_PortControl_Pin_Level(Relays[i].Output_PIN_ID,1); /*Write High*/

			Relays[i].Pointer_Switch->Last_State_Pin = Relays[i].Pointer_Switch->Current_State_Pin; /*store current in previous */
		}
		else
		{

		}
	}
}


/********************Periodic Functions*****************************/
static void Runnable_Object_Update_Relays_And_Switch_Status_10ms(void)
{
	u8 Local_return = 1;
	u8 Local_Data;

	for(u8 i=0 ; i < NUMBER_OF_RELAYS_INTERNAL_ON_CHIP ;i++)
	{
		Rte_PortControl_Pin_Read(Relays[i].Output_PIN_ID,&Local_Data);

		//*Pointer_Data = (*Pointer_Data)|(Local_Data<<Relays[i].Object_Number_In_Status_Message);
		if(1 == Struct_Status_Write_Valus(&Local_Relays_Status,Relays[i].Object_Number_In_Status_Message,Local_Data))
		{

		}
		else
		{
			Local_return = 0;
		}
		if(1 == Struct_Status_Write_Valus(&Local_Switches_Status,Relays[i].Object_Number_In_Status_Message,Relays[i].Pointer_Switch->Current_State_Pin))
		{

		}
		else
		{
			Local_return = 0;
		}
	}
	if(E_OK == Rte_Write_FD02(&Local_Relays_Status))
	{

	}
	else
	{
		Local_return = 0;
	}

	if(E_OK == Rte_Write_FD03(&Local_Relays_Status))
	{

	}
	else
	{
		Local_return = 0;
	}

	return Local_return ;



}
/*************************************************/
static u8 Struct_Status_Write_Valus(u8 *Struct_Pointer,u16 copy_Bit_ID,u8 copy_Level)
{
	u8 Local_Return = 1;

	u8 Bit_Section =  (copy_Bit_ID % 8 ); /*Calculate which Bit in Byte*/
	u8 byte_Section = (copy_Bit_ID / 8); /*Calculate Byte its self*/

	u8 *pointer; 	/*Local Pointer to access Struct in u8 size*/

	pointer = Struct_Pointer; /*giving struct addresses*/

	if(byte_Section < LENGHT_STATUS_OBJECT_ON_SYSTEM*8)
	{
		pointer = pointer + byte_Section;
		if(1 == copy_Level)
		{
			SET_BIT(*pointer, Bit_Section);
		}
		else if(0 == copy_Level)
		{
			CLR_BIT(*pointer, Bit_Section);
		}
		else
		{
			Local_Return = 0; /*Wrong inputs */
		}

	}
	else
	{
		Local_Return = 0; /* wrong inputs*/
	}

	return Local_Return;

}

static u8 Struct_Status_Get_Valus(u8 *Struct_Pointer,u16 copy_Bit_ID,u8 *Pointer_Value)
{

	u8 Local_Return = 1;
	u8 Bit_Section = (copy_Bit_ID % 8 );
	u8 byte_Section = (copy_Bit_ID / 8);

	u8 Local_Data ;
	u8 *pointer;
	pointer = Struct_Pointer;

	if(byte_Section < LENGHT_STATUS_OBJECT_ON_SYSTEM*8)
	{
		pointer = pointer + byte_Section;
		*Pointer_Value =  GET_BIT(*pointer, Bit_Section);
	}
	else
	{
		Local_Return = 0;
	}
	return  Local_Return;
}

