/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*EXTI_CallBack) (void) =NULL;

void MEXTI_voidInit()
{ 
#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI -> IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI -> IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI -> IMR , EXTI_LINE2 );
	#else
		#error ("Wrong Externl Interrupt Line !")
	#endif


	#if		EXTI_SENSE_MODE == FALLING_EDGE
			SET_BIT(EXTI -> FTSR , EXTI_LINE0);
	#elif	EXTI_SENSE_MODE == RISING_EDGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == ON_CHANGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#else
		#error ("Wrong Externl Interrupt Sense Mode !")
	#endif
}
void MEXTI_voidEnableEXTI(u8 copy_u8Line)
{	
	SET_BIT(EXTI->IMR,copy_u8Line);
}
void MEXTI_voidDisableEXTI(u8 copy_u8Line)
{
	CLR_BIT(EXTI->IMR,copy_u8Line);	
}
void MEXTI_voidSwTrigger(u8 copy_u8Line)
{
	SET_BIT(EXTI->SWIER,copy_u8Line);
}

void MEXTI_voidSetSignaLatch(u8 copy_u8Line,u8 copy_u8Mode)
{
	switch(copy_u8Mode)
	{
		case RISING		: SET_BIT(EXTI -> RTSR ,EXTI_LINE);	break;
		case FALLING	: SET_BIT(EXTI -> FTSR ,EXTI_LINE);	break;
		case ON_CHANGE	: SET_BIT(EXTI -> RTSR ,EXTI_LINE);
						  SET_BIT(EXTI -> FTSR ,EXTI_LINE); 	break;
	
		default: break;
	}                    
}

void MEXTI_voidSetCallBack(void (*ptr)(void))
{

	EXTI_CallBack = ptr;
}

void EXTI0_IRQHandler(void)
{
	EXTI_CallBack();
	SET_BIT(EXTI -> PR , 0);
}
