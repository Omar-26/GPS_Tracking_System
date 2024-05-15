#ifndef __GPIO_SPI_H__
#define __GPIO_SPI_H__
#include "data_types.h"


//Master function. for SPI0 mapped to PORTA and configure pins for master and slave mode.
void GPIO_Spi0(void);

//Pull system down to choose slave
void GPIO_SPI_SS_LOW(void);

//let system high to choose IDL
void GPIO_SPI_SS_IDL(void);



#endif //__GPIO_SPI_H__
