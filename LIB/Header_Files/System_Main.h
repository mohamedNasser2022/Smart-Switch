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
#define NUMBER_OF_RELAYS_INTERNAL_ON_CHIP               4
#define LENGHT_STATUS_OBJECT_ON_SYSTEM                  8






/*System mode*/
enum
{
    UNDEFINED,
    INITIOLAZTION_MODE,
    WIFI_INITIOLAZTION_MODE,
    WIFI_INITIOLAZTION_MODE_BUSY,
    WIFI_MODE,
    WIFI_MODE_Stand_by,
    NORMAL_MODE,
    GO_APPLICATION_MODE,
    WIFI_OK,
    WIFI_DONE,
    WIFI_ERROR,
    STAND_BY_MODE,
    Sys_OnGoing,
    Sys_Done,
    Sys_Faild,
    SYSTEM_ENABLE_SEQUENCE   ,   
    OBJECT_FINISHED_SEQUENCE ,   
    WIFI_FINISHED_SEQUENCE   ,   
    WIFI_ERROR_SEQUENCE   ,      
    OBJECT_DATA_LOADED_DONE,
    OBJECT_DATA_LOADED_ERROR,
         
}Sys_Modes;



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
