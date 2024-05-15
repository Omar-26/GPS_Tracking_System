#include "HW_gpio.h"
#include "GPIO_SPI.h"
#include "SysCtrl.h"

void GPIO_Spi0(void){
//test mode
  //Clock enable portA.
	clock_Enable_PORT(Clock_PortA);
	//Open lock
	GPIO_PORTA_lock=0x4c4f434b;
	GPIO_PORTA_CR|=0x0000003C;
	//Select alternating Function for PORTA pins as SPI
	GPIO_PORTA_AFSEL|=0x3C;
	// Access port functions from control table
	GPIO_PORTA_PCTRL|=0x00222200;
	//Enable digital function for PORTA pins
	GPIO_PORTA_DEN|=(1<<PA5)|(1<<PA4)|(1<<PA3)|(1<<PA2);
	//Turn off Analog function
	GPIO_PORTA_AMSEL=0x00;	
	//Enable the direction of PORTA pins as master ss pin .      
	GPIO_PORTA_DIR|=(1<<PA3);
	
}//!End of GPIO SPI Function.

void GPIO_SPI_SS_LOW(void){
	GPIO_PORTA_DATA&=~(1<<3); // In binary: 1 to 1000
}//!End of SS GPIO SPI Function.

void GPIO_SPI_SS_IDL(void){
	GPIO_PORTA_DATA|=(1<<3); // In binary: 1 to 1000
}//!End of SS GPIO SPI Function.
