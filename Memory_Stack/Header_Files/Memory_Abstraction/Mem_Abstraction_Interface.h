/*
 * Mem_Abstraction_Interface.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Mohamed Nasser
 */

#ifndef MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_INTERFACE_H_
#define MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_INTERFACE_H_

void MemIf_Init(void);
void MemIf_Polling(void);
void MemIf_Time(void);
void MemIf_Immediate_Write_Rec005(Idt_Rec005 *Pointer_data);
void MemIf_Immediate_Write_Rec006(Idt_Rec006 *Pointer_data);

#endif /* MEMORY_STACK_HEADER_FILES_MEMORY_ABSTRACTION_MEM_ABSTRACTION_INTERFACE_H_ */
