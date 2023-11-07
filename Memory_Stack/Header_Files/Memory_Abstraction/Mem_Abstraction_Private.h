/*
 * Mem_Abstraction_Private.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Mohamed Nasser
 */

#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_

static void Notification_Handler_Physical_Layer(void* Modes,void* Pointer);
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
static void MemIf_Loadong_Default_Valus_Rec001(void);
static void MemIf_Loadong_Default_Valus_Rec002(void);
static void MemIf_Loadong_Default_Valus_Rec003(void);
static void MemIf_Loadong_Default_Valus_Rec004(void);
static void MemIf_Write_Rec001(void);
static void MemIf_Write_Rec002(void);
static void MemIf_Write_Rec003(void);
static void MemIf_Write_Rec004(void);
#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_PRIVATE_H_ */
