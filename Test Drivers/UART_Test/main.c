/**
 * main.c
 */
/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/**< MCAL */
#include "UART_Private.h"
#include "UART_Interface.h"
#include "UART_Config.h"

int main(void)
{
	u8 ch = 'A';
	UART_u8Init(UART0, UART_BDR_9600, UART_DATA_8, UART_PARITY_NONE, UART_STOP_BIT_1);
	UART_u8SendByte(UART0,ch);
  return 0;
}