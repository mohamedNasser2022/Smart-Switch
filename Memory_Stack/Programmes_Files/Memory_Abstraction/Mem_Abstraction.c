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

volatile static u32 MemIf_Time_ms = 0;

/*****************************************************************/

struct 
{
	u8 Number_Of_Blocks;
	u8 EEPROM_Status;
	u8 Reserved[12];
	u16 Check_Sum_Nvm_Manger_Data;
}Nvm_Manger_Data;

struct 
{
	u8 Module_Mode;
	u8 current_Mode_Status;


}MemIf_Controller;

enum{

	MemIf_Undefined,
	MemIf_Initialization,
	MemIf_OnGoing,
	MemIf_Done,
	MemIf_Reading,
	MemIf_Writing,
	MemIf_Stand_by,
	MemIf_Erasing,
	MemIf_Normal,
	MemIf_Busy,
	MemIf_Ok,

}Modes;

enum{

	Virgin = 0x60,
	On_Using = 0x70,

}EEPROM_Status;


/*****************************************************************/

enum{

	Writing_Reading_Undefined,
	Writing_Needed,
	Writing_On_Going,
	Writing_Done,
	Writing_Failed,
	Read_Faild,
	Read_On_Going,
	Read_Done,

}Reading_Writing_Enum;

/***************************Nvm Blocks******************/

static struct 
{
	u8 Block_Type;
	Idt_Rec001_FD00 Rec001_copy_FD00;
	u8 writing_Counter;
	u16 Block_Check_Sum;
	u8 Write_Status:4;
	u8 Read_Status:4;

}Nvm_Descriptor_Rec001;

static struct 
{
	u8 Block_Type;
	Idt_Rec002_FD01 Rec002_copy_FD01;
	u8 writing_Counter;
	u16 Block_Check_Sum ;
	u8 Write_Status:4;
	u8 Read_Status:4;

}Nvm_Descriptor_Rec002;

static struct 
{
	u8 Block_Type;
	Idt_Rec003_FD02 Rec003_copy_FD02;
	u8 writing_Counter;
	u8 Block_Time_1count_30sec;
	u16 Block_Check_Sum ;
	u8 Writing_Enable:1;
	u8 Write_Status:4;
	u8 Read_Status:4;

}Nvm_Descriptor_Rec003;

static struct 
{
	u8 Block_Type;
	Idt_Rec004_FD03 Rec004_copy_FD03;
	u8 writing_Counter;
	u8 Block_Time_1count_30sec;
	u16 Block_Check_Sum ;
	u8 Writing_Enable:1;
	u8 Write_Status:4;
	u8 Read_Status:4;

}Nvm_Descriptor_Rec004;

static struct 
{
	u8 Block_Type;
	Idt_Rec005 Rec005_copy_FD04;
	u8 writing_Counter;
	u8 Block_Time_1count_30sec;
	u16 Block_Check_Sum ;
	u8 Writing_Enable:1;
	u8 Write_Status:4;
	u8 Read_Status:4;

}Nvm_Descriptor_Rec005;

static struct 
{
	u8 Block_Type;
	Idt_Rec006 Rec006_copy_FD05;
	u8 writing_Counter;
	u8 Block_Time_1count_30sec;
	u16 Block_Check_Sum ;
	u8 Writing_Enable:1;
	u8 Write_Status:4;
	u8 Read_Status:4;

}Nvm_Descriptor_Rec006;

/*******************************************************/



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

	if(Control_test == 1)
	{
		MemIF_Module_Modes_Switching();
	}
	else if(Control_test == 2)
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
	switch (MemIf_Controller.Module_Mode)
	{
	case MemIf_Initialization:

		if(MemIf_Undefined == MemIf_Controller.current_Mode_Status)
		{
			if(On_Progress == EEPROM_Driver_Read(128,16,Notification_Handler_Physical_Layer))
			{
				MemIf_Controller.current_Mode_Status = MemIf_OnGoing;
			}
		}
		else if(MemIf_Controller.current_Mode_Status == MemIf_Done)
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
			if(MemIf_Ok == MemIf_Nvm_Read_All())
			{
				MemIf_Controller.current_Mode_Status = MemIf_Done;
			}
			else
			{

			}

		}
		else if(MemIf_Controller.current_Mode_Status == MemIf_Done)
		{
			MemIf_Runnable_Writing_to_Rte();
			MemIf_Controller.Module_Mode = MemIf_Normal;
			MemIf_Controller.current_Mode_Status = MemIf_Undefined;
		}
		else
		{

		}




		break;

	case Virgin:

		MemIf_Write_Nvm_Manger_Data();
		MemIf_Loadong_Default_Valus_Rec001();
		MemIf_Loadong_Default_Valus_Rec002();
		MemIf_Loadong_Default_Valus_Rec003();



		MemIf_Controller.Module_Mode = MemIf_Normal;



		break;

	case MemIf_Normal:

		MemIf_Running_Normally();
		MemIf_Faults_detections();
		MemIf_Runnable_Reading_From_Rte();

		if(MemIf_Time_ms % 30000 == 0)
		{
			MemIf_Update_Writing_Enable();
		}

		break;

	case MemIf_Stand_by:

		break;

	default:


		break;
	}



}

