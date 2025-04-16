#include"Mem_Abstraction_Private.h"

#ifndef	MEMIF_NVM_INTERFACE_H
#define	MEMIF_NVM_INTERFACE_H

enum Reading_Writing_Enum{

	Writing_Reading_Undefined,
	Writing_On_Going,
	Writing_Done,
	Writing_Failed,
	Read_Faild,
	Read_On_Going,
	Read_Done,
	RTE_Port_Busy,
	RTE_Write_Done,
	RTE_Read_Done,

};


typedef struct {

	Idt_Rec000_t Rec000_copy_Nvm_Manger;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct_t;

typedef struct {

	Idt_Rec001_t Rec001_copy_FD00;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec001_FD00_Struct_t;

typedef struct {

	Idt_Rec002_t Rec002_copy_FD01;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec002_FD01_Struct_t;

typedef struct {

	Idt_Rec003_t Rec003_copy_FD02;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec003_FD02_Struct_t;

typedef struct {

	Idt_Rec004_t Rec004_copy_FD03;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec004_FD03_Struct_t;

typedef struct {

	Idt_Rec005_t Rec005_copy_FD04;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec005_FD04_Struct_t;

typedef struct {

	Idt_Rec006_t Rec006_copy_FD05;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec006_FD05_Struct_t;

void Memif_Normal_Write_Blocks(void);
void Memif_Immediate_Write_Blocks(void);
u8 Nvm_Read_All(void);
/*---------------------Rec000-----------------*/
void Memif_Write_Rec000_EEPROM(void);
void Memif_Read_Rec000_EEPROM(void);
void CallBack_Rec000(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec000-----------------*/

/*---------------------Rec001-----------------*/
void Memif_Write_Rec001_EEPROM(void);
void Memif_Read_Rec001_EEPROM(void);
void CallBack_Rec001(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec001-----------------*/

/*---------------------Rec002-----------------*/
void Memif_Write_Rec002_EEPROM(void);
void Memif_Read_Rec002_EEPROM(void);
void CallBack_Rec002(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec002-----------------*/

/*---------------------Rec003-----------------*/
void Memif_Write_Rec003_EEPROM(void);
void Memif_Read_Rec003_EEPROM(void);
void CallBack_Rec003(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec003-----------------*/

/*---------------------Rec004-----------------*/
void Memif_Write_Rec004_EEPROM(void);
void Memif_Read_Rec004_EEPROM(void);
void CallBack_Rec004(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec004-----------------*/

/*---------------------Rec005-----------------*/
void Memif_Write_Rec005_EEPROM(void);
void Memif_Read_Rec005_EEPROM(void);
void CallBack_Rec005(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec005-----------------*/

/*---------------------Rec006-----------------*/
void Memif_Write_Rec006_EEPROM(void);
void Memif_Read_Rec006_EEPROM(void);
void CallBack_Rec006(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec006-----------------*/


#endif