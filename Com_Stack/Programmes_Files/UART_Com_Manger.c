/*
 * Com.c
 *
 *  Created on: Jan 28, 2023
 *      Author: Mohamed Nasser
 *     Version: 02
 */



#include"STD_TYPES.h"
#include"BIT_MATH.h"


#include"UART_interface.h"
#include"Queue_Interface.h"

#include"SYSTICK_interface.h"

#include"Data_Structure.h"
#include"UART_Com_Manger.h"
#include"Comunication_Manger.h"

static Uart_Buffer_Nested Buffer_UART_Data_to_be_Send;
static Uart_Buffer_Nested Buffer_UART_Data_to_be_Recevied;

static volatile u8 Comunication_Pervious_Byte = 0;
static volatile u8 Comunication_Current_Byte = 0;

Uart_Buffer Send_Data_UART;
Uart_Buffer Recived_Data_UART;

#define UART_START_CONDITIONS 0x0A
#define UART_STOP_CONDITIONS  0x0F
#define UART_HEADER 0x90
#define SUCCESS  1
#define ERROR    0

volatile u32 UART_Manger_System_Time_ms = 0;
volatile u8 Enable_Count_to_Rest_Bus = 0;

volatile u8 count_to_Reset_ms = 0;

volatile u8 BUS_Mode_Flag = IDEAL_MODE; // 10 Transmit  30 Recived mode  20 Ideal mode

static volatile u8 Local_Ack_Recived_Flag = 0;


void Uart_Manger_Init(void)
{

	MUSART_voidInit();

	Queue3_Create(&Send_Data_UART); //Initalization Queue
	Queue3_Create(&Recived_Data_UART);
	Nested_Queue3_Create(&Buffer_UART_Data_to_be_Send);
	Nested_Queue3_Create(&Buffer_UART_Data_to_be_Recevied);


}


void Uart_Manger_ContinousPolling(void)
{


	HAL_staticvoid_Com_CheckBus_Status();
	UART_Manger_Write_Data_To_Comunication_Manger();
	Uart_Manger_Move_Data_From_Send_Buffer_Header_to_Send_Buffer();
	HAL_staticu8_Comuncation_Handler(&Send_Data_UART,&Recived_Data_UART);

}

void UART_Manger_Time(void)
{
	UART_Manger_System_Time_ms++;

	if(BUS_Mode_Flag != IDEAL_MODE)
	{
		count_to_Reset_ms++;
		if(count_to_Reset_ms == TIMEOUT_RESET_BUS)
		{

			Comunication_Sequence_Reset();
			count_to_Reset_ms = 0;
		}
	}
	else
	{
		count_to_Reset_ms = 0;
	}

}

static void Comunication_Sequence_Reset(void)
{
	BUS_Mode_Flag = IDEAL_MODE;
	Queue3_Clear(&Send_Data_UART); //Initalization Queue
	Queue3_Clear(&Recived_Data_UART);
	Comunication_Pervious_Byte = 0;
	Comunication_Current_Byte = 0;
	Nested_Queue3_Clear(&Buffer_UART_Data_to_be_Send);
	Nested_Queue3_Clear(&Buffer_UART_Data_to_be_Recevied);
}

u8 Comuncation_Manger_Send_Data_to_UART_Buffer(void* Pointer_To_Data)
{

	u8 Local_Return = 0;
	if(Nested_Queue3_Push(&Buffer_UART_Data_to_be_Send,Pointer_To_Data))
	{
		Local_Return =  SUCCESS;

	}
	else
	{
		Local_Return = ERROR;
	}
	return Local_Return;

}

void UART_Manger_Write_Data_To_Comunication_Manger(void)
{
	Comuncation_Manger_Interface Local_Data_Swap;
	Queue3_Clear(&Local_Data_Swap);
	Queue3_Push(&Local_Data_Swap,UART_HEADER);

	if(Nested_Queue3_Pop(&Buffer_UART_Data_to_be_Recevied,&Local_Data_Swap))
	{

		Uart_Manger_Write_Port_to_Comunication_Manger(&Local_Data_Swap);

	}



}




static void Uart_Manger_Move_Data_From_Send_Buffer_Header_to_Send_Buffer(void)
{
	Uart_Buffer Local_Data_Swap;
	Queue3_Clear(&Local_Data_Swap);
	u8 Local_Data = 0;

	if(BUS_Mode_Flag == IDEAL_MODE)
	{
		if(Nested_Queue3_Pop(&Buffer_UART_Data_to_be_Send,&Local_Data_Swap))
		{
			Queue3_Push(&Send_Data_UART,UART_START_CONDITIONS);
			Queue3_Push(&Send_Data_UART,UART_START_CONDITIONS);

			while(Queue3_Pop(&Local_Data_Swap,&Local_Data))
			{
				Queue3_Push(&Send_Data_UART,Local_Data);

			}

			Queue3_Push(&Send_Data_UART,UART_STOP_CONDITIONS);
			Queue3_Push(&Send_Data_UART,UART_STOP_CONDITIONS);
			BUS_Mode_Flag = TRANSMIT_MODE;

		}
		else
		{

		}
	}




}

