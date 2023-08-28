/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"



#include "DIO_private.h"
#include "DIO_config.h"
#include "DIO_interface.h"



void MGPIO_voidSetPinDirection(u8 copy_u8PORT,u8 copy_u8PIN,u8 copy_u8Mode)
{
	if(copy_u8Mode == PULL_UP || copy_u8Mode == PULL_DOWN)
	{
		MGPIO_voidSetPinInputPull_Up_Down(copy_u8PORT,copy_u8PIN,copy_u8Mode);
	}
	else
	{


		switch (copy_u8PORT)
		{
		case GPIOA :
			if(copy_u8PIN<=7)
			{
				GPIOA_CRL &= ~ ((0b1111)<<(copy_u8PIN*4));
				GPIOA_CRL |=   ((copy_u8Mode)<<(copy_u8PIN*4));
			}
			else if(copy_u8PIN<=15)
			{
				copy_u8PIN = copy_u8PIN - 8;
				GPIOA_CRH &= ~ ((0b1111)<<(copy_u8PIN*4));
				GPIOA_CRH |=   ((copy_u8Mode)<<(copy_u8PIN*4));
			}
			break;
		case GPIOB :
			if(copy_u8PIN<=7)
			{
				GPIOB_CRL &= ~ ((0b1111)<<(copy_u8PIN*4));
				GPIOB_CRL |=   ((copy_u8Mode)<<(copy_u8PIN*4));
			}
			else if(copy_u8PIN<=15)
			{
				copy_u8PIN = copy_u8PIN - 8;
				GPIOB_CRH &= ~ ((0b1111)<<(copy_u8PIN*4));
				GPIOB_CRH |=   ((copy_u8Mode)<<(copy_u8PIN*4));
			}
			break;

		case GPIOC :
			if(copy_u8PIN<=7)
			{
				GPIOC_CRL &= ~ ((0b1111)<<(copy_u8PIN*4));
				GPIOC_CRL |=   ((copy_u8Mode)<<(copy_u8PIN*4));
			}
			else if(copy_u8PIN<=15)
			{
				copy_u8PIN = copy_u8PIN - 8;
				GPIOC_CRH &= ~ ((0b1111)<<(copy_u8PIN*4));
				GPIOC_CRH |=   ((copy_u8Mode)<<(copy_u8PIN*4));
			}
			break;

		default:
			break;
		}
	}
}

void MGPIO_voidSetPinValue(u8 copy_u8PORT,u8 copy_u8PIN,u8 copy_u8Value)
{
	switch (copy_u8PORT)
	{
	case GPIOA :
		if(copy_u8Value == GPIO_HIGH)
		{
			SET_BIT(GPIOA_ODR ,copy_u8PIN );
		}
		else if(copy_u8Value == GPIO_LOW)
		{
			CLR_BIT(GPIOA_ODR ,copy_u8PIN );
		}
		else {//Error
		}
		break;
	case GPIOB :
		if(copy_u8Value == GPIO_HIGH)
		{
			SET_BIT(GPIOB_ODR ,copy_u8PIN );
		}
		else if(copy_u8Value == GPIO_LOW)
		{
			CLR_BIT(GPIOB_ODR ,copy_u8PIN );
		}
		else {//Error
		}
		break;
	case GPIOC :
		if(copy_u8Value == GPIO_HIGH)
		{
			SET_BIT(GPIOC_ODR ,copy_u8PIN );
		}
		else if(copy_u8Value == GPIO_LOW)
		{
			CLR_BIT(GPIOC_ODR ,copy_u8PIN );
		}
		else {//Error
		}
		break;
	default: break;
	}
}

void MGPIO_voidSetPinInputPull_Up_Down(u8 copy_u8PORT,u8 copy_u8PIN,u8 copy_u8Setting)
{
	MGPIO_voidSetPinDirection(copy_u8PORT,copy_u8PIN,INPUT_PULL);
	MGPIO_voidSetPinValue(copy_u8PORT,copy_u8PIN,copy_u8Setting&0x0F);

}

u8 MGPIO_u8GetPinValue(u8 copy_u8PORT,u8 copy_u8PIN)
{	u8 LOC_u8Result = 0;
switch (copy_u8PORT)
{
case GPIOA :
	LOC_u8Result = GET_BIT(GPIOA_IDR ,copy_u8PIN );
	break;
case GPIOB :
	LOC_u8Result = GET_BIT(GPIOB_IDR ,copy_u8PIN );
	break;
case GPIOC :
	LOC_u8Result = GET_BIT(GPIOC_IDR ,copy_u8PIN );
	break;
default: break;
}
return LOC_u8Result;
}

void MGPIO_voidTogglePin(u8 copy_u8PORT,u8 copy_u8PIN)
{
	switch (copy_u8PORT)
	{
	case GPIOA :
		TOG_BIR(GPIOA_ODR ,copy_u8PIN );


		break;
	case GPIOB :

		TOG_BIR(GPIOB_ODR ,copy_u8PIN );

		break;
	case GPIOC :
		TOG_BIR(GPIOC_ODR ,copy_u8PIN );

		break;

	default:
		break;
	}

}