static void MemIf_Runnable_Writing_to_Rte(void)
{
	Rte_Nvm_Write_FD00(&Nvm_Descriptor_Rec001.Rec001_copy_FD00);
	Rte_Nvm_Write_FD01(&Nvm_Descriptor_Rec002.Rec002_copy_FD01);
	Rte_Nvm_Write_FD02(&Nvm_Descriptor_Rec003.Rec003_copy_FD02);
	Rte_Nvm_Write_FD03(&Nvm_Descriptor_Rec004.Rec004_copy_FD03);
	Rte_Nvm_Write_FD04(&Nvm_Descriptor_Rec005.Rec005_copy_FD04);
	Rte_Nvm_Write_FD05(&Nvm_Descriptor_Rec006.Rec006_copy_FD05);
}

static void MemIf_Runnable_Reading_From_Rte(void)
{
	u16 Local_Check_sum = 0;
	Rte_Read_FD00(&Nvm_Descriptor_Rec001.Rec001_copy_FD00);
	Rte_Read_FD01(&Nvm_Descriptor_Rec002.Rec002_copy_FD01);
	Rte_Read_FD02(&Nvm_Descriptor_Rec003.Rec003_copy_FD02);
	Rte_Read_FD02(&Nvm_Descriptor_Rec004.Rec004_copy_FD03);

	/*Calculate Check sum of reading to check if writing is needed */

	if(Check_Sum_calculator(&Nvm_Descriptor_Rec001.Rec001_copy_FD00.Hardware_Version,6,1) != Nvm_Descriptor_Rec001.Block_Check_Sum)
	{
		Nvm_Descriptor_Rec001.Write_Status = Writing_Needed;
	}
	if(Check_Sum_calculator(&Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Relays_On_Syetem,4,1) != Nvm_Descriptor_Rec002.Block_Check_Sum)
	{
		Nvm_Descriptor_Rec002.Write_Status = Writing_Needed;
	}
	if(Check_Sum_calculator(&Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[0],8,1) != Nvm_Descriptor_Rec003.Block_Check_Sum)
	{
		Nvm_Descriptor_Rec003.Write_Status = Writing_Needed;
	}
	if(Check_Sum_calculator(&Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[0],8,1) != Nvm_Descriptor_Rec004.Block_Check_Sum)
	{
		Nvm_Descriptor_Rec004.Write_Status = Writing_Needed;
	}


}

static void MemIf_Running_Normally(void)
{
	/*-----------------Trigger Writing-------------------------*/

	if(Writing_Needed == Nvm_Descriptor_Rec001.Write_Status)
	{
		MemIf_Write_Rec001();
	}
	if(Writing_Needed == Nvm_Descriptor_Rec002.Write_Status)
	{
		MemIf_Write_Rec002();
	}
	if(Writing_Needed == Nvm_Descriptor_Rec003.Write_Status)
	{
		if(1 == Nvm_Descriptor_Rec003.Writing_Enable)
		{
			MemIf_Write_Rec003();
			Nvm_Descriptor_Rec003.Writing_Enable = 0;
		}

	}
	if(Writing_Needed == Nvm_Descriptor_Rec004.Write_Status)
	{
		if(1 == Nvm_Descriptor_Rec004.Writing_Enable)
		{
			MemIf_Write_Rec004();
			Nvm_Descriptor_Rec004.Writing_Enable = 0;
		}

	}

}

