/*
 * Stack.c
 *
 *  Created on: Dec 29, 2021
 *      Author: Mohamed Nasser
 */
#include"STD_TYPES.h"

#include"Stack_Interface.h"



void STACK_Init(Stack *ps)
{
	ps->top = 0;

}

u8 STACK_Push(Stack *ps,StackEntry e)
{
	if(ps->top== MAXSTACK)
	{
		return 0;
	}
	else
	{
		ps->entry[ps->top] = e;
		ps->top++;
		return 1;
	}
}

u8 STACK_Pop(Stack *ps,StackEntry *pe)
{
	if(ps->top == 0)
	{
		return 0;
	}
	else
	{
		ps->top--;
		*pe = ps->entry[ps->top];
		return 1;
	}
}

void STACK_Clear(Stack *ps)
{
	ps->top=0;
}

u8 STACK_Size(Stack *ps)
{
	return ps->top;
}

u8 STACK_Empty(Stack *ps)
{
	return !(ps->top);
}

u8 STACK_Full(Stack *ps)
{
	return (ps->top== MAXSTACK);
}
