/*
 * DIO_Expander_Interface.h
 *
 *  Created on: Jun 4, 2023
 *      Author: Mohamed Nasser
 */
#include"DIO_Expander_Config.h"
#ifndef I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_INTERFACE_H_
#define I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_INTERFACE_H_




void DIO_Expander_Set_Pin_Mode(u8 Pin_No,u8 Mode);
void DIO_Expander_Set_Pin_Level(u8 Pin_No,u8 Pin_Level);
void DIO_Expander_Toggle(u8 Pin_No);

#endif /* I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_INTERFACE_H_ */

