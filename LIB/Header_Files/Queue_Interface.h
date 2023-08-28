

#include"STD_TYPES.h"
#include"Queue_Private.h"
#include"Queue_Data_Types.h"

#ifndef	QUEUE_Interface_H_
#define	QUEUE_Interface_H_

typedef Array_Of_Queue_0		Comuncation_Manger_Interface;
typedef Nested_Queue_0		Comuncation_Manger_Interface_Nested;
typedef Array_Of_Queue_1		Queue_Of_Message_Data_0;
typedef Nested_Queue_1		Queue_Of_Message_Data_0_Nested;
typedef Array_Of_Queue_2		Queue_Of_Message_Data_1;
typedef Nested_Queue_2		Queue_Of_Message_Data_1_Nested;
typedef Array_Of_Queue_3		Uart_Buffer;
typedef Nested_Queue_3		Uart_Buffer_Nested;
typedef Array_Of_Queue_4		Function_Pointer;

#define Queue0_Create(QUEUE_POINTER)			General_Queue_Create(QUEUE_ID_0,QUEUE_POINTER)
#define Queue0_Clear(QUEUE_POINTER)			General_Queue_Clear(QUEUE_ID_0,QUEUE_POINTER)
#define Queue0_Push(QUEUE_POINTER,DATA)			General_Queue_Push(QUEUE_ID_0,QUEUE_POINTER,DATA)
#define Queue0_Pop(QUEUE_POINTER,POINTER_DATA)			General_Queue_Pop(QUEUE_ID_0,QUEUE_POINTER,POINTER_DATA)
#define Queue0_Empty(QUEUE_POINTER)			General_Queue_Is_Empty(QUEUE_ID_0,QUEUE_POINTER)
#define Queue0_Full(QUEUE_POINTER)			General_Queue_Is_Full(QUEUE_ID_0,QUEUE_POINTER)
#define Queue0_Size(QUEUE_POINTER)			General_Queue_Size(QUEUE_ID_0,QUEUE_POINTER)
#define Queue0_Undo_Last_Pop(QUEUE_POINTER)			General_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_0,QUEUE_POINTER)

#define Queue1_Create(QUEUE_POINTER)			General_Queue_Create(QUEUE_ID_1,QUEUE_POINTER)
#define Queue1_Clear(QUEUE_POINTER)			General_Queue_Clear(QUEUE_ID_1,QUEUE_POINTER)
#define Queue1_Push(QUEUE_POINTER,DATA)			General_Queue_Push(QUEUE_ID_1,QUEUE_POINTER,DATA)
#define Queue1_Pop(QUEUE_POINTER,POINTER_DATA)			General_Queue_Pop(QUEUE_ID_1,QUEUE_POINTER,POINTER_DATA)
#define Queue1_Empty(QUEUE_POINTER)			General_Queue_Is_Empty(QUEUE_ID_1,QUEUE_POINTER)
#define Queue1_Full(QUEUE_POINTER)			General_Queue_Is_Full(QUEUE_ID_1,QUEUE_POINTER)
#define Queue1_Size(QUEUE_POINTER)			General_Queue_Size(QUEUE_ID_1,QUEUE_POINTER)
#define Queue1_Undo_Last_Pop(QUEUE_POINTER)			General_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_1,QUEUE_POINTER)

#define Queue2_Create(QUEUE_POINTER)			General_Queue_Create(QUEUE_ID_2,QUEUE_POINTER)
#define Queue2_Clear(QUEUE_POINTER)			General_Queue_Clear(QUEUE_ID_2,QUEUE_POINTER)
#define Queue2_Push(QUEUE_POINTER,DATA)			General_Queue_Push(QUEUE_ID_2,QUEUE_POINTER,DATA)
#define Queue2_Pop(QUEUE_POINTER,POINTER_DATA)			General_Queue_Pop(QUEUE_ID_2,QUEUE_POINTER,POINTER_DATA)
#define Queue2_Empty(QUEUE_POINTER)			General_Queue_Is_Empty(QUEUE_ID_2,QUEUE_POINTER)
#define Queue2_Full(QUEUE_POINTER)			General_Queue_Is_Full(QUEUE_ID_2,QUEUE_POINTER)
#define Queue2_Size(QUEUE_POINTER)			General_Queue_Size(QUEUE_ID_2,QUEUE_POINTER)
#define Queue2_Undo_Last_Pop(QUEUE_POINTER)			General_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_2,QUEUE_POINTER)

