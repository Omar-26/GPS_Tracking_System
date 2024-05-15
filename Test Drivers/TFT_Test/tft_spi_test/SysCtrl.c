#include "SysCtrl.h"

/* Grant coprocessor access*/

void SystemIniT(void){
/* This is required since TM4C123G has a floating point coprocessor */
SCB_CPAC |= 0x00F00000;
	
}

//GPIO CLOCK
void clock_Enable_PORT(U8_t port){
	// make a delay to manipulate instruction well.
	U32_t delay=0;
	//Access clock register.
	GPIO_RCGC_PORT|=port;
	delay=GPIO_RCGC_PORT;
		
}//End of clock function

//SPI clock
void Clock_Enable_SPI(U8_t SPI_n){
	// make a delay to manipulate instruction well.
	U32_t delay=0;
	//Access clock register.	
	SPI_clock|=SPI_n;
	delay=SPI_clock;

}//End of clock function
