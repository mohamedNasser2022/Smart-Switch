/*
 * Input_Output_Private.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Mohamed Nasser
 */

#include"DIO_Expander_Interface.h"

#ifndef I_O_INTERFACE_HEADER_FILES_INPUT_OUTPUT_PRIVATE_H_
#define I_O_INTERFACE_HEADER_FILES_INPUT_OUTPUT_PRIVATE_H_


#define PORTS_DONT_CARE   0x20


#define INPUT_OUTPUT_PIN_0_DIO_PHYSICAL 			Hardware_PIN2
#define INPUT_OUTPUT_PIN_1_DIO_PHYSICAL 			Hardware_PIN3
#define INPUT_OUTPUT_PIN_2_DIO_PHYSICAL 			Hardware_PIN4
#define INPUT_OUTPUT_PIN_3_DIO_PHYSICAL 			Hardware_PIN5
#define INPUT_OUTPUT_PIN_4_DIO_PHYSICAL 			Hardware_PIN6
#define INPUT_OUTPUT_PIN_5_DIO_PHYSICAL 			Hardware_PIN7
#define INPUT_OUTPUT_PIN_6_DIO_PHYSICAL 			Hardware_PIN8
#define INPUT_OUTPUT_PIN_7_DIO_PHYSICAL 			Hardware_PIN9
#define INPUT_OUTPUT_PIN_8_DIO_PHYSICAL 			Hardware_PIN10
#define INPUT_OUTPUT_PIN_9_DIO_PHYSICAL 			Hardware_PIN11
#define INPUT_OUTPUT_PIN_10_DIO_PHYSICAL 			Hardware_PIN12
#define INPUT_OUTPUT_PIN_11_DIO_PHYSICAL 			Hardware_PIN21
#define INPUT_OUTPUT_PIN_12_DIO_PHYSICAL 			Hardware_PIN22
#define INPUT_OUTPUT_PIN_13_DIO_PHYSICAL 			Hardware_PIN23
#define INPUT_OUTPUT_PIN_14_DIO_PHYSICAL 			Hardware_PIN24
#define INPUT_OUTPUT_PIN_15_DIO_PHYSICAL 			Hardware_PIN25
#define INPUT_OUTPUT_PIN_16_DIO_PHYSICAL 			Hardware_PIN28
#define INPUT_OUTPUT_PIN_17_DIO_PHYSICAL 			Hardware_PIN29
#define INPUT_OUTPUT_PIN_18_DIO_PHYSICAL 			Hardware_PIN30
#define INPUT_OUTPUT_PIN_19_DIO_PHYSICAL 			Hardware_PIN31
#define INPUT_OUTPUT_PIN_20_DIO_PHYSICAL 			Hardware_PIN32
#define INPUT_OUTPUT_PIN_21_DIO_PHYSICAL 			Hardware_PIN33
#define INPUT_OUTPUT_PIN_22_DIO_PHYSICAL 			Hardware_PIN36
#define INPUT_OUTPUT_PIN_23_DIO_PHYSICAL 			Hardware_PIN37

static u8 IO_Hardware_Switching_on_Input_Number(u8 copy_Pin_ID);
static void Splite_into_ports_and_Pins(u8 copy_Port,u8 copy_ID);
static u8 Translate_Pin_ID_Into_Port_and_Number(u8 copy_Pin_ID);
#endif /* I_O_INTERFACE_HEADER_FILES_INPUT_OUTPUT_PRIVATE_H_ */
