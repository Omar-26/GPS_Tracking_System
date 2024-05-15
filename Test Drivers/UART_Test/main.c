/**
 * main.c
 */
/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "tm4c123gh6pm.h"
#include "io.h"
/**< MCAL */
#include "UART_Private.h"
#include "UART_Interface.h"
#include "UART_Config.h"

void RGBLED_Init(void){
SYSCTL_RCGCGPIO_R |= PF_mask;
while((SYSCTL_PRGPIO_R & 0x20)==0 )
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R = 0x0E;
GPIO_PORTF_AMSEL_R &= ~PF123_mask;
GPIO_PORTF_AFSEL_R &= ~PF123_mask;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTF_DIR_R |= PF123_mask;
GPIO_PORTF_DEN_R |= PF123_mask;
GPIO_PORTF_DATA_R &= ~PF123_mask;
}

void LEDS_output(unsigned char data){
GPIO_PORTF_DATA_R &=~ 0x0E;
GPIO_PORTF_DATA_R |= data;
}
int main(void)
{
	RGBLED_Init();
	UART_u8Init(UART0, UART_BDR_9600, UART_DATA_8, UART_PARITY_NONE, UART_STOP_BIT_1);
	// u8 ch[] = "ABC";
	// UART_u8SendString(UART0,ch);
	/*u8 local_u8ReceivedCommand = UART_u8RecieveByte(UART0);
	if(local_u8ReceivedCommand == 'U')
		{ 
		LEDS_output(GREEN);
	   //GPIO_PORTF_DATA_R |= 0x0E;
		}*/
	u8 ch[10];
	// UART_u8ReceiveString (UART0, &ch[0]);
	UART_voidReceiveString(UART0, &ch[10]);
	
  UART_u8SendByte(UART0, ch[0]);
	UART_u8SendByte(UART0, ch[1]);
	 
	u8 flag = 0;
	uint32_t i ;
	for (i = 0 ; i < 3 ; i++)
	{
	}
	if( ch[1] == 'B' ) // A
		{ 
		LEDS_output(GREEN);
	   GPIO_PORTF_DATA_R |= 0x0E;
		}
  return 0;
}