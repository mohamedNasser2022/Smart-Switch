/*
 * Smart_protocol.h
 *
 *  Created on: JAN 30, 2023
 *      Author: Mohamed Nasser
 *     Version: V02
 */

#include"Data_Structure.h"


#ifndef SMART_PROTOCOL_PRIVATE_H_
#define SMART_PROTOCOL_PRIVATE_H_

#define THIS_MY_ID  SW_PROTOCOL_TRANSLATOR_ID

#define MAX_NUMER_OF_DATA_LENGTH  42




/*------------------------------------------------------------------------------*/
static void Runnable_Read_Messages_Status_10ms(void);
static void Runnable_Read_Messages_1ms(void);

static void Protocol_Translator_Fetch_Data_From_Comunication_Manger_Throw_Rte(void);
static void Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(u8* Pointer_To_Data,u8 copy_MessageID,u8 copy_Data_Length);
static void Protocol_Translator_Fetch_Message_From_Rte(void);
static void Gate_Way(u8* Message);
static void Removing_Comunication_Header_Create_Message(void* Pointer_Data);
static void Rte_Read_Ports(void);
static void Protocol_Translator_Send_Data_To_Other_Compounents(void);

#endif /* SMART_PROTOCOL_H_ */
