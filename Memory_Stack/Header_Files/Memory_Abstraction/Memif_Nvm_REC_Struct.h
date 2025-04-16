#include"STD_TYPES.h"
#ifndef	MEMIF_NVM_REC_STRUCT_H
#define	MEMIF_NVM_REC_STRUCT_H

typedef struct
{
	u8 Number_Of_Blocks;
	u8 EEPROM_Status;
	u8 Reserver[10];
}Idt_Rec000_t;

typedef struct
{
	u8 Hardware_Version;
	u8 Host_Software_Version;
	u8 WIFI_Software_Version;
	u8 Reserver[3];
}Idt_Rec001_t;

typedef struct
{
	u8 Number_Relays_On_Syetem;
	u8 Number_Switches_On_Syetem;
	u8 Number_Sensors_On_Syetem;
	u8 Reserver[1];
}Idt_Rec002_t;

typedef struct
{
	u8 Relays_Status[8];
}Idt_Rec003_t;

typedef struct
{
	u8 Switch_Status[8];
}Idt_Rec004_t;

typedef struct
{
	u8 Data[20];
}Idt_Rec005_t;

typedef struct
{
	u8 Data[40];
}Idt_Rec006_t;


#endif