static void MemIf_Faults_detections(void)
{
	/*Check if any faults happen on writing blocks*/
	if(Writing_Failed == Nvm_Descriptor_Rec001.Write_Status)
	{

	}
	if(Writing_Failed == Nvm_Descriptor_Rec001.Write_Status)
	{

	}
	if(Writing_Failed == Nvm_Descriptor_Rec001.Write_Status)
	{

	}

}


static void MemIf_Update_Writing_Enable(void)
{
	/*called each 30 seconds*/
	if(0 == Nvm_Descriptor_Rec003.Writing_Enable)
	{
		Nvm_Descriptor_Rec003.Block_Time_1count_30sec ++;
		if(2 == Nvm_Descriptor_Rec003.Block_Time_1count_30sec)
		{
			Nvm_Descriptor_Rec003.Writing_Enable = 1;
			Nvm_Descriptor_Rec003.Block_Time_1count_30sec = 0;

		}

	}

}

static void updates_Writing_state_of_each_block(u16 copy_address,u8 copy_status)
{
	switch (copy_address)
	{
	case 3:

		if( OK_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec001.Write_Status = Writing_Done;
			Rte_Nvm_Write_FD00(&Nvm_Descriptor_Rec001.Rec001_copy_FD00);
		}
		else if(Faild_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec001.Write_Status = Writing_Failed;
		}
		else
		{
			Nvm_Descriptor_Rec001.Write_Status = Undefined;
		}

		break;

	case 11:

		if( OK_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec002.Write_Status = Writing_Done;
			Rte_Nvm_Write_FD01(&Nvm_Descriptor_Rec002.Rec002_copy_FD01);
		}
		else if(Faild_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec002.Write_Status = Writing_Failed;
		}
		else
		{
			Nvm_Descriptor_Rec002.Write_Status = Undefined;
		}
		break;

	case 17:

		if( OK_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec003.Write_Status = Writing_Done;
			Rte_Nvm_Write_FD02(&Nvm_Descriptor_Rec003.Rec003_copy_FD02);
		}
		else if(Faild_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec003.Write_Status = Writing_Failed;
		}
		else
		{
			Nvm_Descriptor_Rec003.Write_Status = Undefined;
		}

		break;

	case 27:

		if( OK_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec004.Write_Status = Writing_Done;
			Rte_Nvm_Write_FD03(&Nvm_Descriptor_Rec004.Rec004_copy_FD03);
		}
		else if(Faild_EEPROM == copy_status)
		{
			Nvm_Descriptor_Rec004.Write_Status = Writing_Failed;
		}
		else
		{
			Nvm_Descriptor_Rec004.Write_Status = Undefined;
		}

		break;

	default:
		break;
	}

}



static void MemIf_Loading_Blocks(void *Pointer)
{
	u8 Local_Data = 0;
	u8 *Local_Pointer = &Nvm_Descriptor_Rec001.Rec001_copy_FD00.Hardware_Version;
	u8 Block_Counter = 0;
	volatile u8 i = 0;

	for( i = 0 ; i < 6 ; i++) // Data loading
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

	Local_Pointer = &Nvm_Descriptor_Rec001.Block_Check_Sum;

	for( i = 0 ; i < 2 ; i++) // CheckSum loading
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}



	Local_Pointer = &Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Relays_On_Syetem;

	for( i = 0 ; i < 4 ; i++)
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

	Local_Pointer = &Nvm_Descriptor_Rec002.Block_Check_Sum;

	for( i = 0 ; i < 2 ; i++) // CheckSum loading
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

	Local_Pointer = &Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[0];

	for( i = 0 ; i < 8 ; i++)
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

	Local_Pointer = &Nvm_Descriptor_Rec003.Block_Check_Sum;

	for( i = 0 ; i < 2 ; i++) // CheckSum loading
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

	Local_Pointer = &Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[0];

	for( i = 0 ; i < 8 ; i++)
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

	Local_Pointer = &Nvm_Descriptor_Rec004.Block_Check_Sum;

	for( i = 0 ; i < 2 ; i++) // CheckSum loading
	{
		if(EEPROM_Queue_Pop(Pointer,&Local_Data))
		{
			*(Local_Pointer + i) = Local_Data;
		}
		else
		{
			MemIf_Controller.Module_Mode =  MemIf_Stand_by;
			break;
		}
	}

}