static void Uart_Manger_Move_Data_From_Received_Buffer_to_Received_Header_Buffer(void)
{
	Comuncation_Manger_Interface Local_Data_Swap;
	Queue3_Clear(&Local_Data_Swap);
	u8 Local_Data_Byte_1 = 0;
	u8 Local_Data_Byte_2 = 0;


	while(Queue3_Pop(&Recived_Data_UART,&Local_Data_Byte_1))
	{
		Queue3_Push(&Local_Data_Swap,Local_Data_Byte_1);
		if(Queue3_Size(&Recived_Data_UART) == 2)
		{
			Queue3_Pop(&Recived_Data_UART,&Local_Data_Byte_1);
			Queue3_Pop(&Recived_Data_UART,&Local_Data_Byte_2);
			if(Local_Data_Byte_1 == UART_STOP_CONDITIONS && Local_Data_Byte_2 == UART_STOP_CONDITIONS)
			{

			}
		}
		else
		{


		}

	}

	Nested_Queue3_Push(&Buffer_UART_Data_to_be_Recevied,&Local_Data_Swap);






}





static u8 HAL_staticu8_Comuncation_Handler(Uart_Buffer *Queue_ptr,Uart_Buffer *STACK_ptr)
{

	volatile u8 Local_Return_Fun = 0;
	u8 Local_Data_Recived = 0;

	switch(BUS_Mode_Flag)
	{
	case IDEAL_MODE:
		if(MUSART_u8Recive_Polling(&Local_Data_Recived))
		{
			UART_Check_Logic(Local_Data_Recived);
			HAL_staticvoidCom_Send_Ack();
		}
		break;
	case BUSY_MODE:
		if(MUSART_u8Recive_Polling(&Local_Data_Recived))
		{
			UART_Check_Logic(Local_Data_Recived);
			HAL_staticvoidCom_Send_Ack();
		}
		break;
	case TRANSMIT_MODE:
		Local_Return_Fun = UART_Com_Interface_Transmit(Queue_ptr);
		if(Local_Return_Fun == 1)
		{// Switch to ACK mode
			BUS_Mode_Flag = ACK_RECEIVE;
		}
		else if(Local_Return_Fun == 2)
		{// Transmit Finished
			BUS_Mode_Flag =  IDEAL_MODE;
		}
		else if(Local_Return_Fun == 0)
		{
			// Wait
		}
		else
		{

		}

		break;
	case RECEVIE_MODE:

		Local_Return_Fun =	UART_Com_Interface_Recive(STACK_ptr);

		if(BUS_Mode_Flag == IDEAL_MODE)
		{
			Uart_Manger_Move_Data_From_Received_Buffer_to_Received_Header_Buffer();
		}

		break;
	case ACK_RECEIVE:

		if(MUSART_u8Recive_Polling(&Local_Data_Recived) )
		{
			if(Local_Data_Recived == ACK_PROTOCOL_SEND)
			{
				BUS_Mode_Flag = TRANSMIT_MODE;

			}
			else
			{
				//Recived Wrong Data
			}
		}

		break;
	default:

		break;

	}

}


static void HAL_staticvoidCom_Send_Ack(void)
{
	MUSART_u8TransmitNumbers_Polling(ACK_PROTOCOL_SEND);

}




static void HAL_staticvoid_Com_CheckBus_Status(void)
{
	if(BUS_Mode_Flag != IDEAL_MODE || Local_Ack_Recived_Flag != 0)
	{

		Enable_Count_to_Rest_Bus = 1; //Start count


	}
	else
	{
		Enable_Count_to_Rest_Bus = 0;
		count_to_Reset_ms = 0;
	}


}





static u8 UART_Com_Interface_Transmit(Uart_Buffer *Queue_ptr)
{


	u8 Data_Send = 0;
	if(Queue3_Pop(Queue_ptr,&Data_Send))
	{


		if(MUSART_u8TransmitNumbers_Polling(Data_Send))
		{
			//Queue3_Pop(Queue_ptr,&Data_Send);
			return 1; //Send Success
		}
		else
		{

			return 0; //UART Is Busy
		}

	}
	else
	{
		return 2;  //Queue Is empty
	}

}



static u8 UART_Com_Interface_Recive(Uart_Buffer *Queue_ptr)
{
	u8 Data_Recived = 0;
	if(!Queue3_Full(Queue_ptr))
	{
		if(MUSART_u8Recive_Polling(&Data_Recived) )
		{
			Queue3_Push(Queue_ptr,Data_Recived); //Data Recived
			UART_Check_Logic(Data_Recived);
			HAL_staticvoidCom_Send_Ack();  //Ack should Send
			return 1;
		}
		else
		{

			return 0; //Data not Recived
		}

	}
	else
	{
		return 2; // Queue is Full
	}

}

static void UART_Check_Logic(u8 Current_Data_Recived)
{
	Comunication_Current_Byte = Current_Data_Recived;
	switch(BUS_Mode_Flag)
	{
	case IDEAL_MODE:

		BUS_Mode_Flag = BUSY_MODE;
		break;
	case BUSY_MODE:

		if(Comunication_Pervious_Byte == UART_START_CONDITIONS && Comunication_Current_Byte == UART_START_CONDITIONS)
		{
			BUS_Mode_Flag = RECEVIE_MODE;
		}
		else
		{

		}
		break;
	case RECEVIE_MODE:
		if(Comunication_Pervious_Byte == UART_STOP_CONDITIONS && Comunication_Current_Byte == UART_STOP_CONDITIONS)
		{
			BUS_Mode_Flag = IDEAL_MODE;
		}
		else
		{

		}
		break;
	case TRANSMIT_MODE:

		break;
	default:

		break;

	}
	Comunication_Pervious_Byte = Comunication_Current_Byte;
	Comunication_Current_Byte = 0;

}

/*
 #Bug 0001
  	  this bug consider that the Transmit won't report Busy, but if transmit report busy, it will push the
  	  data in the end of Queue.

 */
