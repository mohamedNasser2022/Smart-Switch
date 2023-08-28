/*
 * RTE.c
 *
 *  Created on: Jan 21, 2023
 *      Author: Mohamed Nasser
 */

#include"Queue_Interface.h"
#include"system_Main.h"
#include"STD_TYPES.h"
#include"Data_Structure.h"
#include"LIB_ERROR.h"
#include"RTE.h"

/*--------------------------system Varabies---------------------------------------*/

static u8 System_Mode = INITIOLAZTION_MODE;
static u8 WIFI_Sequenc_Variable = NOT_DEFINE;
static u8 Object_Finished_WIFI_Init = NOT_DEFINE;
static u8 Status_Ecu_ID;
/*--------------------------------------------------------------------------------*/


/*------------------------------------System Messages to WIFI--------------------*/

/*-----------------------------------------------------------*/


/*Port between Comuncation_Manger and Protocol Translator*/
static Comuncation_Manger_Interface_Nested Buffer_ProtocolTranslator_Send_Comunication;
static Comuncation_Manger_Interface_Nested Buffer_Comunication_Send_ProtocolTranslator;
/*------------------------------------------------------------------------*/



void RTE_Init(void)
{

	/*-----------------------------------------------------------*/
	Nested_Queue0_Create(&Buffer_ProtocolTranslator_Send_Comunication);
	Nested_Queue0_Create(&Buffer_Comunication_Send_ProtocolTranslator);
	Comunication_Manger_Init();
	HAL_voidSmartProtocol_Init();
	System_Init();
	Object_Init();
	I_O_Interface_Initialization();

	EEPROM_Driver_Initialization();

}

void RTE_Polling(void)
{
	comunication_Manger_Polling();
	Protocol_Translator_Polling();
	system_Polling();
	I_O_Interface_Polling();
	Object_Polling();
	EEPROM_Driver_Polling();


}

void RTE_Periodic(void)
{
	Object_Periodic();
	system_Periodic();
	UART_Manger_Time();
	I_O_Interface_Periodic();
	I2C_Periodic();
	EEPROM_Driver_Time();
}

/*---------------Port between Comuncation_Manger and Protocol Translator-------------------------------------------------*/
/*Send Port*/

u8 Rte_Send_Port_Comunication_Manger_Protocol_Translator(u8 copy_Source,Comuncation_Manger_Interface* Pointer_To_Data)
{
	Comuncation_Manger_Interface_Nested* Local_Pointer_Data ;
	u8 Local_Return = 0;
	switch(copy_Source)
	{
	case PROTOCOLTRANSLATOR_AS_SOURCE:
		Local_Pointer_Data = &Buffer_ProtocolTranslator_Send_Comunication;
		Local_Return = 1;
		break;
	case COMUNICATION_MANGER_AS_SOURCE:
		Local_Pointer_Data = &Buffer_Comunication_Send_ProtocolTranslator;
		Local_Return = 1;
		break;
	default:
		Local_Return = 0;
		break;
	}


	if(!Nested_Queue0_Full(Local_Pointer_Data) && Local_Return == 1)
	{

		Nested_Queue0_Push(Local_Pointer_Data,Pointer_To_Data);

		return Local_Return;
	}
	else
	{
		return Local_Return;
	}


}

/*Reading*/
u8 Rte_Read_Port_Comunication_Manger_Protocol_Translator(u8 copy_Source,Comuncation_Manger_Interface_Nested *Pointer_to_Data)
{
	Comuncation_Manger_Interface_Nested* Local_Pointer_Data ;
	u8 Local_Return = 0;
	switch(copy_Source)
	{
	case PROTOCOLTRANSLATOR_AS_SOURCE:
		Local_Pointer_Data = &Buffer_ProtocolTranslator_Send_Comunication;
		Local_Return = 1;
		break;
	case COMUNICATION_MANGER_AS_SOURCE:
		Local_Pointer_Data = &Buffer_Comunication_Send_ProtocolTranslator;
		Local_Return = 1;
		break;
	default:
		Local_Return = 0;
		break;
	}

	if(Local_Return == 1)
	{
		Comuncation_Manger_Interface Local_Swap;
		Queue0_Clear(&Local_Swap);

		if(Nested_Queue0_Pop(Local_Pointer_Data,&Local_Swap))
		{
			Nested_Queue0_Push(Pointer_to_Data,&Local_Swap);
		}
		else
		{
			return 0;
		}
		return 1;
	}
	else
	{
		return 0;
	}

}

