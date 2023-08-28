/*
 * I2C.c
 *
 *  Created on: Oct 22, 2022
 *      Author: Mohamed Nasser
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"DIO_interface.h"
#include"RCC_interface.h"
#include"SYSTICK_interface.h"

#include"I2C_Private.h"
#include"I2C_config.h"
#include"I2C_Interface.h"
#include"I2C_Configuration.h"
static u32 I2C_Time_ms;
void (*Call_Back)(void*);
static volatile u8 Local_Requested_Address = 0;
extern  I2C_cf_1;

I2C_Data_Controller I2C_Peripheral_No_1_Handler;

I2C_Struct_Buffer_Transmit I2C_Peripheral_No1_Buffer;

/*--------------------------------------*/
struct {
	u8 Periheral_Mode;
	u8 Time_measure;

}Peripheral_Montoring;

enum {
	on_processing,
	Ideal,
	Error,
};

/*----------------------------------------*/

void I2C_Init(void)
{
	MSTK_voidInit();

	I2C_Set_Values();
	I2C_Initialization_Peripheral_data_Handler();
	I2C_staticInit(&I2C_cf_1);
	Queue3_Create(&I2C_Peripheral_No1_Buffer.Data_Queue_Recived);
	Queue3_Create(&I2C_Peripheral_No1_Buffer.Data_Queue_Send);
	Nested_Queue3_Create(&I2C_Peripheral_No1_Buffer.Queue_Of_Requests);
	Queue4_Create(&I2C_Peripheral_No1_Buffer.Function_Pointer);

}


#if I2C1_INTERRUPT_AT_BUFFER == I2C_DISABLE



void I2C1_Polling(void)
{

	I2C_Comunication_Polling();


}

void I2C_Periodic(void)
{
	I2C_Time_ms++;
	I2C_Make_Request_On_Progress();
	I2C_TimeOut();
	if(BUS_IDEAL != I2C_Peripheral_No_1_Handler.Bus_Mode)
	{
		Peripheral_Montoring.Periheral_Mode = on_processing;
		Peripheral_Montoring.Time_measure++;
		if(Peripheral_Montoring.Periheral_Mode == on_processing && Peripheral_Montoring.Time_measure % 500 == 0)
		{
			Peripheral_Montoring.Periheral_Mode = Error;

		}
	}
	else
	{
		Peripheral_Montoring.Periheral_Mode = Ideal;
		Peripheral_Montoring.Time_measure = 0;
	}

}



#endif


static void I2C_TimeOut(void)  /*this function shall return I2C to Ideal Mode*/
{
	if(Peripheral_Montoring.Periheral_Mode == Error)
	{
		switch(I2C_Peripheral_No_1_Handler.Bus_Status)
		{
		case BUS_IDEAL :
			Peripheral_Montoring.Periheral_Mode = Ideal;
			break;

		case BUS_REQUEST_ADDRESS_PHASE:

			I2C_Peripheral_No_1_Handler.Bus_Status = BUS_REQUEST_GENERATE_STOP_PHASE ;
			CLR_BIT(I2C_Peripheral_No_1_Handler.I2C_Peripheral_Registers->I2C_SR1,10);
			u8 Local = I2C_Request_Faild;
			Local_Requested_Address = 0;
			if(I2C_Send_Address_check_Request == I2C_Peripheral_No_1_Handler.Bus_Mode )
			{
				Call_Back(&Local);
			}


			break;

		default :

			break;

		}

	}


}


static void I2C_Comunication_Polling(void)
{
	if(BUS_IDEAL != I2C_Peripheral_No_1_Handler.Bus_Mode )
	{
		Set_Bus_Mode_Sequence(&I2C_Peripheral_No_1_Handler);

		Generate_Control_Singals(&I2C_Peripheral_No_1_Handler);
	}
	else
	{

	}


}

