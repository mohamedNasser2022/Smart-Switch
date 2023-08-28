/*
 * I2C_Config.h
 *
 *  Created on: Oct 22, 2022
 *      Author: Mohamed Nasser
 */
#include"Queue_Interface.h"


#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_


/*----------------------------------------------------*/



#define I2C_ADDRESS_WRITE  0
#define I2C_ADDRESS_READ   1
#define I2C_DATA_READY     1
#define I2C_DATA_NOTREADY  0

#define I2C_BUSY    20
#define I2C_POLLING 10

#define I2C_MODE   I2C_POLLING


#define I2C1_CLK  				 I2C_ENABLE    /* Options   I2C1_CLK = I2C_ENABLE,I2C_DISABLE */
#define I2C1_INTERRUPT_AT_EVENT  I2C_DISABLE
#define I2C1_INTERRUPT_AT_BUFFER I2C_DISABLE
#define I2C1_INTERRUPT_AT_ERROR  I2C_DISABLE
#define I2C1_ACK 				 I2C_ENABLE
#define I2C1_GENERALL_CALL 		 I2C_DISABLE
#define I2C1_BUS_MODE 	    	 I2C_I2CBUS
#define I2C1_SPEED 				 I2C_2_MHZ


#define I2C2_CLK  I2C_DISABLE  /* Options   I2C1_CLK = I2C_ENABLE,I2C_DISABLE */


#define ADDRESS_MODE    SINGL_ADDRESSES
#define ADDRESS_LENGTH  BIT7_ADDRESS

#define DUAL_ADDRESSES  1
#define SINGL_ADDRESSES 0

#define BIT7_ADDRESS  	0
#define BIT10_ADDRESS   1

#define I2C_ENABLE  1
#define I2C_DISABLE 0

#define I2C_I2CBUS	  0
#define I2C_SMBUS     1

#define I2C_SUCCESS 1
#define I2C_FAILD   0

#define I2C_SUCCESS_FILLED_BUFFER   3
#define I2C_NODATA_TO_BUFFER        4
#define I2C_FAILD_FILLED_BUFFER     5
#define I2C_DATA_REGESITER_IS_BUSY 	6

#endif /* I2C_CONFIG_H_ */
