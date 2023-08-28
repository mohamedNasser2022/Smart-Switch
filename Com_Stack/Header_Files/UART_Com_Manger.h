/*
 * Com.c
 *
 *  Created on: Sep 9, 2022
 *      Author: Mohamed Nasser
 *     Version: 01
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Stack_Interface.h"
#include"Queue_Interface.h"

#ifndef UART_COM_MANAGER_
#define UART_COM_MANAGER_


#define TRANSMIT_MODE     10
#define BUSY_MODE         50
#define IDEAL_MODE 	      20
#define RECEVIE_MODE      30
#define ACK_RECEIVE 	  60


#define TIMEOUT_RESET_BUS 200
#define ACK_PROTOCOL_SEND	0x05
#define SENDING_BUFFER  0x01
#define RECEVING_BUFFER 0x02


#define SUCCESS_FILLED 0x01
#define NO_DATA 0x08
#define BUFFER_IS_FULL 0x06


u8 Comuncation_Manger_Send_Data_to_UART_Buffer(void* Pointer_To_Data);
void UART_Manger_Time(void);
void HAL_voidCom_Init(void);
void Uart_Manger_ContinousPolling(void);
void UART_Manger_Write_Data_To_Comunication_Manger(void);

static u8 HAL_staticu8_Comuncation_Handler(Uart_Buffer *Queue_ptr,Uart_Buffer *STACK_ptr);
static void UART_Check_Logic(u8 Current_Data_Recived);
static void HAL_staticvoidCom_Send_Ack(void);
static void HAL_staticvoid_Com_CheckBus_Status(void);
static u8 UART_Com_Interface_Transmit(Uart_Buffer *Queue_ptr);
static u8 UART_Com_Interface_Recive(Uart_Buffer *Queue_ptr);
static void Uart_Manger_Move_Data_From_Send_Buffer_Header_to_Send_Buffer(void);
static void Comunication_Sequence_Reset(void);




#endif /* COM_H_ */
