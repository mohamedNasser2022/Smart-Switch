#ifndef	MEMIF_NVM_REC_STRUCT_H
#define	MEMIF_NVM_REC_STRUCT_H
#include"STD_TYPES.h"
typedef struct
{
	u8 Number_Of_Blocks;
	u8 EEPROM_Status;
	u8 Reserver[10];
}Idt_Rec000_t;

typedef struct
{
	u8 No;
	u8 Seif;
	u8 Reserver[4];
}Idt_Rec001_t;


#endif