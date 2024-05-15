
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
//#include "UART_Interface.h"
//#include "SPI_Interface.h" 
#include "EEPROM_Interface.h"
/******************************< HAL ******************************/
#include "GPS_interface.h"
#include "TFT_interface.h"
#include "mcal/nvic/nvic.h"
#include "mcal/SysCtr/SysCtr.h"
#include "mcal/dio/dio_types.h"
#include "mcal/PortDriver/port.h"
#include "mcal/dio/dio.h"
#include "mcal/mcu_hw.h"
#include "Service/Delay_ms/Delay_ms.h"
#include "mcal/ssi/ssi.h"
#include "TFT/ST7735.h"
#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 1
/******************************< APP ******************************/
// #include "APP/APP.h"
#include "iota.h"
/******************************< Global Variables *****************/
extern f64 currentLatitude, currentLongitude;
extern u8  flag , GPS_Counter , GPS[80];
/******************************< main *****************************/
int main(){
	/******************************< init *****************************/
	f64 destintaion = 0 , destinationLatitude = 0 , destinationLongitude = 0 ;
	f64 previousLatitude = 0 , previousLongitude = 0;
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
		//TFT_WriteString(string_totalDistance);
		deltaDistance = Calc_Distance(previousLatitude , previousLongitude ,currentLatitude ,currentLongitude);
		walkedDistance += deltaDistance;
		currentLatitude = previousLatitude;
		currentLongitude = previousLongitude;
		// remainingDistance = 100 - walkedDistance;
		if (walkedDistance < 101){
			// Time Delay with Systick
			GPS_Read();
			GPS_format();
		}
		else{
		  GPIO_voidRGB_LED(BLUE_LED , LED_ON);
			write_Array_EEPROM(latitude,longitude ,GPS_Counter);
			GPIO_voidRGB_LED(GREEN_LED , LED_ON);
		}
		while(1){ 
			if(UART_u8RecieveByte(UART0) == 'U'){
				// Send Data to the PC
			}
		}
	}
}
