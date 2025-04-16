#include"STD_TYPES.h"
#include"RTE_Memif_Config_Interface.h"
#include"Memif_Nvm_Interface.h"

extern Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct_t Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct;
extern Nvm_Descriptor_Block_Rec001_FD00_Struct_t Nvm_Descriptor_Block_Rec001_FD00_Struct;
extern Nvm_Descriptor_Block_Rec002_FD01_Struct_t Nvm_Descriptor_Block_Rec002_FD01_Struct;
extern Nvm_Descriptor_Block_Rec003_FD02_Struct_t Nvm_Descriptor_Block_Rec003_FD02_Struct;
extern Nvm_Descriptor_Block_Rec004_FD03_Struct_t Nvm_Descriptor_Block_Rec004_FD03_Struct;
extern Nvm_Descriptor_Block_Rec005_FD04_Struct_t Nvm_Descriptor_Block_Rec005_FD04_Struct;
extern Nvm_Descriptor_Block_Rec006_FD05_Struct_t Nvm_Descriptor_Block_Rec006_FD05_Struct;



STD_Returns Rte_Write_FD02(u8* Pointer_Data)
{
	u8 Local_Return = E_OK;

	u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec003_FD02_Struct.Rec003_copy_FD02.Relays_Status)/sizeof(u8);
	for(u8 i =0;i<Local_Lenth;i++)
	{
		Nvm_Descriptor_Block_Rec003_FD02_Struct.Rec003_copy_FD02.Relays_Status[i] = *(Pointer_Data + i);

	}


	return Local_Return;
}
STD_Returns Rte_Read_FD02(u8* Pointer_Data)
{
	volatile u8 Local_Return = E_OK;


	if(Read_Done ==  Nvm_Descriptor_Block_Rec003_FD02_Struct.Read_Status)
	{
		u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec003_FD02_Struct.Rec003_copy_FD02.Relays_Status)/sizeof(u8);

		for(u8 i =0;i<Local_Lenth;i++)
		{
			 *(Pointer_Data + i) = Nvm_Descriptor_Block_Rec003_FD02_Struct.Rec003_copy_FD02.Relays_Status[i];

		}

	}
	else
	{
		Local_Return = NOT_OK;
	}
	return Local_Return;
}


STD_Returns Rte_Write_FD03(u8* Pointer_Data)
{
	u8 Local_Return = E_OK;

	u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec004_FD03_Struct.Rec004_copy_FD03.Switch_Status)/sizeof(u8);
	for(u8 i =0;i<Local_Lenth;i++)
	{
		  Nvm_Descriptor_Block_Rec004_FD03_Struct.Rec004_copy_FD03.Switch_Status[i] = *(Pointer_Data + i) ;

	}

	return Local_Return;
}
STD_Returns Rte_Read_FD03(u8* Pointer_Data)
{
	volatile u8 Local_Return = E_OK;


	if(Read_Done == Nvm_Descriptor_Block_Rec004_FD03_Struct.Read_Status)
	{
		u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec004_FD03_Struct.Rec004_copy_FD03.Switch_Status)/sizeof(u8);

		for(u8 i =0;i<Local_Lenth;i++)
		{
			*(Pointer_Data + i) = Nvm_Descriptor_Block_Rec004_FD03_Struct.Rec004_copy_FD03.Switch_Status[i];

		}

	}
	else
	{
		Local_Return = NOT_OK;
	}
	return Local_Return;
}

STD_Returns Rte_Write_FD04(u8* Pointer_Data)
{
	u8 Local_Return = E_OK;



	u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec005_FD04_Struct.Rec005_copy_FD04.Data)/sizeof(u8);
	for(u8 i =0;i<Local_Lenth;i++)
	{
	     Nvm_Descriptor_Block_Rec005_FD04_Struct.Rec005_copy_FD04.Data[i] = *(Pointer_Data + i);

	}

	return Local_Return;

}

STD_Returns Rte_Read_FD04(u8* Pointer_Data)
{
	volatile u8 Local_Return = E_OK;


	if(Read_Done ==  Nvm_Descriptor_Block_Rec005_FD04_Struct.Read_Status)
	{
		u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec005_FD04_Struct.Rec005_copy_FD04.Data)/sizeof(u8);

		for(u8 i =0;i<Local_Lenth;i++)
		{
			*(Pointer_Data + i) = Nvm_Descriptor_Block_Rec005_FD04_Struct.Rec005_copy_FD04.Data[i];
		}


	}
	else
	{
		Local_Return = NOT_OK;
	}
	return Local_Return;
}

STD_Returns Rte_Write_FD05(u8* Pointer_Data)
{
	u8 Local_Return = E_OK;


	u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec006_FD05_Struct.Rec006_copy_FD05.Data)/sizeof(u8);
	for(u8 i =0;i<Local_Lenth;i++)
	{
		   Nvm_Descriptor_Block_Rec006_FD05_Struct.Rec006_copy_FD05.Data[i] = *(Pointer_Data + i);

	}

	return Local_Return;

}

STD_Returns Rte_Read_FD05(u8* Pointer_Data)
{
	volatile u8 Local_Return = E_OK;


	if(Read_Done == Nvm_Descriptor_Block_Rec006_FD05_Struct.Read_Status)
	{
		u8 Local_Lenth = sizeof(Nvm_Descriptor_Block_Rec006_FD05_Struct.Rec006_copy_FD05.Data)/sizeof(u8);

		for(u8 i =0;i<Local_Lenth;i++)
		{
			*(Pointer_Data + i) = Nvm_Descriptor_Block_Rec006_FD05_Struct.Rec006_copy_FD05.Data[i];
		}


	}
	else
	{
		Local_Return = NOT_OK;
	}
	return Local_Return;

}
