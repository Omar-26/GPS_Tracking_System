
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
//#include "SPI_Interface.h" 
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
// #include "APP/APP.h"
#include "iota.h"
/******************************< Global Variables *****************/
extern f32 currentLatitude, currentLongitude;
extern u8  flag , GPS_Counter , GPS[80];
/******************************< main *****************************/
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <string.h>

#define CB 0x2A								//HexaDecimal for (*)

void UART0_Init(void){
	SYSCTL_RCGCUART_R |=0x0001; //Activate UART0 
	SYSCTL_RCGCGPIO_R |=0x0001; //Activate PortA
	while(GET_BIT(SYSCTL_PRGPIO_R,0)==0 );	
	UART0_CTL_R &= ~(0x0001);	//Disable UART0
	UART0_IBRD_R = 0x68; //IBRD=int(160000000/(16*9600)) = 104;
	UART0_FBRD_R = 0xB;	//FBRD = int(0.166*64 +0.5) = 11
	UART0_LCRH_R = 0x0070;	// 8-bit word length, enable FIFO 001110000
	UART0_CTL_R = 0x0301; //enable RXE , TXE and UART 001100000001
	GPIO_PORTA_AFSEL_R |= 0x03; //enable alt function PA0, PA1
	GPIO_PORTA_PCTL_R = ( GPIO_PORTA_PCTL_R & 0xFFFFFF00 ) + 0x00000011; //configure UART for PA0,PA1
	GPIO_PORTA_DEN_R |= 0x03;	//enable digital I/O on PA0, PA1
	GPIO_PORTA_AMSEL_R &= ~0x03;	//disable analog function on PA0, PA1
}

char UART0_getChar() {
	while((UART0_FR_R & 0x10) !=0);
return (char) UART0_DR_R;
}

void UART0_OutChar(char data){
		while((UART0_FR_R & 0x20)!=0);
	UART0_DR_R=data;
}

void UART0_OutString(char *pt){
	while(*pt){
		UART0_OutChar(*pt);
		pt++;
	}
}
void GetCommand_UART0(char *Command,int len ){ 		
		char character;
		int i;
		for(i=0 ; i< len; i++){
			character = UART0_getChar();
			if(character!=CB)
			{
				Command[i]=character;
				UART0_OutChar(character);
			}
			else if(character==CB ||i==len)
				break;		
		}
}



void UART1_Init (void){// Should be called only once
	SET_BIT(SYSCTL_RCGCUART_R , 1); // Activate UART1
	SET_BIT(SYSCTL_RCGCGPIO_R,1); // Activate Port B 
	while(GET_BIT(SYSCTL_PRGPIO_R , 1)==0); //Check on the clock
	CLR_BIT(UART1_CTL_R , 0); // Disable UART1
	UART1_IBRD_R = 0x68; // IBRD=int (160000000/ (16*9600) ) = 104
	UART1_FBRD_R = 0xB; // FBRD = int (0.166 * 69 + 0.5)=11
	UART1_LCRH_R = 0x0070; // 8-bit word length, enable FIFO 001110000
	UART1_CTL_R = 0x0301; // Enable RE, IXE and UART 001100000001
	GPIO_PORTB_AFSEL_R |= 0x03; // Enable alt function PBO , PB1  
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) +0x00000011; // Configure UART on PB0 , PB1
	GPIO_PORTB_DEN_R |= 0x03; // Enable digital I/0 on PBO , PB1 
	GPIO_PORTB_AMSEL_R &= ~0x03; // Disable analog function on PBO , PB1
}

char UART1_getChar() {
	while((UART1_FR_R & 0x10) !=0);
return (char) UART1_DR_R;
}

void UART1_OutChar(char data){
		while((UART1_FR_R & 0x20)!=0);
	UART1_DR_R=data;
}

void UART1_OutString(char *pt){
	while(*pt){
		UART1_OutChar(*pt);
		pt++;
	}
}

void GetCommand_UART1(char *Command,int len ){ 
		
		char character_UART1;
		int p;		
		for(p=0 ; p< len; p++){
			character_UART1 = UART1_getChar();
			if(character_UART1!=CB)
			{
				Command[p]=character_UART1;
			}
			else if(character_UART1==CB)
				break;		
		}
}


void GetCommand_UART1_Modified(char *Command,int len ){ 
		
		char character_UART1;
		int p;		
		for(p=0 ; p< len; p++){
			character_UART1 = UART1_getChar();
			if(character_UART1!=CB)
			{
				Command[p]=character_UART1;
			}
			else if(character_UART1==CB)
				break;		
		}
}
int main(){
//	f64 destintaion = 0 , destinationLatitude = 0 , destinationLongitude = 0 ;
//	f32 previousLatitude = 0 , previousLongitude = 0;
//	f64 walkedDistance = 0 , deltaDistance = 0, remainingDistance = 0;
//	f32 latitude[50] , longitude[50]; 
//	u8 Int_walkedDistance = 0;
//	char String_walkedDistance[4];
		char arr[60] = {0};
	/******************************< init *****************************/
//	GPIO_voidInit_port_A();
//	GPIO_voidInit_port_F();
//	SysTick_Init();
//	SysCtr_init();
//  PORT_init();
//  SSI_INIT();
//  ST7735_Init();
	// UART_u8Init(UART0,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
	 UART0_Init();
	 UART1_Init();
		////////////////////////////////////////////////////
	// UART_u8Init(UART1,UART_BDR_9600,UART_DATA_8,UART_PARITY_NONE,UART_STOP_BIT_1);
		/////////////////////////////////////////////////////
	// ST7735_fillRect(0,0,132, 160,0Xffff);


	while(1){
			GetCommand_UART1(arr , 60);
			UART0_OutString(arr);
//		UART_u8ReceiveString(UART1 ,arr , 60);
//		UART_u8SendString(UART0, arr);
//		if (walkedDistance < 101){
//			// GPS_Read();
//			ST7735_drawString("after read",4, 4,0X0000,0Xffff,1);
//			deltaDistance = calcDistance(previousLatitude , previousLongitude ,currentLatitude ,currentLongitude);
//			walkedDistance += deltaDistance;
//			currentLatitude = previousLatitude;
//		  currentLongitude = previousLongitude;
//			Int_walkedDistance = (u32)walkedDistance;
//		  itoa(Int_walkedDistance, String_walkedDistance, 10);
//			ST7735_fillRect(0,0,132, 132,0X0000);
//		}
//		else{
//		  GPIO_voidRGB_LED(BLUE_LED , LED_ON);
//			write_Array_EEPROM(latitude,longitude ,GPS_Counter);
//			GPIO_voidRGB_LED(GREEN_LED , LED_ON);
//		}
		
		// Format Using FTOS

		/*while(1){ 
			if(UART_u8ReceiveByte(UART0) == 'U'){
				// Send Data to the PC
				
			}
		}*/
	}
}
