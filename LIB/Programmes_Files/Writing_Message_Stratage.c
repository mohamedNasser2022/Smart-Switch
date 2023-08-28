/*
 * Writing_Message_Stratage.c
 *
 *  Created on: May 1, 2023
 *      Author: Mohamed Nasser
 */

#include"Writing_Message_Stratage.h"


 u8 Writing_Message_0x01(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_u8_Data3,u8 copy_Recevier_ID)
{
	u8 Local_Arra[] = {copy_u8_Data1,copy_u8_Data2,copy_u8_Data3};

	Write_Message_0x01(Local_Arra,copy_Recevier_ID);
 	return 1;
}

 u8 Writing_Message_0x02(u8 copy_u8_Data1,u8 copy_Recevier_ID)
{
	u8 Local_Arra[] = {copy_u8_Data1};

	Write_Message_0x02(Local_Arra,copy_Recevier_ID);
 	return 1;
}

 u8 Writing_Message_0x03(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_u8_Data3,u8 copy_Recevier_ID)
{
	u8 Local_Arra[] = {copy_u8_Data1,copy_u8_Data2,copy_u8_Data3};

	Write_Message_0x03(Local_Arra,copy_Recevier_ID);
 	return 1;
}


 u8 Writing_Message_0x10(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_u8_Data3,u8 copy_u8_Data4,u8 copy_u8_Data5,u8 copy_u8_Data6,u8 copy_Recevier_ID)
 {

	 	u8 Local_Array[] = {copy_u8_Data1,copy_u8_Data2,copy_u8_Data3,copy_u8_Data4,copy_u8_Data5,copy_u8_Data6};

	 	Write_Message_0x10(Local_Array,copy_Recevier_ID);

	 	return 1;

 }

 u8 Writing_Message_0x11(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_u8_Data3,u8 copy_u8_Data4,u8 copy_u8_Data5,u8 copy_u8_Data6,u8 copy_Recevier_ID)
 {

	 	u8 Local_Array[] = {copy_u8_Data1,copy_u8_Data2,copy_u8_Data3,copy_u8_Data4,copy_u8_Data5,copy_u8_Data6};

	 	Write_Message_0x11(Local_Array,copy_Recevier_ID);
	 	return 1;

 }

u8 Writing_Message_0x13(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_u8_Data3,u8 copy_u8_Data4,u8 copy_u8_Data5,u8 copy_u8_Data6,u8 copy_Recevier_ID)
 {

 	u8 Local_Array[] = {copy_u8_Data1,copy_u8_Data2,copy_u8_Data3,copy_u8_Data4,copy_u8_Data5,copy_u8_Data6};

 	Write_Message_0x13(Local_Array,copy_Recevier_ID);
 	return 1;
 }

u8 Writing_Message_0x14(u8 copy_u8_Data1,u8 copy_u8_Data2,u8 copy_Recevier_ID)
 {
 	u8 Local_Array[] = {copy_u8_Data1,copy_u8_Data2};


 	Write_Message_0x14(Local_Array,copy_Recevier_ID);
 	return 1;
 }

u8 Writing_Message_0x20(u8* Pointer,u8 copy_Recevier_ID)
{
	Write_Message_0x20(Pointer,copy_Recevier_ID);
	return 1;
}

u8 Writing_Message_0x21(u8* Pointer,u8 copy_Recevier_ID)
{
	Write_Message_0x21(Pointer,copy_Recevier_ID);
	return 1;
}