/*----------------------------------------------------------------------------------------------------------*/

/*--------------------------------Control Port I/O--------------------------------------*/

u8 Rte_Port_Control_Pins(u8 copy_Command,u8 copy_Pin_ID,u8 copy_Pin_Mode,u8 copy_Pin_Level,u8* pointer_to_Save)
{
	u8 Local_Return = 0;
	switch(copy_Command)
	{
	case PIN_INITIOLIZATION:
		I_O_Interface_Init_Pin(copy_Pin_ID,copy_Pin_Mode);
		Local_Return = 1 ;
		break;
	case PIN_CONTROL_LEVEL:
		I_O_Interface_set_Pin_Level(copy_Pin_ID,copy_Pin_Level);
		Local_Return = 1 ;
		break;
	case PIN_READ_LEVEL:
		I_O_Interface_Read_Pin_Level(copy_Pin_ID,pointer_to_Save);
		Local_Return = 1 ;
		break;
	case PIN_TOGGLE_LEVEL:
		I_O_Interface_Toggle_Pin(copy_Pin_ID);
		Local_Return = 1 ;
		break;
	default:
		Local_Return = 0 ;
		break;

	}
	return Local_Return ;
}

/*------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------*/

/*------------------------------ Global port read/Write for shared variables ----------------------*/

u8 Rte_Compounent_Read_Write_Shared_Data(u8 copy_ID_Of_Variable,u8 copy_Read_Write,u8 copy_Data,u8* Pointer_to_Get_Data_In)
{
	u8 Local_Return = 1;
	switch(copy_ID_Of_Variable)
	{

	case SYSTEM_MODE:

		if(copy_Read_Write == READ_MESSAGE)
		{
			*Pointer_to_Get_Data_In = System_Mode;
		}
		else if(copy_Read_Write == WRITE_MESSAGE)
		{
			System_Mode = copy_Data;
		}
		else
		{
			Local_Return = 0 ;
		}

		break;

	case WIFI_SEQUENCE_VARIABLE:

		if(copy_Read_Write == READ_MESSAGE)
		{
			*Pointer_to_Get_Data_In = WIFI_Sequenc_Variable;
		}
		else if(copy_Read_Write == WRITE_MESSAGE)
		{
			WIFI_Sequenc_Variable = copy_Data;
		}
		else
		{
			Local_Return = 0 ;
		}



		break;
	case OBJECT_FINISHED_WFIFI_INIT:

		if(copy_Read_Write == READ_MESSAGE)
		{
			*Pointer_to_Get_Data_In = Object_Finished_WIFI_Init;
		}
		else if(copy_Read_Write == WRITE_MESSAGE)
		{
			Object_Finished_WIFI_Init = copy_Data;

		}
		else
		{
			Local_Return = 0 ;
		}



		break;
	case STATUS_ECU_ID:

		if(copy_Read_Write == READ_MESSAGE)
		{
			*Pointer_to_Get_Data_In = Status_Ecu_ID;
		}
		else if(copy_Read_Write == WRITE_MESSAGE)
		{
			Status_Ecu_ID = copy_Data;

		}
		else
		{
			Local_Return = 0 ;
		}



		break;

	default:
		Local_Return = 0;

		break;
	}

	return Local_Return ;
}


