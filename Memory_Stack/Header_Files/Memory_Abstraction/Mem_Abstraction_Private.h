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

	MemIf_Ok,
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


};


typedef struct
{
	enum Modes Module_Mode;
	u8 current_Mode_Status;


}MemIf_Controller_t;






static void MemIf_Loading_Nvm_Manger_Data(void *Pointer);
static void MemIF_Module_Modes_Switching(void);
u16 Check_Sum_calculator(u8 *Pointer_Data,u8 Data_Lenght,u8 copy_Gain);
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

/*-------------------Loading default value for each Record -----------------------------*/

/*------------------Writing Function for each Record -------------------------*/

/*------------------Writing Function for each Record -------------------------*/

/*------------------Reading Function for each Record --------------------------*/

/*------------------Reading Function for each Record --------------------------*/

/*-------------------------CAll Back-----------------------------------------*/


/*-------------------------CAll Back-----------------------------------------*/

#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_ */
