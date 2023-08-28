/*
 * Main.h
 *
 *  Created on: Sep 10, 2022
 *      Author: Mohamed Nasser
 */

#ifndef SYSTEM_MAIN_H_
#define SYSTEM_MAIN_H_

#define GO_APPLICATION  0x90
#define BOOT_HALT  0x00

/*System Parameters*/
#define NUMBER_RELAYS_ON_THIS_ECU    4
#define NUMBER_SWITCHS_ON_THIS_ECU   4
#define PROTOCOL_DATA_LENGTH         6


/*System mode*/
#define  UNDEFINED		         	     0
#define  INITIOLAZTION_MODE			     1
#define  WIFI_INITIOLAZTION_MODE	     2
#define  WIFI_INITIOLAZTION_MODE_BUSY	 3
#define  WIFI_MODE  		   		     14
#define  NORMAL_MODE 			 	     5
#define  GO_APPLICATION_MODE			 6
#define  WIFI_OK		            	 7
#define  WIFI_DONE		            	 8
#define  WIFI_ERROR		            	 9
#define  STAND_BY_MODE			         10

#define ECU_NUMBER   MY_ID
#define MY_ID        HOST_ECU_ID
/* ECU IDs*/
#define HOST_ECU_ID 0x01
#define WIFI_ECU_ID 0x02
/*Com Define*/
#define I2C_No_1  0
#define UART_No_1 1
/*--------------------------------------*/
#endif /* SYSTEM_MAIN_H_ */
