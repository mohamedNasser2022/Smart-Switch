/*
 * object_Controller.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */


#include "LIB_ERROR.h"
#include "Objects_Definitions.h"


#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H

typedef struct{

	u8 Input_PIN_ID;
	u8 Last_State_Pin:1;

}Switch_t;

typedef struct{

	u8 Object_WIFI_ID;
	u8 Output_PIN_ID;
	u8 Object_Number_In_Status_Message;
	u32 Timer_Referance:20;
	u32 SaveTriggerTimer:20;
	Switch_t* Pointer_Switch;

}Relay_t;



#define OBJECT_INTIOLIZATION_MODE 0x90
#define OBJECT_ERROR  			  0x80
#define OBJECT_RUNNING_NORMAL     0x70

typedef struct{

	u8 Relay_Counter;
	u8 Switch_Counter;
	u8 Object_App_Status;
	u8 Object_Status_ID;

}Object_Data_Manger_t;




#define OBJECT_TOGGLE   8
#define OBJECT_STATUS	9
#define OBJECT_READING  10
#define OBJECT_OFF      11
#define OBJECT_ON       12
#define OBJECT_ERROR    50

/*------------------------------------------------Messages Interface----------------------------------------------------------*/
#define THIS_MY_ID  SW_OBJECT_ID









/*---------------------------------------------------------------------------------------------------------------------------*/
void Object_Init(void);

void Object_Polling(void);

void Object_Periodic(void);


/*Private Functions*/
static u8 Relay_Initilaizations(u8 Object_ID_IN_Local_ECU,u8 Com_WIFI_ID,u8 Relay_Pin,u8 switch_Pin,u32 Time_to_Be_off_In_Seconds);
/*********************************************************************************Messages****************************************************************************/

static void Object_Fetch_Message_From_Rte(void);
static void Object_Analize_Message_0x10(u8* Pointer_Data);



/**************************************************************************************************************************************************************************************/
static void Object_Init_Objects_In_WIFI(void);

static void Object_Fetch_Shared_Varaibles(void);
static u8 Get_Search_About_WIFI_ID(u8 *Pointer_ID);
//
static void Object_Status_Message_Send_Each_10ms(void);
/**/
#endif
