/*
 * I2C_Manger.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Mohamed Nasser
 */

#include"Queue_Interface.h"

#ifndef I2C_MANGER_H
#define I2C_MANGER_H

u8 Comuncation_Manger_Send_Data_to_I2C_Buffer(Comuncation_Manger_Interface* Pointer_To_Data);
void I2C_Manger_Init(void);


#endif
