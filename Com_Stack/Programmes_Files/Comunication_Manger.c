/*
 * Comunication_Manger.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Nasser
 *      Version : V01
 */
#include"Data_Structure.h"
#include"RTE.h"
#include"Queue_Interface.h"

#include"Comunication_Manger.h"
#include"I2C_Manger.h"
#include"System_Main.h"

#define Queue_Push_Com_Manger(POINTER,DATA)  Queue1_Push(POINTER,DATA)
#define Queue_Pop_Com_Manger(POINTER,DATA)  Queue1_Pop(POINTER,DATA)

#define Nested_Queue_Push_Com_Manger(QUEUE_POINTER,DATA)  Nested_Queue1_Push(QUEUE_POINTER,DATA)
#define Nested_Queue_Pop_Com_Manger(QUEUE_POINTER,DATA)  Nested_Queue1_Pop(QUEUE_POINTER,DATA)

/*-------------For Largest Data ----------*/
#define Queue_Push_Com_Manger_Largest(POINTER,DATA)  Queue2_Push(POINTER,DATA)
#define Queue_Pop_Com_Manger_Largest(POINTER,DATA)  Queue2_Pop(POINTER,DATA)

#define Nested_Queue_Push_Com_Manger_Largest(QUEUE_POINTER,DATA)  Nested_Queue2_Push(QUEUE_POINTER,DATA)
#define Nested_Queue_Pop_Com_Manger_Largest(QUEUE_POINTER,DATA)  Nested_Queue2_Pop(QUEUE_POINTER,DATA)

/*-----------------*/

#define SUCCESS  1
#define ERROR    0

Queue_Of_Message_Data_0_Nested Queue_Of_Messages_To_Send;
Queue_Of_Message_Data_1_Nested Queue_Of_Messages_To_Send_1;  /*For message above 10 bytes*/
Comuncation_Manger_Interface_Nested Buffe_Comunication_Contain_Data_which_Received_Throw_Hardware_Comunication;

void Comunication_Manger_Init(void)
{
	I2C_Manger_Init();
	Uart_Manger_Init();
	Nested_Queue1_Create(&Queue_Of_Messages_To_Send);
	Nested_Queue2_Create(&Queue_Of_Messages_To_Send_1);
	Nested_Queue0_Create(&Buffe_Comunication_Contain_Data_which_Received_Throw_Hardware_Comunication);


}

void comunication_Manger_Polling(void)
{


	/*Comunication_Manger_Fetch_Data_From_Rte();
	Comunication_Manger_Send_Data_to_Rte();*/
	Comunication_Manger_ParseData_to_Comunication_ID();

	Uart_Manger_ContinousPolling();
	I2C_Manger_Polling();
}

/*---------------------*/

u8 Comunication_Manger_Send_Messages_to_Prtocol_Translator(void *Pointer_to_Queue)
{

	Protocol_Translator_Receive_Messages_From_Comunication_Manger(Pointer_to_Queue);

}



u8 Comunication_Manger_Receive_Messages_From_Prtocol_Translator(void *Pointer_to_Queue)
{
	u8 Local_Return = 0;

	u8 Local_Size = Queue1_Size(Pointer_to_Queue);

	if(Local_Size < 10)
	{
		Nested_Queue_Push_Com_Manger(&Queue_Of_Messages_To_Send,Pointer_to_Queue);
	}
	else if(Local_Size < 45)
	{
		Nested_Queue_Push_Com_Manger_Largest(&Queue_Of_Messages_To_Send_1,Pointer_to_Queue);
	}
	else
	{

	}
	return Local_Return;
}




static void Comunication_Manger_ParseData_to_Comunication_ID(void)
{
	u8 Local_Get_Return = 7;
	Queue_Of_Message_Data_0 Local_Swap;
	Queue1_Clear(&Local_Swap);
	u8 Comuncation_Destine ;
	Queue1_Pop(&Queue_Of_Messages_To_Send.Queue_Elements[Queue_Of_Messages_To_Send.Front],&Comuncation_Destine); // Destination

	if(Nested_Queue1_Pop(&Queue_Of_Messages_To_Send,&Local_Swap))
	{


		switch(Comuncation_Destine)
		{
		case I2C_No_1:	 /*Send Data to I2C_Manger*/
			Local_Get_Return = Comuncation_Manger_Send_Data_to_I2C_Buffer(&Local_Swap);

			break;
		case UART_No_1:
			Local_Get_Return = Comuncation_Manger_Send_Data_to_UART_Buffer(&Local_Swap);
			break;
		default:
			break;
		}
	}
	if(Local_Get_Return == SUCCESS)
	{

	}
	else if(Local_Get_Return == ERROR)
	{
		Nested_Queue1_Push(&Queue_Of_Messages_To_Send,&Local_Swap);
	}
	else
	{

	}

	/*Larg*/
	Queue_Of_Message_Data_1 Local_Swap_Larg;
	Queue2_Clear(&Local_Swap_Larg);

	Comuncation_Destine = 0;
	Queue2_Pop(&Queue_Of_Messages_To_Send_1.Queue_Elements[Queue_Of_Messages_To_Send_1.Front],&Comuncation_Destine); // Destination

		if(Nested_Queue2_Pop(&Queue_Of_Messages_To_Send_1,&Local_Swap_Larg))
		{


			switch(Comuncation_Destine)
			{
			case I2C_No_1:	 /*Send Data to I2C_Manger*/
				Local_Get_Return = Comuncation_Manger_Send_Data_to_I2C_Buffer(&Local_Swap_Larg);

				break;
			case UART_No_1:
				Local_Get_Return = Comuncation_Manger_Send_Data_to_UART_Buffer(&Local_Swap_Larg);
				break;
			default:
				break;
			}
		}
		if(Local_Get_Return == SUCCESS)
		{

		}
		else if(Local_Get_Return == ERROR)
		{
			Nested_Queue1_Push(&Queue_Of_Messages_To_Send,&Local_Swap);
		}
		else
		{

		}

}

//Comunication_Manger_Read_Data_From_Uart_Manger_Port
/*------------------------------------------------------Uart_Manger_Ports--------------------------------------------*/
void Comunication_Manger_Recive_Data_From_Comunication_Hardware_Manger(void *Pointer_Data) //Received port
{
	Protocol_Translator_Receive_Messages_Comunication_Manger(Pointer_Data);



}
/*--------------------------------------------------------------------------------*/
