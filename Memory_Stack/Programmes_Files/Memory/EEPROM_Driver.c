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


/*------------------------------------Typedef--------------------------------------------*/

static Comuncation_Manger_Interface_Nested Queue_Of_Data;

struct
{
	u8 EEPROM_MODE;
	u8 EEPROM_Page_counter;
	u16 EEPROM_Current_Word_Address;

}EEPROM_Driver_System_Mode;



/*------------------------------------------------------------------------------------*/

void EEPROM_Driver_Initialization(void)
{
	EEPROM_Driver_System_Mode.EEPROM_MODE = Undefined;  /*----------------*/
	Nested_Queue0_Create(&Queue_Of_Data);

	EEPROM_Driver_Test_Address();

}

void EEPROM_Driver_Polling(void)
{


	test();



}
volatile u32 count = 0;
void EEPROM_Driver_Time(void)
{
	count++;
	if(count % 5 == 0)
	{
		EEPROM_Driver_Write_on_Physical();
		EEPROM_Erasing_ALL();
	}





}

void test(void)
{
	volatile u8 Control = 0;
	volatile u8 Data_Write = 20;
	Comuncation_Manger_Interface Local_Queue_Data;
	Queue0_Create(&Local_Queue_Data);
	volatile u8 Local_Data = 2;


	for(u8 i = 0; i<Data_Write ; i++)
	{
		Queue0_Push(&Local_Queue_Data,Local_Data);
	}




	if(1 == Control)
	{
		EEPROM_Driver_Write(0,&Local_Queue_Data);
	}
	else if(2 == Control)
	{
		EEPROM_Driver_Read(0,Data_Write);  // Addresses
	}
	else if(3 == Control)
	{
		EEPROM_Driver_System_Mode.EEPROM_MODE = Erasing;
	}

}

u8 EEPROM_Driver_Write(u16 WordAddress,Comuncation_Manger_Interface *Pointer_To_Queue)
{
	u8 Local_Return = Undefined;
	u8 Local_Data = 0;

	u8 Local_Page = WordAddress / EEPROM_PAGE_SIZE ;
	u8 Local_Start_Byte_In_Page = WordAddress % EEPROM_PAGE_SIZE;
	u8 Local_Max_Size_Can_Stored_In_Current_Page = EEPROM_PAGE_SIZE - Local_Start_Byte_In_Page ;

	Comuncation_Manger_Interface Local_Queue_Data;
	Queue0_Create(&Local_Queue_Data);

	Queue0_Push(&Local_Queue_Data,WordAddress);
	Queue0_Push(&Local_Queue_Data,(u8)(WordAddress >> 7));


	while(Queue0_Size(Pointer_To_Queue))
	{
		for(u8 i = 0 ;i < Local_Max_Size_Can_Stored_In_Current_Page ; i++)
		{
			if(Queue0_Pop(Pointer_To_Queue,&Local_Data))
			{
				Queue0_Push(&Local_Queue_Data,Local_Data);
			}
			else
			{
				break;
			}
		}

		if(Nested_Queue0_Push(&Queue_Of_Data,&Local_Queue_Data))
		{
			Local_Return = On_Progress;
			Queue0_Create(&Local_Queue_Data);
			Local_Page ++;
			WordAddress = Local_Page * EEPROM_PAGE_SIZE;
			Queue0_Push(&Local_Queue_Data,WordAddress);
			Queue0_Push(&Local_Queue_Data,(u8)(WordAddress >> 7));
		}
		else
		{
			Local_Return = Faild;
		}
		Local_Max_Size_Can_Stored_In_Current_Page = 16;
	}



	return Local_Return;
}

u8 EEPROM_Driver_Read(u16 copy_Reading_Starting_from,u8 Lenght_of_Reading)
{
	u8 Local_Return = Undefined;

	Array_Of_Queue_0  Local_Data;
	Queue0_Create(&Local_Data);



	Queue0_Push(&Local_Data,copy_Reading_Starting_from);

	if(EEPROM_Driver_Read_From_Hardware(copy_Reading_Starting_from,&Local_Data,Lenght_of_Reading))
	{
		EEPROM_Driver_System_Mode.EEPROM_MODE = Reading;

		Local_Return = On_Progress;
	}
	else
	{
		Local_Return = Faild;
	}


	return Local_Return;

}


/*-------------------------------------- Private Functions-------------------------------------------*/
static void EEPROM_Driver_Write_on_Physical(void)
{
	Comuncation_Manger_Interface Local_Queue_Data;
	Queue0_Create(&Local_Queue_Data);

	Array_Of_Queue_0 Local_Queue_Send_I2C ;
	Queue0_Create(&Local_Queue_Send_I2C);

	u8 Local_Data ;
	u16 Word_Addresses = 0;
	if(EEPROM_Driver_System_Mode.EEPROM_MODE == Normal)
	{
		if(Nested_Queue0_Pop(&Queue_Of_Data,&Local_Queue_Data))
		{
			Queue0_Pop(&Local_Queue_Data,&Local_Data); /*Reading Word address first 8 bits*/

			Word_Addresses = Local_Data;

			Queue0_Pop(&Local_Queue_Data,&Local_Data);  /*Reading Word address seconds 3 bits*/

			Word_Addresses |= (Local_Data << 7);

			Queue0_Push(&Local_Queue_Send_I2C,(u8) Word_Addresses );  	/*Word Address */

			while(Queue0_Pop(&Local_Queue_Data,&Local_Data))
			{
				Queue0_Push(&Local_Queue_Send_I2C,Local_Data);
			}
			/*Here you have to handel the writing pages*/
			if(EEPROM_Driver_Interface_With_I2C(Word_Addresses,&Local_Queue_Send_I2C))
			{
				EEPROM_Driver_System_Mode.EEPROM_Current_Word_Address = 0; // Addresses
				EEPROM_Driver_System_Mode.EEPROM_MODE = Writing;
				Nested_Queue0_Pop(&Queue_Of_Data,&Local_Queue_Data);

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

static void EEPROM_Erasing_ALL(void)
{

	if(Erasing == EEPROM_Driver_System_Mode.EEPROM_MODE)
	{
		Array_Of_Queue_0 Erasing_Queue;
		Queue0_Create(&Erasing_Queue);

		u16 Addresses = EEPROM_Driver_System_Mode.EEPROM_Page_counter * EEPROM_PAGE_SIZE;

		Queue0_Push(&Erasing_Queue,(u8) Addresses );  	/*Word Address */

		for(u8 i = 0; i<EEPROM_PAGE_SIZE ; i++)
		{
			Queue0_Push(&Erasing_Queue,0xFF);

		}
		if(EEPROM_Driver_Interface_With_I2C(Addresses,&Erasing_Queue))
		{

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
	switch(EEPROM_Driver_System_Mode.EEPROM_MODE)
	{
	case Erasing:
		if(*((u8*)Pointer) ==  I2C_Request_Done)
		{
			EEPROM_Driver_System_Mode.EEPROM_Page_counter++;
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

		EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
		break;
	case Reading:

		while(Queue0_Pop((Array_Of_Queue_0*) Pointer,&Local_Data))
		{



		}


		EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
		break;

	case Undefined:

		if(*((u8*)Pointer) ==  I2C_Valid_Address)
		{
			EEPROM_Driver_System_Mode.EEPROM_MODE = Normal;
		}
		else if(*((u8*)Pointer) ==  I2C_Error_Address)
		{
			EEPROM_Driver_System_Mode.EEPROM_MODE = Faild;
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
