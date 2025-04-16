/*
 * I2C_Private.h
 *
 *  Created on: Oct 22, 2022
 *      Author: Mohamed Nasser
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"I2C_Configuration.h"
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

typedef struct {

	volatile u32 I2C_CR1;
	volatile u32 I2C_CR2;
	volatile u32 I2C_OAR1;
	volatile u32 I2C_OAR2;
	volatile u32 I2C_DR;
	volatile u32 I2C_SR1;
	volatile u32 I2C_SR2;
	volatile u32 I2C_CCR;
	volatile u32 I2C_TRISE;

}I2C_t;

typedef struct {

	u8 Address;
	u8 Length_of_Data_To_Be_Read;
	Array_Of_Queue_3  Data_Queue_Send;
	Array_Of_Queue_3  Data_Queue_Recived;
	Nested_Queue_3    Queue_Of_Requests;
	Function_Pointer_t  Function_Pointer;


}I2C_Struct_Buffer_Transmit;

typedef struct{
	u8 Bus_Mode;
	u8 Bus_Status;
	I2C_t* I2C_Peripheral_Registers;
	I2C_Configuration_Struct* Configrations;
	I2C_Struct_Buffer_Transmit* Buffer;

}I2C_Data_Controller;

#define I2C_1  ((volatile I2C_t*) 0x40005400)
#define I2C_2  ((volatile I2C_t*) 0x40005800)



#define BUFFER_IS_FULL  6
#define BUFFER_IS_EMPTY 7

/*---------------------Bus Status & I2C System status--------------------*/

#define BUS_IDEAL 			                  0
#define BUS_BUSY 						      1
#define BUS_REQUEST_GENERATE_START_CONDITIONS 2
#define BUS_GENERATE_START_CONDITIONS         3
#define BUS_REQUEST_ADDRESS_PHASE             4
#define BUS_ADDRESS_PHASE                     5
#define BUS_ENDED_DATA_PHASE     			  6
#define BUS_REQUEST_GENERATE_STOP_PHASE		  7
#define BUS_GENERATE_STOP_PHASE				  8
#define BUS_SENDING_ENDED					  9
#define BUS_READING 						  10
#define BUS_READING_ENDED					  11



#define I2C_GENERATED                         12
#define I2C_WAITING							  13
#define I2C_FAILD							  0
#define BUS_DATA_PHASE						  15

/*----------------------------------------------------*/

static void I2C_Comunication_Polling(void);
static void Set_Bus_Mode_Sequence(I2C_Data_Controller *pointer_to_Buffer);
static void Generate_Control_Singals(I2C_Data_Controller *pointer_to_Buffer);
static void I2C_Reset(I2C_Configuration_Struct *ptr_I2C);
static u8 I2C_staticInit(I2C_Configuration_Struct *ptr_I2C);
static u8 I2C_Set_Pointer_Right_Perpherial(I2C_t **I2C_Register,u8 copy_perpherail_ID);
static u8 I2C_Reading_DR(I2C_Data_Controller* pointer_to_Buffer);
static u8 I2C_Sending_DR(I2C_Data_Controller* pointer_to_Buffer);
static u8 I2C_Addressing(I2C_Data_Controller* pointer_to_Buffer);
static u8 I2C_Send_Start_BIT(I2C_Data_Controller* pointer_to_Buffer);
static u8 I2C_Send_Stop_BIT(I2C_Data_Controller* pointer_to_Buffer);
static u8 I2C_Status_1(I2C_t *I2C_Register,u8 copy_ID);
static u8 I2C_Status_2(I2C_t *I2C_Register,u8 copy_ID);
static void I2C_Initialization_Peripheral_data_Handler(void);
static void I2C_Make_Request_On_Progress(void);
static void I2C_TimeOut(void);

/*---------------------------------*/

#endif /* I2C_PRIVATE_H_ */
