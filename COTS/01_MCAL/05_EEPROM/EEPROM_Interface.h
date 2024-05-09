/**************************************************************/
/********** Name      : Shorouk Amr Aly	        	***********/
/********** Date      : 20/04/2024              	***********/
/********** File Name : EEPROM_Interface.h          ***********/
/********** Version   : 1.0                    		***********/
/**************************************************************/
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/**< Include standard integer types for fixed-size definitions */
#include "STD_TYPES.h"

Std_ReturnType init_EEPROM(void);

void write_EEPROM(uint16_t address, uint32_t data);

uint32_t read_EEPROM(uint16_t address);

#define Activate_eeprom (0x01)

#endif /* EEPROM_INTERFACE_H_ */