static void MemIf_Write_Nvm_Manger_Data(void) 
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);

	u8 *Local_Pointer = &Nvm_Manger_Data.Number_Of_Blocks;
	Nvm_Manger_Data.Number_Of_Blocks = 3;
	Nvm_Manger_Data.EEPROM_Status = On_Using;

	Nvm_Manger_Data.Check_Sum_Nvm_Manger_Data =  Check_Sum_calculator(&Nvm_Manger_Data.Number_Of_Blocks,14,1);

	for(u8 i = 0 ; i < 14; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec001.Block_Check_Sum);     	/*Push CheckSum Low Byte*/
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec001.Block_Check_Sum>>8)); /*Push CheckSum High Byte*/

	EEPROM_Driver_Write(128,&Local_Queue_IF);


}

static void MemIf_Loading_Nvm_Manger_Data(void *Pointer) /* load data from EERPOM*/
{
	u8 Local_Data = 0;
	u8 *Local_Pointer = &Nvm_Manger_Data.Number_Of_Blocks;
	u8 Counter = 0;
	while(EEPROM_Queue_Pop(Pointer,&Local_Data))
	{
		*(Local_Pointer + Counter) = Local_Data;
		Counter++;
	}

}

static u8 MemIf_Nvm_Read_All(void)
{
	u8 Local_Return = MemIf_Busy;
	
	if(Undefined == Nvm_Descriptor_Rec001.Read_Status)
	{
		MemIf_Read_Rec001();
		Local_Return = MemIf_Busy;
	}
	else
	{
		Local_Return = MemIf_Ok;
	}
	

	if(Undefined == Nvm_Descriptor_Rec002.Read_Status)
	{
		MemIf_Read_Rec002();
		Local_Return = MemIf_Busy;
	}
	else
	{
		Local_Return |= MemIf_Ok;
	}

	if(Undefined == Nvm_Descriptor_Rec003.Read_Status)
	{
		MemIf_Read_Rec003();
		Local_Return = MemIf_Busy;
	}
	else
	{
		Local_Return |= MemIf_Ok;
	}

	if(Undefined == Nvm_Descriptor_Rec004.Read_Status)
	{
		MemIf_Read_Rec004();
		Local_Return = MemIf_Busy;
	}
	else
	{
		Local_Return |= MemIf_Ok;
	}
	if(Undefined == Nvm_Descriptor_Rec005.Read_Status)
	{
		MemIf_Read_Rec005();
		Local_Return = MemIf_Busy;
	}
	else
	{
		Local_Return |= MemIf_Ok;
	}
		if(Undefined == Nvm_Descriptor_Rec006.Read_Status)
	{
		MemIf_Read_Rec006();
		Local_Return = MemIf_Busy;
	}
	else
	{
		Local_Return |= MemIf_Ok;
	}


	return Local_Return;
}




/*-------------------Loading default value for each Record -----------------------------*/
static void MemIf_Loadong_Default_Valus_Rec001(void)
{
	Nvm_Descriptor_Rec001.Rec001_copy_FD00.Hardware_Version = 0x06;
	Nvm_Descriptor_Rec001.Rec001_copy_FD00.Host_Software_Version = 0x09;
	Nvm_Descriptor_Rec001.Rec001_copy_FD00.WIFI_Software_Version = 0x09;
	Nvm_Descriptor_Rec001.Rec001_copy_FD00.Reserved[0] = 0;
	Nvm_Descriptor_Rec001.Rec001_copy_FD00.Reserved[1] = 0;
	Nvm_Descriptor_Rec001.Rec001_copy_FD00.Reserved[2] = 0;

	Nvm_Descriptor_Rec001.Block_Check_Sum =  Check_Sum_calculator(&Nvm_Descriptor_Rec001.Rec001_copy_FD00.Hardware_Version,6,1);

	Nvm_Descriptor_Rec001.Write_Status = Writing_Needed;
}

static void MemIf_Loadong_Default_Valus_Rec002(void)
{
	Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Relays_On_Syetem = 0x03;
	Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Switches_On_Syetem = 0x03;
	Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Sensors_On_Syetem = 0x03;
	Nvm_Descriptor_Rec002.Rec002_copy_FD01.Reserved;

	Nvm_Descriptor_Rec002.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Relays_On_Syetem,4,1);

	Nvm_Descriptor_Rec002.Write_Status = Writing_Needed;
}

