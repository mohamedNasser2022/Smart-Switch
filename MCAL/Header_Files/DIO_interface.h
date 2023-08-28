/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#include"STD_TYPES.h"

#include"DIO_config.h"

#ifndef  DIO_INTERFACE_H
#define  DIO_INTERFACE_H

#define Hardware_PIN1  	// BV
#define Hardware_PIN2   GPIOC,DIO_PIN13
#define Hardware_PIN3   GPIOC,DIO_PIN14
#define Hardware_PIN4   GPIOC,DIO_PIN15
#define Hardware_PIN5   GPIOA,DIO_PIN0
#define Hardware_PIN6   GPIOA,DIO_PIN1
#define Hardware_PIN7   GPIOA,DIO_PIN2
#define Hardware_PIN8   GPIOA,DIO_PIN3
#define Hardware_PIN9   GPIOA,DIO_PIN4
#define Hardware_PIN10  GPIOA,DIO_PIN5
#define Hardware_PIN11  GPIOA,DIO_PIN6
#define Hardware_PIN12  GPIOA,DIO_PIN7
#define Hardware_PIN13  GPIOB,DIO_PIN0
#define Hardware_PIN14  GPIOB,DIO_PIN1
#define Hardware_PIN15  GPIOB,DIO_PIN10
#define Hardware_PIN16  GPIOB,DIO_PIN11
#define Hardware_PIN17  // Reset Pin
#define Hardware_PIN18  // 3.3 V
#define Hardware_PIN19  // Ground
#define Hardware_PIN20  // Ground

#define Hardware_PIN21  GPIOB,DIO_PIN12
#define Hardware_PIN22  GPIOB,DIO_PIN13
#define Hardware_PIN23	GPIOB,DIO_PIN14
#define Hardware_PIN24	GPIOB,DIO_PIN15
#define Hardware_PIN25	GPIOA,DIO_PIN8
#define Hardware_PIN26	GPIOA,DIO_PIN9
#define Hardware_PIN27	GPIOA,DIO_PIN10
#define Hardware_PIN28	GPIOA,DIO_PIN11
#define Hardware_PIN29	GPIOA,DIO_PIN12
#define Hardware_PIN30	GPIOA,DIO_PIN15
#define Hardware_PIN31	GPIOB,DIO_PIN3
#define Hardware_PIN32	GPIOB,DIO_PIN4
#define Hardware_PIN33	GPIOB,DIO_PIN5
#define Hardware_PIN34	GPIOB,DIO_PIN6
#define Hardware_PIN35	GPIOB,DIO_PIN7
#define Hardware_PIN36	GPIOB,DIO_PIN8
#define Hardware_PIN37  GPIOB,DIO_PIN9
#define Hardware_PIN38  // 5V
#define Hardware_PIN39  // Ground
#define Hardware_PIN40  // 3.3 V




/*For Input*/
#define INPUT_ANALOG     0b0000
#define INPUT_FLOATING   0b0100
#define INPUT_PULL       0b1000

#define PULL_UP			0x11
#define PULL_DOWN		0x10

#define GPIO_HIGH 1
#define GPIO_LOW  0

/*For OUTPUT*/
#define OUTPUT_SPEED_10MHZ_PP   0b0001
#define OUTPUT_SPEED_10MHZ_OD   0b0101
#define OUTPUT_SPEED_10MHZ_AFPP 0b1001
#define OUTPUT_SPEED_10MHZ_AFOD 0b1101

#define OUTPUT_SPEED_2MHZ_PP    0b0010
#define OUTPUT_SPEED_2MHZ_OD    0b0110
#define OUTPUT_SPEED_2MHZ_AFPP  0b1010
#define OUTPUT_SPEED_2MHZ_AFOD  0b1110

#define OUTPUT_SPEED_50MHZ_PP   0b0011
#define OUTPUT_SPEED_50MHZ_OD   0b0111
#define OUTPUT_SPEED_50MHZ_AFPP 0b1011
#define OUTPUT_SPEED_50MHZ_AFOD 0b1111


void MGPIO_voidSetPinDirection(u8 copy_u8PORT,u8 copy_u8PIN,u8 copy_u8Mode);

void MGPIO_voidSetPinValue(u8 copy_u8PORT,u8 copy_u8PIN,u8 copy_u8Value);

void MGPIO_voidSetPinInputPull_Up_Down(u8 copy_u8PORT,u8 copy_u8PIN,u8 copy_u8Setting);

u8 MGPIO_u8GetPinValue(u8 copy_u8PORT,u8 copy_u8PIN);

void MGPIO_voidTogglePin(u8 copy_u8PORT,u8 copy_u8PIN);





#endif
