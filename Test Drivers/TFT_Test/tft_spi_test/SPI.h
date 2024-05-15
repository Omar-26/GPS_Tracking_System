#ifndef __SPI_H__
#define __SPI_H__
#include "data_types.h"

// SPI Setup Function.
void SPI_Master_init(void);
/********************************************************************************
-prescaler:CPSDVSR
-register that has bitrate value is :SCR
#default::CPSDVSR=0x2, SCR must be 0x2.
#Assuming the system clock is 16 MHz, the bit rate calculation would be:
SSIClk = SysClk  / (CPSDVSR * (1 + SCR))
3x10^6 = 16x10^6 / (CPSDVSR * (1 + SCR))
In this case, if CPSDVSR=0x2, SCR must be 0x2.
********************************************************************************/

// Transmition Function. 
void SPI_SendData(U16_t data);

// Reciever Function.
U16_t SPI_GetData(void);

#endif //__SPI_H__
