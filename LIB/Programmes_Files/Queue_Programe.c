#include"STD_TYPES.h"
#include"Queue_Data_Types.h"
#include"Queue_Private.h"
#include"Queue_Interface.h"
void General_Queue_Create(u8 Queue_ID,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			((Array_Of_Queue_0*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_0*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_0*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_1:
			((Array_Of_Queue_1*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_1*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_1*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_2:
			((Array_Of_Queue_2*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_2*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_2*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_3:
			((Array_Of_Queue_3*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_3*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_3*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_4:
			((Array_Of_Queue_4*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_4*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_4*)Queue_Pointer)->Size =0 ;
		break;
	}
}
void General_Queue_Clear(u8 Queue_ID,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			((Array_Of_Queue_0*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_0*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_0*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_1:
			((Array_Of_Queue_1*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_1*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_1*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_2:
			((Array_Of_Queue_2*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_2*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_2*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_3:
			((Array_Of_Queue_3*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_3*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_3*)Queue_Pointer)->Size =0 ;
		break;
		case	QUEUE_ID_4:
			((Array_Of_Queue_4*)Queue_Pointer)->Front =0 ;
			((Array_Of_Queue_4*)Queue_Pointer)->Rear =-1 ;
			((Array_Of_Queue_4*)Queue_Pointer)->Size =0 ;
		break;
	}
}
u8 General_Queue_Push(u8 Queue_ID,void *Queue_Pointer,u32 copy_Data)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			if(10!= (((Array_Of_Queue_0*)Queue_Pointer)->Size))
			{
				((Array_Of_Queue_0*)Queue_Pointer)->Rear = ((u8)(((Array_Of_Queue_0*)Queue_Pointer)->Rear+1)) % 10;
				((Array_Of_Queue_0*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_0*)Queue_Pointer)->Rear] = copy_Data ;
				((Array_Of_Queue_0*)Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_1:
			if(10!= (((Array_Of_Queue_1*)Queue_Pointer)->Size))
			{
				((Array_Of_Queue_1*)Queue_Pointer)->Rear = ((u8)(((Array_Of_Queue_1*)Queue_Pointer)->Rear+1)) % 10;
				((Array_Of_Queue_1*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_1*)Queue_Pointer)->Rear] = copy_Data ;
				((Array_Of_Queue_1*)Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_2:
			if(45!= (((Array_Of_Queue_2*)Queue_Pointer)->Size))
			{
				((Array_Of_Queue_2*)Queue_Pointer)->Rear = ((u8)(((Array_Of_Queue_2*)Queue_Pointer)->Rear+1)) % 45;
				((Array_Of_Queue_2*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_2*)Queue_Pointer)->Rear] = copy_Data ;
				((Array_Of_Queue_2*)Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_3:
			if(50!= (((Array_Of_Queue_3*)Queue_Pointer)->Size))
			{
				((Array_Of_Queue_3*)Queue_Pointer)->Rear = ((u8)(((Array_Of_Queue_3*)Queue_Pointer)->Rear+1)) % 50;
				((Array_Of_Queue_3*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_3*)Queue_Pointer)->Rear] = copy_Data ;
				((Array_Of_Queue_3*)Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_4:
			if(5!= (((Array_Of_Queue_4*)Queue_Pointer)->Size))
			{
				((Array_Of_Queue_4*)Queue_Pointer)->Rear = ((u8)(((Array_Of_Queue_4*)Queue_Pointer)->Rear+1)) % 5;
				((Array_Of_Queue_4*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_4*)Queue_Pointer)->Rear] = copy_Data ;
				((Array_Of_Queue_4*)Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
	}
	 return Local_Return ;
}
u8 General_Queue_Pop(u8 Queue_ID,void *Queue_Pointer,void *Data_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			if(0!= (((Array_Of_Queue_0*)Queue_Pointer)->Size))
			{
				*(u8*)Data_Pointer = ((Array_Of_Queue_0*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_0*)Queue_Pointer)->Front];
				((Array_Of_Queue_0*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_0*)Queue_Pointer)->Front+1)) % 10;
				((Array_Of_Queue_0*)Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_1:
			if(0!= (((Array_Of_Queue_1*)Queue_Pointer)->Size))
			{
				*(u8*)Data_Pointer = ((Array_Of_Queue_1*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_1*)Queue_Pointer)->Front];
				((Array_Of_Queue_1*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_1*)Queue_Pointer)->Front+1)) % 10;
				((Array_Of_Queue_1*)Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_2:
			if(0!= (((Array_Of_Queue_2*)Queue_Pointer)->Size))
			{
				*(u8*)Data_Pointer = ((Array_Of_Queue_2*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_2*)Queue_Pointer)->Front];
				((Array_Of_Queue_2*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_2*)Queue_Pointer)->Front+1)) % 45;
				((Array_Of_Queue_2*)Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_3:
			if(0!= (((Array_Of_Queue_3*)Queue_Pointer)->Size))
			{
				*(u8*)Data_Pointer = ((Array_Of_Queue_3*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_3*)Queue_Pointer)->Front];
				((Array_Of_Queue_3*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_3*)Queue_Pointer)->Front+1)) % 50;
				((Array_Of_Queue_3*)Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_4:
			if(0!= (((Array_Of_Queue_4*)Queue_Pointer)->Size))
			{
				*(u32*)Data_Pointer = ((Array_Of_Queue_4*)Queue_Pointer)->Queue_Elements[((Array_Of_Queue_4*)Queue_Pointer)->Front];
				((Array_Of_Queue_4*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_4*)Queue_Pointer)->Front+1)) % 5;
				((Array_Of_Queue_4*)Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
	}
	 return Local_Return ;
}
u8 General_Queue_Is_Empty(u8 Queue_ID,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			Local_Return = !((Array_Of_Queue_0*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_1:
			Local_Return = !((Array_Of_Queue_1*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_2:
			Local_Return = !((Array_Of_Queue_2*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_3:
			Local_Return = !((Array_Of_Queue_3*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_4:
			Local_Return = !((Array_Of_Queue_4*)Queue_Pointer)->Size;
		break;
	}
	 return Local_Return ;
}
u8 General_Queue_Is_Full(u8 Queue_ID,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			Local_Return = !((Array_Of_Queue_0*)Queue_Pointer)->Size == 10;
		break;
		case	QUEUE_ID_1:
			Local_Return = !((Array_Of_Queue_1*)Queue_Pointer)->Size == 10;
		break;
		case	QUEUE_ID_2:
			Local_Return = !((Array_Of_Queue_2*)Queue_Pointer)->Size == 45;
		break;
		case	QUEUE_ID_3:
			Local_Return = !((Array_Of_Queue_3*)Queue_Pointer)->Size == 50;
		break;
		case	QUEUE_ID_4:
			Local_Return = !((Array_Of_Queue_4*)Queue_Pointer)->Size == 5;
		break;
	}
	 return Local_Return ;
}
u16 General_Queue_Size(u8 Queue_ID,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			Local_Return = ((Array_Of_Queue_0*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_1:
			Local_Return = ((Array_Of_Queue_1*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_2:
			Local_Return = ((Array_Of_Queue_2*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_3:
			Local_Return = ((Array_Of_Queue_3*)Queue_Pointer)->Size;
		break;
		case	QUEUE_ID_4:
			Local_Return = ((Array_Of_Queue_4*)Queue_Pointer)->Size;
		break;
	}
	 return Local_Return ;
}
void General_Queue_Undo_Last_Pop(u8 Queue_ID,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
				((Array_Of_Queue_0*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_0*)Queue_Pointer)->Front-1)) % 10;
				((Array_Of_Queue_0*)Queue_Pointer)->Size++;
		break;
		case	QUEUE_ID_1:
				((Array_Of_Queue_1*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_1*)Queue_Pointer)->Front-1)) % 10;
				((Array_Of_Queue_1*)Queue_Pointer)->Size++;
		break;
		case	QUEUE_ID_2:
				((Array_Of_Queue_2*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_2*)Queue_Pointer)->Front-1)) % 3;
				((Array_Of_Queue_2*)Queue_Pointer)->Size++;
		break;
		case	QUEUE_ID_3:
				((Array_Of_Queue_3*)Queue_Pointer)->Front = ((u8)(((Array_Of_Queue_3*)Queue_Pointer)->Front-1)) % 5;
				((Array_Of_Queue_3*)Queue_Pointer)->Size++;
		break;
		case	QUEUE_ID_4:
				((Array_Of_Queue_4*)Queue_Pointer)->Front = ((u32)(((Array_Of_Queue_4*)Queue_Pointer)->Front-1)) % 5;
				((Array_Of_Queue_4*)Queue_Pointer)->Size++;
		break;
	}
}

/*----------------------------Nested Queue Functions ---------------------------------*/

void General_Nested_Queue_Create(u8 Queue_ID,void *Nested_Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
			((Nested_Queue_0*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_0*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_0*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 10; i++)
			{
				 Queue0_Create(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
		case	NESTED_QUEUE_ID_1:
			((Nested_Queue_1*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_1*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_1*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 10; i++)
			{
				 Queue1_Create(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
		case	NESTED_QUEUE_ID_2:
			((Nested_Queue_2*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_2*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_2*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 3; i++)
			{
				 Queue2_Create(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
		case	NESTED_QUEUE_ID_3:
			((Nested_Queue_3*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_3*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_3*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 5; i++)
			{
				 Queue3_Create(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
	}
}
void General_Nested_Queue_Clear(u8 Queue_ID,void *Nested_Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
			((Nested_Queue_0*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_0*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_0*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 10; i++)
			{
				 Queue0_Clear(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
		case	NESTED_QUEUE_ID_1:
			((Nested_Queue_1*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_1*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_1*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 10; i++)
			{
				 Queue1_Clear(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
		case	NESTED_QUEUE_ID_2:
			((Nested_Queue_2*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_2*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_2*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 3; i++)
			{
				 Queue2_Clear(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
		case	NESTED_QUEUE_ID_3:
			((Nested_Queue_3*)Nested_Queue_Pointer)->Front =0 ;
			((Nested_Queue_3*)Nested_Queue_Pointer)->Rear =-1 ;
			((Nested_Queue_3*)Nested_Queue_Pointer)->Size =0 ;
			for(u8 i = 0; i < 5; i++)
			{
				 Queue3_Clear(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[i]);
			}
		break;
	}
}
u8 General_Nested_Queue_Push(u8 Queue_ID,void *Nested_Queue_Pointer,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	 u8 Local_Data = 0;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
			if(10!= (((Nested_Queue_0*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_0*)Nested_Queue_Pointer)->Rear = ((u8)(((Nested_Queue_0*)Nested_Queue_Pointer)->Rear+1)) % 10;
				while(Queue0_Pop(Queue_Pointer,&Local_Data))
				{
					Queue0_Push(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_0*)Nested_Queue_Pointer)->Rear],Local_Data);
				}
				((Nested_Queue_0*)Nested_Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	NESTED_QUEUE_ID_1:
			if(10!= (((Nested_Queue_1*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_1*)Nested_Queue_Pointer)->Rear = ((u8)(((Nested_Queue_1*)Nested_Queue_Pointer)->Rear+1)) % 10;
				while(Queue1_Pop(Queue_Pointer,&Local_Data))
				{
					Queue1_Push(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_1*)Nested_Queue_Pointer)->Rear],Local_Data);
				}
				((Nested_Queue_1*)Nested_Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	NESTED_QUEUE_ID_2:
			if(3!= (((Nested_Queue_2*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_2*)Nested_Queue_Pointer)->Rear = ((u8)(((Nested_Queue_2*)Nested_Queue_Pointer)->Rear+1)) % 3;
				while(Queue2_Pop(Queue_Pointer,&Local_Data))
				{
					Queue2_Push(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_2*)Nested_Queue_Pointer)->Rear],Local_Data);
				}
				((Nested_Queue_2*)Nested_Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	NESTED_QUEUE_ID_3:
			if(5!= (((Nested_Queue_3*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_3*)Nested_Queue_Pointer)->Rear = ((u8)(((Nested_Queue_3*)Nested_Queue_Pointer)->Rear+1)) % 5;
				while(Queue3_Pop(Queue_Pointer,&Local_Data))
				{
					Queue3_Push(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_3*)Nested_Queue_Pointer)->Rear],Local_Data);
				}
				((Nested_Queue_3*)Nested_Queue_Pointer)->Size++;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
	}
	 return Local_Return ;
}
u8 General_Nested_Queue_Pop(u8 Queue_ID,void *Nested_Queue_Pointer,void *Queue_Pointer)
{
	 u8 Local_Return = 1;
	 u8 Local_Data = 0;
	switch(Queue_ID)
	{
		case	QUEUE_ID_0:
			if(0!= (((Nested_Queue_0*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_0*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue = Queue0_Size(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_0*)Nested_Queue_Pointer)->Front]);
				while(Queue0_Pop(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_0*)Nested_Queue_Pointer)->Front],&Local_Data))
				{
					Queue0_Push(Queue_Pointer,Local_Data);
				}
				((Nested_Queue_0*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_0*)Nested_Queue_Pointer)->Front+1)) % 10;
				((Nested_Queue_0*)Nested_Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_1:
			if(0!= (((Nested_Queue_1*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_1*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue = Queue1_Size(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_1*)Nested_Queue_Pointer)->Front]);
				while(Queue1_Pop(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_1*)Nested_Queue_Pointer)->Front],&Local_Data))
				{
					Queue1_Push(Queue_Pointer,Local_Data);
				}
				((Nested_Queue_1*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_1*)Nested_Queue_Pointer)->Front+1)) % 10;
				((Nested_Queue_1*)Nested_Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_2:
			if(0!= (((Nested_Queue_2*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_2*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue = Queue2_Size(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_2*)Nested_Queue_Pointer)->Front]);
				while(Queue2_Pop(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_2*)Nested_Queue_Pointer)->Front],&Local_Data))
				{
					Queue2_Push(Queue_Pointer,Local_Data);
				}
				((Nested_Queue_2*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_2*)Nested_Queue_Pointer)->Front+1)) % 3;
				((Nested_Queue_2*)Nested_Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
		case	QUEUE_ID_3:
			if(0!= (((Nested_Queue_3*)Nested_Queue_Pointer)->Size))
			{
				((Nested_Queue_3*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue = Queue3_Size(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_3*)Nested_Queue_Pointer)->Front]);
				while(Queue3_Pop(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_3*)Nested_Queue_Pointer)->Front],&Local_Data))
				{
					Queue3_Push(Queue_Pointer,Local_Data);
				}
				((Nested_Queue_3*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_3*)Nested_Queue_Pointer)->Front+1)) % 5;
				((Nested_Queue_3*)Nested_Queue_Pointer)->Size--;
			}
			else
			{
				 Local_Return = 0;
			}
		break;
	}
	 return Local_Return ;
}
u8 General_Nested_Queue_Is_Empty(u8 Queue_ID,void *Nested_Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
			Local_Return = !((Nested_Queue_0*)Nested_Queue_Pointer)->Size;
		break;
		case	NESTED_QUEUE_ID_1:
			Local_Return = !((Nested_Queue_1*)Nested_Queue_Pointer)->Size;
		break;
		case	NESTED_QUEUE_ID_2:
			Local_Return = !((Nested_Queue_2*)Nested_Queue_Pointer)->Size;
		break;
		case	NESTED_QUEUE_ID_3:
			Local_Return = !((Nested_Queue_3*)Nested_Queue_Pointer)->Size;
		break;
	}
	 return Local_Return ;
}
u8 General_Nested_Queue_Is_Full(u8 Queue_ID,void *Nested_Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
			Local_Return = ((Nested_Queue_0*)Nested_Queue_Pointer)->Size == 10;
		break;
		case	NESTED_QUEUE_ID_1:
			Local_Return = ((Nested_Queue_1*)Nested_Queue_Pointer)->Size == 10;
		break;
		case	NESTED_QUEUE_ID_2:
			Local_Return = ((Nested_Queue_2*)Nested_Queue_Pointer)->Size == 3;
		break;
		case	NESTED_QUEUE_ID_3:
			Local_Return = ((Nested_Queue_3*)Nested_Queue_Pointer)->Size == 5;
		break;
	}
	 return Local_Return ;
}
u16 General_Nested_Queue_Size(u8 Queue_ID,void *Nested_Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
			Local_Return = ((Nested_Queue_0*)Nested_Queue_Pointer)->Size;
		break;
		case	NESTED_QUEUE_ID_1:
			Local_Return = ((Nested_Queue_1*)Nested_Queue_Pointer)->Size;
		break;
		case	NESTED_QUEUE_ID_2:
			Local_Return = ((Nested_Queue_2*)Nested_Queue_Pointer)->Size;
		break;
		case	NESTED_QUEUE_ID_3:
			Local_Return = ((Nested_Queue_3*)Nested_Queue_Pointer)->Size;
		break;
	}
	 return Local_Return ;
}
void General_Nested_Queue_Undo_Last_Pop(u8 Queue_ID,void *Nested_Queue_Pointer)
{
	 u8 Local_Return = 1;
	switch(Queue_ID)
	{
		case	NESTED_QUEUE_ID_0:
				if(((Nested_Queue_0*)Nested_Queue_Pointer)->Front == 0)
				{
					((Nested_Queue_0*)Nested_Queue_Pointer)->Front = 10-1;
				}
				else
				{
				((Nested_Queue_0*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_0*)Nested_Queue_Pointer)->Front-1)) % 10;
				}
				((Nested_Queue_0*)Nested_Queue_Pointer)->Size++;
				while(Queue0_Size(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_0*)Nested_Queue_Pointer)->Front]) !=((Nested_Queue_0*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue)
				{
					Queue0_Undo_Last_Pop(&((Nested_Queue_0*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_0*)Nested_Queue_Pointer)->Front]);
				}
		break;
		case	NESTED_QUEUE_ID_1:
				if(((Nested_Queue_1*)Nested_Queue_Pointer)->Front == 0)
				{
					((Nested_Queue_1*)Nested_Queue_Pointer)->Front = 10-1;
				}
				else
				{
				((Nested_Queue_1*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_1*)Nested_Queue_Pointer)->Front-1)) % 10;
				}
				((Nested_Queue_1*)Nested_Queue_Pointer)->Size++;
				while(Queue1_Size(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_1*)Nested_Queue_Pointer)->Front]) !=((Nested_Queue_1*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue)
				{
					Queue1_Undo_Last_Pop(&((Nested_Queue_1*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_1*)Nested_Queue_Pointer)->Front]);
				}
		break;
		case	NESTED_QUEUE_ID_2:
				if(((Nested_Queue_2*)Nested_Queue_Pointer)->Front == 0)
				{
					((Nested_Queue_2*)Nested_Queue_Pointer)->Front = 3-1;
				}
				else
				{
				((Nested_Queue_2*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_2*)Nested_Queue_Pointer)->Front-1)) % 3;
				}
				((Nested_Queue_2*)Nested_Queue_Pointer)->Size++;
				while(Queue2_Size(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_2*)Nested_Queue_Pointer)->Front]) !=((Nested_Queue_2*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue)
				{
					Queue2_Undo_Last_Pop(&((Nested_Queue_2*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_2*)Nested_Queue_Pointer)->Front]);
				}
		break;
		case	NESTED_QUEUE_ID_3:
				if(((Nested_Queue_3*)Nested_Queue_Pointer)->Front == 0)
				{
					((Nested_Queue_3*)Nested_Queue_Pointer)->Front = 5-1;
				}
				else
				{
				((Nested_Queue_3*)Nested_Queue_Pointer)->Front = ((u8)(((Nested_Queue_3*)Nested_Queue_Pointer)->Front-1)) % 5;
				}
				((Nested_Queue_3*)Nested_Queue_Pointer)->Size++;
				while(Queue3_Size(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_3*)Nested_Queue_Pointer)->Front]) !=((Nested_Queue_3*)Nested_Queue_Pointer)->Size_Of_Last_Poped_Queue)
				{
					Queue3_Undo_Last_Pop(&((Nested_Queue_3*)Nested_Queue_Pointer)->Queue_Elements[((Nested_Queue_3*)Nested_Queue_Pointer)->Front]);
				}
		break;
	}
}
