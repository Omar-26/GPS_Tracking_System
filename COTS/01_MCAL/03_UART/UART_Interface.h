/**************************************************************/
/********** Name      : TEAM_NO	        	        ***********/
/********** Date      : 24/04/2024              	***********/
/********** File Name : UART_Interface.h            ***********/
/********** Version   : 1.0                    		***********/
/**************************************************************/
#ifndef _MCAL_UART_INTERFACE_H_
#define _MCAL_UART_INTERFACE_H_

/************************************* < UART ***************************************************/
#define UART0 0
#define UART1 1
#define UART2 2
#define UART3 3
#define UART4 4
#define UART5 5
#define UART6 6
#define UART7 7
/*************************************< UART PARITY ********************************************/
#define UART_PARITY_NONE 0
#define UART_PARITY_ODD 1
#define UART_PARITY_EVEN 2
/*************************************< UART DATA **********************************************/
#define UART_DATA_5 5
#define UART_DATA_6 6
#define UART_DATA_7 7
#define UART_DATA_8 8
/*************************************< UART STOP_BIT ******************************************/
#define UART_STOP_BIT_1 1
#define UART_STOP_BIT_2 2
/*************************************< UART BAUD_RATE *****************************************/
#define UART_BDR_2400 2400
#define UART_BDR_4800 4800
#define UART_BDR_9600 9600
#define UART_BDR_14400 14400
#define UART_BDR_19200 19200
#define UART_BDR_28800 28800
#define UART_BDR_38400 38400
#define UART_BDR_57600 57600
#define UART_BDR_76800 76800
#define UART_BDR_115200 115200
#define UART_BDR_230400 230400
#define UART_BDR_250000 250000

/************************************< FUNCTIONS ***********************************************/

/** @brief 	This function UART_voidInit initializes a UART (Universal Asynchronous Rx/Tx)
 *			module for a specified UART number, with the specified baud rate, data bits,
 *			parity, and stop bits. The function first calculates the divisor value for the
 *			specified baud rate and sets the clock for the UART and GPIO pins.
 *			then configures the UART pins for the specified UART number and sets the data
 *			format, including the data bits, parity, and stop bits. Finally, it enables the UART.
 *
 *			The function takes five arguments:
 *
 *			copy_u8UartNo: specifies the UART number to be initialized (e.g., UART0, UART1, etc.).
 *			copy_u32BaudRate: specifies the baud rate for the UART.
 *			copy_u8DataBits: specifies the number of data bits (5-8 bits).
 *			copy_u8Parity: specifies the parity type (None, Even, or Odd).
 *			copy_u8StopBits: specifies the number of stop bits (1 or 2 bits).
 *
 * @param 	copy_u8UARTNo: YOUR_OPTIONS:
 *										1) UART0
 *										2) UART1
 *										3) UART2
 *										4) UART3
 *										5) UART4
 *										6) UART5
 *										7) UART6
 *										8) UART7
 *	@param	copy_u32BaudRate: YOUR_OPTIONS:
 *										1) UART_BDR_2400
 *										2) UART_BDR_4800
 *										3) UART_BDR_9600
 *										4) UART_BDR_14400
 *										5) UART_BDR_19200
 *										6) UART_BDR_28800
 *										7) UART_BDR_38400
 *										8) UART_BDR_57600
 *										9) UART_BDR_76800
 *										10)UART_BDR_115200
 *										11)UART_BDR_230400
 *										12)UART_BDR_250000
 *	@param	copy_u8DataBits: YOUR_OPTIONS:
 *										1) UART_DATA_5
 *										2) UART_DATA_6
 *										3) UART_DATA_7
 *										4) UART_DATA_8
 *	@param	copy_u8Parity: YOUR_OPTIONS:
 *										1) UART_PARITY_NONE
 *										2) UART_PARITY_ODD
 *										3) UART_PARITY_EVEN
 *	@param	copy_u8StopBits: YOUR_OPTIONS:
 *										1) UART_STOP_BIT_1
 *										2) UART_STOP_BIT_2
 * @return 	void
 *
 */
u8 UART_u8Init(u8 copy_u8UARTNo, u32 copy_u32BaudRate, u8 copy_u8DataBits, u8 copy_u8Parity, u8 copy_u8StopBits);

u8 UART_u8SendByte(u8 copy_u8UARTNo, u8 copy_u8Data);

u8 UART_u8ReceiveByte(u8 copy_u8UARTNo, u8 *copy_pu8ReceivedData);

u8 UART_u8SendString(u8 copy_u8UARTNo, u8 *copy_pu8SentString);

u8 UART_u8ReceiveString(u8 copy_u8UARTNo, u8 *copy_pu8StringBuffer);

#endif /**< _MCAL_UART_INTERFACE_H_ */
