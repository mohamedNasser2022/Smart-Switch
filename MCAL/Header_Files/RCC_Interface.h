/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 26 OCT 2022									   */
/*	Version: V02  											   */
/***************************************************************/


#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#define RCC_AFIO    RCC_APB2,0
#define RCC_IOPA    RCC_APB2,2
#define RCC_IOPB    RCC_APB2,3
#define RCC_IOPC    RCC_APB2,4
#define RCC_IOPD    RCC_APB2,5
#define RCC_IOPE    RCC_APB2,6
#define RCC_ADC1    RCC_APB2,9
#define RCC_ADC2    RCC_APB2,10
#define RCC_TIM1    RCC_APB2,11
#define RCC_SPI1    RCC_APB2,12
#define RCC_USART1  RCC_APB2,14

#define RCC_TIM2     RCC_APB1,0
#define RCC_TIM3     RCC_APB1,1
#define RCC_TIM4     RCC_APB1,2
#define RCC_TIM5     RCC_APB1,3
#define RCC_TIM6     RCC_APB1,4
#define RCC_TIM7     RCC_APB1,5
#define RCC_WWDG     RCC_APB1,11
#define RCC_SPI2     RCC_APB1,14
#define RCC_SPI3     RCC_APB1,15
#define RCC_USART2   RCC_APB1,17
#define RCC_USART3   RCC_APB1,18
#define RCC_UART4    RCC_APB1,19
#define RCC_UART5    RCC_APB1,20
#define RCC_I2C1     RCC_APB1,21
#define RCC_I2C2     RCC_APB1,22
#define RCC_CAN1     RCC_APB1,25
#define RCC_CAN2     RCC_APB1,26

#define RCC_DMA1       RCC_AHP,0
#define RCC_DMA2       RCC_AHP,1
#define RCC_SRAM       RCC_AHP,2
#define RCC_FLITF      RCC_AHP,4
#define RCC_CRC        RCC_AHP,6
#define RCC_OTGFS      RCC_AHP,12
#define RCC_ETHMAC     RCC_AHP,14
#define RCC_ETHMACTX   RCC_AHP,15
#define RCC_ETHMACRX   RCC_AHP,16




void RCC_voidInitSystemClock(void);
void RCC_voidEnableClock(u8 BusID, u8 PerID);
void RCC_voidDisableClock(u8 BusID, u8 PerID);

#define RCC_AHP  0
#define RCC_APB1 1
#define RCC_APB2 2


#endif
