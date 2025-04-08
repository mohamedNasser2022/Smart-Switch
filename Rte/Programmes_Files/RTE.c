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
	System_Init(); /* this shall be before UART conf*/
	Comunication_Manger_Init();
	Protocol_Init();
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

/*--------------Nvm Interface --------------*/

STD_Returns Rte_Read_Hardware_Version(u8 *Pointer_Data)
{
	/*Pointer_Data = Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version;
	return E_OK;*/
}

STD_Returns Rte_Write_Hardware_Version(u8 copy_Data)
{
	/*
	Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version = copy_Data;

	return E_OK;*/
}

STD_Returns Rte_Write_FD00(Idt_Rec001_FD00 *Pointer_data)
{
	/*Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version = Pointer_data->Hardware_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.Host_Software_Version = Pointer_data->Host_Software_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.WIFI_Software_Version = Pointer_data->WIFI_Software_Version;

	return E_OK;*/
}

STD_Returns Rte_Nvm_Write_FD00(Idt_Rec001_FD00 *Pointer_data)
{
	/*Rte_Data_Rec001_FD00.Rec001_FD00.Hardware_Version = Pointer_data->Hardware_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.Host_Software_Version = Pointer_data->Host_Software_Version;
	Rte_Data_Rec001_FD00.Rec001_FD00.WIFI_Software_Version = Pointer_data->WIFI_Software_Version;

	Rte_Data_Rec001_FD00.Nvm_Data_Status = Rte_Load_Done;

	return E_OK;*/
}

STD_Returns Rte_Write_FD01(Idt_Rec002_FD01 *Pointer_data)
{ 
	/*Rte_Data_Rec002_FD01.Rec002_FD01.Number_Relays_On_Syetem = Pointer_data->Number_Relays_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Sensors_On_Syetem = Pointer_data->Number_Sensors_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Switches_On_Syetem = Pointer_data->Number_Switches_On_Syetem;

	return E_OK;*/
}

STD_Returns Rte_Nvm_Write_FD01(Idt_Rec002_FD01 *Pointer_data)
{ 
	/*Rte_Data_Rec002_FD01.Rec002_FD01.Number_Relays_On_Syetem = Pointer_data->Number_Relays_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Sensors_On_Syetem = Pointer_data->Number_Sensors_On_Syetem;
	Rte_Data_Rec002_FD01.Rec002_FD01.Number_Switches_On_Syetem = Pointer_data->Number_Switches_On_Syetem;

	Rte_Data_Rec002_FD01.Nvm_Data_Status = Rte_Load_Done;

	return E_OK;*/
}

STD_Returns Rte_Write_FD02(Idt_Rec003_FD02 *Pointer_data)
{
	/*u8 Data_Lenght = sizeof(Rte_Data_Rec003_FD02.Rec003_FD02)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec003_FD02.Rec003_FD02.Relay_status[i] = Pointer_data->Relay_status[i];
	}

	return Write_Done;*/
}

STD_Returns Rte_Nvm_Write_FD02(Idt_Rec003_FD02 *Pointer_data)
{
	/*u8 Data_Lenght = sizeof(Rte_Data_Rec003_FD02.Rec003_FD02)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec003_FD02.Rec003_FD02.Relay_status[i] = Pointer_data->Relay_status[i];
	}
	Rte_Data_Rec003_FD02.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;*/
}

STD_Returns Rte_Write_FD03(Idt_Rec004_FD03 *Pointer_data)
{
	/*u8 Data_Lenght = sizeof(Rte_Data_Rec004_FD03.Rec004_FD03)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec004_FD03.Rec004_FD03.Switch_status[i] = Pointer_data->Switch_status[i];
	}

	return Write_Done;*/
}

STD_Returns Rte_Nvm_Write_FD03(Idt_Rec004_FD03 *Pointer_data)
{
	/*u8 Data_Lenght = sizeof(Rte_Data_Rec004_FD03.Rec004_FD03)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec004_FD03.Rec004_FD03.Switch_status[i] = Pointer_data->Switch_status[i];
	}
	Rte_Data_Rec004_FD03.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;*/
}

STD_Returns Rte_Write_FD04(Idt_Rec005 *Pointer_data)
{
	/*MemIf_Immediate_Write_Rec005(Pointer_data);
	return Write_Done;*/
}

STD_Returns Rte_Nvm_Write_FD04(Idt_Rec005 *Pointer_data)
{
	/*u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec005.WiFi_Name.Data[i] = Pointer_data->Data[i];
	}
	Rte_Data_Rec005.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;*/
}

STD_Returns Rte_Write_FD05(Idt_Rec006 *Pointer_data)
{
	/*MemIf_Immediate_Write_Rec006(Pointer_data);

	return Write_Done;*/
}

STD_Returns Rte_Nvm_Write_FD05(Idt_Rec006 *Pointer_data)
{
	/*u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		Rte_Data_Rec006.WiFi_Password.Data[i] = Pointer_data->Data[i];
	}
	Rte_Data_Rec006.Nvm_Data_Status = Rte_Load_Done;
	return Write_Done;*/
}

STD_Returns Rte_Read_FD00(Idt_Rec001_FD00 *Pointer_data)
{
	/*u8 Local_Return = Read_Done;
	
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
	return Local_Return;*/
}

STD_Returns Rte_Read_FD01(Idt_Rec002_FD01 *Pointer_data)
{
	/*u8 Local_Return = Read_Done;

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

	return Local_Return;*/
}

STD_Returns Rte_Read_FD02(Idt_Rec003_FD02 *Pointer_data)
{
	/*u8 Local_Return = Read_Done;

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


	return Local_Return;*/
}

STD_Returns Rte_Read_FD03(Idt_Rec004_FD03 *Pointer_data)
{
	/*u8 Local_Return = Read_Done;

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


	return Local_Return;*/
}

STD_Returns Rte_Read_FD04(Idt_Rec005 *Pointer_data)
{
	/*u8 Local_Return = Read_Done;

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


	return Local_Return;*/
}

STD_Returns Rte_Read_FD05(Idt_Rec006 *Pointer_data)
{
	/*u8 Local_Return = Read_Done;

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


	return Local_Return;*/
}

