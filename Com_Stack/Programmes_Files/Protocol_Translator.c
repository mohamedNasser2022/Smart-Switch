/*
 * Smart_protocol.h
 *
 *  Created on: JAN 30, 2023
 *      Author: Mohamed Nasser
 *     Version: V03
 */



#include "Queue_Interface.h"
#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"Data_Structure.h"
#include"RTE.h"
#include"System_Main.h"

#include"Comunication_Manger.h"
#include "Protocol_Translator.h"
#include "Protocol_Translator_Private.h"

volatile u32 Protocol_System_Time_ms = 0;

void HAL_voidSmartProtocol_Init(void)
{





}


void Protocol_Translator_Polling(void)
{
	volatile u8 Local_For_Test = 0;

	Rte_Read_Ports();


}


void Protocol_Translator_Time(void)
{
	Protocol_System_Time_ms++;

	if(Protocol_System_Time_ms % 200 == 0 )
	{
		HAL_voidCheckReceving_DataFrom_ComLayer_each_200ms();  // Polling on Recevied data
	}
	//if(System_Mode == GO_APPLICATION )
	{
		if(Protocol_System_Time_ms % 10 == 0)
		{
#if CONTROLLER_ID == STM_CONTROLLER
			HAL_voidSendObjectsStatusToWifiController_each_10ms();
#endif
		}
	}
}

static void Rte_Read_Ports(void)
{
	u8 Local_Data[MAX_NUMER_OF_DATA_LENGTH];
	if(Read_Done == Rte_Read_Message_0x01(&Local_Data))
	{
		Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(&Local_Data,MESSAGE_0x01,MESSAGE_ARRAY_ELEMENTS_NUMBER_0x01);
	}
	if(Read_Done == Rte_Read_Message_0x02(&Local_Data))
	{
		Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(&Local_Data,MESSAGE_0x02,MESSAGE_ARRAY_ELEMENTS_NUMBER_0x02);
	}

	if(Read_Done == Rte_Read_Message_0x13(&Local_Data))
	{
		Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(&Local_Data,MESSAGE_0x13,MESSAGE_ARRAY_ELEMENTS_NUMBER_0x13);
	}
	if(Read_Done == Rte_Read_Message_0x14(&Local_Data))
	{
		Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(&Local_Data,MESSAGE_0x14,MESSAGE_ARRAY_ELEMENTS_NUMBER_0x14);
	}
	if(Read_Done == Rte_Read_Message_0x20(&Local_Data))
	{
		Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(&Local_Data,MESSAGE_0x20,MESSAGE_ARRAY_ELEMENTS_NUMBER_0x20);
	}
	if(Read_Done == Rte_Read_Message_0x21(&Local_Data))
	{
		Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(&Local_Data,MESSAGE_0x21,MESSAGE_ARRAY_ELEMENTS_NUMBER_0x21);
	}



}

u8 Protocol_Translator_Receive_Messages_Comunication_Manger(void *Pointer_Data)
{
	u8 Local_Return = 0;



	Removing_Comunication_Header_Create_Message(Pointer_Data);




	return Local_Return;


}

static void Adding_And_Push_Message_Data_To_Comunication_Manger_Throw_Rte(u8* Pointer_To_Data,u8 copy_MessageID,u8 copy_Data_Length)
{
	if(copy_Data_Length < 10)
	{
		Comuncation_Manger_Interface Local_Swap;
		Queue0_Create(&Local_Swap);

		Queue0_Push(&Local_Swap,UART_No_1);

		Queue0_Push(&Local_Swap,copy_MessageID);

		Queue0_Push(&Local_Swap,ECU_NUMBER);  // need to Discuss

		for(u8 i = 0; i < copy_Data_Length; i++)
		{
			Queue0_Push(&Local_Swap,Pointer_To_Data[i]);
		}

		Comunication_Manger_Receive_Messages_From_Prtocol_Translator(&Local_Swap);
	}
	else if(copy_Data_Length < 45)
	{
		Array_Of_Queue_2 Local_Swap;
		Queue2_Create(&Local_Swap);

		Queue2_Push(&Local_Swap,UART_No_1);

		Queue2_Push(&Local_Swap,copy_MessageID);

		Queue2_Push(&Local_Swap,ECU_NUMBER);  // need to Discuss

		for(u8 i = 0; i < copy_Data_Length; i++)
		{
			Queue2_Push(&Local_Swap,Pointer_To_Data[i]);
		}

		Comunication_Manger_Receive_Messages_From_Prtocol_Translator(&Local_Swap);
	}
	else
	{

	}


}

static void Removing_Comunication_Header_Create_Message(void* Pointer_Data)
{
	//Gate_Way_Message
	volatile u8 Local_Counter = 1;
	volatile u8 Local_Data = 0;
	volatile u8 Local_ECU_ID = 0;
	u8 Comunication_Header = 0;
	u8 Local_Array[MAX_NUMER_OF_DATA_LENGTH];


	Queue0_Pop(Pointer_Data,&Comunication_Header);   // Comunication Header
	Queue0_Pop(Pointer_Data,&Local_Array[0]);        // Message ID
	Queue0_Pop(Pointer_Data,&Local_ECU_ID); 		 // ECU ID

	while(Queue0_Pop(Pointer_Data,&Local_Data))
	{
		Local_Array[Local_Counter] = Local_Data;
		Local_Counter++;
	}

	Gate_Way(Local_Array);

}

static void Gate_Way(u8* Message_Data)
{


	switch(Message_Data[0])
	{
	case MESSAGE_0x03:

		Rte_Write_Message_0x03(Message_Data[1],Message_Data[2]);

		break;
	case MESSAGE_0x10:

		Rte_Write_Message_0x10(&Message_Data[1]);

		break;
	default:


		break;
	}

}



