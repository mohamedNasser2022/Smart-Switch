/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"UART_interface.h"
#include"UART_private.h"
#include"UART_config.h"
#include"SYSTICK_interface.h"
#include"DIO_Interface.h"


void MUSART_voidInit(void)
{
	MGPIO_voidSetPinDirection(GPIOA,DIO_PIN9,OUTPUT_SPEED_50MHZ_AFPP);//TX
	MGPIO_voidSetPinDirection(GPIOA,DIO_PIN10,INPUT_FLOATING);//RX
	/*Set Baud rate at 50 000*/ //0xD3 150 000
	MUSART1->BRR = 0x280;
	/*Enable Tx	3
	  Enable RX 2
	  Enable UART*/
	SET_BIT(MUSART1->CR1,2);
	SET_BIT(MUSART1->CR1,3);
	SET_BIT(MUSART1->CR1,13);



}

void MUSART_voidTransmit_Wait(u8 arr[])
{
	u8 i=0;
	u32 l=0;
	while(arr[i] != '\0')
	{
		MUSART1->DR = arr[i];
		while(((MUSART1->SR)& 1<<6) == 0);
		i++;
	}
}

void MUSART_voidTransmitNumbers_Wait(u8 copy_u8SendNumber)
{
	u8 i=0;
	u32 l=0;

	MUSART1->DR = copy_u8SendNumber;
	while(((MUSART1->SR)& 1<<6) == 0);




}

u8 MUSART_u8Recive_Wait(void)
{

	u8  Recive = 0;
	while(((MUSART1->SR)& 1<<5) == 0)
	{

	}

	Recive = MUSART1->DR;

	return Recive;
}

u8 MUSART_u8TransmitNumbers_Polling(u8 copy_u8SendNumber)
{

	if(((MUSART1->SR) & 1<<6) == 0)
	{
		return 0; //wait until Trasmit
	}
	else
	{
		MUSART1->DR = copy_u8SendNumber;
		return 1;
	}

}

u8 MUSART_u8Recive_Polling(u8 *ptr_u8RecivedNumber)
{
	if(((MUSART1->SR)& 1<<5) == 0)
	{
		// No Serial Avalabile
		return 0 ;
	}
	else
	{
		//Serial Avalabile
		*ptr_u8RecivedNumber = MUSART1->DR;

		return 1;
	}
}