static void MemIf_Loadong_Default_Valus_Rec003(void)
{
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[0] = 0;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[1] = 0;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[2] = 0;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[3] = 0;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[4] = 0;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[5] = 0;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[6] = 8;
	Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[7] = 0;


	Nvm_Descriptor_Rec003.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[0],8,1);

	Nvm_Descriptor_Rec003.Write_Status = Writing_Needed;
}

static void MemIf_Loadong_Default_Valus_Rec004(void)
{
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[0] = 0;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[1] = 0;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[2] = 0;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[3] = 0;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[4] = 0;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[5] = 0;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[6] = 8;
	Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[7] = 0;


	Nvm_Descriptor_Rec004.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[0],8,1);

	Nvm_Descriptor_Rec004.Write_Status = Writing_Needed;
}

/*-------------------Loading default value for each Record -----------------------------*/

/*------------------Immediate Writing Function  -------------------------*/
void MemIf_Immediate_Write_Rec005(Idt_Rec005 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec005.Block_Type) + 1;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		*(Local_Pointer + i) = Pointer_data->Data[i];
	}
	MemIf_Write_Rec005();
}

void MemIf_Immediate_Write_Rec006(Idt_Rec006 *Pointer_data)
{
	u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec006.Block_Type) + 1;

	for(u8 i = 0 ; i < Data_Lenght ; i++)
	{
		*(Local_Pointer + i) = Pointer_data->Data[i];
	}
	MemIf_Write_Rec006();
}

/*------------------Immediate Writing Function  -------------------------*/

/*------------------Writing Function for each Record -------------------------*/

static void MemIf_Write_Rec001(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec001.Block_Type) + 1;

	for(u8 i = 0 ; i < 6; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	Nvm_Descriptor_Rec001.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec001.Rec001_copy_FD00.Hardware_Version,6,1);

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec001.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec001.Block_Check_Sum>>8));


	if(OK_EEPROM == EEPROM_Driver_Write(3,&Local_Queue_IF))
	{
		Nvm_Descriptor_Rec001.Write_Status = Writing_On_Going;
	}
}

static void MemIf_Write_Rec002(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec002.Block_Type) + 1;

	for(u8 i = 0 ; i < 4; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	Nvm_Descriptor_Rec002.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec002.Rec002_copy_FD01.Number_Relays_On_Syetem,4,1);

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec002.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec002.Block_Check_Sum>>8));

	if(OK_EEPROM == EEPROM_Driver_Write(11,&Local_Queue_IF))
	{
		Nvm_Descriptor_Rec002.Write_Status = Writing_On_Going;
	}
}

static void MemIf_Write_Rec003(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec003.Block_Type) + 1;

	for(u8 i = 0 ; i < 8; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	Nvm_Descriptor_Rec003.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec003.Rec003_copy_FD02.Relay_status[0],8,1);

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec003.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec003.Block_Check_Sum>>8));

	if(OK_EEPROM == EEPROM_Driver_Write(17,&Local_Queue_IF))
	{
		Nvm_Descriptor_Rec003.Write_Status = Writing_On_Going;
	}
}

static void MemIf_Write_Rec004(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec004.Block_Type) + 1;

	for(u8 i = 0 ; i < 8; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	Nvm_Descriptor_Rec004.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec004.Rec004_copy_FD03.Switch_status[0],8,1);

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec004.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec004.Block_Check_Sum>>8));

	if(OK_EEPROM == EEPROM_Driver_Write(27,&Local_Queue_IF))
	{
		Nvm_Descriptor_Rec004.Write_Status = Writing_On_Going;
	}
}

static void MemIf_Write_Rec005(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec005.Block_Type) + 1;

	for(u8 i = 0 ; i < Data_Lenght; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	Nvm_Descriptor_Rec005.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec005.Rec005_copy_FD04,8,1);

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec005.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec005.Block_Check_Sum>>8));

	if(OK_EEPROM == EEPROM_Driver_Write(37,&Local_Queue_IF))
	{
		Nvm_Descriptor_Rec005.Write_Status = Writing_On_Going;
	}
}

static void MemIf_Write_Rec006(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec006.Block_Type) + 1;

	for(u8 i = 0 ; i < Data_Lenght; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));

	}

	Nvm_Descriptor_Rec005.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Rec006.Rec006_copy_FD05,8,1);

	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Rec006.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Rec006.Block_Check_Sum>>8));

	if(OK_EEPROM == EEPROM_Driver_Write(59,&Local_Queue_IF))
	{
		Nvm_Descriptor_Rec006.Write_Status = Writing_On_Going;
	}
}


