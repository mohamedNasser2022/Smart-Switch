/*
 * Mem_Abstraction_Private.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Mohamed Nasser
 */
#include "Memif_Nvm_REC_Struct.h"
#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_


enum Modes{

	MemIf_Undefined,
	MemIf_Initialization,
	MemIf_OnGoing,
	MemIf_Done,
	MemIf_Reading,
	MemIf_Writing,
	MemIf_Stand_by,
	MemIf_Erasing,
	MemIf_Normal,
	MemIf_Busy,
	MemIf_Ok,

};

enum Reading_Writing_Enum{

	Writing_Reading_Undefined,
	Writing_Needed,
	Writing_On_Going,
	Writing_Done,
	Writing_Failed,
	Read_Faild,
	Read_On_Going,
	Read_Done,

};


struct 
{
	enum Modes Module_Mode;
	u8 current_Mode_Status;


}MemIf_Controller;


static struct {

	Idt_Rec000_t Rec000_copy_Nvm_Manger;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec000_Nvm_Manger_Struct;

static struct {

	Idt_Rec001_t Rec001_copy_FD00;
	u8 Block_Type:2;
	u16 writing_Counter;
	u16 Block_Check_Sum;
	enum Reading_Writing_Enum Write_Status:4;
	enum Reading_Writing_Enum Read_Status:4;

}Nvm_Descriptor_Block_Rec001_FD00_Struct;



static void MemIf_Loading_Nvm_Manger_Data(void *Pointer);
static void MemIF_Module_Modes_Switching(void);
static u16 Check_Sum_calculator(u8 *Pointer_Data,u8 Data_Lenght,u8 copy_Gain);
static void MemIf_Write_Nvm_Manger_Data(void);
static void MemIf_Running_Normally(void);
static void MemIf_Update_Writing_Enable(void);
static void MemIf_Faults_detections(void);
static void MemIf_Runnable_Writing_to_Rte(void);
static void MemIf_Runnable_Reading_From_Rte(void);
static void updates_Writing_state_of_each_block(u16 copy_address,u8 copy_status);
static u8 MemIf_Nvm_Read_All(void);
static void MemIf_Loading_Blocks(void *Pointer);

/*-------------------Loading default value for each Record -----------------------------*/
static void MemIf_Loading_Default_Valus_Rec001(void);
static void MemIf_Loading_Default_Valus_Rec002(void);
static void MemIf_Loading_Default_Valus_Rec003(void);
static void MemIf_Loading_Default_Valus_Rec004(void);
/*-------------------Loading default value for each Record -----------------------------*/

/*------------------Writing Function for each Record -------------------------*/
static void MemIf_Write_Rec001(void);
static void MemIf_Write_Rec002(void);
static void MemIf_Write_Rec003(void);
static void MemIf_Write_Rec004(void);
static void MemIf_Write_Rec005(void);
static void MemIf_Write_Rec006(void);
/*------------------Writing Function for each Record -------------------------*/

/*------------------Reading Function for each Record --------------------------*/
static void MemIf_Read_Rec001(void);
static void MemIf_Read_Rec002(void);
static void MemIf_Read_Rec003(void);
static void MemIf_Read_Rec004(void);
static void MemIf_Read_Rec005(void);
static void MemIf_Read_Rec006(void);
/*------------------Reading Function for each Record --------------------------*/

/*-------------------------CAll Back-----------------------------------------*/
static void CallBack_Rec001(void* Modes,void* Mode_Status,void* Pointer);
static void CallBack_Rec002(void* Modes,void* Mode_Status,void* Pointer);
static void CallBack_Rec003(void* Modes,void* Mode_Status,void* Pointer);
static void CallBack_Rec004(void* Modes,void* Mode_Status,void* Pointer);
static void CallBack_Rec005(void* Modes,void* Mode_Status,void* Pointer);
static void CallBack_Rec006(void* Modes,void* Mode_Status,void* Pointer);
static void Notification_Handler_Physical_Layer(void* Modes,void* Mode_Status,void* Pointer);
/*-------------------------CAll Back-----------------------------------------*/

#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_ */
