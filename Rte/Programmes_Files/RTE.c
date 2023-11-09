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
#include"Rte_Nvm_STD.h"
#include"Rte_Message_STD.h"


/*--------------------------system Varabies---------------------------------------*/

static u8 System_Mode = NOT_DEFINE;
static u8 WIFI_Sequenc_Variable = NOT_DEFINE;
static u8 Object_Finished_WIFI_Init = NOT_DEFINE;
static u8 Status_Ecu_ID;



static struct
{
	Idt_Rec001_FD00 Rec001_FD00;
	u8 Nvm_Data_Status;

}Rte_Data_Rec001_FD00;

static struct
{
	Idt_Rec002_FD01 Rec002_FD01;
	u8 Nvm_Data_Status;

}Rte_Data_Rec002_FD01;

static struct
{
	Idt_Rec003_FD02 Rec003_FD02;
	u8 Nvm_Data_Status;

}Rte_Data_Rec003_FD02;

static struct
{
	Idt_Rec004_FD03 Rec004_FD03;
	u8 Nvm_Data_Status;

}Rte_Data_Rec004_FD03;

static struct
{
	Idt_Rec005 WiFi_Name;
	u8 Nvm_Data_Status;

}Rte_Data_Rec005;

static struct
{
	Idt_Rec006 WiFi_Password;
	u8 Nvm_Data_Status;

}Rte_Data_Rec006;

static struct {

	Idt_Message_0x10_t Rte_Message_0x10;
	u8 Rte_Message_Status;

}Rte_Message_0x10_Struct;

static struct {

	Idt_Message_0x11_t Rte_Message_0x11;
	u8 Rte_Message_Status;

}Rte_Message_0x11_Struct;

static struct
{
	Idt_Message_0x13_t Relays_Status;
	u8 Rte_Message_Status;
}Message_0x13;

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
	MemIf_Init();
	

}

void RTE_Polling(void)
{
	comunication_Manger_Polling();
	Protocol_Translator_Polling();
	system_Polling();
	I_O_Interface_Polling();
	Object_Polling();
	MemIf_Polling();
	


}

void RTE_Periodic(void)
{
	Object_Periodic();
	system_Periodic();
	UART_Manger_Time();
	I_O_Interface_Periodic();
	I2C_Periodic();
	Protocol_Translator_Time();
	EEPROM_Driver_Time();
	MemIf_Time();
}

/*---------------Port between Comuncation_Manger and Protocol Translator-------------------------------------------------*/
/*Send Port*/

u8 Rte_Read_Relays_Status()
{
	/*read status*/
}

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

/*-------------------------------- Control Port I/O --------------------------------------*/

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

u8 Rte_Read_System_Mode(u8* Pointer_Syste_Mode)
{
	
	*Pointer_Syste_Mode = System_Mode;
	return 1;
}

u8 Rte_Write_System_Mode(u8* Pointer_Syste_Mode)
{
	
	System_Mode = *Pointer_Syste_Mode;
	return 1;
}

u8 Rte_Read_WIFI_Sequenc_Variable(u8* Pointer_WIFI_Sequenc_Variable)
{
	
	*Pointer_WIFI_Sequenc_Variable = WIFI_Sequenc_Variable;
	return 1;
}

u8 Rte_Write_WIFI_Sequenc_Variable(u8* Pointer_WIFI_Sequenc_Variable)
{
	
	WIFI_Sequenc_Variable = *Pointer_WIFI_Sequenc_Variable;
	return 1;
}

/*------------------------------------------------------------------*/
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


u8 Rte_Write_Message_0x14(copy_Data_0,copy_Data_1) /*Object SW shall write this message*/
{
	u8 Local_Return = Write_Done ;

	if(On_progress != Message_0x14.Message_Status && Available != Message_0x14.Message_Status)
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

u8 Rte_Write_Message_0x10(Idt_Message_0x10_t *Pointer_Data) /*Protocol Translator shall write this message*/
{
	u8 Local_Return = Write_Done ;

	u8 Data_Lenght = sizeof(Idt_Message_0x10_t)/sizeof(u8) ;


	if(On_progress != Rte_Message_0x10_Struct.Rte_Message_Status)
	{
		Rte_Message_0x10_Struct.Rte_Message_Status = On_progress;

		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			Rte_Message_0x10_Struct.Rte_Message_0x10.Data[i] = Pointer_Data->Data[i];
		}


		Rte_Message_0x10_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;

}

u8 Rte_Read_Message_0x10(Idt_Message_0x10_t *Pointer_Data) /*any SWs Read shall read this message*/
{
	u8 Local_Return = Read_Done ;

	u8 Data_Lenght = sizeof(Idt_Message_0x10_t)/sizeof(u8) ;

	if(Available == Rte_Message_0x10_Struct.Rte_Message_Status)
	{
		Rte_Message_0x10_Struct.Rte_Message_Status = On_progress;

		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			Pointer_Data->Data[i] = Rte_Message_0x10_Struct.Rte_Message_0x10.Data[i] ;
			
		}

		Rte_Message_0x10_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}

u8 Rte_Write_Message_0x11(Idt_Message_0x11_t *Pointer_Data) /*Protocol Translator shall write this message*/
{
	u8 Local_Return = Write_Done ;

	u8 Data_Lenght = sizeof(Idt_Message_0x11_t)/sizeof(u8) ;


	if(On_progress != Rte_Message_0x11_Struct.Rte_Message_Status)
	{
		Rte_Message_0x11_Struct.Rte_Message_Status = On_progress;

		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			Rte_Message_0x11_Struct.Rte_Message_0x11.Data[i] = Pointer_Data->Data[i];
		}


		Rte_Message_0x11_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}

	return Local_Return;

}

