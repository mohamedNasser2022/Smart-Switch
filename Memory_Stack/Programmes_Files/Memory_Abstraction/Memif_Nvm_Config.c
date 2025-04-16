#include"System_Main.h"
#include"Mem_Abstraction_Private.h"
#include"EEPROM_Driver_Interface.h"

#include"Memif_Nvm_Interface.h"

Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct_t Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct;
Nvm_Descriptor_Block_Rec001_FD00_Struct_t Nvm_Descriptor_Block_Rec001_FD00_Struct;
Nvm_Descriptor_Block_Rec002_FD01_Struct_t Nvm_Descriptor_Block_Rec002_FD01_Struct;
Nvm_Descriptor_Block_Rec003_FD02_Struct_t Nvm_Descriptor_Block_Rec003_FD02_Struct;
Nvm_Descriptor_Block_Rec004_FD03_Struct_t Nvm_Descriptor_Block_Rec004_FD03_Struct;
Nvm_Descriptor_Block_Rec005_FD04_Struct_t Nvm_Descriptor_Block_Rec005_FD04_Struct;
Nvm_Descriptor_Block_Rec006_FD05_Struct_t Nvm_Descriptor_Block_Rec006_FD05_Struct;

void Memif_Normal_Write_Blocks(void) /*---this get updates each 1000ms-----*/
{
	Memif_Write_Rec001_EEPROM();
	Memif_Write_Rec002_EEPROM();
	Memif_Write_Rec003_EEPROM();
	Memif_Write_Rec004_EEPROM();
	Memif_Write_Rec005_EEPROM();
	Memif_Write_Rec006_EEPROM();
}

void Memif_Immediate_Write_Blocks(void) /*---this get updates each 50ms-----*/
{
	Memif_Write_Rec000_EEPROM();
}

u8 Nvm_Read_All(void) /*---Read All Data From Nvm-----*/
{
	volatile u8 Local_Control = 0;
	if(Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec000_EEPROM();
		Local_Control = 1;
	}
	else if(Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec001_EEPROM();
		Local_Control = 2;
	}
	else if(Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec002_EEPROM();
		Local_Control = 3;
	}
	else if(Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec003_EEPROM();
		Local_Control = 4;
	}
	else if(Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec004_EEPROM();
		Local_Control = 5;
	}
	else if(Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec005_EEPROM();
		Local_Control = 6;
	}
	else if(Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status != Read_Done && 0 == Local_Control)
	{
		Memif_Read_Rec006_EEPROM();
		Local_Control = 7;
	}
	else if(Local_Control == 0)
	{
		Local_Control = MemIf_Ok;
	}
	return Local_Control;
}

void Memif_Write_Rec000_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,12,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 12; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter = Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(128,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
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
					Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status = Read_Faild;
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
					Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status = Read_Faild;
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
					Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct.Read_Status = Read_Faild;
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

void Memif_Write_Rec001_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec001_FD00_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,6,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 6; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter = Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec001_FD00_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec001_FD00_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(3,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec001_FD00_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
	}
}

void Memif_Read_Rec001_EEPROM(void)
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

void CallBack_Rec001(void* Modes,void* Mode_Status,void* Pointer)
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
					Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status = Read_Faild;
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
					Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status = Read_Faild;
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
					Nvm_Descriptor_Block_Rec001_FD00_Struct.Read_Status = Read_Faild;
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

void Memif_Write_Rec002_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec002_FD01_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,4,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec002_FD01_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec002_FD01_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 4; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec002_FD01_Struct.writing_Counter = Nvm_Descriptor_Block_Rec002_FD01_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec002_FD01_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec002_FD01_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec002_FD01_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec002_FD01_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(13,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec002_FD01_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
	}
}

