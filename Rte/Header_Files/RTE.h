/*
 * RTE.h
 *
 *  Created on: Jan 21, 2023
 *      Author: Mohamed Nasser
 */

#include"Lib.h"
#include"Queue_Interface.h"

#ifndef RTE_H_
#define RTE_H_

/*Port between Comuncation_Manger and Protocol Translator*/
#define PROTOCOLTRANSLATOR_AS_SOURCE 5
#define COMUNICATION_MANGER_AS_SOURCE 10

#define  Rte_ProtocolTranslator_Write_Data_To_Comunication_Manger(POINTER_TO_DATA)  Rte_Send_Port_Comunication_Manger_Protocol_Translator(PROTOCOLTRANSLATOR_AS_SOURCE,POINTER_TO_DATA)
#define  Rte_Comunication_Manger_Write_Data_To_ProtocolTranslator(POINTER_TO_DATA)  Rte_Send_Port_Comunication_Manger_Protocol_Translator(COMUNICATION_MANGER_AS_SOURCE,POINTER_TO_DATA)

#define Rte_ProtocolTranslator_Read_Data_From_Comunication_Manger(POINTER_TO_DATA)  Rte_Read_Port_Comunication_Manger_Protocol_Translator(COMUNICATION_MANGER_AS_SOURCE,POINTER_TO_DATA)
#define Rte_Comunication_Manger_Read_Data_From_ProtocolTranslator(POINTER_TO_DATA)  Rte_Read_Port_Comunication_Manger_Protocol_Translator(PROTOCOLTRANSLATOR_AS_SOURCE,POINTER_TO_DATA)




u8 Rte_Send_Port_Comunication_Manger_Protocol_Translator(u8 copy_Source,Comuncation_Manger_Interface* Pointer_To_Data);
u8 Rte_Read_Port_Comunication_Manger_Protocol_Translator(u8 copy_Source,Comuncation_Manger_Interface_Nested *Pointer_to_Data);

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


u8 Rte_Port_Control_Pins(u8 copy_Command,u8 copy_Pin_ID,u8 copy_Pin_Mode,u8 copy_Pin_Level,u8* pointer_to_Save);
/*-----------------------------------------------------------------------------------------------*/






/*------------------------------Interface Between System SW & Object SW ----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#define SYSTEM_MODE 			          10
#define OBJECT_FINISHED_WFIFI_INIT        11
#define STATUS_ECU_ID					  13
/*--------------------------------------------------------*/
#define WIFI_SEQUENCE_VARIABLE            12

			/*******/
#define SYSTEM_ENABLE_SEQUENCE      0x01
#define OBJECT_FINISHED_SEQUENCE    0x02
#define WIFI_FINISHED_SEQUENCE      0x03
#define WIFI_ERROR_SEQUENCE         0x04

#define Rte_Write_System_Mode(DATA)													Rte_Compounent_Read_Write_Shared_Data(SYSTEM_MODE,WRITE_MESSAGE,DATA,NULL)
#define Rte_Read_System_Mode(POINTER)    											Rte_Compounent_Read_Write_Shared_Data(SYSTEM_MODE,READ_MESSAGE,NULL,POINTER)

#define Rte_Write_Object_Finished_WIFI_Seq(DATA)									Rte_Compounent_Read_Write_Shared_Data(OBJECT_FINISHED_WFIFI_INIT,WRITE_MESSAGE,DATA,NULL)
#define Rte_Read_Object_Finished_WIFI_Seq(POINTER)    								Rte_Compounent_Read_Write_Shared_Data(OBJECT_FINISHED_WFIFI_INIT,READ_MESSAGE,NULL,POINTER)

#define Rte_Write_WIFI_Sequenc_Variable(DATA)								Rte_Compounent_Read_Write_Shared_Data(WIFI_SEQUENCE_VARIABLE,WRITE_MESSAGE,DATA,NULL)
#define Rte_Read_WIFI_Sequenc_Variable(POINTER)    						    Rte_Compounent_Read_Write_Shared_Data(WIFI_SEQUENCE_VARIABLE,READ_MESSAGE,NULL,POINTER)

#define Rte_Write_Status_ID(DATA)								Rte_Compounent_Read_Write_Shared_Data(STATUS_ECU_ID,WRITE_MESSAGE,DATA,NULL)
#define Rte_Read_Status_ID(POINTER)    						    Rte_Compounent_Read_Write_Shared_Data(STATUS_ECU_ID,READ_MESSAGE,NULL,POINTER)
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

u8 Rte_Compounent_Read_Write_Shared_Data(u8 copy_ID_Of_Variable,u8 copy_Read_Write,u8 copy_Data,u8* Pointer_to_Get_Data_In);

u8 Rte_Compounent_Read_Write_Shared_Data_Messages(u8 copy_Message_ID,u8 Read_OR_Write,u8* pointer_Data,u8 Number_of_Elments,u8 Reader_Receciver_ID);
static u8 Rte_Read_Write_Message(u8* source,u8 Read_OR_Write,u8 Number_of_Elments,u8* Destination);

#endif /* RTE_H_ */
