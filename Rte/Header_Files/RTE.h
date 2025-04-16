/*
 * RTE.h
 *
 *  Created on: Jan 21, 2023
 *      Author: Mohamed Nasser
 */

#include"Lib.h"
#include"Queue_Interface.h"
#include"RTE_Memif_Config_Interface.h"

#ifndef RTE_H_
#define RTE_H_

/*Port between Comuncation_Manger and Protocol Translator*/
#define PROTOCOLTRANSLATOR_AS_SOURCE 5
#define COMUNICATION_MANGER_AS_SOURCE 10






/*----------------------------------------------------------------------------------------------------------*/

/*-------------------------Input_Output_Interface------------------------------------------------*/
#define PIN_INITIOLIZATION 0
#define PIN_CONTROL_LEVEL  1
#define PIN_READ_LEVEL     2
#define PIN_TOGGLE_LEVEL   3
#define DONT_CARE		   4

#define Rte_PortControl_Pin_Init(PIN_ID,MODE)         Rte_Port_Control_Pins(PIN_INITIOLIZATION,PIN_ID,MODE,DONT_CARE,DONT_CARE)
#define Rte_PortControl_Pin_Level(PIN_ID,LEVEL)       Rte_Port_Control_Pins(PIN_CONTROL_LEVEL,PIN_ID,DONT_CARE,LEVEL,DONT_CARE)
#define Rte_PortControl_Pin_Read(PIN_ID,POINTER)      Rte_Port_Control_Pins(PIN_READ_LEVEL,PIN_ID,DONT_CARE,DONT_CARE,POINTER)
#define Rte_PortControl_Pin_Toggle(PIN_ID)            Rte_Port_Control_Pins(PIN_TOGGLE_LEVEL,PIN_ID,DONT_CARE,DONT_CARE,DONT_CARE)

enum{
	Not_Availabe,
	Available,
	Write_Done,
	Write_Faild,
	Read_Done,
	Read_Faild,
	On_progress,
	Rte_Load_Done,
	Rte_Load_Faild,
};



u8 Rte_Port_Control_Pins(u8 copy_Command,u8 copy_Pin_ID,u8 copy_Pin_Mode,u8 copy_Pin_Level,u8* pointer_to_Save);
/*-----------------------------------------------------------------------------------------------*/






/*------------------------------Interface Between System SW & Object SW ----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#define SYSTEM_MODE 			          10
#define OBJECT_FINISHED_WFIFI_INIT        11
#define STATUS_ECU_ID					  13
/*--------------------------------------------------------*/
#define WIFI_SEQUENCE_VARIABLE            12

			/*******/


u8 Rte_Write_System_Mode(u8* Pointer_Syste_Mode);												
u8 Rte_Read_System_Mode(u8* Pointer_Syste_Mode) ;  											

u8 Rte_Write_WIFI_Sequenc_Variable(u8* Pointer_WIFI_Sequenc_Variable);								
u8 Rte_Read_WIFI_Sequenc_Variable(u8* Pointer_WIFI_Sequenc_Variable); 						   


/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


u8 Rte_Compounent_Read_Write_Shared_Data_Messages(u8 copy_Message_ID,u8 Read_OR_Write,u8* pointer_Data,u8 Number_of_Elments,u8 Reader_Receciver_ID);
static u8 Rte_Read_Write_Message(u8* source,u8 Read_OR_Write,u8 Number_of_Elments,u8* Destination);

#endif /* RTE_H_ */