u8 Rte_Write_Message_0x01(u8 copy_Data_0,u8 copy_Data_1,u8 copy_Data_2) /*System Mode shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x01.Message_Status)
	{
		Message_0x01.Message_Status = On_progress;

		Message_0x01.Data[0] = copy_Data_0;
		Message_0x01.Data[1] = copy_Data_1;
		Message_0x01.Data[2] = copy_Data_2;

		Message_0x01.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x01(u8 *Pointer_Data) /*Protocol Translator shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x01.Message_Status)
	{
		Message_0x01.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x01; i++)
		{
			*(Pointer_Data + i) = Message_0x01.Data[i] ;
		}



		Message_0x01.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x02(u8 copy_Data_0) /*System Mode shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x02.Message_Status)
	{
		Message_0x02.Message_Status = On_progress;


		Message_0x02.Data[0] = copy_Data_0;


		Message_0x02.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x02(u8 *Pointer_Data) /*Protocol Translator shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x02.Message_Status)
	{
		Message_0x02.Message_Status = On_progress;

		*Pointer_Data  = Message_0x02.Data[0];

		Message_0x02.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x13(u8 copy_Data_0,u8 copy_Data_1,u8 copy_Data_2,u8 copy_Data_3,u8 copy_Data_4,u8 copy_Data_5) /*Object SW shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x13.Message_Status)
	{
		Message_0x13.Message_Status = On_progress;


		Message_0x13.Data[0] = copy_Data_0;
		Message_0x13.Data[1] = copy_Data_1;
		Message_0x13.Data[2] = copy_Data_2;
		Message_0x13.Data[3] = copy_Data_3;
		Message_0x13.Data[4] = copy_Data_4;
		Message_0x13.Data[5] = copy_Data_5;

		Message_0x13.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x13(u8 *Pointer_Data) /*Protocol Translator shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x13.Message_Status)
	{
		Message_0x13.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x13; i++)
		{
			*(Pointer_Data + i) = Message_0x13.Data[i] ;
		}

		Message_0x13.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x14(copy_Data_0,copy_Data_1) /*Object SW shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x14.Message_Status)
	{
		Message_0x14.Message_Status = On_progress;


		Message_0x14.Data[0] = copy_Data_0;
		Message_0x14.Data[1] = copy_Data_1;

		Message_0x14.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x14(u8 *Pointer_Data) /*Protocol Translator shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x14.Message_Status)
	{
		Message_0x14.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x14; i++)
		{
			*(Pointer_Data + i) = Message_0x14.Data[i] ;
		}

		Message_0x14.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x20(u8 *Pointer_Data) /*Object SW shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x20.Message_Status)
	{
		Message_0x20.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x20; i++)
		{
			Message_0x20.Data[i] = *(Pointer_Data + i);
		}

		Message_0x20.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x20(u8 *Pointer_Data) /*Protocol Translator shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x20.Message_Status)
	{
		Message_0x20.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x20; i++)
		{
			*(Pointer_Data + i) = Message_0x20.Data[i] ;
		}

		Message_0x20.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x21(u8 *Pointer_Data) /*Object SW shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x21.Message_Status)
	{
		Message_0x21.Message_Status = On_progress;


		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x21; i++)
		{
			Message_0x21.Data[i] = *(Pointer_Data + i);
		}


		Message_0x21.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x21(u8 *Pointer_Data) /*Protocol Translator shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x21.Message_Status)
	{
		Message_0x21.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x21; i++)
		{
			*(Pointer_Data + i) = Message_0x21.Data[i] ;
		}

		Message_0x21.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

/* Messages for Protocol to SW*/

