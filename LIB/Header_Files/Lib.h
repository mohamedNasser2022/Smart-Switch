/*
 * Lib.h
 *
 *  Created on: Apr 29, 2023
 *      Author: Mohamed Nasser
 */

#include "Pin_mapping.h"

#ifndef LIB_H_
#define LIB_H_

#define DO_ACCESSED       1
#define NOT_ACCESSED      2

/*------------------------------------------------------------------------------------------------------------------------*/
#define READ_MESSAGE      1
#define WRITE_MESSAGE     2
#define MESSAGE_VALID     3
#define MESSAGE_NOT_VALID 0
#define NULL      0
/*------------------------------------------------------------------------------------------------------------------------*/

/*Software Compunent IDs*/
#define SW_PROTOCOL_TRANSLATOR_ID  0x10
#define SW_SYSTEM_MODE_ID		   0x20
#define SW_OBJECT_ID 			   0x30
#define SW_WIFI_MANGER_ID 		   0x11
/*------------------------------------------------------------------------------------------------------------------------*/

#endif /* LIB_H_ */
