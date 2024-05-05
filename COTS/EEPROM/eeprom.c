#include "eeprom.h"
#include "tm4c123gh6pm.h"

//intialization of eeprom clk

Std_ReturnType init_EEPROM(void)
{
    SYSCTL_RCGCEEPROM_R |= Activate_eeprom;

    //_delay_cycles(3);

    while((SYSCTL_RCGCEEPROM_R & Activate_eeprom)==0);

    while((EEPROM_EEDONE_R & 0x01) == 1);

    if ((EEPROM_EESUPP_R & 0XC) == 1)
    {
     return E_NOT_OK;
    }
    else 
    {
     return E_OK;
    }

}

void write_EEPROM(uint16_t address, uint32_t data)
{

    EEPROM_EEBLOCK_R = address >> 4;

    EEPROM_EEOFFSET_R = address & 0xF;

    EEPROM_EERDWR_R = data;

    while (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);

}

uint32_t read_EEPROM(uint16_t address)
{

EEPROM_EEBLOCK_R = address >> 4;

EEPROM_EEOFFSET_R = address & 0xF;

return EEPROM_EERDWR_R;

}