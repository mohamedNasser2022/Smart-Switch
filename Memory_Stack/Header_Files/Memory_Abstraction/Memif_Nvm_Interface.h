#ifndef	MEMIF_NVM_INTERFACE_H
#define	MEMIF_NVM_INTERFACE_H

/*---------------------Rec000-----------------*/
static void Memif_Write_Rec000_EEPROM(void);
void Memif_Read_Rec000_EEPROM(void);
void CallBack_Rec000(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec000-----------------*/

/*---------------------Rec001-----------------*/
static void Memif_Write_Rec001_EEPROM(void);
static void Memif_Read_Rec001_EEPROM(void);
static void CallBack_Rec001(void* Modes,void* Mode_Status,void* Pointer);
/*---------------------Rec001-----------------*/


#endif