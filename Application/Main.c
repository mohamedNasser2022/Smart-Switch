/*
 * Main.c
 *
 *  Created on: 15 OCT 2022
 *      Author: Mohamed
 */



#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"RCC_Interface.h"
#include"DIO_interface.h"
#include"NVIC_interface.h"
#include"EXTI_interface.h"
#include"SYSTICK_interface.h"
#include"I2C_Configuration.h"
#include"System_Main.h"

volatile u8 System_Mode = BOOT_HALT;
void Polling_Functions_For_System(void);

void main()
{
	//RCC_voidInitSystemClock(); /*Rcc Enable*/

	/*
	LCD_Init();
	MGPIO_voidSetPinDirection(GPIOB,PIN1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(GPIOB,PIN1,0);

	MGPIO_voidSetPinValue(GPIOB,PIN1,1);
	LCD_SendString("Developing Kit  V5 Nasrallah");
	MGPIO_voidSetPinValue(GPIOB,PIN1,1);
	MGPIO_voidSetPinValue(GPIOB,PIN1,0);
	//4E 6F 75 72 68 61 6E 20 49 20 6C 6F 76 65 20 79 6F 75
	LCD_SendCommand(0x01);
	LCD_SendString("4E6F75722049204C6F766520596F75");
	MGPIO_voidSetPinValue(GPIOB,PIN1,1);
	//LCD_Sys();
	while(1);*/




	volatile u8 status = 0;

	RCC_voidInitSystemClock();       /*Rcc Enable*/
	RCC_voidEnableClock(RCC_IOPA);   /*GPIOA Enable*/
	RCC_voidEnableClock(RCC_IOPB);   /*GPIOA Enable*/
	RCC_voidEnableClock(RCC_IOPC);   /*GPIOA Enable*/
	RCC_voidEnableClock(RCC_USART1); /*Enable UART1*/

	RTE_Init();



	/*Enable systick*/
	MSTK_voidInit();
	MSTK_voidSetIntervalPeriodic(1000,Polling_Functions_For_System); // this calling each 1 ms



	while(1)
	{
		RTE_Polling();
	}
}



void Polling_Functions_For_System(void)
{
	RTE_Periodic();
}

