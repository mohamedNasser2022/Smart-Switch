/*
 * Stack_Interface.h
 *
 *  Created on: Dec 29, 2021
 *      Author: Mohamed Nasser
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#ifndef STACK_INTERFACE_H_
#define STACK_INTERFACE_H_

#define MAXSTACK 10
#define StackEntry u8

typedef struct stack{
	u8 top ;
	StackEntry entry[MAXSTACK];
}Stack;

u8 STACK_DataBuffer(u16 *ptr,Stack *ps);
void STACK_Init(Stack *ps);
u8 STACK_Push(Stack *ps,StackEntry e);
u8 STACK_Pop(Stack *ps,StackEntry *pe);
void STACK_Clear(Stack *ps);
u8 STACK_Size(Stack *ps);
u8 STACK_Full(Stack *ps);
u8 STACK_Empty(Stack *ps);

#endif /* STACK_INTERFACE_H_ */
