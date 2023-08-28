/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 26 OCT 2022									   */
/*	Version: V02  											   */
/***************************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* Options RCC_CLOCK_TYPE :
 * 				RCC_HSE_CRYSTAL
				RCC_HSE_RC		
				RCC_HSI 		
				RCC_PLL	 		 */

#define RCC_CLOCK_TYPE  RCC_PLL

/* Options RCC_CLOCK_TYPE :
 * 				RCC_PLL_IN_HSI_DIV_2
				RCC_PLL_IN_HSE_DIV_2 
				RCC_PLL_IN_HSE      */
#if  RCC_CLOCK_TYPE == RCC_PLL

#define RCC_PLL_INPUT RCC_PLL_IN_HSE

/* Options RCC_PLL_MUL_VAL:
 	 	 	 	 	 	 	 RCC_PLLMUL_4
 	 	 	 	 	 	 	 RCC_PLLMUL_5
 	 	 	 	 	 	 	 RCC_PLLMUL_6
 	 	 	 	 	 	 	 RCC_PLLMUL_7
 	 	 	 	 	 	 	 RCC_PLLMUL_8
 	 	 	 	 	 	 	 RCC_PLLMUL_9
 	 	 	 	 	 	 	 RCC_PLLMUL_6_AND_HALF
*/
#define RCC_PLL_MUL_VAL  RCC_PLLMUL_4


#endif

/*Options RCC_PRE_APB2:
 	 	 	 	 RCC_PPRE2_DIV_0
 	 	 	 	 RCC_PPRE2_DIV_2
 	 	 	 	 RCC_PPRE2_DIV_4
 	 	 	 	 RCC_PPRE2_DIV_8
 	 	 	 	 RCC_PPRE2_DIV_16
								*/

#define RCC_PRE_APB2  RCC_PPRE2_DIV_0

/*Options RCC_PRE_APB1:
 	 	 	 	 RCC_PPRE1_DIV_0
 	 	 	 	 RCC_PPRE1_DIV_2
 	 	 	 	 RCC_PPRE1_DIV_4
 	 	 	 	 RCC_PPRE1_DIV_8
 	 	 	 	 RCC_PPRE1_DIV_16
								*/

#define RCC_PRE_APB1  RCC_PPRE1_DIV_0

/*Options RCC_PRE_ADC:
 	 	 	 	 RCC_ADCPRE_DIV_2
 	 	 	 	 RCC_ADCPRE_DIV_4
 	 	 	 	 RCC_ADCPRE_DIV_6
 	 	 	 	 RCC_ADCPRE_DIV_8
								*/
#define RCC_PRE_ADC  RCC_ADCPRE_DIV_2

#endif
