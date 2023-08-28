/*
 * DIO_Expander_Private.h
 *
 *  Created on: Jun 4, 2023
 *      Author: Mohamed Nasser
 */

#include "STD_TYPES.h"

#ifndef I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_PRIVATE_H_
#define I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_PRIVATE_H_

#define DIO_EXPANDER_DONT_CARE       0x0A

#define DIO_EXPANDERTOTAL_NUMBER_OF_PINS  16

#define DIO_EXPANDER_PIN0    0
#define DIO_EXPANDER_PIN1    1
#define DIO_EXPANDER_PIN2    2
#define DIO_EXPANDER_PIN3    3
#define DIO_EXPANDER_PIN4    4
#define DIO_EXPANDER_PIN5    5
#define DIO_EXPANDER_PIN6    6
#define DIO_EXPANDER_PIN7    7
#define DIO_EXPANDER_PIN8    8
#define DIO_EXPANDER_PIN9    9
#define DIO_EXPANDER_PIN10   10
#define DIO_EXPANDER_PIN11   11
#define DIO_EXPANDER_PIN12   12
#define DIO_EXPANDER_PIN13   13
#define DIO_EXPANDER_PIN14   14
#define DIO_EXPANDER_PIN15   15


typedef enum {

	Address_RegInputDisableB = 0x00,
	Address_RegInputDisableA,
	Address_RegLongSlewB,
	Address_RegLongSlewA,
	Address_RegLowDriveB,
	Address_RegLowDriveA,
	Address_RegPullUpB,
	Address_RegPullUpA,
	Address_RegPullDownB,
	Address_RegPullDownA,
	Address_RegOpenDrainB,
	Address_RegOpenDrainA,
	Address_RegPolarityB,
	Address_RegPolarityA,
	Address_RegDirB,
	Address_RegDirA,
	Address_RegDataB,
	Address_RegDataA,
	Address_RegInterruptMaskB,
	Address_RegInterruptMaskA,
	Address_RegSenseHighB,
	Address_RegSenseLowB,
	Address_RegSenseHighA,
	Address_RegSenseLowA,
	Address_RegInterruptSourceB,
	Address_RegInterruptSourceA,
	Address_RegEventStatusB,
	Address_RegEventStatusA,
	Address_RegLevelShifter1,
	Address_RegLevelShifter2,
	Address_RegClock,
	Address_RegMisc,
	Address_RegLEDDriverEnableB,
	Address_RegLEDDriverEnableA,
	Address_RegDebounceConfig,
	Address_RegDebounceEnableB,
	Address_RegDebounceEnableA,
	Address_RegKeyConfig1,
	Address_RegKeyConfig2,
	Address_RegKeyData1,
	Address_RegKeyData2,


}Enum_DIO_Registers_Addresses_Sector_1;  // Device and IO Banks

#define END_OF_ADDRESSES  Address_RegKeyData2

/*
typedef enum {


}Enum_DIO_Registers_Addresses_Sector_3; //LED Driver (PWM, blinking, breathing)

typedef enum {


}Enum_DIO_Registers_Addresses_Sector_4; //Miscellaneous

typedef enum {


}Enum_DIO_Registers_Addresses_Sector_5; //Software Reset

typedef enum {


}Enum_DIO_Registers_Addresses_Sector_6; //Test (not to be written)
*/
struct {

	u8 RegInputDisableB;
	u8 RegInputDisableA;
	u8 RegLongSlewB;
	u8 RegLongSlewA;
	u8 RegLowDriveB;
	u8 RegLowDriveA;
	u8 RegPullUpB;
	u8 RegPullUpA;
	u8 RegPullDownB;
	u8 RegPullDownA;
	u8 RegOpenDrainB;
	u8 RegOpenDrainA;
	u8 RegPolarityB;
	u8 RegPolarityA;
	u8 RegDirB;
	u8 RegDirA;
	u8 RegDataB;
	u8 RegDataA;
	u8 RegInterruptMaskB;
	u8 RegInterruptMaskA;
	u8 RegSenseHighB;
	u8 RegSenseLowB;
	u8 RegSenseHighA;
	u8 RegSenseLowA;
	u8 RegInterruptSourceB;
	u8 RegInterruptSourceA;
	u8 RegEventStatusB;
	u8 RegEventStatusA;
	u8 RegLevelShifter1;
	u8 RegLevelShifter2;
	u8 RegClock;
	u8 RegMisc;
	u8 RegLEDDriverEnableB;
	u8 RegLEDDriverEnableA;
	u8 RegDebounceConfig;
	u8 RegDebounceEnableB;
	u8 RegDebounceEnableA;
	u8 RegKeyConfig1;
	u8 RegKeyConfig2;
	u8 RegKeyData1;
	u8 RegKeyData2;

}DIO_Registers_Data;

#define UPDATES_NEEDED    1
#define NO_UPDATES_NEEDED 0

struct
{
	u8 Reading_On_Going:1;
	u8* Read_Pointer;
}DIO_Expander_Reading_Controller;

typedef struct
{
	u8 Set_Direction_Called:1;
	u8 Set_Pin_Level_Called:1;


}Functions_Flags_t;

union
{
	u8 Flag_Updates;
	Functions_Flags_t Flags_Update_Bit_Level;
}Flags;

/*-----------------------------static Functions---------------------------------------*/
static void Special_Function_To_SET_CLR(u8* Pointer,u8 Pin_No,u8 Boolean);


#endif /* I_O_INTERFACE_HEADER_FILES_DIO_EXPANDER_PRIVATE_H_ */
