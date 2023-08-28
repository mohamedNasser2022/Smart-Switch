/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  EXTI_INTERFACE_H
#define  EXTI_INTERFACE_H

/*Line and mode need Check*/
void MEXTI_voidInit();
void MEXTI_voidEnableEXTI(u8 copy_u8Line);
void MEXTI_voidDisableEXTI(u8 copy_u8Line);
void MEXTI_voidSwTrigger(u8 copy_u8Line);
void MEXTI_voidSetCallBack(void (*ptr)(void));


#endif