u8 Rte_Read_Message_0x11(Idt_Message_0x11_t *Pointer_Data) /*any SWs Read shall read this message*/
{
	u8 Local_Return = Read_Done ;

	u8 Data_Lenght = sizeof(Idt_Message_0x11_t)/sizeof(u8) ;

	if(Available == Rte_Message_0x11_Struct.Rte_Message_Status)
	{
		Rte_Message_0x11_Struct.Rte_Message_Status = On_progress;

		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			Pointer_Data->Data[i] = Rte_Message_0x11_Struct.Rte_Message_0x11.Data[i] ;
			
		}

		Rte_Message_0x11_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}

	return Local_Return;

}
/*--------------Nvm Interface --------------*/

STD_Returns Rte_Read_Hardware_Version(u8 *Pointer_Data)
{
	*Pointer_Data = Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version;
	return E_OK;
}

STD_Returns Rte_Write_Hardware_Version(u8 copy_Data)
{
	Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version = copy_Data;

	return E_OK;
}

STD_Returns Rte_Write_FD00(Idt_Rec001_FD00 *Pointer_data)
{
	Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version = Pointer_data->Hardware_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.Host_Software_Version = Pointer_data->Host_Software_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.WIFI_Software_Version = Pointer_data->WIFI_Software_Version;

	return E_OK;
}

STD_Returns Rte_Nvm_Write_FD00(Idt_Rec001_FD00 *Pointer_data)
{
	Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version = Pointer_data->Hardware_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.Host_Software_Version = Pointer_data->Host_Software_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.WIFI_Software_Version = Pointer_data->WIFI_Software_Version;

	Rte_Data_Rec001_FD00.Nvm_Data_Status = Rte_Load_Done;

	return E_OK;
}

STD_Returns Rte_Write_FD01(Idt_Rec002_FD01 *Pointer_data)
{ 
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Relays_On_Syetem = Pointer_data->Number_Relays_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Sensors_On_Syetem = Pointer_data->Number_Sensors_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Switches_On_Syetem = Pointer_data->Number_Switches_On_Syetem;

	return E_OK;
}

STD_Returns Rte_Nvm_Write_FD01(Idt_Rec002_FD01 *Pointer_data)
{ 
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Relays_On_Syetem = Pointer_data->Number_Relays_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Sensors_On_Syetem = Pointer_data->Number_Sensors_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Switches_On_Syetem = Pointer_data->Number_Switches_On_Syetem;

	Rte_Data_Rec002_FD01.Nvm_Data_Status = Rte_Load_Done;

	return E_OK;
}

STD_Returns Rte_Write_FD02(Idt_Rec003_FD02 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Rte_Data_Rec003_FD02.Rec003_FD02)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec003_FD02.Rec003_FD02.Relay_status[i] = Pointer_data->Relay_status[i];
	}

	return Write_Done;
}

STD_Returns Rte_Nvm_Write_FD02(Idt_Rec003_FD02 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Rte_Data_Rec003_FD02.Rec003_FD02)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec003_FD02.Rec003_FD02.Relay_status[i] = Pointer_data->Relay_status[i];
	}
	Rte_Data_Rec003_FD02.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;
}

STD_Returns Rte_Write_FD03(Idt_Rec004_FD03 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Rte_Data_Rec004_FD03.Rec004_FD03)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec004_FD03.Rec004_FD03.Switch_status[i] = Pointer_data->Switch_status[i];
	}

	return Write_Done;
}

STD_Returns Rte_Nvm_Write_FD03(Idt_Rec004_FD03 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Rte_Data_Rec004_FD03.Rec004_FD03)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec004_FD03.Rec004_FD03.Switch_status[i] = Pointer_data->Switch_status[i];
	}
	Rte_Data_Rec004_FD03.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;
}

