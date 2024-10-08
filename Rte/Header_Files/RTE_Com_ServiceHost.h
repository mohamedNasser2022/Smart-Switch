#include"STD_TYPES.h"

#include"STD_MessageHost.h"

#ifndef	RTE_COM_SERVICE_H_
#define	RTE_COM_SERVICE_H_

u8 Rte_Write_Message_0x01(Idt_Message_0x01_t *Pointer_Data);
u8 Rte_Read_Message_0x01 (Idt_Message_0x01_t *Pointer_Data);

u8 Rte_Write_Message_0x11(Idt_Message_0x11_t *Pointer_Data);
u8 Rte_Read_Message_0x11 (Idt_Message_0x11_t *Pointer_Data);

u8 Rte_Write_Message_0x13(Idt_Message_0x13_t *Pointer_Data);
u8 Rte_Read_Message_0x13 (Idt_Message_0x13_t *Pointer_Data);

u8 Rte_Write_Message_0x14(Idt_Message_0x14_t *Pointer_Data);
u8 Rte_Read_Message_0x14 (Idt_Message_0x14_t *Pointer_Data);

u8 Rte_Write_Message_0x20(Idt_Message_0x20_t *Pointer_Data);
u8 Rte_Read_Message_0x20 (Idt_Message_0x20_t *Pointer_Data);

u8 Rte_Write_Message_0x21(Idt_Message_0x21_t *Pointer_Data);
u8 Rte_Read_Message_0x21 (Idt_Message_0x21_t *Pointer_Data);

u8 Rte_Write_Message_0x03(Idt_Message_0x03_t *Pointer_Data);
u8 Rte_Read_Message_0x03 (Idt_Message_0x03_t *Pointer_Data);

u8 Rte_Write_Message_0x10(Idt_Message_0x10_t *Pointer_Data);
u8 Rte_Read_Message_0x10 (Idt_Message_0x10_t *Pointer_Data);

u8 Rte_Write_Message_0x30(Idt_Message_0x30_t *Pointer_Data);
u8 Rte_Read_Message_0x30 (Idt_Message_0x30_t *Pointer_Data);

u8 Rte_Write_Message_0x31(Idt_Message_0x31_t *Pointer_Data);
u8 Rte_Read_Message_0x31 (Idt_Message_0x31_t *Pointer_Data);

u8 Rte_Write_Message_0x15(Idt_Message_0x15_t *Pointer_Data);
u8 Rte_Read_Message_0x15 (Idt_Message_0x15_t *Pointer_Data);


#endif