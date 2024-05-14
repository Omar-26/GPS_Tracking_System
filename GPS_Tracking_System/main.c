
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
#include "EEPROM_Interface.h"
/******************************< HAL ******************************/
#include "GPS_interface.h"
#include "TFT_interface.h"
/******************************< APP ******************************/
// #include "APP/APP.h"
#include "iota.h"
/******************************< Global Variables *****************/
extern f64 currentLatitude, currentLongitude;
extern u8 GPS[80];
/******************************< main *****************************/
int main(){
	/******************************< init *****************************/
	f64 destintaion = 0 , destinationLatitude = 0 , destinationLongitude = 0 , previousLatitude = 0 , previousLongitude = 0;
	f64 walkedDistance = 0 , deltaDistance = 0, remainingDistance = 0;
	u8 Int_walkedDistance = 0;
	char string_totalDistance[4];
	// totalDistance = deltaDistance + remainingDistance
	GPIO_voidInit_port_A();
	GPIO_voidInit_port_F();
	UART_u8Init(UART0,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
	SysTick_Init();
	// SPI_Init();
	
	while(1){
	GPS_Read();
	GPS_format();
	deltaDistance = Calc_Distance(previousLatitude , previousLongitude ,currentLatitude ,currentLongitude);
	walkedDistance += deltaDistance;
		remainingDistance = 100 - walkedDistance;
		Int_walkedDistance = (u8)walkedDistance;
		itoa(Int_walkedDistance,string_totalDistance,10);
		//TFT_WriteString(string_totalDistance);
		// store in EEPROM
		if (walkedDistance >= 100){};
			// Stop Reading	
			// LED_On
			u8 local_pu8ReceivedCommand;
			UART_u8ReceiveByte( UART7 , &local_pu8ReceivedCommand);
			if( local_pu8ReceivedCommand == 'U')
		{
			// Send Data to the PC
		}
			
	}
}