void Memif_Read_Rec002_EEPROM(void)
{
	u8 Data_Lenght = 4+4;
	if(On_Progress == EEPROM_Driver_Read(13,Data_Lenght,CallBack_Rec002))
	{
		Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

void CallBack_Rec002(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec002_FD01_Struct);
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
					Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec002_FD01_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec002_FD01_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec002_FD01_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

void Memif_Write_Rec003_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec003_FD02_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,8,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec003_FD02_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec003_FD02_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 8; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec003_FD02_Struct.writing_Counter = Nvm_Descriptor_Block_Rec003_FD02_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec003_FD02_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec003_FD02_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec003_FD02_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec003_FD02_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(21,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec003_FD02_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
	}
}

void Memif_Read_Rec003_EEPROM(void)
{
	u8 Data_Lenght = 8+4;
	if(On_Progress == EEPROM_Driver_Read(21,Data_Lenght,CallBack_Rec003))
	{
		Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

void CallBack_Rec003(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec003_FD02_Struct);
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
					Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec003_FD02_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec003_FD02_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

void Memif_Write_Rec004_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec004_FD03_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,8,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec004_FD03_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec004_FD03_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 8; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec004_FD03_Struct.writing_Counter = Nvm_Descriptor_Block_Rec004_FD03_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec004_FD03_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec004_FD03_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec004_FD03_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec004_FD03_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(33,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec004_FD03_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
	}
}

void Memif_Read_Rec004_EEPROM(void)
{
	u8 Data_Lenght = 8+4;
	if(On_Progress == EEPROM_Driver_Read(33,Data_Lenght,CallBack_Rec004))
	{
		Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

void CallBack_Rec004(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec004_FD03_Struct);
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
					Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec004_FD03_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec004_FD03_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

void Memif_Write_Rec005_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec005_FD04_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,20,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec005_FD04_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec005_FD04_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 20; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec005_FD04_Struct.writing_Counter = Nvm_Descriptor_Block_Rec005_FD04_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec005_FD04_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec005_FD04_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec005_FD04_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec005_FD04_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(45,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec005_FD04_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
	}
}

void Memif_Read_Rec005_EEPROM(void)
{
	u8 Data_Lenght = 20+4;
	if(On_Progress == EEPROM_Driver_Read(45,Data_Lenght,CallBack_Rec005))
	{
		Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

void CallBack_Rec005(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec005_FD04_Struct);
	u8 Local_Data = 0;
	switch (*((u8*)Modes))
	{
	case Reading:
		if(OK_EEPROM ==*((u8*)Mode_Status))
		{
			for(u8 i = 0 ; i < 20 ; i++) // Data loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec005_FD04_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec005_FD04_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

void Memif_Write_Rec006_EEPROM(void)
{
	EEROM_Queue Local_Queue_IF;
	EEPROM_Queue_Create(&Local_Queue_IF);
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec006_FD05_Struct);
	u16 Lcoal_Check_sum = Check_Sum_calculator(Local_Pointer,40,1) ;
	if(Lcoal_Check_sum != Nvm_Descriptor_Block_Rec006_FD05_Struct.Block_Check_Sum)
	{
		Nvm_Descriptor_Block_Rec006_FD05_Struct.Block_Check_Sum = Lcoal_Check_sum;
		for(u8 i = 0 ; i < 40; i++)
		{
			EEPROM_Queue_Push(&Local_Queue_IF,*(Local_Pointer + i));
		}
		Nvm_Descriptor_Block_Rec006_FD05_Struct.writing_Counter = Nvm_Descriptor_Block_Rec006_FD05_Struct.writing_Counter + 1;
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec006_FD05_Struct.writing_Counter);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec006_FD05_Struct.writing_Counter>>8));
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)Nvm_Descriptor_Block_Rec006_FD05_Struct.Block_Check_Sum);
		EEPROM_Queue_Push(&Local_Queue_IF,(u8)(Nvm_Descriptor_Block_Rec006_FD05_Struct.Block_Check_Sum>>8));
		if(OK_EEPROM == EEPROM_Driver_Write(69,&Local_Queue_IF))
		{
			Nvm_Descriptor_Block_Rec006_FD05_Struct.Write_Status = Writing_On_Going;
		}
		else
		{
		
		}
	}
}

void Memif_Read_Rec006_EEPROM(void)
{
	u8 Data_Lenght = 40+4;
	if(On_Progress == EEPROM_Driver_Read(69,Data_Lenght,CallBack_Rec006))
	{
		Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status = Read_On_Going;
	}
	else
	{
	
	}
}

void CallBack_Rec006(void* Modes,void* Mode_Status,void* Pointer)
{
	u8 *Local_Pointer = (&Nvm_Descriptor_Block_Rec006_FD05_Struct);
	u8 Local_Data = 0;
	switch (*((u8*)Modes))
	{
	case Reading:
		if(OK_EEPROM ==*((u8*)Mode_Status))
		{
			for(u8 i = 0 ; i < 40 ; i++) // Data loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec006_FD05_Struct.writing_Counter;
			for(u8 i = 0 ; i < 2 ; i++) // Writing Counter loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Local_Pointer = &Nvm_Descriptor_Block_Rec006_FD05_Struct.Block_Check_Sum;
			for(u8 i = 0 ; i < 2 ; i++) // Checksum loading
			{
				if(EEPROM_Queue_Pop(Pointer,&Local_Data))
				{
					*(Local_Pointer + i) = Local_Data;
				}
				else
				{
					Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status = Read_Faild;
					break;
				}
			}
			Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status = Read_Done;
		}
		else
		{
			Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status = Read_Faild;
		}
		break;
	case Writing:
		break;
	default:
		break;
	}
}

