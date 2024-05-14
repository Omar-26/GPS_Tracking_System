
/******************************< SYSTEM ***************************/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/******************************< LIB ******************************/
#include "STD_TYPES.h"
/******************************< MCAL *****************************/
#include "GPIO_Interface.h"
#include "Sys_Tick.h"
#include "UART_Interface.h"
#include "SPI_Interface.h" 
/******************************< HAL ******************************/
#include "GPS_interface.h"
#include "TFT_interface.h"
/******************************< APP ******************************/
// #include "APP/APP.h"
#include "iota.h"
/******************************< Global Variables *****************/
extern f64 currentLat, currentLong;
extern u8 GPS[80];
/******************************< main *****************************/
int main(){
	/******************************< init *****************************/
	f64 destintaion = 0 , destLat = 0 , destLong = 0 , oldLat = 0 , oldLong = 0;
	f64 totalDistance = 0 , deltaDistance = 0, RemainingDistance = 0;
	u8 Int_totalDistance=0;
	char string_totalDistance[4];
	// totalDistance = deltaDistance + RemainingDistance
	GPIO_voidInit_port_A();
	GPIO_voidInit_port_F();
	UART_u8Init(UART0,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
	SysTick_Init(); //
	// SPI_Init();
	
	while(1){
	GPS_Read();
	GPS_format();
	deltaDistance = Calc_Distance(oldLat , oldLong ,currentLat,currentLong);
	totalDistance += deltaDistance;
		RemainingDistance = 100 - totalDistance;
		Int_totalDistance = (u8)totalDistance;
		itoa(Int_totalDistance,string_totalDistance,10);
		//TFT_WriteString(string_totalDistance);
		// store in EEPROM
		if (totalDistance >= 100){};
			// Stop Reading
			
		
	
	
	}
	


}