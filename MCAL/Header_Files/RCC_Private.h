/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 26 OCT 2022									   */
/*	Version: V02  											   */
/***************************************************************/


#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H





/*Registers Definitions*/
#define RCC_CR       *((volatile u32*)0x40021000)
#define RCC_CFGR     *((volatile u32*)0x40021004)
#define RCC_CIR      *((volatile u32*)0x40021008)
#define RCC_APB2RSTR *((volatile u32*)0x4002100C)
#define RCC_APB1RSTR *((volatile u32*)0x40021010)
#define RCC_AHBENR   *((volatile u32*)0x40021014)
#define RCC_APB2ENR  *((volatile u32*)0x40021018)
#define RCC_APB1ENR  *((volatile u32*)0x4002101C)
#define RCC_BDCR     *((volatile u32*)0x40021020)
#define RCC_CSR      *((volatile u32*)0x40021024)



/*Clock Types*/
#define RCC_HSE_CRYSTAL 0 
#define RCC_HSE_RC		1
#define RCC_HSI 		2
#define RCC_PLL	 		3

/*PLL Options*/
#define RCC_PLL_IN_HSI_DIV_2 0
#define RCC_PLL_IN_HSE_DIV_2 1
#define RCC_PLL_IN_HSE       2

/*PLL Multiplication*/
#define RCC_PLLMUL_4  			0b0010
#define RCC_PLLMUL_5 			0b0011
#define RCC_PLLMUL_6  			0b0100
#define RCC_PLLMUL_7  			0b0101
#define RCC_PLLMUL_8 			0b0110
#define RCC_PLLMUL_9 		    0b0111
#define RCC_PLLMUL_6_AND_HALF   0b1101

 
/*APB2 PreScaler*/
#define RCC_PPRE2_DIV_0 	0b000
#define RCC_PPRE2_DIV_2 	0b100
#define RCC_PPRE2_DIV_4		0b101
#define RCC_PPRE2_DIV_8 	0b110
#define RCC_PPRE2_DIV_16 	0b111

/*APB1 PreScaler*/
#define RCC_PPRE1_DIV_0 	0b000
#define RCC_PPRE1_DIV_2 	0b100
#define RCC_PPRE1_DIV_4		0b101
#define RCC_PPRE1_DIV_8 	0b110
#define RCC_PPRE1_DIV_16 	0b111

/*ADC PreScaler*/
#define RCC_ADCPRE_DIV_2 	0b00
#define RCC_ADCPRE_DIV_4 	0b01
#define RCC_ADCPRE_DIV_6	0b10
#define RCC_ADCPRE_DIV_8 	0b11


#endif