static void Set_Bus_Mode_Sequence(I2C_Data_Controller *pointer_to_Buffer)
{
	switch(pointer_to_Buffer->Bus_Status)
	{
	case BUS_IDEAL :

		pointer_to_Buffer->Bus_Status = BUS_REQUEST_GENERATE_START_CONDITIONS;

		break;

	case BUS_GENERATE_START_CONDITIONS :

		pointer_to_Buffer->Bus_Status = BUS_REQUEST_ADDRESS_PHASE;

		break;

	case BUS_ADDRESS_PHASE :

		if(pointer_to_Buffer->Bus_Mode == I2C_Read_Request && (pointer_to_Buffer->Buffer->Address & 0x01 == 1))
		{
			pointer_to_Buffer->Bus_Status = BUS_READING;
		}
		else if(pointer_to_Buffer->Bus_Mode == I2C_Send_Address_check_Request)
		{
			pointer_to_Buffer->Bus_Status = BUS_REQUEST_GENERATE_STOP_PHASE;
		}
		else
		{
			pointer_to_Buffer->Bus_Status = BUS_DATA_PHASE;
		}

		break;

	case BUS_ENDED_DATA_PHASE :

		pointer_to_Buffer->Bus_Status  = BUS_REQUEST_GENERATE_STOP_PHASE;

		break;

	case BUS_GENERATE_STOP_PHASE :

		I2C_Peripheral_No_1_Handler.Bus_Status = BUS_IDEAL;
		I2C_Peripheral_No_1_Handler.Bus_Mode = BUS_IDEAL;

		break;

	default :

		break;
	}

}


static void Generate_Control_Singals(I2C_Data_Controller *pointer_to_Buffer)
{
	switch(pointer_to_Buffer->Bus_Status)
	{

	case BUS_REQUEST_GENERATE_START_CONDITIONS:

		if(I2C_GENERATED == I2C_Send_Start_BIT(pointer_to_Buffer))
		{
			pointer_to_Buffer->Bus_Status = BUS_GENERATE_START_CONDITIONS;
		}
		else
		{

		}

		break;

	case BUS_REQUEST_ADDRESS_PHASE:

		if(I2C_GENERATED == I2C_Addressing(pointer_to_Buffer))
		{
			pointer_to_Buffer->Bus_Status = BUS_ADDRESS_PHASE;
		}
		else
		{

		}

		break;

	case BUS_DATA_PHASE:

		if(BUS_SENDING_ENDED == I2C_Sending_DR(pointer_to_Buffer))
		{
			if(	I2C_Read_Request == pointer_to_Buffer->Bus_Mode )
			{
				pointer_to_Buffer->Bus_Status = BUS_REQUEST_GENERATE_START_CONDITIONS;
				pointer_to_Buffer->Buffer->Address |= 0x01; // Make it Reading
			}
			else
			{
				pointer_to_Buffer->Bus_Status = BUS_ENDED_DATA_PHASE;
			}
		}
		else
		{

		}

		break;

	case BUS_READING:

		if(BUS_READING_ENDED == I2C_Reading_DR(&I2C_Peripheral_No_1_Handler))
		{
			pointer_to_Buffer->Bus_Status = BUS_ENDED_DATA_PHASE;
		}


		break;

	case BUS_REQUEST_GENERATE_STOP_PHASE:

		if(I2C_GENERATED == I2C_Send_Stop_BIT(pointer_to_Buffer))
		{
			pointer_to_Buffer->Bus_Status = BUS_GENERATE_STOP_PHASE;

			if( I2C_Read_Request == pointer_to_Buffer->Bus_Mode )
			{
				Call_Back(&pointer_to_Buffer->Buffer->Data_Queue_Recived);
				Call_Back = 0;
			}
			else if(I2C_Send_Address_check_Request == pointer_to_Buffer->Bus_Mode || I2C_Send_notify_Request == pointer_to_Buffer->Bus_Mode)
			{
				u8 Local_Data = I2C_Valid_Address;
				Call_Back(&Local_Data);
				Call_Back = (void*)0;
			}
		}
		else
		{

		}

		break;

	default :

		break;
	}

}

#if I2C1_INTERRUPT_AT_EVENT == I2C_ENABLE

I2C1_EV_IRQHandler(void)
{


}

#endif

#if I2C1_INTERRUPT_AT_ERROR == I2C_ENABLE

I2C1_ER_IRQHandler(void)
{


}

#endif


/*----------------------------------------- Data Handling Functions ----------------------------------------*/

