/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 29 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  NVIC_PRIVATE_H
#define  NVIC_PRIVATE_H

/*Base address 0xE000E100*/

#define NVIC_ISER0  *((u32*)0xE000E100) /*Enable 0  to 31*/
#define NVIC_ISER1  *((u32*)0xE000E104) /*Enavle 32 to 63*/

#define NVIC_ICER0  *((u32*)0xE000E180) /*Disable 0  to 31*/ 
#define NVIC_ICER1  *((u32*)0xE000E184) /*Disable 32 to 63*/ 

#define NVIC_ISPR0  *((u32*)0xE000E200) /*Set Pending 0  to 31 */
#define NVIC_ISPR1  *((u32*)0xE000E204) /*Set Pending 32 to 63 */

#define NVIC_ICPR0  *((u32*)0xE000E280) /*Clear pending 0  to 31*/
#define NVIC_ICPR1  *((u32*)0xE000E284) /*Clear pending 32 to 63*/

#define NVIC_IABR0  *((volatile u32*)0xE000E300) /*Active bit registers 0 to 31*/
#define NVIC_IABR1  *((volatile u32*)0xE000E304) /*Active 32 to 63 */

#define NVIC_IPR     ((volatile u8 *)0xE000E400)
#define SCB_AIRCR	*((u32*)0xE000ED00+0x0C)



#endif