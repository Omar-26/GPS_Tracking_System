/**
 * main.c
 */
/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/**< MCAL */
#include "GPIO_Interface.h"
#include "uart_Header.h"
#include "GPIO_Private.h"

int main(void)
{
    //u8 Local_u8Test = 0;
		u8 arr='A';
    UART_u8Init (UART0,UART_BDR_9600, UART_DATA_8, UART_PARITY_NONE, UART_STOP_BIT_1);
		UART_u8SendByte(UART0,arr);
		//init_port_f();
    //while(1)
    //{
				//UART_u8SendString(UART7,arr);
				
				//if(Local_u8Test=='R')
        //{
        //    RGB_LED(RED_LED, LED_ON);
        //}
        //else if (Local_u8Test == 'B')
        //{
        //    RGB_LED(BLUE_LED, LED_ON);
        //}
        //else if (Local_u8Test == 'G')
        //{
       //     RGB_LED(GREEN_LED, LED_ON);
        //else
        //{
         //   RGB_LED(RED_LED, LED_OFF);
					//	RGB_LED(BLUE_LED, LED_OFF);
					//  RGB_LED(GREEN_LED, LED_OFF);
        //}
    //}

	return 0;
}