u8 I2C_Manger_Parse_Data_to_I2C_Hardware(u8 copy_u8I2C_ID,u8 copy_u8Address,Array_Of_Queue_0* Pointer_to_Queue)
{
	I2C_Data_Controller *Pointer_to_Perpherail_Controller;
	u8 Local_Data = 0;
	u8 Local_Return = 0;
	switch(copy_u8I2C_ID)
	{
	case I2C_PERPHEIAL_1:
		Pointer_to_Perpherail_Controller = &I2C_Peripheral_No_1_Handler;
		Local_Return = 1;
		break;
	case I2C_PERPHEIAL_2:

		break;
	default:
		Local_Return = 0;
		break;
	}

	if(Pointer_to_Perpherail_Controller->Bus_Mode == BUS_IDEAL && Local_Return != 0)
	{
		Pointer_to_Perpherail_Controller->Buffer->Address = copy_u8Address;

		while(Queue3_Pop(Pointer_to_Queue,&Local_Data))
		{
			Queue3_Push(&Pointer_to_Perpherail_Controller->Buffer->Data_Queue_Send,Local_Data);

		}



		Local_Return = 1;
	}
	else
	{
		Local_Return = 0;
	}

	return Local_Return;

}

u8 I2C_Push_Data_To_Buffer(u8 copy_Mode,u8 copy_u8I2C_ID,u8 copy_u8Address,void* Pointer_to_Data,u8 copy_Number_of_bytes_to_Be_Read,void (*Pointer_Function)(void*))
{

	I2C_Data_Controller *Pointer_to_Perpherail_Controller;

	u8 Local_Data = 0;
	u8 Local_Return = I2C_Request_Sent;

	switch(copy_u8I2C_ID)
	{
	case I2C_PERPHEIAL_1:
		Pointer_to_Perpherail_Controller = &I2C_Peripheral_No_1_Handler;

		break;
	case I2C_PERPHEIAL_2:

		break;
	default:
		Local_Return = I2C_Request_Faild;
		break;
	}


	u8 Local_Data_Buffer = 0;

	Array_Of_Queue_3 Local_Queue;
	Queue3_Create(&Local_Queue);

	Queue3_Push(&Local_Queue,copy_Mode); 	   /*Push Mode*/
	Queue3_Push(&Local_Queue,copy_u8Address); /*Push Addresses*/

	if(I2C_Read_Request == copy_Mode)
	{
		Queue3_Push(&Local_Queue,copy_Number_of_bytes_to_Be_Read); /*Push Lenght of reading*/
		Queue4_Push(&Pointer_to_Perpherail_Controller->Buffer->Function_Pointer,Pointer_Function); /*Push Function*/
	}
	else
	{
		if(I2C_Send_notify_Request == copy_Mode || I2C_Send_Address_check_Request == copy_Mode)
		{
			Queue4_Push(&Pointer_to_Perpherail_Controller->Buffer->Function_Pointer,Pointer_Function); /*Push Function*/
		}

	}

	while(Queue3_Pop(Pointer_to_Data,&Local_Data))
	{
		Queue3_Push(&Local_Queue,Local_Data); /*Push Lenght of reading*/
	}
	Nested_Queue3_Push(&Pointer_to_Perpherail_Controller->Buffer->Queue_Of_Requests,&Local_Queue);
	/*

	if(Queue3_Empty(&Pointer_to_Perpherail_Controller->Buffer->Data_Queue_Recived) ||  I2C_Send_Request == copy_Mode)
	{
		if(copy_u8I2C_ID == I2C_PERPHEIAL_1 && Pointer_to_Perpherail_Controller->Bus_Mode == BUS_IDEAL )
		{

			Pointer_to_Perpherail_Controller->Buffer->Address = copy_u8Address ;
			Pointer_to_Perpherail_Controller->Buffer->Length_of_Data_To_Be_Read = copy_Number_of_bytes_to_Be_Read;

			if(I2C_Send_Request == copy_Mode || I2C_Send_notify_Request == copy_Mode || I2C_Read_Request == copy_Mode)
			{
				while(Queue3_Pop(Pointer_to_Data,&Local_Data_Buffer))
				{
					Queue3_Push(&Pointer_to_Perpherail_Controller->Buffer->Data_Queue_Send,Local_Data_Buffer);
				}
			}


			Pointer_to_Perpherail_Controller->Bus_Mode = copy_Mode;

			if(I2C_Read_Request == copy_Mode || I2C_Send_Address_check_Request == copy_Mode || I2C_Send_notify_Request == copy_Mode)
			{
				Call_Back = ptr;

			}
			else
			{

			}


		}
		else if(copy_u8I2C_ID == I2C_PERPHEIAL_2)
		{

		}
		else
		{
			Local_Return = I2C_FAILD ;
		}
	}
	else
	{
		Local_Return = I2C_FAILD ;
	}
*/
	return Local_Return;
}
/*------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------Static Functions----------------------------------------*/

