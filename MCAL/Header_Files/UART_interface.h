/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  UART_INTERFACE_H
#define  UART_INTERFACE_H

void MUSART_voidInit(void);
void MUSART_voidTransmit_Wait(u8 arr[]);
void MUSART_voidTransmitNumbers_Wait(u8 copy_u8SendNumber);
u8 MUSART_u8Recive_Wait(void);
u8 MUSART_u8TransmitNumbers_Polling(u8 copy_u8SendNumber);
u8 MUSART_u8Recive_Polling(u8 *ptr_u8RecivedNumber);
#endif
