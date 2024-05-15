#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__
#include "data_types.h"


//! coprocessor access control register 
#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))
	

//!This function is called by the startup assembly code to perform system specific
//!initialization tasks.

void SystemIniT(void);

//!---------------------------------------------------------------------------------.


// BASE FOR RUN MODE CLOCK GAtING CONTROL

#define RCGC_BASE 0x400FE000

// RCGC register with offset  0x608 at PORTA
#define GPIO_RCGC_PORT  *((volatile U32_t *)0X400FE608)

//SPI clock
#define SPI_clock       *((volatile U32_t *)0x400FE61c)

//!------------------------------------------------------------------------------------

// function: Enable clock for PORT is a must   
void clock_Enable_PORT(U8_t port);

/* ---------------------------------------------/
- Input: unsigned char 1 byte
-
- Description: Access clock. 
- 
- return : void.
* ---------------------------------------------*/ 
// port:: RCGC register PINS offset
#define Clock_PortA  0x01
#define Clock_PortB  0x02
#define Clock_PortC  0x04
#define Clock_PortD  0x08
#define Clock_PortE  0x10
#define Clock_PortF  0x20

//!------------------------------------------------------------------------------------


// function: Enable clock for PORT
void clock_Enable_PORT(U8_t port);
/* ---------------------------------------------/
- Input: unsigned char 1 byte
-
- Description: Access clock. 
- 
- return : void.
* ---------------------------------------------*/ 
// port:: RCGC register PINS offset
#define Clock_PortA  0x01
#define Clock_PortB  0x02
#define Clock_PortC  0x04
#define Clock_PortD  0x08
#define Clock_PortE  0x10
#define Clock_PortF  0x20


/*---------------------------------------------- SPI ENABLE OFFSET -----------------------------------------------------------*/
void Clock_Enable_SPI(U8_t SPI_n);
//SPI Number ::as shown down  
/* ---------------------------------------------/
- Input: unsigned char 1 byte
-
- Description: Access clock. 
- 
- return : void.
* ---------------------------------------------*/ 
#define SPI0  0X01
#define SPI1  0X02


#endif //__SYSCTRL_H__
