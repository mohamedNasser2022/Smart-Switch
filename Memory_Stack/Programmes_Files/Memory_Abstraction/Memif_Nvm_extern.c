#include"System_Main.h"
#include"STD_TYPES.h"
#include "Memif_Nvm_REC_Struct.h"
#include"EEPROM_Driver_Interface.h"
#include"Memif_Nvm_Interface.h"
#include "Mem_Abstraction_Private.h"



static void Memif_Write_Rec000_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct);
	for(u8 i = 0 ; i < 12; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
	}
	Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter = Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter + 1;
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter>>8);
	Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Rec000_copy_Nvm_Manger,12,1);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum>>8);
	if(OK_EEPROM == EEPROM_Driver_Write(128,&Local_Queue_IF))
	{
		Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Write_Status = Writing_On_Going;
	}
	else
	{
	
	}
}

 void Memif_Read_Rec000_EEPROM(void)
{
	u8 Data_Lenght = 12+4;
	if(On_Progress == EEPROM_Driver_Read(128,Data_Lenght,CallBack_Rec000))
	{
		Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

void CallBack_Rec000(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct);
	u8 Local_Data = 0;
	switch (*((u8*)Modes))
	{
	case Reading:
		if(OK_EEPROM ==*((u8*)Mode_Status))
		{
			for(u8 i = 0 ; i < 12 ; i++) // Data loading
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
			Local_Pointer = &Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
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
			Local_Pointer = &Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
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
			Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

static void Memif_Write_Rec001_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec001_FD00_Struct);
	for(u8 i = 0 ; i < 6; i++)
	{
		EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
	}
	Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter = Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter + 1;
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter>>8);
	Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum = Check_Sum_calculator(&Nvm_Descriptor_Block_Rec001_FD00_Struct.Rec001_copy_FD00,6,1);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum);
	EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum>>8);
	if(OK_EEPROM == EEPROM_Driver_Write(3,&Local_Queue_IF))
	{
		Nvm_Descriptor_Block_Rec001_FD00_Struct.Write_Status = Writing_On_Going;
	}
	else
	{
	
	}
}

static void Memif_Read_Rec001_EEPROM(void)
{
	u8 Data_Lenght = 6+4;
	if(On_Progress == EEPROM_Driver_Read(3,Data_Lenght,CallBack_Rec001))
	{
		Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

static void CallBack_Rec001(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec001_FD00_Struct);
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
			Local_Pointer = &Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
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
			Local_Pointer = &Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
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
			Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

