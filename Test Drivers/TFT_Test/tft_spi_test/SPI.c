#include "SPI.h"
#include "SysCtrl.h"
#include "HW_SPI.h"
#include "GPIO_SPI.h"

// SPI Setup Function.
void SPI_Master_init(void){
	//Enable clock for SPI module.
	Clock_Enable_SPI(SPI0);
	//GPIO_SPI configuration.
	GPIO_Spi0();
	//! Access SPI Registers  
	//disable SPI.	
	SSICR1&=~(1<<1);
	//SPI AS master.
	SSICR1&=~(1<<2);
	//choose System clock source and divisor as SPI clock.
	SSICC=0x00; 	
	//configure the bitRate according to HW component this is default.
	SSICPSR=0x02;
	SSICR0|=0x00000700;
	//phase-data captured at first edge transition "rising edge".
	SSICR0&=~(1<<7);
	//SSI Serial Clock Polarity-low in steady state.
	SSICR0&=~(1<<6);
	//Freescale SPI Frame Format
	SSICR0&=~((1<<4)|(1<<5));
	//SSI Data Size Select 8 bit
	SSICR0|=0x00000007;
	//Enable SPI.
	SSICR1|=(1<<1);
		
}//!End of MASTER Setup Function.

//************************************************************************************************


// Transmition Function. 
void SPI_SendData(U16_t data){	
	//select slave.
	GPIO_SPI_SS_LOW();
	//SSI Transmit * check FIFO Not Full / can use SSI Busy Bit to check if data sent after writing to SSIDR.
	while((SSISR&(1<<4)));
	//send 16 bit data or less to FIFO
	SSIDR=data;	
	while((SSISR&(1<<4)));
	//left the slave.
	GPIO_SPI_SS_IDL();
	
}//!End of SPI_SendData Function.



//*************************************************************************************************************

// Reciever Function.
U16_t SPI_GetData(void){

	//check FIFO if it has data .Read it.
	while(!(SSISR&(1<<2)));	
	//Read and return data when FIFO is not empty.
	return SSIDR;
	
}//!End of SPI_GetData Function.


//*************************************************************************************************************
