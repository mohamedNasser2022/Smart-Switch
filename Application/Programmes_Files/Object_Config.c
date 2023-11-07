#include"Pin_mapping.h"
#include"object_Controller.h"
#include"System_Main.h"

#include"Object_Config.h"


u8 Object_Relays_Switches_Initialization(void)
{
	u8 Local_Return = SUCCESS;

	if(OBJECT_CONFIG_NUMBERS == NUMBER_OF_RELAYS_INTERNAL_ON_CHIP)
	{

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_1,OBJECT_WIFI_ID_1,OBJECT_RELAY_OUTPUT_1,OBJECT_SWITCH_INPUT_1,OBJECT_TURN_OFF_TIME_1))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_2,OBJECT_WIFI_ID_2,OBJECT_RELAY_OUTPUT_2,OBJECT_SWITCH_INPUT_2,OBJECT_TURN_OFF_TIME_2))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_3,OBJECT_WIFI_ID_3,OBJECT_RELAY_OUTPUT_3,OBJECT_SWITCH_INPUT_3,OBJECT_TURN_OFF_TIME_3))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_4,OBJECT_WIFI_ID_4,OBJECT_RELAY_OUTPUT_4,OBJECT_SWITCH_INPUT_4,OBJECT_TURN_OFF_TIME_4))
		{
			
		}
		else{
			Local_Return = ERROR;
		}
	}
	else{
		Local_Return = ERROR;
	}


	return Local_Return;
}