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

static u8 System_Mode = NOT_DEFINE;
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

