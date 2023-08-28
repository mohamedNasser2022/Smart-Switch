/*
 * Data_Structure.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Mohamed Nasser
 */


#include"STD_TYPES.h"
#include"System_Main.h"

#include"Lib.h"

#include"Writing_Message_Stratage.h"

#ifndef DATA_STRUCTURE_H_
#define DATA_STRUCTURE_H_



typedef struct
{
	u8 Button_Mode;
	u8 Button_Pressed_counter;
	u8 Pin_ID;
	u8 Button_Current_Status:1;
	u8 Button_Pervious_Status:1;
	u16 Button_Time_Counter_ms;
}push_button_t;

#define BUTTON_NOT_PRESSED         1
#define BUTTON_PRESSED		       0
#define BUTTON_CONFIRMED_PRESSED   2
#define BUTTON_RESET_TIME_MS       5*1000
#define BUTTON_AUTO_RESET_TIME_MS  30*1000



/*************************************************************************/
#endif /* DATA_STRUCTURE_H_ */
