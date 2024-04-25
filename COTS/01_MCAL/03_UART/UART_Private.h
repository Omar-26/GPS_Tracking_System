/**************************************************************/
/********** Name      : TEAM_NO	        	        ***********/
/********** Date      : 24/04/2024              	***********/
/********** File Name : UART_Private.h                 ***********/
/********** Version   : 1.0                    		***********/
/**************************************************************/
#ifndef _MCAL_UART_PRIVATE_H_
#define _MCAL_UART_PRIVATE_H_

/**< UART0 */
#define GPIO_PA0_U0RX 0
#define GPIO_PA1_U0TX 1
/**< UART1 */
#define GPIO_PB0_U1RX 0
#define GPIO_PB1_U1TX 1
/**< UART2 */
#define GPIO_PD6_U2RX 6
#define GPIO_PD7_U2TX 7
/**< UART3 */
#define GPIO_PC6_U3RX 6
#define GPIO_PC7_U3TX 7
/**< UART4 */
#define GPIO_PC4_U4RX 4
#define GPIO_PC5_U4TX 5
/**< UART5 */
#define GPIO_PE4_U5RX 4
#define GPIO_PE5_U5TX 5
/**< UART6 */
#define GPIO_PD4_U6RX 4
#define GPIO_PD5_U6TX 5
/**< UART7 */
#define GPIO_PE0_U7RX 0
#define GPIO_PE1_U7TX 1

#define UART_PORTA 0
#define UART_PORTB 1
#define UART_PORTC 2
#define UART_PORTD 3
#define UART_PORTE 4

#define UART_CTL_UARTEN   0

#define UART_LCRH_PEN     1
#define UART_LCRH_EPS     2
#define UART_LCRH_STP2    3
#define UART_LCRH_FEN     4
#define UART_LCRH_WLEN    5
#define UART_LCRH_SPS     7

#define UART_CLK 16000000
#endif /**< _MCAL_UART_PRIVATE_H_ */