STD_Returns Rte_Write_FD04(Idt_Rec005 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec005.WiFi_Name.Data[i] = Pointer_data->Data[i];
	}

	return Write_Done;
}

STD_Returns Rte_Nvm_Write_FD04(Idt_Rec005 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec005.WiFi_Name.Data[i] = Pointer_data->Data[i];
	}
	Rte_Data_Rec005.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;
}

STD_Returns Rte_Write_FD05(Idt_Rec006 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec006.WiFi_Password.Data[i] = Pointer_data->Data[i];
	}

	return Write_Done;
}

STD_Returns Rte_Nvm_Write_FD05(Idt_Rec006 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec006.WiFi_Password.Data[i] = Pointer_data->Data[i];
	}
	Rte_Data_Rec006.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;
}

STD_Returns Rte_Read_FD00(Idt_Rec001_FD00 *Pointer_data)
{
	u8 Local_Return = Read_Done;
	
	if(Rte_Load_Done == Rte_Data_Rec001_FD00.Nvm_Data_Status)
	{
		Pointer_data->Hardware_Version = Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version ;
		Pointer_data->Host_Software_Version = Rte_Data_Rec001_FD00.Rec001_FD00.Host_Software_Version ;
		Pointer_data->WIFI_Software_Version = Rte_Data_Rec001_FD00.Rec001_FD00.WIFI_Software_Version ;
	}
	else
	{
		Local_Return = Read_Faild ;
	}
	return Local_Return;
}

STD_Returns Rte_Read_FD01(Idt_Rec002_FD01 *Pointer_data)
{
	u8 Local_Return = Read_Done;

	if(Rte_Load_Done == Rte_Data_Rec002_FD01.Nvm_Data_Status)
	{
		Pointer_data->Number_Relays_On_Syetem = Rte_Data_Rec002_FD01.Rec002_FD01.Number_Relays_On_Syetem ;
		Pointer_data->Number_Switches_On_Syetem = Rte_Data_Rec002_FD01.Rec002_FD01.Number_Switches_On_Syetem ;
		Pointer_data->Number_Sensors_On_Syetem = Rte_Data_Rec002_FD01.Rec002_FD01.Number_Sensors_On_Syetem ;
	}
	else
	{
		Local_Return = Read_Faild ;
	}

	return Local_Return;
}

STD_Returns Rte_Read_FD02(Idt_Rec003_FD02 *Pointer_data)
{
	u8 Local_Return = Read_Done;

	u8 Data_Lenght = sizeof(Rte_Data_Rec003_FD02.Rec003_FD02)/sizeof(u8) ;

	if(Rte_Load_Done == Rte_Data_Rec003_FD02.Nvm_Data_Status)
	{
		for(u8 i = 0 ; i < Data_Lenght ; i++)
		{
			Pointer_data->Relay_status[i] = Rte_Data_Rec003_FD02.Rec003_FD02.Relay_status[i] ;
		}

	}
	else
	{
		Local_Return = Read_Faild;
	}


	return Local_Return;
}

STD_Returns Rte_Read_FD03(Idt_Rec004_FD03 *Pointer_data)
{
	u8 Local_Return = Read_Done;

	u8 Data_Lenght = sizeof(Rte_Data_Rec004_FD03.Rec004_FD03)/sizeof(u8) ;

	if(Rte_Load_Done == Rte_Data_Rec004_FD03.Nvm_Data_Status)
	{
		for(u8 i = 0 ; i < Data_Lenght ; i++)
		{
			Pointer_data->Switch_status[i] = Rte_Data_Rec004_FD03.Rec004_FD03.Switch_status[i] ;
		}

	}
	else
	{
		Local_Return = Read_Faild;
	}


	return Local_Return;
}

STD_Returns Rte_Read_FD04(Idt_Rec005 *Pointer_data)
{
	u8 Local_Return = Read_Done;

	u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;

	if(Rte_Load_Done == Rte_Data_Rec005.Nvm_Data_Status)
	{
		for(u8 i = 0 ; i < Data_Lenght ; i++)
		{
			Pointer_data->Data[i] = Rte_Data_Rec005.WiFi_Name.Data[i] ;
		}

	}
	else
	{
		Local_Return = Read_Faild;
	}


	return Local_Return;
}

STD_Returns Rte_Read_FD05(Idt_Rec006 *Pointer_data)
{
	u8 Local_Return = Read_Done;

	u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;

	if(Rte_Load_Done == Rte_Data_Rec006.Nvm_Data_Status)
	{
		for(u8 i = 0 ; i < Data_Lenght ; i++)
		{
			Pointer_data->Data[i] = Rte_Data_Rec006.WiFi_Password.Data[i] ;
		}

	}
	else
	{
		Local_Return = Read_Faild;
	}


	return Local_Return;
}