static void I2C_Make_Request_On_Progress(void)
{
	if(I2C_Peripheral_No_1_Handler.Bus_Mode == BUS_IDEAL)
	{
		Array_Of_Queue_3 Local_Queue;
		Queue3_Create(&Local_Queue);
		u32 Local_Pointer;
		if(Nested_Queue3_Pop(&I2C_Peripheral_No_1_Handler.Buffer->Queue_Of_Requests,&Local_Queue))
		{
			u8 Local_Mode;
			u8 Local_Address;
			u8 Local_Buffer;
			Queue3_Pop(&Local_Queue,&Local_Mode); /*Mode*/

			Queue3_Pop(&Local_Queue,&Local_Address); /*Address*/

			I2C_Peripheral_No_1_Handler.Buffer->Address = Local_Address;

			if(I2C_Read_Request == Local_Mode)
			{
				Queue3_Pop(&Local_Queue,&Local_Buffer);
				I2C_Peripheral_No_1_Handler.Buffer->Length_of_Data_To_Be_Read = Local_Buffer;

				Queue4_Pop(&I2C_Peripheral_No_1_Handler.Buffer->Function_Pointer,&Local_Pointer); /*Get Function Address*/
				Call_Back = Local_Pointer;

			}
			else
			{
				if(I2C_Send_notify_Request == Local_Mode || I2C_Send_Address_check_Request == Local_Mode)
				{
					Queue4_Pop(&I2C_Peripheral_No_1_Handler.Buffer->Function_Pointer,&Local_Pointer); /*Get Function Address*/
					Call_Back = Local_Pointer;
				}
			}

			while(Queue3_Pop(&Local_Queue,&Local_Buffer))
			{
				Queue3_Push(&I2C_Peripheral_No_1_Handler.Buffer->Data_Queue_Send,Local_Buffer);
			}
			I2C_Peripheral_No_1_Handler.Bus_Mode = Local_Mode;

		}

	}
}

static u8 I2C_staticInit(I2C_Configuration_Struct *ptr_I2C)
{
	RCC_voidEnableClock(RCC_IOPB); /*GPIOB Enable*/
	MGPIO_voidSetPinDirection(Hardware_PIN35,OUTPUT_SPEED_50MHZ_AFOD); // DATA  // Port B PIN 7
	MGPIO_voidSetPinDirection(Hardware_PIN34,OUTPUT_SPEED_50MHZ_AFOD); //clock  // Port B PIN 6



	u8 Local_Return = 0;
	I2C_t *I2C_Register;
	Local_Return = I2C_Set_Pointer_Right_Perpherial(&I2C_Register,ptr_I2C->I2C_No);
	switch(ptr_I2C->I2C_No)
	{
	case I2C_PERPHEIAL_1:
		RCC_voidEnableClock(RCC_I2C1);

		break;
	case I2C_PERPHEIAL_2:
		RCC_voidEnableClock(RCC_I2C2);

		break;
	default:
		Local_Return &= I2C_FAILD;
		break;

	}


	SET_BIT(I2C_Register->I2C_CR1,15);
	CLR_BIT(I2C_Register->I2C_CR1,15);



	I2C_Register->I2C_OAR1 |= (ptr_I2C->I2C_ADDMODE<<15);
	I2C_Register->I2C_OAR2 |= (ptr_I2C->I2C_DualMode_ADD);

#if ADDRESS_MODE == DUAL_ADDRESSES
	I2C_Register->I2C_OAR2 |= (ptr_I2C->I2C_Address_2<<1);
#endif

#if ADDRESS_LENGTH == BIT10_ADDRESS
	I2C_Register->I2C_OAR1 |= ptr_I2C->I2C_Address_1;
#else
	I2C_Register->I2C_OAR1 |= (ptr_I2C->I2C_Address_1<<1);
#endif

	if(ptr_I2C->I2C_Frequency <= 100000)
	{
		// SM mode
		CLR_BIT(I2C_Register->I2C_CCR,15); // Select Sm Standerd mode
		I2C_Register->I2C_CR2 |= 10; // Input clock to prepherial is 10 MHZ
		I2C_Register->I2C_CCR |= ((u32)((I2C_Register->I2C_CR2 & 0x001F)*1000000))/(2*ptr_I2C->I2C_Frequency);


	}
	else
	{
		if(ptr_I2C->I2C_Frequency < 400000)
		{
			SET_BIT(I2C_Register->I2C_CCR,15); // Select Fm Standerd mode
			CLR_BIT(I2C_Register->I2C_CCR,14); // Duty set 0
			I2C_Register->I2C_CR2 |= 8; // Input clock to prepherial is 8 MHZ
			I2C_Register->I2C_CCR |= ((u32)((I2C_Register->I2C_CR2 & 0x001F)*1000000))/(3*ptr_I2C->I2C_Frequency);


		}
		else
		{
			SET_BIT(I2C_Register->I2C_CCR,15); // Select Fm Standerd mode
			SET_BIT(I2C_Register->I2C_CCR,14); // Duty set 0
			I2C_Register->I2C_CR2 |= 8; // Input clock to prepherial is 10 MHZ
			I2C_Register->I2C_CCR |= ((u32)((I2C_Register->I2C_CR2 & 0x001F)*1000000*9))/(25*ptr_I2C->I2C_Frequency);


		}
	}





	I2C_Register->I2C_TRISE = 9;
	SET_BIT(I2C_Register->I2C_CR1,0); // Enable Perherial
	I2C_Register ->I2C_CR1 |=
			(ptr_I2C->I2C_Bus_Mode<<1)|
			(ptr_I2C->I2C_ACK_Enable<<10)|
			(ptr_I2C->I2C_General_Call_Enable<<6);

	I2C_Register ->I2C_CR2  |=
			(ptr_I2C->I2C_Interrupt_Enable_Buffer<<10)|
			(ptr_I2C->I2C_Interrupt_Enable_Event<<9)|
			(ptr_I2C->I2C_Interrupt_Enable_Error<<8);

	/*Buffer Initilazations */

	/*-----------------------------------------------------*/
	return Local_Return;
}