#define Queue3_Create(QUEUE_POINTER)			General_Queue_Create(QUEUE_ID_3,QUEUE_POINTER)
#define Queue3_Clear(QUEUE_POINTER)			General_Queue_Clear(QUEUE_ID_3,QUEUE_POINTER)
#define Queue3_Push(QUEUE_POINTER,DATA)			General_Queue_Push(QUEUE_ID_3,QUEUE_POINTER,DATA)
#define Queue3_Pop(QUEUE_POINTER,POINTER_DATA)			General_Queue_Pop(QUEUE_ID_3,QUEUE_POINTER,POINTER_DATA)
#define Queue3_Empty(QUEUE_POINTER)			General_Queue_Is_Empty(QUEUE_ID_3,QUEUE_POINTER)
#define Queue3_Full(QUEUE_POINTER)			General_Queue_Is_Full(QUEUE_ID_3,QUEUE_POINTER)
#define Queue3_Size(QUEUE_POINTER)			General_Queue_Size(QUEUE_ID_3,QUEUE_POINTER)
#define Queue3_Undo_Last_Pop(QUEUE_POINTER)			General_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_3,QUEUE_POINTER)

#define Queue4_Create(QUEUE_POINTER)			General_Queue_Create(QUEUE_ID_4,QUEUE_POINTER)
#define Queue4_Clear(QUEUE_POINTER)			General_Queue_Clear(QUEUE_ID_4,QUEUE_POINTER)
#define Queue4_Push(QUEUE_POINTER,DATA)			General_Queue_Push(QUEUE_ID_4,QUEUE_POINTER,DATA)
#define Queue4_Pop(QUEUE_POINTER,POINTER_DATA)			General_Queue_Pop(QUEUE_ID_4,QUEUE_POINTER,POINTER_DATA)
#define Queue4_Empty(QUEUE_POINTER)			General_Queue_Is_Empty(QUEUE_ID_4,QUEUE_POINTER)
#define Queue4_Full(QUEUE_POINTER)			General_Queue_Is_Full(QUEUE_ID_4,QUEUE_POINTER)
#define Queue4_Size(QUEUE_POINTER)			General_Queue_Size(QUEUE_ID_4,QUEUE_POINTER)
#define Queue4_Undo_Last_Pop(QUEUE_POINTER)			General_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_4,QUEUE_POINTER)


/*---------------------------------------------------------*/ 
#define Nested_Queue0_Create(QUEUE_POINTER)			General_Nested_Queue_Create(NESTED_QUEUE_ID_0,QUEUE_POINTER)
#define Nested_Queue0_Clear(QUEUE_POINTER)			General_Nested_Queue_Clear(NESTED_QUEUE_ID_0,QUEUE_POINTER)
#define Nested_Queue0_Push(QUEUE_POINTER,DATA)			General_Nested_Queue_Push(NESTED_QUEUE_ID_0,QUEUE_POINTER,DATA)
#define Nested_Queue0_Pop(QUEUE_POINTER,POINTER_DATA)			General_Nested_Queue_Pop(NESTED_QUEUE_ID_0,QUEUE_POINTER,POINTER_DATA)
#define Nested_Queue0_Empty(QUEUE_POINTER)			General_Nested_Queue_Is_Empty(NESTED_QUEUE_ID_0,QUEUE_POINTER)
#define Nested_Queue0_Full(QUEUE_POINTER)			General_Nested_Queue_Is_Full(NESTED_QUEUE_ID_0,QUEUE_POINTER)
#define Nested_Queue0_Size(QUEUE_POINTER)			General_Nested_Queue_Size(NESTED_QUEUE_ID_0,QUEUE_POINTER)
#define Nested_Queue0_Undo_Last_Pop(QUEUE_POINTER)			General_Nested_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_0,QUEUE_POINTER)

#define Nested_Queue1_Create(QUEUE_POINTER)			General_Nested_Queue_Create(NESTED_QUEUE_ID_1,QUEUE_POINTER)
#define Nested_Queue1_Clear(QUEUE_POINTER)			General_Nested_Queue_Clear(NESTED_QUEUE_ID_1,QUEUE_POINTER)
#define Nested_Queue1_Push(QUEUE_POINTER,DATA)			General_Nested_Queue_Push(NESTED_QUEUE_ID_1,QUEUE_POINTER,DATA)
#define Nested_Queue1_Pop(QUEUE_POINTER,POINTER_DATA)			General_Nested_Queue_Pop(NESTED_QUEUE_ID_1,QUEUE_POINTER,POINTER_DATA)
#define Nested_Queue1_Empty(QUEUE_POINTER)			General_Nested_Queue_Is_Empty(NESTED_QUEUE_ID_1,QUEUE_POINTER)
#define Nested_Queue1_Full(QUEUE_POINTER)			General_Nested_Queue_Is_Full(NESTED_QUEUE_ID_1,QUEUE_POINTER)
#define Nested_Queue1_Size(QUEUE_POINTER)			General_Nested_Queue_Size(NESTED_QUEUE_ID_1,QUEUE_POINTER)
#define Nested_Queue1_Undo_Last_Pop(QUEUE_POINTER)			General_Nested_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_1,QUEUE_POINTER)

