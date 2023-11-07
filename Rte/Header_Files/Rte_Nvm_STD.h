
#include"STD_TYPES.h"
#include"System_Main.h"
#ifndef  RTE_NVM_STD
#define  RTE_NVM_STD

typedef struct 
{
    /* data */
    u8 Hardware_Version;
    u8 Host_Software_Version;
    u8 WIFI_Software_Version;
    u8 Reserved[3];
}Idt_Rec001_FD00;

typedef struct 
{
    /* data */
    u8 Number_Relays_On_Syetem;
    u8 Number_Switches_On_Syetem;
    u8 Number_Sensors_On_Syetem;
    u8 Reserved;
}Idt_Rec002_FD01;

typedef struct 
{
    /* data */
    u8 Relay_status[LENGHT_STATUS_OBJECT_ON_SYSTEM];
}Idt_Rec003_FD02;

typedef struct 
{
    /* data */
    u8 Switch_status[LENGHT_STATUS_OBJECT_ON_SYSTEM];
}Idt_Rec004_FD03;

#endif