static u8 I2C_Set_Pointer_Right_Perpherial(I2C_t **I2C_Register,u8 copy_perpherail_ID)
{
	u8 Local_Return;
	switch(copy_perpherail_ID)
	{
	case I2C_PERPHEIAL_1:

		*I2C_Register = I2C_1;
		Local_Return = I2C_SUCCESS;
		break;
	case I2C_PERPHEIAL_2:

		*I2C_Register = I2C_2;
		Local_Return = I2C_SUCCESS;
		break;
	default:
		Local_Return = I2C_FAILD;
		break;

	}
	return Local_Return;

}

#if I2C_MODE == I2C_BUSY

static u8 I2C_Reading_DR(I2C_Data_Controller* pointer_to_Buffer)
{
	u8 Local_Return = 0;
	if(pointer_to_Buffer->Bus_Status == BUS_READ_PHASE)
	{

		while( I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,BUFFER_IS_FULL) == 0 ); // wait data received
		volatile u8 Data = pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR;  //Reading DATA
		Queue3_Push(&pointer_to_Buffer->Buffer->Data_Queue_Recived,Data);
		Local_Return = I2C_SUCCESS_FILLED_BUFFER;
		pointer_to_Buffer->Bus_Status = BUS_GENERATE_STOP_PHASE;
		if(pointer_to_Buffer->Buffer->Sequence_of_Transmit_V == 1 )
		{
			pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter++;
			pointer_to_Buffer->Bus_Status = pointer_to_Buffer->Buffer->Sequence_of_Transmit[pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter];

		}

	}
	else
	{

	}
	return Local_Return;
}

static u8 I2C_Sending_DR(I2C_Data_Controller* pointer_to_Buffer)
{
	volatile u8 Local_Return = 0;
	u8 Status = 0;
	volatile u8 Local_Data = 0;


	if(pointer_to_Buffer->Bus_Status == BUS_DATA_PHASE)
	{



		while(Queue3_Empty(&pointer_to_Buffer->Buffer->Data_Queue_Send) != 1 )
		{
			Queue3_Pop(&pointer_to_Buffer->Buffer->Data_Queue_Send,&Local_Data);
			pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR = Local_Data;  //Push Data to be sent
			while( I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,BUFFER_IS_EMPTY) == 0 );
		}

		pointer_to_Buffer->Bus_Status = BUS_GENERATE_STOP_PHASE;
		if(pointer_to_Buffer->Buffer->Sequence_of_Transmit_V == 1 )
		{
			pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter++;
			pointer_to_Buffer->Bus_Status = pointer_to_Buffer->Buffer->Sequence_of_Transmit[pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter];

		}


		if(Queue3_Empty(&pointer_to_Buffer->Buffer->Data_Queue_Send) == 1 )
		{
			pointer_to_Buffer->Bus_Status = BUS_GENERATE_STOP_PHASE;
			if(pointer_to_Buffer->Buffer->Sequence_of_Transmit_V == 1 )
			{
				pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter++;
				pointer_to_Buffer->Bus_Status = pointer_to_Buffer->Buffer->Sequence_of_Transmit[pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter];

			}
		}
	}
	else
	{

	}
	return Local_Return;
}

