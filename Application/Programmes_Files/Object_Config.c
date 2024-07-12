#include"Pin_mapping.h"
#include"object_Controller.h"
#include"System_Main.h"

#include"Object_Config.h"


u8 Object_Relays_Switches_Initialization(void)
{
	u8 Local_Return = SUCCESS;

	if(OBJECT_CONFIG_NUMBERS == NUMBER_OF_RELAYS_INTERNAL_ON_CHIP)
	{

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_50,OBJECT_WIFI_ID_50,OBJECT_RELAY_OUTPUT_50,OBJECT_SWITCH_INPUT_50,OBJECT_TURN_OFF_TIME_50))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_51,OBJECT_WIFI_ID_51,OBJECT_RELAY_OUTPUT_51,OBJECT_SWITCH_INPUT_51,OBJECT_TURN_OFF_TIME_51))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_52,OBJECT_WIFI_ID_52,OBJECT_RELAY_OUTPUT_52,OBJECT_SWITCH_INPUT_52,OBJECT_TURN_OFF_TIME_52))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_53,OBJECT_WIFI_ID_53,OBJECT_RELAY_OUTPUT_53,OBJECT_SWITCH_INPUT_53,OBJECT_TURN_OFF_TIME_53))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_54,OBJECT_WIFI_ID_54,OBJECT_RELAY_OUTPUT_54,OBJECT_SWITCH_INPUT_54,OBJECT_TURN_OFF_TIME_54))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_55,OBJECT_WIFI_ID_55,OBJECT_RELAY_OUTPUT_55,OBJECT_SWITCH_INPUT_55,OBJECT_TURN_OFF_TIME_55))
		{
			
		}
		else{
			Local_Return = ERROR;
		}

		if(SUCCESS == Relay_Initilaizations(OBJECT_NO_ON_SYSTEM_56,OBJECT_WIFI_ID_56,OBJECT_RELAY_OUTPUT_56,OBJECT_SWITCH_INPUT_56,OBJECT_TURN_OFF_TIME_56))
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
