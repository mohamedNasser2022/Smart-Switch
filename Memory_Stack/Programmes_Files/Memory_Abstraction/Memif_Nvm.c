/*
 * Mem_Abstraction.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Mohamed Nasser
 *     Version: 02
 */


#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"EEPROM_Driver_Interface.h"

#include"Rte_Nvm_STD.h"

#include "Mem_Abstraction_Config.h"
#include "Mem_Abstraction_Interface.h"
#include "Mem_Abstraction_Private.h"
#include"Memif_Nvm_Interface.h"
volatile static u32 MemIf_Time_ms = 0;

/*****************************************************************/


enum EEPROM_STATUS{

	Virgin = 0x60,
	On_Using = 0x70,

};


struct 
{
	u8 Number_Of_Blocks;
	enum EEPROM_STATUS EEPROM_Status;
	u8 Reserved[12];
	u16 Check_Sum_Nvm_Manger_Data;
}Nvm_Manger_Data;








/*****************************************************************/






void MemIf_Init(void)
{
	EEPROM_Driver_Set_Call_Back_Writing(Notification_Handler_Physical_Layer);
	EEPROM_Driver_Initialization();
	MemIf_Controller.Module_Mode = MemIf_Initialization;
	MemIf_Controller.current_Mode_Status = MemIf_Undefined;



}

void MemIf_Polling(void)
{
	EEPROM_Driver_Polling();
}

volatile u8 Control_test = 1;

void MemIf_Time(void)
{
	MemIf_Time_ms++;


	MemIF_Module_Modes_Switching();

	// Reading each 1 mins and update 
	// Reading each 50ms and update

	/*if(On_Progress == EEPROM_Driver_Erasing_All())
	{
		MemIf_Controller.Module_Mode = MemIf_Erasing;
	}*/



}

/*-------------------------- Static Functions ---------------------------*/

static void MemIF_Module_Modes_Switching(void)
{
	static volatile u8 loca_ = 0;
	switch (MemIf_Controller.Module_Mode)
	{
	case MemIf_Initialization:

		if(MemIf_Undefined == MemIf_Controller.current_Mode_Status)
		{
			Memif_Read_Rec000_EEPROM();
			if(Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status == Read_On_Going)
			{
				MemIf_Controller.current_Mode_Status = MemIf_OnGoing;
			}
			


		}
		else if(Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status == Read_Done)
		{
			if(On_Using != Nvm_Manger_Data.EEPROM_Status)
			{
				Nvm_Manger_Data.EEPROM_Status = Virgin;
				MemIf_Controller.Module_Mode = Virgin;
			}
			else
			{
				MemIf_Controller.Module_Mode = MemIf_Reading;
			}

			MemIf_Controller.current_Mode_Status = MemIf_Undefined;


		}


		break;

	case MemIf_Reading:

		/*Loading All Data From Nvm*/
		if(MemIf_Controller.current_Mode_Status == MemIf_Undefined)
		{
			//if(MemIf_Ok == MemIf_Nvm_Read_All())
			{
				MemIf_Controller.current_Mode_Status = MemIf_Done;
			}
			//else
			{

			}

		}
		else if(MemIf_Controller.current_Mode_Status == MemIf_Done)
		{
			//MemIf_Runnable_Writing_to_Rte();
			MemIf_Controller.Module_Mode = MemIf_Normal;
			MemIf_Controller.current_Mode_Status = MemIf_Undefined;
		}
		else
		{

		}




		break;

	case Virgin:

		


		MemIf_Controller.Module_Mode = MemIf_Normal;



		break;

	case MemIf_Normal:

	

		if(MemIf_Time_ms % 30000 == 0)
		{
			//MemIf_Update_Writing_Enable();
		}

		break;

	case MemIf_Stand_by:

		break;

	default:


		break;
	}



}





/*-------------------Loading default value for each Record -----------------------------*/


/*-------------------Loading default value for each Record -----------------------------*/

/*------------------Immediate Writing Function  -------------------------*/


/*------------------Immediate Writing Function  -------------------------*/

/*------------------Writing Function for each Record -------------------------*/


/*------------------Writing Function for each Record -------------------------*/

/*------------------Reading Function for each Record --------------------------*/



/*------------------Reading Function for each Record --------------------------*/

/*-------------------------CAll Back-----------------------------------------*/


static void Notification_Handler_Physical_Layer(void* Modes,void* Mode_Status,void* Pointer)
{
	volatile u16 Local_Address = 0;
	volatile u16 Local_State = 0;

	switch (*((u8*)Modes))
	{
	case Reading:

		if(MemIf_Initialization == MemIf_Controller.Module_Mode)
		{
			//MemIf_Loading_Nvm_Manger_Data(Pointer);
			MemIf_Controller.current_Mode_Status = MemIf_Done;
		}


		break;

	case Writing:

		Local_Address = *((u16*)Pointer);
		Local_State   = *(((u16*)Pointer)+1);

		//updates_Writing_state_of_each_block(Local_Address,Local_State);

		break;

	default:
		break;
	}

}

/*-------------------------CAll Back-----------------------------------------*/






static u16 Check_Sum_calculator(u8 *Pointer_Data,u8 Data_Lenght,u8 copy_Gain)
{
	u32 Accumlative_Data = 0;
	u16 Sum_Return = 0;
	for(u8 i = 0 ; i < Data_Lenght; i++)
	{
		Accumlative_Data = Accumlative_Data + *(Pointer_Data + i)* copy_Gain;
	}

	Sum_Return = (u16) Accumlative_Data;
	return Sum_Return;

}


