/*
 * Smart_protocol.h
 *
 *  Created on: JAN 30, 2023
 *      Author: Mohamed Nasser
 *     Version: V02
 */



#include"Data_Structure.h"


#ifndef SMART_PROTOCOL_H_
#define SMART_PROTOCOL_H_

#define WIFI_CONTROLLER 2
#define STM_CONTROLLER 1
#define CONTROLLER_ID  STM_CONTROLLER


/*---------------------------------Interface with System Mode & Protocol------------------------------------------------------------------------------------------------------------*/
#define Protocol_Translator_0x01_to_System_Mode(DATA0,DATA1,DATA2)	                       Rte_Write_Message_0x01(DATA0,DATA1,DATA2,SW_SYSTEM_MODE_ID)
#define Protocol_Translator_Read_0x01(POINTER)											   Rte_Read_Message_0x01(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x02(DATA0)	      							   Rte_Write_Message_0x02(DATA0,SW_SYSTEM_MODE_ID)
#define Protocol_Translator_Read_Message_0x02(POINTER)									   Rte_Read_Message_0x02(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x03(DATA0,DATA1,DATA2)	       				   Rte_Write_Message_0x03(DATA0,DATA1,DATA2,SW_SYSTEM_MODE_ID)
#define Protocol_Translator_Read_Message_0x03(POINTER)									   Rte_Read_Message_0x03(POINTER,THIS_MY_ID)
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------Interface with Objects & Protocol------------------------------------------------------------------------------------------------------------*/

#define Protocol_Translator_Write_Message_0x10(DATA0,DATA1,DATA2,DATA3,DATA4,DATA5)	        Rte_Write_Message_0x10(DATA0,DATA1,DATA2,DATA3,DATA4,DATA5,SW_OBJECT_ID)
#define Protocol_Translator_Read_Message_0x10(POINTER)										Rte_Read_Message_0x10(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x11(DATA0,DATA1,DATA2,DATA3,DATA4,DATA5)	        Rte_Write_Message_0x11(DATA0,DATA1,DATA2,DATA3,DATA4,DATA5,SW_OBJECT_ID)
#define Protocol_Translator_Read_Message_0x11(POINTER)										Rte_Read_Message_0x11(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x13(DATA0,DATA1,DATA2,DATA3,DATA4,DATA5)	        Rte_Write_Message_0x13(DATA0,DATA1,DATA2,DATA3,DATA4,DATA5,SW_OBJECT_ID)
#define Protocol_Translator_Read_Message_0x13(POINTER)										Rte_Read_Message_0x13(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x14(DATA0,DATA1)	        						Rte_Write_Message_0x14(DATA0,DATA1,SW_OBJECT_ID)
#define Protocol_Translator_Read_Message_0x14(POINTER)										Rte_Read_Message_0x14(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x20(POINTER)	        						    Rte_Write_Message_0x20(POINTER,SW_WIFI_MANGER_ID)
#define Protocol_Translator_Read_Message_0x20(POINTER)										Rte_Read_Message_0x20(POINTER,THIS_MY_ID)

#define Protocol_Translator_Write_Message_0x21(POINTER)	        						    Rte_Write_Message_0x21(POINTER,SW_WIFI_MANGER_ID)
#define Protocol_Translator_Read_Message_0x21(POINTER)										Rte_Read_Message_0x21(POINTER,THIS_MY_ID)
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/




#endif /* SMART_PROTOCOL_H_ */
