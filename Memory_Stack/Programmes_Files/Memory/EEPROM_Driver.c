/*
 * EEPROM_Driver.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Mohamed Nasser
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Data_Structure.h"
#include"Queue_Interface.h"

#include"I2C_Interface.h"

#include"EEPROM_Driver_Private.h"
#include"EEPROM_Driver_Interface.h"
#include"EEPROM_Driver_Config.h"
volatile static u32 EEPROM_Driver_Time_ms = 0;
void (*EEPROM_Call_Back)(void*,void*,void*);

/*------------------------------------Typedef--------------------------------------------*/

static volatile EEPROM_Pages_Queue_Nested Queue_Of_Data;

struct
{
	u8 EEPROM_MODE;
	u8 EEPROM_MODE_Status;
	u8 EEPROM_Page_counter;
	u16 EEPROM_Current_Word_Address;

}EEPROM_Driver_System_Mode;



/*------------------------------------------------------------------------------------*/

void EEPROM_Driver_Initialization(void)
{
	EEPROM_Driver_System_Mode.EEPROM_MODE = Undefined;  /*----------------*/
	Nested_Queue5_Create(&Queue_Of_Data);

	EEPROM_Driver_Test_Address();

}

void EEPROM_Driver_Polling(void)
{


	test();



}


void EEPROM_Driver_Time(void)
{
	EEPROM_Driver_Time_ms++;
	if(EEPROM_Driver_Time_ms % 5 == 0)
	{
		EEPROM_Driver_Write_on_Physical();
		EEPROM_Erasing_ALL();
	}





}

void test(void)
{
	volatile u8 Control = 0;
	volatile u8 Data_Write = 20;
	EEROM_Queue Local_Queue_Data;
	Queue3_Create(&Local_Queue_Data);
	volatile u8 Local_Data = 2;


	if(1 == Control)
	{
		EEPROM_Driver_Write(0,&Local_Queue_Data);
	}
	else if(2 == Control)
	{

	}
	else if(3 == Control)
	{
		EEPROM_Driver_System_Mode.EEPROM_MODE = Erasing;
	}

}

u8 EEPROM_Driver_Write(u16 WordAddress,EEROM_Queue *Pointer_To_Queue)
{
	volatile u8 Local_Return = OK_EEPROM;
	u8 Local_Data = 0;

	u8 Local_Page = WordAddress / EEPROM_PAGE_SIZE ;
	u8 Local_Start_Byte_In_Page = WordAddress % EEPROM_PAGE_SIZE;
	u8 Local_Max_Size_Can_Stored_In_Current_Page = EEPROM_PAGE_SIZE - Local_Start_Byte_In_Page ;

	EEROM_Queue Local_Queue_Data;
	Queue3_Create(&Local_Queue_Data);

	Queue3_Push(&Local_Queue_Data,WordAddress);
	Queue3_Push(&Local_Queue_Data,(u8)(WordAddress >> 8));


	while(Queue3_Size(Pointer_To_Queue))
	{
		for(u8 i = 0 ;i < Local_Max_Size_Can_Stored_In_Current_Page ; i++)
		{
			if(Queue3_Pop(Pointer_To_Queue,&Local_Data))
			{
				Queue3_Push(&Local_Queue_Data,Local_Data);
			}
			else
			{
				break;
			}
		}

		if(Nested_Queue5_Push(&Queue_Of_Data,&Local_Queue_Data))
		{
			Local_Return = OK_EEPROM;
			Queue3_Create(&Local_Queue_Data);
			Local_Page ++;
			WordAddress = Local_Page * EEPROM_PAGE_SIZE;
			Queue3_Push(&Local_Queue_Data,WordAddress);
			Queue3_Push(&Local_Queue_Data,(u8)(WordAddress >> 8));
		}
		else
		{
			Local_Return = Faild_EEPROM;
		}
		Local_Max_Size_Can_Stored_In_Current_Page = 16;
	}



	return Local_Return;
}

u8 EEPROM_Driver_Read(u16 copy_Reading_Starting_from,u8 Lenght_of_Reading,void (*Pointer_Function)(void*))
{
	u8 Local_Return = Undefined;

	Array_Of_Queue_0  Local_Data;
	Queue3_Create(&Local_Data);



	Queue3_Push(&Local_Data,(u8)copy_Reading_Starting_from);
	if(EEPROM_Driver_System_Mode.EEPROM_MODE == Normal)
	{
		if(EEPROM_Driver_Read_From_Hardware(copy_Reading_Starting_from,&Local_Data,Lenght_of_Reading) )
		{
			EEPROM_Driver_System_Mode.EEPROM_MODE = Reading;
			EEPROM_Call_Back = Pointer_Function;
			Local_Return = On_Progress;
		}
		else
		{
			Local_Return = Faild_EEPROM;
		}
	}
	else
	{
		Local_Return = Faild_EEPROM;
	}



	return Local_Return;

}

u8 EEPROM_Driver_Erasing_All(void)
{
	u8 Local_Return = On_Progress;

	if(Normal == EEPROM_Driver_System_Mode.EEPROM_MODE)
	{
		EEPROM_Driver_System_Mode.EEPROM_MODE = Erasing;
		EEPROM_Driver_System_Mode.EEPROM_MODE_Status = Undefined;
	}
	else
	{
		Local_Return = Faild_EEPROM;
	}

	return Local_Return;
}

