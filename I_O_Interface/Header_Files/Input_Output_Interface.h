/*
 * Input_Outpu_Interface.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Mohamed Nasser
 */
#include "STD_TYPES.h"

#include"Input_Output_Configuration.h"

#ifndef INPUT_OUTPUT_INTERFACE_H_
#define INPUT_OUTPUT_INTERFACE_H_

#define VIRTUAL_PIN_0 	VIRTUAL_PIN_TO_PHY_PIN_0
#define VIRTUAL_PIN_1 	VIRTUAL_PIN_TO_PHY_PIN_1
#define VIRTUAL_PIN_2 	VIRTUAL_PIN_TO_PHY_PIN_2
#define VIRTUAL_PIN_3 	VIRTUAL_PIN_TO_PHY_PIN_3
#define VIRTUAL_PIN_4 	VIRTUAL_PIN_TO_PHY_PIN_4
#define VIRTUAL_PIN_5 	VIRTUAL_PIN_TO_PHY_PIN_5
#define VIRTUAL_PIN_6 	VIRTUAL_PIN_TO_PHY_PIN_6
#define VIRTUAL_PIN_7 	VIRTUAL_PIN_TO_PHY_PIN_7
#define VIRTUAL_PIN_8 	VIRTUAL_PIN_TO_PHY_PIN_8
#define VIRTUAL_PIN_9 	VIRTUAL_PIN_TO_PHY_PIN_9
#define VIRTUAL_PIN_10 	VIRTUAL_PIN_TO_PHY_PIN_10
#define VIRTUAL_PIN_11 	VIRTUAL_PIN_TO_PHY_PIN_11
#define VIRTUAL_PIN_12 	VIRTUAL_PIN_TO_PHY_PIN_12
#define VIRTUAL_PIN_13 	VIRTUAL_PIN_TO_PHY_PIN_13


void I_O_Interface_Initiolization(void);
u8 I_O_Interface_Init_Pin(u8 copy_Pin_ID,u8 copy_Pin_Mode);
u8 I_O_Interface_set_Pin_Level(u8 copy_Pin_ID,u8 copy_Pin_Level);
u8 I_O_Interface_Read_Pin_Level(u8 copy_Pin_ID,u8* Location_of_Pin_State_Level_Save);
u8 I_O_Interface_Toggle_Pin(u8 copy_Pin_ID);


/*-----------------------private Functions -----------------------------*/




#endif /* INPUT_OUTPU_INTERFACE_H_ */
