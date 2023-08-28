/*
 * I_O_Expander.c
 *
 *  Created on: Jun 4, 2023
 *      Author: Mohamed Nasser
 */

#include"BIT_MATH.h"



#include"DIO_Expander_Private.h"
#include"DIO_Expander_Interface.h"
#include"DIO_Expander_Config.h"



void DIO_Expander_Initialization(void)
{
	DIO_Expander_Com_Initialization();

}

void DIO_Expander_Polling(void)
{
	DIO_Expander_Com_Polling();

}



void DIO_Expander_Time(void)
{
	DIO_Expander_Com_Time();
}

void DIO_Expander_Set_Pin_Level(u8 Pin_No,u8 Pin_Level)
{
	if(Pin_No <= 7)
	{
		Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDataA,Pin_No,Pin_Level);

	}
	else if(Pin_No <= 15)
	{

		Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDataB,Pin_No - 8,Pin_Level);
	}
	else
	{

	}
	Flags.Flags_Update_Bit_Level.Set_Pin_Level_Called = UPDATES_NEEDED;
}

u8 DIO_Expander_Read_Pin(Pin_No)
{
	u8 Local_Data;
	if(Pin_No <= 7)
	{
		Local_Data = GET_BIT(DIO_Registers_Data.RegDataA,Pin_No);

	}
	else if(Pin_No <= 15)
	{

		Local_Data = GET_BIT(DIO_Registers_Data.RegDataB,Pin_No-8);
	}
	else
	{

	}
	return Local_Data;
}

void DIO_Expander_Toggle(u8 Pin_No)
{
	if(Pin_No <= 7)
	{
		TOG_BIR(DIO_Registers_Data.RegDataA,Pin_No);

	}
	else if(Pin_No <= 15)
	{

		TOG_BIR(DIO_Registers_Data.RegDataB,Pin_No - 8);
	}
	else
	{

	}
	Flags.Flags_Update_Bit_Level.Set_Pin_Level_Called = UPDATES_NEEDED;
}

void DIO_Expander_Set_Pin_Mode(u8 Pin_No,u8 Mode)
{
	switch(Mode)
	{
	case DIO_Expander_INPUT_FLOAT :

		if(Pin_No >= 7)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirA,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDebounceEnableA,Pin_No,EXPANDER_INPUT);
		}
		else if(Pin_No >= 15)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirB,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDebounceEnableB,Pin_No,EXPANDER_INPUT);
		}
		else
		{

		}
		break;

	case DIO_Expander_INPUT_PULL_UP :

		if(Pin_No >= 7)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirA,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDebounceEnableA,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegPullUpA,Pin_No,EXPANDER_ENABLE);
		}
		else if(Pin_No >= 15)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirB,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDebounceEnableB,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegPullUpB,Pin_No,EXPANDER_ENABLE);
		}
		else
		{

		}
		break;

	case DIO_Expander_INPUT_PULL_DOWN :

		if(Pin_No >= 7)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirA,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDebounceEnableA,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegPullDownA,Pin_No,EXPANDER_ENABLE);
		}
		else if(Pin_No >= 15)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirB,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDebounceEnableB,Pin_No,EXPANDER_INPUT);
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegPullDownB,Pin_No,EXPANDER_ENABLE);

		}
		else
		{

		}
		break;

	case DIO_Expander_OUPUT :

		if(Pin_No >= 7)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirA,Pin_No,EXPANDER_OUTPUT);
		}
		else if(Pin_No >= 15)
		{
			Special_Function_To_SET_CLR(&DIO_Registers_Data.RegDirB,Pin_No,EXPANDER_OUTPUT);
		}
		else
		{

		}
		break;
	case DIO_Expander_Open_Drain :
		if(Pin_No >= 7)
		{

		}
		else if(Pin_No >= 15)
		{

		}
		else
		{

		}
		break;

	default :
		// Do nothing
		break;

	}

	Flags.Flags_Update_Bit_Level.Set_Direction_Called = UPDATES_NEEDED;

}


static void Special_Function_To_SET_CLR(u8* Pointer,u8 Pin_No,u8 Boolean )
{
	Boolean = 0x01 & Boolean;

	switch(Boolean)
	{
	case 0:
		CLR_BIT(*Pointer,Pin_No);
		break;
	case 1:
		SET_BIT(*Pointer,Pin_No);
		break;
	default:
		// Do nothing
		break;
	}

}


