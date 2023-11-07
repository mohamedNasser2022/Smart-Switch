#include"STD_TYPES.h"
#ifndef	QUEUE_DATA_TYPES_H_
#define	QUEUE_DATA_TYPES_H_

typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u8	Queue_Elements[10];
}Array_Of_Queue_0;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u16 Size_Of_Last_Poped_Queue;
	Array_Of_Queue_0	Queue_Elements[10];
}Nested_Queue_0;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u8	Queue_Elements[10];
}Array_Of_Queue_1;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u16 Size_Of_Last_Poped_Queue;
	Array_Of_Queue_1	Queue_Elements[10];
}Nested_Queue_1;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u8	Queue_Elements[45];
}Array_Of_Queue_2;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u16 Size_Of_Last_Poped_Queue;
	Array_Of_Queue_2	Queue_Elements[3];
}Nested_Queue_2;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u8	Queue_Elements[50];
}Array_Of_Queue_3;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u16 Size_Of_Last_Poped_Queue;
	Array_Of_Queue_3	Queue_Elements[5];
}Nested_Queue_3;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u32	Queue_Elements[5];
}Array_Of_Queue_4;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u8	Queue_Elements[18];
}Array_Of_Queue_5;
typedef struct
{
	u8	Front;
	u8	Rear;
	u8	Size;
	u16 Size_Of_Last_Poped_Queue;
	Array_Of_Queue_5	Queue_Elements[12];
}Nested_Queue_5;

#endif