u8 Rte_Write_Message_0x03(DATA1,DATA2) /*Protocol Translator shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x03.Message_Status)
	{
		Message_0x03.Message_Status = On_progress;


		Message_0x03.Data[0] = DATA1;
		Message_0x03.Data[1] = DATA2;

		Message_0x03.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x03(u8 *Pointer_Data_0,u8 *Pointer_Data_1) /*any SWs Read shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x03.Message_Status)
	{
		Message_0x03.Message_Status = On_progress;

		*Pointer_Data_0 = Message_0x03.Data[0];
		*Pointer_Data_1 = Message_0x03.Data[1];

		Message_0x03.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x10(u8 *Pointer_Data) /*Protocol Translator shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x10.Message_Status)
	{
		Message_0x10.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x10; i++)
		{
			Message_0x10.Data[i] = *(Pointer_Data + i);
		}


		Message_0x10.Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;
}

u8 Rte_Read_Message_0x10(u8 *Pointer_Data) /*any SWs Read shall read this message*/
{
	u8 Local_Return = Read_Done ;

	if(Available == Message_0x10.Message_Status)
	{
		Message_0x10.Message_Status = On_progress;

		for(u8 i = 0 ; i < MESSAGE_ARRAY_ELEMENTS_NUMBER_0x10; i++)
		{
			 *(Pointer_Data + i) = Message_0x10.Data[i] ;
		}

		;

		Message_0x10.Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

/*
u8 Rte_Compounent_Read_Write_Shared_Data_Messages(u8 copy_Message_ID,u8 Read_OR_Write,u8* pointer_Data,u8 Number_of_Elments
		,u8 Reader_Receciver_ID)
{
	volatile u8 Local_Return = 1;

	switch(copy_Message_ID)
	{
	case MESSAGE_0x01:

		if( Message_System_Configurations_0x01.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_System_Configurations_0x01.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_System_Configurations_0x01.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_System_Configurations_0x01.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write)
		{
			if ( Rte_Read_Write_Message(&Message_System_Configurations_0x01.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_System_Configurations_0x01.To_Who_Read = Reader_Receciver_ID;
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

		break;
	case MESSAGE_0x02:  // Message_System_Mode_0x02

		if( Message_System_Mode_0x02.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_System_Mode_0x02.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_System_Mode_0x02.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_System_Mode_0x02.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_System_Mode_0x02.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_System_Mode_0x02.To_Who_Read = Reader_Receciver_ID;
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

		break;

	case MESSAGE_0x03:  // Message_WIFI_Respond_0x03

		if( Message_WIFI_Respond_0x03.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_WIFI_Respond_0x03.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_WIFI_Respond_0x03.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_WIFI_Respond_0x03.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_WIFI_Respond_0x03.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_WIFI_Respond_0x03.To_Who_Read = Reader_Receciver_ID;
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

		break;

	case MESSAGE_0x10: //Message_Object_Control_0x10

		if( Message_Object_Control_0x10.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_Object_Control_0x10.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Control_0x10.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_Object_Control_0x10.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_Object_Control_0x10.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Control_0x10.To_Who_Read = Reader_Receciver_ID;
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

		break;
	case MESSAGE_0x11: // Message_Object_Reading_0x11

		if( Message_Object_Reading_0x11.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_Object_Reading_0x11.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Reading_0x11.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_Object_Reading_0x11.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_Object_Reading_0x11.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Reading_0x11.To_Who_Read = Reader_Receciver_ID;
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

		break;

	case MESSAGE_0x13: // Message_Object_Status_0x13

		if( Message_Object_Status_0x13.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_Object_Status_0x13.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Status_0x13.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_Object_Status_0x13.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_Object_Status_0x13.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Status_0x13.To_Who_Read = Reader_Receciver_ID;
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

		break;

	case MESSAGE_0x14: //Message_Object_Information_0x14

		if( Message_Object_Information_0x14.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_Object_Information_0x14.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Information_0x14.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_Object_Information_0x14.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_Object_Information_0x14.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_Object_Information_0x14.To_Who_Read = Reader_Receciver_ID;
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

		break;
	case MESSAGE_0x20:

		if( Message_SSID_0x20.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_SSID_0x20.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_SSID_0x20.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_SSID_0x20.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_SSID_0x20.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_SSID_0x20.To_Who_Read = Reader_Receciver_ID;
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

		break;
	case MESSAGE_0x21:

		if( Message_PASS_0x21.To_Who_Read == Reader_Receciver_ID )
		{
			if( Rte_Read_Write_Message(&Message_PASS_0x21.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_PASS_0x21.To_Who_Read = MESSAGE_NOT_VALID;
			}
			else
			{
				Local_Return = 0;
			}
		}
		else if(Message_PASS_0x21.To_Who_Read == MESSAGE_NOT_VALID && WRITE_MESSAGE == Read_OR_Write )
		{
			if ( Rte_Read_Write_Message(&Message_PASS_0x21.Data,Read_OR_Write,Number_of_Elments,pointer_Data) )
			{
				Message_PASS_0x21.To_Who_Read = Reader_Receciver_ID;
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

		break;

	default:

		Local_Return = 0;

		break;

	}
	return Local_Return;
}

static u8 Rte_Read_Write_Message(u8* source,u8 Read_OR_Write,u8 Number_of_Elments,u8* Destination)
{
	u8* Local_Swap_Pointer;
	u8  Local_Return = 1;

	if( READ_MESSAGE  == Read_OR_Write )
	{

	}
	else if(WRITE_MESSAGE  == Read_OR_Write )
	{
		Local_Swap_Pointer = source;
		source = Destination;
		Destination = Local_Swap_Pointer;
	}
	else
	{
		Local_Return = 0;
	}

	if(1 == Local_Return)
	{
		for(u8 i = 0 ; i < Number_of_Elments ; i++)
		{
			Destination[i] = source[i];
			if(Destination[i] == '\0')
			{
				break;
			}
		}
	}
	else
	{

	}


	return Local_Return;

}

 */
/*-------------------------------------------------------------------------------------------*/
