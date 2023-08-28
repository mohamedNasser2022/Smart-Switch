/*
 * DIO_Expander_Comunication_Layer_Interface.h
 *
 *  Created on: Jun 4, 2023
 *      Author: Mohamed Nasser
 */

#ifndef I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_COMUNICATION_LAYER_INTERFACE_H_
#define I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_COMUNICATION_LAYER_INTERFACE_H_

#define DIO_Expander_ADDRESS    0x7C

#define DIO_Expander_Reading_From_Chip(POINTER,LENTH_OF_READING,FUNC) Reading_From_I2C_Perpherial_1(DIO_Expander_ADDRESS,POINTER,LENTH_OF_READING,FUNC)

static void DIO_Expander_Com_Check_Buffer_And_Send_Data_To_Physical_Layer(void);
static void DIO_Expander_Com_Check_If_Updates_Needed(void);
static u8 Reconfigure_Read_Pointer(u8 Register_Address);
static u8 Request_of_Reading(u8 copy_Reading_Starting_from,u8 Lenght_of_Reading);
static void Notification_Handler_I2C(void* ptr);

#endif /* I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_COMUNICATION_LAYER_INTERFACE_H_ */