/*------------------Writing Function for each Record -------------------------*/

/*------------------Reading Function for each Record --------------------------*/

static void MemIf_Read_Rec001(void)
{
	if(On_Progress == EEPROM_Driver_Read(3,8,CallBack_Rec001))
	{
		Nvm_Descriptor_Rec001.Read_Status = Read_On_Going;
	}
	else
	{

	}

}

static void MemIf_Read_Rec002(void)
{
	if(On_Progress == EEPROM_Driver_Read(11,6,CallBack_Rec002))
	{
		Nvm_Descriptor_Rec002.Read_Status = Read_On_Going;
	}
	else
	{

	}

}

static void MemIf_Read_Rec003(void)
{
	if(On_Progress == EEPROM_Driver_Read(17,10,CallBack_Rec003))
	{
		Nvm_Descriptor_Rec003.Read_Status = Read_On_Going;
	}
	else
	{

	}

}

static void MemIf_Read_Rec004(void)
{
	if(On_Progress == EEPROM_Driver_Read(27,10,CallBack_Rec004))
	{
		Nvm_Descriptor_Rec004.Read_Status = Read_On_Going;
	}
	else
	{

	}

}

static void MemIf_Read_Rec005(void)
{
	u8 Data_Lenght = (sizeof(Idt_Rec005)/sizeof(u8)) +  (sizeof(u16)/sizeof(u8));
	if(On_Progress == EEPROM_Driver_Read(37,Data_Lenght,CallBack_Rec005))
	{
		Nvm_Descriptor_Rec004.Read_Status = Read_On_Going;
	}
	else
	{

	}

}

static void MemIf_Read_Rec006(void)
{
	u8 Data_Lenght = (sizeof(Idt_Rec006)/sizeof(u8)) +  (sizeof(u16)/sizeof(u8));
	if(On_Progress == EEPROM_Driver_Read(59,Data_Lenght,CallBack_Rec006))
	{
		Nvm_Descriptor_Rec004.Read_Status = Read_On_Going;
	}
	else
	{

	}

}


/*------------------Reading Function for each Record --------------------------*/

/*-------------------------CAll Back-----------------------------------------*/

static void CallBack_Rec001(void* Modes,void* Mode_Status,void* Pointer)
{

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec001.Block_Type) + 1;
	u8 Local_Data = 0;
	switch (*((u8*)Modes))
	{
		case Reading:


			if(OK_EEPROM ==*((u8*)Mode_Status))
			{
				for(u8 i = 0 ; i < 6 ; i++) // Data loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}

				Local_Pointer = &Nvm_Descriptor_Rec001.Block_Check_Sum;

				for(u8 i = 0 ; i < 2 ; i++) // CheckSum loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}
				Nvm_Descriptor_Rec001.Read_Status = Read_Done;
			}
			else
			{
				Nvm_Descriptor_Rec001.Read_Status = Read_Faild;
			}
		break;
		case Writing:
			/*if()
			{

			}
			else
			{
				
			}*/
		break;
		default : 

		break;
	}


}

static void CallBack_Rec002(void* Modes,void* Mode_Status,void* Pointer)
{

	u8 *Local_Pointer = (&Nvm_Descriptor_Rec002.Block_Type) + 1;
	u8 Local_Data = 0;
	switch (*((u8*)Modes))
	{
		case Reading:


			if(OK_EEPROM ==*((u8*)Mode_Status))
			{
				for(u8 i = 0 ; i < 4 ; i++) // Data loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}

				Local_Pointer = &Nvm_Descriptor_Rec002.Block_Check_Sum;

				for(u8 i = 0 ; i < 2 ; i++) // CheckSum loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}
				Nvm_Descriptor_Rec002.Read_Status = Read_Done;
			}
			else
			{
				Nvm_Descriptor_Rec002.Read_Status = Read_Faild;
			}
		break;
		case Writing:
			/*if()
			{

			}
			else
			{
				
			}*/
		break;
		default : 

		break;
	}


}