/*-------------------------------------- Private Functions-------------------------------------------*/
static void EEPROM_Driver_Write_on_Physical(void)
{
	EEROM_Queue Local_Queue_Data;
	Queue3_Create(&Local_Queue_Data);

	Array_Of_Queue_3 Local_Queue_Send_I2C ;
	Queue3_Create(&Local_Queue_Send_I2C);

	u8 Local_Data ;
	u16 Word_Addresses = 0;
	if(EEPROM_Driver_System_Mode.EEPROM_MODE == Normal)
	{
		if(Nested_Queue5_Pop(&Queue_Of_Data,&Local_Queue_Data))
		{
			Queue3_Pop(&Local_Queue_Data,&Local_Data); /*Reading Word address first 8 bits*/

			Word_Addresses = Local_Data;

			Queue3_Pop(&Local_Queue_Data,&Local_Data);  /*Reading Word address seconds 3 bits*/

			Word_Addresses |= (Local_Data << 8);

			Queue3_Push(&Local_Queue_Send_I2C,(u8) Word_Addresses );  	/*Word Address */

			while(Queue3_Pop(&Local_Queue_Data,&Local_Data))
			{
				Queue3_Push(&Local_Queue_Send_I2C,Local_Data);
			}
			/*Here you have to handel the writing pages*/
			if(EEPROM_Driver_Interface_With_I2C(Word_Addresses,&Local_Queue_Send_I2C))
			{
				EEPROM_Driver_System_Mode.EEPROM_Current_Word_Address = Word_Addresses; // Addresses
				EEPROM_Driver_System_Mode.EEPROM_MODE = Writing;


			}
			else
			{
				Nested_Queue5_Undo_Last_Pop(&Queue_Of_Data);
			}
		}
		else
		{

		}

	}

}

static void EEPROM_Erasing_ALL(void)
{

	if(Erasing == EEPROM_Driver_System_Mode.EEPROM_MODE)
	{
		if(Undefined == EEPROM_Driver_System_Mode.EEPROM_MODE_Status)
		{
			EEPROM_Pages_Queue Erasing_Queue;
			Queue5_Create(&Erasing_Queue);

			u16 Addresses = EEPROM_Driver_System_Mode.EEPROM_Page_counter * EEPROM_PAGE_SIZE;

			Queue5_Push(&Erasing_Queue,(u8) Addresses );  	/*Word Address */

			for(u8 i = 0; i<EEPROM_PAGE_SIZE ; i++)
			{
				Queue5_Push(&Erasing_Queue,0xFF);

			}
			if(I2C_Request_Sent == EEPROM_Driver_Interface_With_I2C(Addresses,&Erasing_Queue))
			{
				EEPROM_Driver_System_Mode.EEPROM_MODE_Status = On_Progress;
			}
		}


	}
}

static u8 EEPROM_Driver_Test_Address(void)
{
	static volatile u8 Local_Static_Control = Undefined;

	if(Undefined == EEPROM_Driver_System_Mode.EEPROM_MODE)
	{
		if(Undefined == Local_Static_Control)
		{
			if( Request_Checking_Device_Address_I2C(EEPROM_ADDRESSES,Notification_Handler_I2C))
			{
				Local_Static_Control = Wait;
			}
			else
			{

			}
		}
		else
		{

		}
	}



}


static void Notification_Handler_I2C(void* Pointer)
{

	u8 Local_Data;
	volatile  u8 Local_Mode = 0;
	volatile  u8 Local_Mode_Status = 0;
	volatile u16 Local_Address_request_status_Data[2];

	switch(EEPROM_Driver_System_Mode.EEPROM_MODE)
	{
	case Erasing:
		if(*((u8*)Pointer) ==  I2C_Request_Done)
		{
			EEPROM_Driver_System_Mode.EEPROM_Page_counter++;
			EEPROM_Driver_System_Mode.EEPROM_MODE_Status = Undefined;
			if(EEPROM_Driver_System_Mode.EEPROM_Page_counter == 64)
			{
				EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
				EEPROM_Driver_System_Mode.EEPROM_Page_counter= 0 ;
			}
		}
		else if(*((u8*)Pointer) ==  I2C_Request_Faild)
		{

		}
		else
		{

		}
		break;
	case Writing:

		Local_Mode = Writing;

		if((*((u8*)Pointer) ==  I2C_Request_Done))
		{
			Local_Mode_Status = OK_EEPROM;
			Local_Address_request_status_Data[0] = EEPROM_Driver_System_Mode.EEPROM_Current_Word_Address;
			Local_Address_request_status_Data[1] = OK_EEPROM;
			EEPROM_Call_Back(&Local_Mode,&Local_Mode_Status,Local_Address_request_status_Data);

		}
		else if(I2C_Request_Faild == (*((u8*)Pointer)))
		{
			Local_Mode_Status = Faild_EEPROM;
			Local_Address_request_status_Data[0] = EEPROM_Driver_System_Mode.EEPROM_Current_Word_Address;
			Local_Address_request_status_Data[1] = Faild_EEPROM;
			EEPROM_Call_Back(&Local_Mode,&Local_Mode_Status,Local_Address_request_status_Data);
		}
		else
		{
			/*Do nothing*/
		}

		EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
		break;
	case Reading:

		Local_Mode = Reading;
		
		if(*((u8*)Pointer) != I2C_Request_Faild)
		{
			
			Local_Mode_Status = OK_EEPROM;
			EEPROM_Call_Back(&Local_Mode,&Local_Mode_Status,Pointer);

			EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;

		}
		else
		{
			Local_Mode_Status = Faild_EEPROM;
			EEPROM_Call_Back(&Local_Mode,&Local_Mode_Status,Pointer);

			EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
		}

		break;

	case Undefined:

		if(*((u8*)Pointer) ==  I2C_Valid_Address)
		{
			EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
		}
		else if(*((u8*)Pointer) ==  I2C_Error_Address)
		{
			EEPROM_Driver_System_Mode.EEPROM_MODE = Faild_EEPROM;
		}
		else
		{

		}

		break;
	default :

		break;

	}



}
/*-----------------------------------------------------------------------------------*/
