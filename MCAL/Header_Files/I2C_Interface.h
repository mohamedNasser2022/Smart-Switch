/*
 * I2C_Interface.h
 *
 *  Created on: Oct 22, 2022
 *      Author: Mohamed Nasser
 */

#include"Data_Structure.h"
#include"I2C_Configuration.h"
#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#define NOTHING_TO_READ 0

enum {
	I2C_Send_Request = 0x01,
	I2C_Send_notify_Request,
	I2C_Send_Address_check_Request,  // 0x12
	I2C_Read_Request ,



	I2C_Valid_Address = 0x10,
	I2C_Error_Address ,
	I2C_Request_Sent,
	I2C_Request_Done,
	I2C_Request_Faild,

	I2C_Busy = 0xF0,

}I2C_Requests_Enum;

/*
#define I2C_MODE_NORMAL       			40
#define I2C_ADDRESSES_CHECKING       	41
#define I2C_MODE_NORMAL_NOTIFICATION    42
#define I2C_READ_MODE                   43
#define VALID_ADDRESS                   100
#define NOT_VALID_ADDRESS				101
#define I2C_ERROR						200
#define I2C_OK						    201
*/
#define Request_Checking_Device_Address_I2C(ADDRESS,FUNCTION)											I2C_Push_Data_To_Buffer(I2C_Send_Address_check_Request,I2C_PERPHEIAL_1,ADDRESS,0,0,FUNCTION)
#define Push_Data_to_I2C_Sending_Buffer_Perpherial_1_With_Notification(ADDRESS,QUEUE_POINTER,FUNCTION)	I2C_Push_Data_To_Buffer(I2C_Send_notify_Request,I2C_PERPHEIAL_1,ADDRESS,QUEUE_POINTER,NOTHING_TO_READ,FUNCTION)
#define Push_Data_to_I2C_Sending_Buffer_Perpherial_1(ADDRESS,QUEUE_POINTER)      				 		I2C_Push_Data_To_Buffer(I2C_Send_Request,I2C_PERPHEIAL_1,ADDRESS,QUEUE_POINTER,NOTHING_TO_READ,0)
#define Reading_From_I2C_Perpherial_1(ADDRESS,QUEUE_POINTER,NUMBER_OF_BYTE_TO_READ,FUNCTION)     		I2C_Push_Data_To_Buffer(I2C_Read_Request,I2C_PERPHEIAL_1,ADDRESS,QUEUE_POINTER,NUMBER_OF_BYTE_TO_READ,FUNCTION)

/*---------------Decleration of Data Handling Functions---------*/
u8 I2C_Push_Data_To_Buffer(u8 copy_Mode,u8 copy_u8I2C_ID,u8 copy_u8Address,void* Pointer_to_Data,u8 copy_Number_of_bytes_to_Be_Read,void (*Pointer_Function)(void*));
/*--------------------------------------------------------------*/
#endif /* I2C_INTERFACE_H_ */
