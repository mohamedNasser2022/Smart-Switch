/*
 * Writing_Message_Stratage.h
 *
 *  Created on: May 1, 2023
 *      Author: Mohamed Nasser
 */


#include"Lib.h"
#include"STD_TYPES.h"

#ifndef WRITING_MESSAGE_STRATAGE_H_
#define WRITING_MESSAGE_STRATAGE_H_

/***************************************************************** Messages ************************************/
#define MAX_SIZE_OF_MESSAGE_DATA   10
#define MESSAGED_ID_TYPE   u8
#define Message_Status_TYPE   u8


/*-------------------------*/

#define MESSAGE_0x01      				        0x01
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x01      3
struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x01];
	u8 Message_Status;

}Message_0x01;


/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x02      0x02
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x02      1
struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x02];
	u8 Message_Status;

}Message_0x02;


/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x03      0x03
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x03      3
 struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x03];
	u8 Message_Status;

}Message_0x03;

/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x04      0x04
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x04      6
 struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x04];
	u8 Message_Status;

}Message_0x04;

/*-------------------------*/

/*-------------------------*/



/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x11	  0x11
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x11      6
 struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x11];
	u8 Message_Status;

}Message_0x11;

/*-------------------------*/

#define MESSAGE_0x13	  0x13
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x13      8
 
/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x14	                        0x14
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x14      2
 struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x14];
	u8 Message_Status;

}Message_0x14;

/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x20	                        0x20
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x20      20
 struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x20];
	u8 Message_Status;

}Message_0x20;

/*-------------------------*/

/*-------------------------*/

#define MESSAGE_0x21	                        0x21
#define MESSAGE_ARRAY_ELEMENTS_NUMBER_0x21      40
 struct
{
	MESSAGED_ID_TYPE Message_ID;
	u8 Data[MESSAGE_ARRAY_ELEMENTS_NUMBER_0x21];
	u8 Message_Status;

}Message_0x21;

/*-------------------------*/

/*--------------------------------------------------------------Message Ended-------------------------------------------------------------------------------*/



#endif /* WRITING_MESSAGE_STRATAGE_H_ */
