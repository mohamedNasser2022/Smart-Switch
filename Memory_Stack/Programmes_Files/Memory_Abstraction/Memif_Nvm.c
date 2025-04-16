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


#include "Mem_Abstraction_Interface.h"
#include "Mem_Abstraction_Config.h"
#include "Mem_Abstraction_Private.h"
#include"Memif_Nvm_Interface.h"
volatile static u32 MemIf_Time_ms = 0;

/*****************************************************************/


enum EEPROM_STATUS{

	Virgin = 0x60,
	On_Using = 0x70,

};

MemIf_Controller_t  MemIf_Controller;


extern Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct_t Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct;





/*****************************************************************/






void MemIf_Init(void)
{
	
	EEPROM_Driver_Initialization();
	MemIf_Controller.Module_Mode = MemIf_Initialization;
	MemIf_Controller.current_Mode_Status = MemIf_Undefined;



}

void MemIf_Polling(void)
{
	EEPROM_Driver_Polling();
}

volatile u8 Enable_Erasing = 0;

void MemIf_Time(void)
{
	MemIf_Time_ms++;


	MemIF_Module_Modes_Switching();

	// Reading each 1 mins and update 
	if(MemIf_Time_ms % 60000 == 0)
	{
		if(MemIf_Normal == MemIf_Controller.Module_Mode)
		{
			Memif_Normal_Write_Blocks();
		}

	}

	// Reading each 50ms and update
	if(MemIf_Time_ms % 50 == 0)
	{
		if(MemIf_Normal == MemIf_Controller.Module_Mode)
		{
			Memif_Immediate_Write_Blocks();
		}

	}

	if(1 == Enable_Erasing)
	{
		if(On_Progress == EEPROM_Driver_Erasing_All())
		{
			MemIf_Controller.Module_Mode = MemIf_Erasing;
		}
	}



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
			if(On_Using != Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Rec000_copy_Nvm_Manger.EEPROM_Status)
			{
				Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Rec000_copy_Nvm_Manger.EEPROM_Status = Virgin;
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
			if(MemIf_Ok == Nvm_Read_All())
			{
				MemIf_Controller.current_Mode_Status = MemIf_Done;
			}
			else
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



/*-------------------------CAll Back-----------------------------------------*/


u16 Check_Sum_calculator(u8 *Pointer_Data,u8 Data_Lenght,u8 copy_Gain)
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


