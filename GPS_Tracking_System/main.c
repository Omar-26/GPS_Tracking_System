
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
extern u8  flag , GPS_Counter , GPS[80];
/******************************< main *****************************/
int main(){
	/******************************< init *****************************/
	f64 destintaion = 0 , destinationLatitude = 0 , destinationLongitude = 0 , previousLatitude = 0 , previousLongitude = 0;
	f64 walkedDistance = 0 , deltaDistance = 0, remainingDistance = 0;
	f32 latitude[50] , longitude[50]; 
	u8 Int_walkedDistance = 0;
	char string_totalDistance[4];
	GPIO_voidInit_port_A();
	GPIO_voidInit_port_F();
	UART_u8Init(UART0,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
	SysTick_Init();
	// SPI_Init();
	
	while(1){
		Int_walkedDistance = (u8)walkedDistance;
		itoa(Int_walkedDistance,string_totalDistance,10);
		//TFT_WriteString(string_totalDistance);
		deltaDistance = Calc_Distance(previousLatitude , previousLongitude ,currentLatitude ,currentLongitude);
		walkedDistance += deltaDistance;
		currentLatitude = previousLatitude;
		currentLongitude = previousLongitude;
		remainingDistance = 100 - walkedDistance;
		if (walkedDistance < 100){
			GPS_Read();
			GPS_format();
		}
		else{
		  GPIO_voidRGB_LED( BLUE_LED , LED_OFF);
			write_Array_EEPROM(latitude,longitude ,GPS_Counter);
		}
		while(1){ 
			if(UART_u8RecieveByte(UART0) == 'U'){
				// Send Data to the PC
			}
		}		
	}
}