static void CallBack_Rec003(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec003.Block_Type) + 1;
	u8 Local_Data = 0;
	switch (*((u8*)Modes))
	{
		case Reading:



			if(OK_EEPROM ==*((u8*)Mode_Status))
			{
				for(u8 i = 0 ; i < 8 ; i++) // Data loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}

				Local_Pointer = &Nvm_Descriptor_Rec003.Block_Check_Sum;

				for(u8 i = 0 ; i < 2 ; i++) // CheckSum loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}
				Nvm_Descriptor_Rec003.Read_Status = Read_Done;
			}
			else
			{
				Nvm_Descriptor_Rec003.Read_Status = Read_Faild;
			}
		break;
		case Writing:
			/*if()
			{

			}
			else
			{
				
			}*/
		break;
		default : 

		break;
	}


}

static void CallBack_Rec004(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec004.Block_Type) + 1;
	u8 Local_Data = 0;

	switch (*((u8*)Modes))
	{
		case Reading:


			if(OK_EEPROM ==*((u8*)Mode_Status))
			{
				for(u8 i = 0 ; i < 8 ; i++) // Data loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}

				Local_Pointer = &Nvm_Descriptor_Rec004.Block_Check_Sum;

				for(u8 i = 0 ; i < 2 ; i++) // CheckSum loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}
				Nvm_Descriptor_Rec004.Read_Status = Read_Done;
			}
			else
			{
				Nvm_Descriptor_Rec004.Read_Status = Read_Faild;
			}
		break;
		case Writing:
			/*if()
			{

			}
			else
			{
				
			}*/
		break;
		default : 

		break;
	}


}

static void CallBack_Rec005(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec005.Block_Type) + 1;
	u8 Local_Data = 0;
	u8 Data_Lenght = sizeof(Idt_Rec005)/sizeof(u8) ;

	switch (*((u8*)Modes))
	{
		case Reading:


			if(OK_EEPROM == *((u8*)Mode_Status))
			{
				for(u8 i = 0 ; i < Data_Lenght ; i++) // Data loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}

				Local_Pointer = &Nvm_Descriptor_Rec005.Block_Check_Sum;

				for(u8 i = 0 ; i < 2 ; i++) // CheckSum loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}
				Nvm_Descriptor_Rec005.Read_Status = Read_Done;
			}
			else
			{
				Nvm_Descriptor_Rec005.Read_Status = Read_Faild;
			}
		break;
		case Writing:
			/*if()
			{

			}
			else
			{
				
			}*/
		break;
		default : 

		break;
	}


}

static void CallBack_Rec006(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Rec006.Block_Type) + 1;
	u8 Local_Data = 0;
	u8 Data_Lenght = sizeof(Idt_Rec006)/sizeof(u8) ;
	switch (*((u8*)Modes))
	{
		case Reading:


			if(OK_EEPROM ==*((u8*)Mode_Status))
			{
				for(u8 i = 0 ; i < Data_Lenght ; i++) // Data loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}

				Local_Pointer = &Nvm_Descriptor_Rec006.Block_Check_Sum;

				for(u8 i = 0 ; i < 2 ; i++) // CheckSum loading
				{
					if(EEPROM_Queue_Pop(Pointer,&Local_Data))
					{
						*(Local_Pointer + i) = Local_Data;
					}
					else
					{
						MemIf_Controller.Module_Mode =  MemIf_Stand_by;
						break;
					}
				}
				Nvm_Descriptor_Rec006.Read_Status = Read_Done;
			}
			else
			{
				Nvm_Descriptor_Rec006.Read_Status = Read_Faild;
			}
		break;
		case Writing:
			/*if()
			{

			}
			else
			{
				
			}*/
		break;
		default : 

		break;
	}


}

static void Notification_Handler_Physical_Layer(void* Modes,void* Mode_Status,void* Pointer)
{
	volatile u16 Local_Address = 0;
	volatile u16 Local_State = 0;

	switch (*((u8*)Modes))
	{
	case Reading:

		if(MemIf_Initialization == MemIf_Controller.Module_Mode)
		{
			MemIf_Loading_Nvm_Manger_Data(Pointer);
			MemIf_Controller.current_Mode_Status = MemIf_Done;
		}
		

		break;

	case Writing:

		Local_Address = *((u16*)Pointer);
		Local_State   = *(((u16*)Pointer)+1);

		updates_Writing_state_of_each_block(Local_Address,Local_State);

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