#define Nested_Queue2_Create(QUEUE_POINTER)			General_Nested_Queue_Create(NESTED_QUEUE_ID_2,QUEUE_POINTER)
#define Nested_Queue2_Clear(QUEUE_POINTER)			General_Nested_Queue_Clear(NESTED_QUEUE_ID_2,QUEUE_POINTER)
#define Nested_Queue2_Push(QUEUE_POINTER,DATA)			General_Nested_Queue_Push(NESTED_QUEUE_ID_2,QUEUE_POINTER,DATA)
#define Nested_Queue2_Pop(QUEUE_POINTER,POINTER_DATA)			General_Nested_Queue_Pop(NESTED_QUEUE_ID_2,QUEUE_POINTER,POINTER_DATA)
#define Nested_Queue2_Empty(QUEUE_POINTER)			General_Nested_Queue_Is_Empty(NESTED_QUEUE_ID_2,QUEUE_POINTER)
#define Nested_Queue2_Full(QUEUE_POINTER)			General_Nested_Queue_Is_Full(NESTED_QUEUE_ID_2,QUEUE_POINTER)
#define Nested_Queue2_Size(QUEUE_POINTER)			General_Nested_Queue_Size(NESTED_QUEUE_ID_2,QUEUE_POINTER)
#define Nested_Queue2_Undo_Last_Pop(QUEUE_POINTER)			General_Nested_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_2,QUEUE_POINTER)

#define Nested_Queue3_Create(QUEUE_POINTER)			General_Nested_Queue_Create(NESTED_QUEUE_ID_3,QUEUE_POINTER)
#define Nested_Queue3_Clear(QUEUE_POINTER)			General_Nested_Queue_Clear(NESTED_QUEUE_ID_3,QUEUE_POINTER)
#define Nested_Queue3_Push(QUEUE_POINTER,DATA)			General_Nested_Queue_Push(NESTED_QUEUE_ID_3,QUEUE_POINTER,DATA)
#define Nested_Queue3_Pop(QUEUE_POINTER,POINTER_DATA)			General_Nested_Queue_Pop(NESTED_QUEUE_ID_3,QUEUE_POINTER,POINTER_DATA)
#define Nested_Queue3_Empty(QUEUE_POINTER)			General_Nested_Queue_Is_Empty(NESTED_QUEUE_ID_3,QUEUE_POINTER)
#define Nested_Queue3_Full(QUEUE_POINTER)			General_Nested_Queue_Is_Full(NESTED_QUEUE_ID_3,QUEUE_POINTER)
#define Nested_Queue3_Size(QUEUE_POINTER)			General_Nested_Queue_Size(NESTED_QUEUE_ID_3,QUEUE_POINTER)
#define Nested_Queue3_Undo_Last_Pop(QUEUE_POINTER)			General_Nested_Queue_Undo_Last_Pop(NESTED_QUEUE_ID_3,QUEUE_POINTER)

void General_Queue_Create(u8 Queue_ID,void *Queue_Pointer);
void General_Queue_Clear(u8 Queue_ID,void *Queue_Pointer);
u8 General_Queue_Push(u8 Queue_ID,void *Queue_Pointer,u32 copy_Data);
u8 General_Queue_Pop(u8 Queue_ID,void *Queue_Pointer,void *Data_Pointer);
u8 General_Queue_Is_Empty(u8 Queue_ID,void *Queue_Pointer);
u8 General_Queue_Is_Full(u8 Queue_ID,void *Queue_Pointer);
void General_Queue_Create(u8 Queue_ID,void *Queue_Pointer);
u16 General_Queue_Size(u8 Queue_ID,void *Queue_Pointer);
void General_Queue_Undo_Last_Pop(u8 Queue_ID,void *Queue_Pointer);


/*------------------Nested Queue Interface---------------------*/ 

void General_Nested_Queue_Create(u8 Queue_ID,void *Queue_Pointer);
void General_Nested_Queue_Clear(u8 Queue_ID,void *Queue_Pointer);
u8 General_Nested_Queue_Push(u8 Queue_ID,void *Nested_Queue_Pointer,void *Queue_Pointer);
u8 General_Nested_Queue_Pop(u8 Queue_ID,void *Queue_Pointer,void *Data_Pointer);
u8 General_Nested_Queue_Is_Empty(u8 Queue_ID,void *Queue_Pointer);
u8 General_Nested_Queue_Is_Full(u8 Queue_ID,void *Queue_Pointer);
void General_Nested_Queue_Create(u8 Queue_ID,void *Queue_Pointer);
u16 General_Nested_Queue_Size(u8 Queue_ID,void *Queue_Pointer);
void General_Nested_Queue_Undo_Last_Pop(u8 Queue_ID,void *Nested_Queue_Pointer);

#endif