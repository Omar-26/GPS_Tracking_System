/******************************< SYSTEM ***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/******************************< LIB ******************************/
#include "STD_TYPES.h"
/******************************< MCAL *****************************/
#include "GPIO_Interface.h"
#include "Sys_Tick.h"
#include "UART_Interface.h"
#include "EEPROM_Interface.h"
/******************************< HAL ******************************/
#include "GPS_interface.h"
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
#include "iota.h"
#include "FTOS.h"
/******************************< Global Variables *****************/
extern char GPS[80], GPS_Tokens[12][20];
f32 currentLatitude, currentLongitude;
f32 latitude_array[50] , longitude_array[50];
f32 Read_latitude[50] = {0} , Read_longitude[50] = {0};
char Total_Coordinates [2100] = "";
uint32_t k;
uint32_t j=0;
u8 button1;
u8 button2;
char* text;
f32 walkedDistance , deltaDistance;
u32 Int_walkedDistance;
char String_walkedDistance[4];
/******************************< main *****************************/
int main(){
	/******************************< init *****************************/
  UART_u8Init(UART0,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
  UART_u8Init(UART1,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
	GPIO_voidInit_port_A();
	GPIO_voidInit_port_F();
	SysTick_Init();
  SysCtr_init();
  PORT_init();
  SSI_INIT();
  ST7735_Init();
	
		// Intailize the array of Coordinates
		for ( j = 0 ; j < 2100; j++){
		Total_Coordinates [j] = '\0';
		}
		while(1)
		{
		if( UART_u8ReceiveByte(UART0) == 'U'){
			write_Array_EEPROM (Read_latitude, Read_longitude, k);
			ftos (Read_latitude , Read_longitude, Total_Coordinates , k);		
			UART_u8SendString(UART0, Total_Coordinates);
		}
	 else
		break;
}

while(1){
	 button1 = GPIO_u8Set_Switch(SW_1);
	 button2 = GPIO_u8Set_Switch(SW_2);
	 walkedDistance = 0;
	 
if (walkedDistance < 101 & k < 50){
			GPS_Read();
			SysTick_Delay10ms(500);
		  GPIO_voidRGB_LED( GREEN_LED, LED_OFF);
			GPIO_voidRGB_LED( BLUE_LED, LED_OFF);
			GPIO_voidRGB_LED( RED_LED, LED_OFF);
	
	if (strcmp(GPS_Tokens[1],"A") == 0){ 	//Validation
				currentLatitude = todegree(atof(GPS_Tokens[2]));
				latitude_array[j] = currentLatitude ;
				currentLongitude =todegree(atof(GPS_Tokens[4]));
				longitude_array[j] = currentLongitude ; 
	
		if(j!= 0)	//Skip the first point
				{
				deltaDistance = calcDistance(latitude_array[k-1] , longitude_array[k-1] ,latitude_array[k] ,longitude_array[k]);
				GPIO_voidRGB_LED( GREEN_LED, LED_OFF);
				GPIO_voidRGB_LED( BLUE_LED, LED_OFF);
				GPIO_voidRGB_LED( RED_LED, LED_OFF);
				walkedDistance += deltaDistance;
				// View Distance on TFT
				Int_walkedDistance = (u32)walkedDistance;
				itoa(Int_walkedDistance, String_walkedDistance, 10);
				ST7735_drawString("Distance",16, 4,0X0000,0XFFFF,2);
				ST7735_drawString(String_walkedDistance,28, 60,0X07E0,0XFFFF,7); 
				}
				
			sprintf(text,"Latitude = %f \n",currentLatitude);
			UART_u8SendString(UART0, text);
			sprintf(text,"Longitude = %f \n",currentLongitude);
			UART_u8SendString(UART0, text);
			sprintf(text,"Latitude1 = %f \n",latitude_array[k-1]);
			UART_u8SendString(UART0, text);
			sprintf(text,"Longitude1 = %f \n",longitude_array[k-1]);
			UART_u8SendString(UART0, text);
			sprintf(text,"Latitude2 = %f \n",latitude_array[k]);
			UART_u8SendString(UART0, text);
			sprintf(text,"Longitude2 = %f \n",longitude_array[k]);
			UART_u8SendString(UART0, text);
			sprintf(text,"Total Distance = %f \n",walkedDistance);
			UART_u8SendString(UART0, text);
			k++ ; 
		}
}
}
 			if ( walkedDistance >= 100) //if sw1 is pressed then turn on red light and stop taking inputs from gps
			GPIO_voidRGB_LED(GREEN_LED , LED_ON);
		  else if (button1 != 0x10)
			GPIO_voidRGB_LED(RED_LED , LED_ON);
		  if ((button2 != 0x01 )){   //if sw2 is pressed save data to eeprom and change color
			write_Array_EEPROM (latitude_array, longitude_array, k);
			GPIO_voidRGB_LED(BLUE_LED , LED_ON);
			}
}
