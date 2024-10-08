#include"STD_TYPES.h"
#include"STD_MessageHost.h"
#include"RTE_Com_ServiceHost.h"
#include"RTE.h"

static struct {

	Idt_Message_0x01_t Rte_Message_0x01;
	u8 Rte_Message_Status;

}Rte_Message_0x01_Struct;

static struct {

	Idt_Message_0x11_t Rte_Message_0x11;
	u8 Rte_Message_Status;

}Rte_Message_0x11_Struct;

static struct {

	Idt_Message_0x13_t Rte_Message_0x13;
	u8 Rte_Message_Status;

}Rte_Message_0x13_Struct;

static struct {

	Idt_Message_0x14_t Rte_Message_0x14;
	u8 Rte_Message_Status;

}Rte_Message_0x14_Struct;

static struct {

	Idt_Message_0x20_t Rte_Message_0x20;
	u8 Rte_Message_Status;

}Rte_Message_0x20_Struct;

static struct {

	Idt_Message_0x21_t Rte_Message_0x21;
	u8 Rte_Message_Status;

}Rte_Message_0x21_Struct;

static struct {

	Idt_Message_0x03_t Rte_Message_0x03;
	u8 Rte_Message_Status;

}Rte_Message_0x03_Struct;

static struct {

	Idt_Message_0x10_t Rte_Message_0x10;
	u8 Rte_Message_Status;

}Rte_Message_0x10_Struct;

static struct {

	Idt_Message_0x30_t Rte_Message_0x30;
	u8 Rte_Message_Status;

}Rte_Message_0x30_Struct;

static struct {

	Idt_Message_0x31_t Rte_Message_0x31;
	u8 Rte_Message_Status;

}Rte_Message_0x31_Struct;

static struct {

	Idt_Message_0x15_t Rte_Message_0x15;
	u8 Rte_Message_Status;

}Rte_Message_0x15_Struct;


u8 Rte_Write_Message_0x01(Idt_Message_0x01_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x01_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x01_Struct.Rte_Message_0x01);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x01_Struct.Rte_Message_Status)
	{
		Rte_Message_0x01_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x01_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x01(Idt_Message_0x01_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x01_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x01_Struct.Rte_Message_0x01;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x01_Struct.Rte_Message_Status)
	{
		Rte_Message_0x01_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x01_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x11(Idt_Message_0x11_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x11_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x11_Struct.Rte_Message_0x11);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x11_Struct.Rte_Message_Status)
	{
		Rte_Message_0x11_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x11_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x11(Idt_Message_0x11_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x11_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x11_Struct.Rte_Message_0x11;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x11_Struct.Rte_Message_Status)
	{
		Rte_Message_0x11_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x11_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x13(Idt_Message_0x13_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x13_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x13_Struct.Rte_Message_0x13);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x13_Struct.Rte_Message_Status)
	{
		Rte_Message_0x13_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x13_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x13(Idt_Message_0x13_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x13_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x13_Struct.Rte_Message_0x13;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x13_Struct.Rte_Message_Status)
	{
		Rte_Message_0x13_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x13_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x14(Idt_Message_0x14_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x14_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x14_Struct.Rte_Message_0x14);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x14_Struct.Rte_Message_Status)
	{
		Rte_Message_0x14_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x14_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x14(Idt_Message_0x14_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x14_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x14_Struct.Rte_Message_0x14;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x14_Struct.Rte_Message_Status)
	{
		Rte_Message_0x14_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x14_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x20(Idt_Message_0x20_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x20_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x20_Struct.Rte_Message_0x20);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x20_Struct.Rte_Message_Status)
	{
		Rte_Message_0x20_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x20_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x20(Idt_Message_0x20_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x20_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x20_Struct.Rte_Message_0x20;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x20_Struct.Rte_Message_Status)
	{
		Rte_Message_0x20_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x20_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x21(Idt_Message_0x21_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x21_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x21_Struct.Rte_Message_0x21);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x21_Struct.Rte_Message_Status)
	{
		Rte_Message_0x21_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x21_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x21(Idt_Message_0x21_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x21_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x21_Struct.Rte_Message_0x21;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x21_Struct.Rte_Message_Status)
	{
		Rte_Message_0x21_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x21_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x03(Idt_Message_0x03_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x03_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x03_Struct.Rte_Message_0x03);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x03_Struct.Rte_Message_Status)
	{
		Rte_Message_0x03_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x03_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x03(Idt_Message_0x03_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x03_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x03_Struct.Rte_Message_0x03;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x03_Struct.Rte_Message_Status)
	{
		Rte_Message_0x03_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x03_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x10(Idt_Message_0x10_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x10_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x10_Struct.Rte_Message_0x10);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x10_Struct.Rte_Message_Status)
	{
		Rte_Message_0x10_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x10_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x10(Idt_Message_0x10_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x10_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x10_Struct.Rte_Message_0x10;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x10_Struct.Rte_Message_Status)
	{
		Rte_Message_0x10_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x10_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x30(Idt_Message_0x30_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x30_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x30_Struct.Rte_Message_0x30);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x30_Struct.Rte_Message_Status)
	{
		Rte_Message_0x30_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x30_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x30(Idt_Message_0x30_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x30_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x30_Struct.Rte_Message_0x30;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x30_Struct.Rte_Message_Status)
	{
		Rte_Message_0x30_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x30_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x31(Idt_Message_0x31_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x31_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x31_Struct.Rte_Message_0x31);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x31_Struct.Rte_Message_Status)
	{
		Rte_Message_0x31_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x31_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x31(Idt_Message_0x31_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x31_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x31_Struct.Rte_Message_0x31;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x31_Struct.Rte_Message_Status)
	{
		Rte_Message_0x31_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x31_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}


u8 Rte_Write_Message_0x15(Idt_Message_0x15_t *Pointer_Data)
{
	u8 Local_Return = Write_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x15_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = (u8*)(&Rte_Message_0x15_Struct.Rte_Message_0x15);
	u8* Local_Pointer_Input = (u8*)Pointer_Data;
	if(On_progress != Rte_Message_0x15_Struct.Rte_Message_Status)
	{
		Rte_Message_0x15_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Main_Message = *Local_Pointer_Input;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x15_Struct.Rte_Message_Status = Available;
	}
	else
	{
		Local_Return = Write_Faild;
	}
	return Local_Return;
}


u8 Rte_Read_Message_0x15(Idt_Message_0x15_t *Pointer_Data)
{
	u8 Local_Return = Read_Done;
	u8 Data_Lenght = sizeof(Idt_Message_0x15_t)/sizeof(u8) ;
	u8* Local_Pointer_Main_Message = &Rte_Message_0x15_Struct.Rte_Message_0x15;
	u8* Local_Pointer_Input = Pointer_Data;
	if(Available == Rte_Message_0x15_Struct.Rte_Message_Status)
	{
		Rte_Message_0x15_Struct.Rte_Message_Status = On_progress;
		for(u8 i = 0 ; i < Data_Lenght; i++)
		{
			*Local_Pointer_Input = *Local_Pointer_Main_Message;
			Local_Pointer_Input++;
			Local_Pointer_Main_Message++;
		}
		Rte_Message_0x15_Struct.Rte_Message_Status = Not_Availabe;
	}
	else
	{
		Local_Return = Read_Faild;
	}
	return Local_Return;
}

