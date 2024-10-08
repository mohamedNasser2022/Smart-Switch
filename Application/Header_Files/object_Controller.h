/*
 * object_Controller.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */


#include "LIB_ERROR.h"



#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H

typedef struct{

	u8 Input_PIN_ID;
	u8 Current_State_Pin:1;
	u8 Last_State_Pin:1;

}Switch_t;
#define PIN_HIGH 1
#define PIN_LOW  0
typedef struct{

	u8 Object_WIFI_ID;
	u8 Output_PIN_ID;
	u8 Object_Number_In_Status_Message;
	u8 Timer_Referance_Mins;
	u32 Time_Counter;
	Switch_t* Pointer_Switch;

}Relay_t;


enum
{
	OBJECT_INTIOLIZATION_MODE = 0x90,
	operation_Done,
	Nvm_Read_Mode,
 	OBJECT_ERROR ,
 	OBJECT_RUNNING_NORMAL,

}Object_System_Mode;


typedef struct{

	u8 Relay_Counter;
	u8 Switch_Counter;
	u8 Object_App_Status;
	u8 Object_Status_ID;

}Object_Data_Manger_t;


enum
{
	Toggle_Command = 10,
	Request_Status,
	Request_Reading,
	Time_Change,
	Request_Time_Ref_Read,
	Respond_Message,

}Message_0x10_Enum_Modes;




/*------------------------------------------------Messages Interface----------------------------------------------------------*/
#define THIS_MY_ID  SW_OBJECT_ID









/*---------------------------------------------------------------------------------------------------------------------------*/
void Object_Init(void);

void Object_Polling(void);

void Object_Periodic(void);

u8 Object_Relays_Switches_Initialization(void);
u8 Relay_Initilaizations(u8 Object_ID_IN_Local_ECU,u8 Com_WIFI_ID,u8 Relay_Pin,u8 switch_Pin,u32 Time_to_Be_off_In_Seconds);

/*Private Functions*/

static void Runnable_Object_Init_Objects_In_WIFI_10ms(void);
static void Runnable_Object_Message_0x10_5ms(void);
static u8 Get_Search_About_WIFI_ID(u8 copy_ID,Relay_t** Pointer_Relay);
static void Runnable_Object_Auto_Off_50ms(void);
static void Runnable_Object_Read_Inputs_Pins_And_Update_Output_Each_10ms(void);
static void Runnable_Object_Update_Relays_And_Switch_Status_10ms(void);
static void Runnable_Object_Update_Relays_Status_10ms(void);
static void Runnable_Load_Nvm_Data(void);
static void Runnable_Object_Time_Data_Update(void);

#endif
