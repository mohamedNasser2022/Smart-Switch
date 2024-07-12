#include"STD_TYPES.h"
#include"Com_ServiceHost.h"
#include"STD_MessageHost.h"
#include"RTE.h"
void Runnable_Read_Messages_1ms(void) /*This is generated Function*/
{
	Message_Read_0x01();
	Message_Read_0x11();
	Message_Read_0x13();
	Message_Read_0x14();
	Message_Read_0x20();
	Message_Read_0x21();
}

void Gate_Way(u8* Message_Data) /*This is generated Function*/
{
	 switch(Message_Data[0])
	{
		case MESSAGE_0x03:
			Rte_Write_Message_0x03(&Message_Data[1]);
		break;
		case MESSAGE_0x10:
			Rte_Write_Message_0x10(&Message_Data[1]);
		break;
		case MESSAGE_0x30:
			Rte_Write_Message_0x30(&Message_Data[1]);
		break;
		case MESSAGE_0x31:
			Rte_Write_Message_0x31(&Message_Data[1]);
		break;
	}
}
static void Message_Read_0x01(void)
{
	Idt_Message_0x01_t Local_Message;
	if(Read_Done == Rte_Read_Message_0x01(&Local_Message))
	{
		Adding_Message_Header_Push_Message_Data_To_Comunication_Manger(&Local_Message,MESSAGE_0x01,MESSAGE_LENGTH_0x01);
	}
}

static void Message_Read_0x11(void)
{
	Idt_Message_0x11_t Local_Message;
	if(Read_Done == Rte_Read_Message_0x11(&Local_Message))
	{
		Adding_Message_Header_Push_Message_Data_To_Comunication_Manger(&Local_Message,MESSAGE_0x11,MESSAGE_LENGTH_0x11);
	}
}

static void Message_Read_0x13(void)
{
	Idt_Message_0x13_t Local_Message;
	if(Read_Done == Rte_Read_Message_0x13(&Local_Message))
	{
		Adding_Message_Header_Push_Message_Data_To_Comunication_Manger(&Local_Message,MESSAGE_0x13,MESSAGE_LENGTH_0x13);
	}
}

static void Message_Read_0x14(void)
{
	Idt_Message_0x14_t Local_Message;
	if(Read_Done == Rte_Read_Message_0x14(&Local_Message))
	{
		Adding_Message_Header_Push_Message_Data_To_Comunication_Manger(&Local_Message,MESSAGE_0x14,MESSAGE_LENGTH_0x14);
	}
}

static void Message_Read_0x20(void)
{
	Idt_Message_0x20_t Local_Message;
	if(Read_Done == Rte_Read_Message_0x20(&Local_Message))
	{
		Adding_Message_Header_Push_Message_Data_To_Comunication_Manger(&Local_Message,MESSAGE_0x20,MESSAGE_LENGTH_0x20);
	}
}

static void Message_Read_0x21(void)
{
	Idt_Message_0x21_t Local_Message;
	if(Read_Done == Rte_Read_Message_0x21(&Local_Message))
	{
		Adding_Message_Header_Push_Message_Data_To_Comunication_Manger(&Local_Message,MESSAGE_0x21,MESSAGE_LENGTH_0x21);
	}
}