static u8 I2C_Addressing(I2C_Data_Controller* pointer_to_Buffer)
{
	u8 Local_Return = 0;



	if( pointer_to_Buffer->Bus_Status == BUS_ADDRESS_PHASE )
	{

		Local_Return = I2C_SUCCESS_FILLED_BUFFER;
		pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR = pointer_to_Buffer->Buffer->Address;  //Push Data to be sent

		while( I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,1) == 0 )
		{
			if(I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,10) == 1)
			{
				CLR_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_SR1,10);
				pointer_to_Buffer->Bus_Status = BUS_GENERATE_START_CONDITIONS;
				I2C_Send_Start_BIT(pointer_to_Buffer);

				pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR = pointer_to_Buffer->Buffer->Address;  //Push Data to be sent
			}
		}
		volatile u8 x = I2C_Status_2(pointer_to_Buffer->I2C_Peripheral_Registers,2); // to clear flag

		pointer_to_Buffer->Bus_Status = BUS_DATA_PHASE ;
		if(pointer_to_Buffer->Buffer->Sequence_of_Transmit_V == 1 )
		{
			pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter++;
			pointer_to_Buffer->Bus_Status = pointer_to_Buffer->Buffer->Sequence_of_Transmit[pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter];

		}

	}
	else
	{

	}
	return Local_Return;
}



static void I2C_Send_Start_BIT(I2C_Data_Controller* pointer_to_Buffer)
{
	u8 Local_Return = 0;

	if(pointer_to_Buffer->Bus_Status == BUS_GENERATE_START_CONDITIONS)
	{
		SET_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_CR1,8);
		while(GET_BIT(I2C_1->I2C_SR1,0) == 0 ); //wait until start bit generated
		pointer_to_Buffer->Bus_Mode = BUS_BUSY;
		pointer_to_Buffer->Bus_Status = BUS_ADDRESS_PHASE ;
		if(pointer_to_Buffer->Buffer->Sequence_of_Transmit_V == 1 )
		{
			pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter++;
			pointer_to_Buffer->Bus_Status = pointer_to_Buffer->Buffer->Sequence_of_Transmit[pointer_to_Buffer->Buffer->Sequence_of_Transmit_Counter];

		}
	}




}

static void I2C_Send_Stop_BIT(I2C_Data_Controller* pointer_to_Buffer)
{
	u8 Local_Return = 0;
	I2C_t* Pointer_Registers;

	SET_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_CR1,9);
	pointer_to_Buffer->Bus_Mode = BUS_IDEAL;
	pointer_to_Buffer->Bus_Status = BUS_IDEAL;

}

#elif I2C_MODE ==   I2C_POLLING


static u8 I2C_Reading_DR(I2C_Data_Controller* pointer_to_Buffer)
{
	u8 Local_Data = 0;
	volatile u8 Local_Return = 0;


	if(I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,BUFFER_IS_FULL) != 0)
	{

		Local_Data = pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR;  //Reading DATA
		Queue3_Push(&pointer_to_Buffer->Buffer->Data_Queue_Recived,Local_Data);

		Local_Return = I2C_WAITING;

	}
	else
	{

	}

	if(Queue3_Size(&pointer_to_Buffer->Buffer->Data_Queue_Recived) == pointer_to_Buffer->Buffer->Length_of_Data_To_Be_Read)
	{
		Local_Return = BUS_READING_ENDED;
		SET_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_CR1,10);

	}
	else if(pointer_to_Buffer->Buffer->Length_of_Data_To_Be_Read - Queue3_Size(&pointer_to_Buffer->Buffer->Data_Queue_Recived) == 1)
	{
		CLR_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_CR1,10);
		for(volatile u16 i = 0 ; i < 32000 ; i++)
		{
			Local_Return++;
		}

	}


	return Local_Return;
}

