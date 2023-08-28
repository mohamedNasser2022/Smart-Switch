/*
 * Comunication_Manger.h
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Nasser
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"





#ifndef COMUNICATION_MANGER_H_
#define COMUNICATION_MANGER_H_
void Comunication_Manger_Init(void);
#define Uart_Manger_Write_Port_to_Comunication_Manger(POINTER_DATA) Comunication_Manger_Recive_Data_From_Comunication_Hardware_Manger(POINTER_DATA)
#define I2C_Manger_Write_Port_to_Comunication_Manger(POINTER_DATA) Comunication_Manger_Recive_Data_From_Comunication_Hardware_Manger(POINTER_DATA)
u8 Comunication_Manger_Send_Messages_to_Prtocol_Translator(void *Pointer_to_Queue);
u8 Comunication_Manger_Receive_Messages_From_Prtocol_Translator(void *Pointer_to_Queue);
static void Comunication_Manger_Fetch_Data_From_Rte(void);
static void Comunication_Manger_Send_Data_Rte(void);
static void Comunication_Manger_ParseData_to_Comunication_ID(void);
static void Comunication_Manger_Send_Data_to_Rte(void);
void Comunication_Manger_Read_Data_From_Uart_Manger_Port(Comuncation_Manger_Interface *Pointer_Data);


#endif /* COMUNICATION_MANGER_H_ */
