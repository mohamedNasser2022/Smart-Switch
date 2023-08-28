/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  SYSTICK_CONFIG_H
#define  SYSTICK_CONFIG_H
/*
 * to calculate STK_PLL_Clock use the following equation
 * tick * count * STK_PLL_CLOCK = 1 ms  count = 1000, where tick is the clock which operate the systick
 *
 * */

#define STK_PLL_CLOCK 4

/*
Select clock of SYSTICK_CLOCK =  AHB/F

F = 1 SYSTICK_DIV_1
F = 8 SYSTICK_DIV_8

*/
#define SYSTICK_CLOCK SYSTICK_DIV_8

#endif