static u8 I2C_Sending_DR(I2C_Data_Controller* pointer_to_Buffer)
{
	static volatile u8 Local_Requested = 0;
	u8 Local_Return = 0;
	volatile u8 Local_Data = 0;

	if(I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,BUFFER_IS_EMPTY) == 1 )
	{

		Queue3_Pop(&pointer_to_Buffer->Buffer->Data_Queue_Send,&Local_Data);
		pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR = Local_Data;  //Push Data to be sent
		Local_Return = I2C_WAITING;

	}
	if(Queue3_Empty(&pointer_to_Buffer->Buffer->Data_Queue_Send) == 1 )
	{
		Local_Return = BUS_SENDING_ENDED;

	}
	else
	{
		// still buffer has data
	}


	return Local_Return;
}

static u8 I2C_Addressing(I2C_Data_Controller* pointer_to_Buffer)
{
	//static volatile u8 Local_Requested_Address = 0; /*this fix we did because this variable need to reset after timeout occurs*/

	u8 Local_Return = 0;

	if(0 == Local_Requested_Address)
	{
		pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR = pointer_to_Buffer->Buffer->Address;  //Push Data to be sent
		Local_Requested_Address = 1;
		Local_Return = I2C_WAITING;
	}
	else if( I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,1) == 1 )
	{
		volatile u8 x = I2C_Status_2(pointer_to_Buffer->I2C_Peripheral_Registers,2); // to clear flag
		Local_Requested_Address = 0;
		Local_Return = I2C_GENERATED;


	}
	else
	{
		/*if(I2C_Status_1(pointer_to_Buffer->I2C_Peripheral_Registers,10) == 1)
		{
			CLR_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_SR1,10);
			pointer_to_Buffer->Bus_Status = BUS_GENERATE_START_CONDITIONS;
			I2C_Send_Start_BIT(pointer_to_Buffer);

			pointer_to_Buffer->I2C_Peripheral_Registers->I2C_DR = pointer_to_Buffer->Buffer->Address;  //Push Data to be sent
		}*/

	}
	return Local_Return;
}



static u8 I2C_Send_Start_BIT(I2C_Data_Controller* pointer_to_Buffer)
{
	static volatile u8 Local_Requested = 0;
	u8 Local_Return = 0;

	if(0 == Local_Requested)
	{
		SET_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_CR1,8);
		Local_Requested = 1;
		Local_Return = I2C_WAITING;


	}
	else if(1 == GET_BIT(I2C_1->I2C_SR1,0))
	{
		//start bit generated
		Local_Requested = 0;
		Local_Return = I2C_GENERATED;

	}
	else
	{

	}

	return Local_Return;


}

static u8 I2C_Send_Stop_BIT(I2C_Data_Controller* pointer_to_Buffer)
{

	u8 Local_Return = 0;


	SET_BIT(pointer_to_Buffer->I2C_Peripheral_Registers->I2C_CR1,9);
	Local_Return = I2C_GENERATED;


	return Local_Return;
}




#endif

static u8 I2C_Status_1(I2C_t *I2C_Register,u8 copy_ID)
{
	return GET_BIT(I2C_Register->I2C_SR1,copy_ID);



}

static u8 I2C_Status_2(I2C_t *I2C_Register,u8 copy_ID)
{
	return GET_BIT(I2C_Register->I2C_SR2,copy_ID);



}

static void I2C_Initialization_Peripheral_data_Handler(void)
{
	I2C_Peripheral_No_1_Handler.Bus_Status    = BUS_IDEAL;

	I2C_Peripheral_No_1_Handler.Bus_Mode      = BUS_IDEAL;
	I2C_Peripheral_No_1_Handler.Configrations = &I2C_cf_1;
	I2C_Peripheral_No_1_Handler.Buffer        = &I2C_Peripheral_No1_Buffer;
	I2C_Peripheral_No_1_Handler.I2C_Peripheral_Registers         = I2C_1;
	Queue3_Create(&I2C_Peripheral_No_1_Handler.Buffer->Data_Queue_Send);
	Queue3_Create(&I2C_Peripheral_No_1_Handler.Buffer->Data_Queue_Recived);


}
/*-----------------------------------------------------------------------------------------------------*/
