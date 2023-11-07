/*
 * System_Mode.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */

#ifndef SYSTEM_MODE_H_
#define SYSTEM_MODE_H_

#define PIN_TO_RESET_SYSTEM_CONFIGRUTIONS  25
#define THIS_MY_ID  SW_SYSTEM_MODE_ID











/*--------------------------------------------------------------------------------------------------*/
static void System_Init_WIFI_Mode_Sequence(void);
static void System_Fetch_Messages(void);
static void System_Mode_Message_0x03_Analize(u8* Pointer_Data);
static void Runnable_System_Mode_Wifi_Init(void);
static void System_Fetch_Shared_Variables(void);
static void Push_Button_Task(void);

static u8 System_Mode_Write_0x01(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_u8_Data3);
static u8 System_Mode_Write_0x02(u8 copy_u8_Data1);
static u8 System_Mode_RRead_0x03(void);
/********************************************************************************************************************************************/
#endif /* SYSTEM_MODE_H_ */
