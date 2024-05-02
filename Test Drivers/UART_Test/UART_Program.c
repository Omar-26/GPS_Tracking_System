/**************************************************************/
/********** Name      : TEAM_NO	        	        ***********/
/********** Date      : 24/04/2024              	***********/
/********** File Name : UART_Program.c              ***********/
/********** Version   : 1.0                    		***********/
/**************************************************************/
/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "tm4c123gh6pm.h"
/**< MCAL_UART */
#include "UART_private.h"
#include "UART_interface.h"
#include "UART_config.h"
/******************************************< UART_FUNCTIONS_IMPLEMENTATION ******************************************/
/******************************************< INIT_FUNCTION_IMPLEMENTATION *******************************************/
Std_ReturnType UART_u8Init(u8 copy_u8UARTNo, u32 copy_u32BaudRate, u8 copy_u8WordLength, u8 copy_u8Parity, u8 copy_u8StopBits)
{
    Std_ReturnType Local_u8ErrorStatus = E_OK;
    switch (copy_u8UARTNo)
    {
        f32 Local_f32Divisor = UART_CLK / (16 * copy_u32BaudRate);
        f32 Local_f32Fraction = (Local_f32Divisor - (u32)Local_f32Divisor) * 64 + 0.5;
    case UART0:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTA);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTA))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTA_AFSEL_R, GPIO_PA0_U0RX);
        SET_BIT(GPIO_PORTA_AFSEL_R, GPIO_PA1_U0TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA0_U0RX);
        SET_BIT(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA1_U0TX);
        /**< Set pin Direction */
        CLR_BIT(GPIO_PORTA_DIR_R, GPIO_PA0_U0RX); // RX (Input)
        SET_BIT(GPIO_PORTA_DIR_R, GPIO_PA1_U0TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTA_DEN_R, GPIO_PA0_U0RX);
        SET_BIT(GPIO_PORTA_DEN_R, GPIO_PA1_U0TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART0_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART0_IBRD_R |= (u32)Local_f32Divisor;
        UART0_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART0_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART0_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART0_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART0_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART0_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART0_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART0_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART0_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART0_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART0_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART0_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART0_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART0_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART0_CTL_R, UART_CTL_TXE);
        SET_BIT(UART0_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART0_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART0 ***************************************************/
    case UART1:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTB);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTB))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTB_AFSEL_R, GPIO_PB0_U1RX);
        SET_BIT(GPIO_PORTB_AFSEL_R, GPIO_PB1_U1TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTB_PCTL_R, GPIO_PCTL_PB0_U1RX);
        SET_BIT(GPIO_PORTB_PCTL_R, GPIO_PCTL_PB1_U1TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTB_DIR_R, GPIO_PB0_U1RX); // RX (Input)
        SET_BIT(GPIO_PORTB_DIR_R, GPIO_PB1_U1TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTB_DEN_R, GPIO_PB0_U1RX);
        SET_BIT(GPIO_PORTB_DEN_R, GPIO_PB1_U1TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART1_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART1_IBRD_R |= (u32)Local_f32Divisor;
        UART1_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART1_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART1_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART1_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART1_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART1_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART1_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART1_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART1_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART1_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART1_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART1_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART1_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART1_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART1_CTL_R, UART_CTL_TXE);
        SET_BIT(UART1_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART1_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART1 ***************************************************/
    case UART2:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTD);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTD))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTD_AFSEL_R, GPIO_PD6_U2RX);
        SET_BIT(GPIO_PORTD_AFSEL_R, GPIO_PD7_U2TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTD_PCTL_R, GPIO_PCTL_PD6_U2RX);
        SET_BIT(GPIO_PORTD_PCTL_R, GPIO_PCTL_PD7_U2TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTD_DIR_R, GPIO_PD6_U2RX); // RX (Input)
        SET_BIT(GPIO_PORTD_DIR_R, GPIO_PD7_U2TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTD_DEN_R, GPIO_PD6_U2RX);
        SET_BIT(GPIO_PORTD_DEN_R, GPIO_PD7_U2TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART2_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART2_IBRD_R |= (u32)Local_f32Divisor;
        UART2_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART2_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART2_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART2_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART2_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART2_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART2_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART2_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART2_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART2_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART2_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART2_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART2_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART2_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART2_CTL_R, UART_CTL_TXE);
        SET_BIT(UART2_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART2_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART2 ***************************************************/
    case UART3:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTC);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTC))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTC_AFSEL_R, GPIO_PC6_U3RX);
        SET_BIT(GPIO_PORTC_AFSEL_R, GPIO_PC7_U3TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTC_PCTL_R, GPIO_PCTL_PC6_U3RX);
        SET_BIT(GPIO_PORTC_PCTL_R, GPIO_PCTL_PC7_U3TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTC_DIR_R, GPIO_PC6_U3RX); // RX (Input)
        SET_BIT(GPIO_PORTC_DIR_R, GPIO_PC7_U3TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTC_DEN_R, GPIO_PC6_U3RX);
        SET_BIT(GPIO_PORTC_DEN_R, GPIO_PC7_U3TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART3_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART3_IBRD_R |= (u32)Local_f32Divisor;
        UART3_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART3_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART3_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART3_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART3_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART3_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART3_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART3_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART3_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART3_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART3_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART3_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART3_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART3_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART3_CTL_R, UART_CTL_TXE);
        SET_BIT(UART3_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART3_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART3 ***************************************************/
    case UART4:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTC);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTC))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTC_AFSEL_R, GPIO_PC4_U4RX);
        SET_BIT(GPIO_PORTC_AFSEL_R, GPIO_PC5_U4TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTC_PCTL_R, GPIO_PCTL_PC4_U4RX);
        SET_BIT(GPIO_PORTC_PCTL_R, GPIO_PCTL_PC5_U4TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTC_DIR_R, GPIO_PC4_U4RX); // RX (Input)
        SET_BIT(GPIO_PORTC_DIR_R, GPIO_PC5_U4TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTC_DEN_R, GPIO_PC4_U4RX);
        SET_BIT(GPIO_PORTC_DEN_R, GPIO_PC5_U4TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART4_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART4_IBRD_R |= (u32)Local_f32Divisor;
        UART4_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART4_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART4_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART4_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART4_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART4_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART4_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART4_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART4_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART4_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART4_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART4_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART4_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART4_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART4_CTL_R, UART_CTL_TXE);
        SET_BIT(UART4_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART4_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART4 ***************************************************/
    case UART5:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTE);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTE))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTE_AFSEL_R, GPIO_PE4_U5RX);
        SET_BIT(GPIO_PORTE_AFSEL_R, GPIO_PE5_U5TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTE_PCTL_R, GPIO_PCTL_PE4_U5RX);
        SET_BIT(GPIO_PORTE_PCTL_R, GPIO_PCTL_PE5_U5TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTE_DIR_R, GPIO_PE4_U5RX); // RX (Input)
        SET_BIT(GPIO_PORTE_DIR_R, GPIO_PE5_U5TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTE_DEN_R, GPIO_PE4_U5RX);
        SET_BIT(GPIO_PORTE_DEN_R, GPIO_PE5_U5TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART5_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART5_IBRD_R |= (u32)Local_f32Divisor;
        UART5_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART5_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART5_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART5_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART5_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART5_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART5_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART5_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART5_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART5_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART5_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART5_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART5_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART5_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART5_CTL_R, UART_CTL_TXE);
        SET_BIT(UART6_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART5_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART5 ***************************************************/
    case UART6:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTD);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTD))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTD_AFSEL_R, GPIO_PD4_U6RX);
        SET_BIT(GPIO_PORTD_AFSEL_R, GPIO_PD5_U6TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTD_PCTL_R, GPIO_PCTL_PD4_U6RX);
        SET_BIT(GPIO_PORTD_PCTL_R, GPIO_PCTL_PD5_U6TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTD_DIR_R, GPIO_PD4_U6RX); // RX (Input)
        SET_BIT(GPIO_PORTD_DIR_R, GPIO_PD5_U6TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTD_DEN_R, GPIO_PD4_U6RX);
        SET_BIT(GPIO_PORTD_DEN_R, GPIO_PD5_U6TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART6_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART6_IBRD_R |= (u32)Local_f32Divisor;
        UART6_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART6_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART6_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART6_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART6_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART6_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART6_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART6_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART6_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART6_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART6_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART6_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART6_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART6_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART6_CTL_R, UART_CTL_TXE);
        SET_BIT(UART6_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART6_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART6 ***************************************************/
    case UART7:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTE);
        /**< Wait for UART Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTE))
            ;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTE_AFSEL_R, GPIO_PE0_U7RX);
        SET_BIT(GPIO_PORTE_AFSEL_R, GPIO_PE1_U7TX);
        /**< Set Port Control */
        SET_BIT(GPIO_PORTE_PCTL_R, GPIO_PCTL_PE0_U7RX);
        SET_BIT(GPIO_PORTE_PCTL_R, GPIO_PCTL_PE1_U7TX);
        /**< Set Bin Direction */
        CLR_BIT(GPIO_PORTE_DIR_R, GPIO_PE0_U7RX); // RX (Input)
        SET_BIT(GPIO_PORTE_DIR_R, GPIO_PE1_U7TX); // TX (Output)
        /**< Set Digital Enable */
        SET_BIT(GPIO_PORTE_DEN_R, GPIO_PE0_U7RX);
        SET_BIT(GPIO_PORTE_DEN_R, GPIO_PE1_U7TX);
        /**< Disable MCAL_UART */
        CLR_BIT(UART7_CTL_R, UART_CTL_UARTEN);
        /**< Configure Baud Rate */
        UART7_IBRD_R |= (u32)Local_f32Divisor;
        UART7_FBRD_R |= (u32)Local_f32Fraction;
        /**< Configure Parity Bits */
        if (copy_u8Parity == UART_PARITY_NONE)
        {
            CLR_BIT(UART7_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART7_LCRH_R, UART_LCRH_EPS);
            CLR_BIT(UART7_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_EVEN)
        {
            SET_BIT(UART7_LCRH_R, UART_LCRH_PEN);
            SET_BIT(UART7_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART7_LCRH_R, UART_LCRH_SPS);
        }
        else if (copy_u8Parity == UART_PARITY_ODD)
        {
            SET_BIT(UART7_LCRH_R, UART_LCRH_PEN);
            CLR_BIT(UART7_LCRH_R, UART_LCRH_EPS);
            SET_BIT(UART7_LCRH_R, UART_LCRH_SPS);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART7_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART7_LCRH_R, UART_LCRH_STP2);
        }
        else
            Local_u8ErrorStatus = E_NOT_OK;
        /**< Enable FIFOs */
        SET_BIT(UART7_LCRH_R, UART_LCRH_FEN);
        /**< Configure Word Length */
        UART7_LCRH_R = (copy_u8WordLength - 5) << UART_LCRH_WLEN;
        /**< Enable RXEs and TXEs */
        SET_BIT(UART7_CTL_R, UART_CTL_TXE);
        SET_BIT(UART7_CTL_R, UART_CTL_RXE);
        /**< Enable MCAL_UART */
        SET_BIT(UART7_CTL_R, UART_CTL_UARTEN);
        break;
    /**************************************************< END_OF_UART7 ***************************************************/
    default:
        Local_u8ErrorStatus = E_NOT_OK;
        break;
    }
    return Local_u8ErrorStatus;
}
/****************************************< SEND_BYTE_FUNCTION_IMPLEMENTATION ****************************************/
Std_ReturnType UART_u8SendByte(u8 copy_u8UARTNo, u8 copy_u8Data)
{
    Std_ReturnType Local_u8ErrorState = E_OK;
    switch (copy_u8UARTNo)
    {
    case UART0:
        if (!GET_BIT(UART0_FR_R, UART_FR_TXFF))
            UART0_DR_R = copy_u8Data;
        break;
    case UART1:
        if (!GET_BIT(UART1_FR_R, UART_FR_TXFF))
            UART1_DR_R = copy_u8Data;
        break;
    case UART2:
        if (!GET_BIT(UART2_FR_R, UART_FR_TXFF))
            UART2_DR_R = copy_u8Data;
        break;
    case UART6:
        if (!GET_BIT(UART6_FR_R, UART_FR_TXFF))
            UART6_DR_R = copy_u8Data;
        break;
    case UART7:
        if (!GET_BIT(UART7_FR_R, UART_FR_TXFF))
            UART7_DR_R = copy_u8Data;
        break;

    default:
        Local_u8ErrorState = E_NOT_OK;
        break;
    }
    return Local_u8ErrorState;
}
/***************************************< Receive_BYTE_FUNCTION_IMPLEMENTATION **************************************/
Std_ReturnType UART_u8ReceiveByte(u8 copy_u8UARTNo, u8 *copy_pu8ReceivedData)
{
    // We May Use Busy Waiting but If Condition is more time friendly
    Std_ReturnType Local_u8ErrorStatus = E_OK;
    switch (copy_u8UARTNo)
    {
    case UART0:
        if (!GET_BIT(UART0_RSR_R, UART_RSR_OE) && !GET_BIT(UART0_RSR_R, UART_RSR_BE) && !GET_BIT(UART0_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART0_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART0_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;

    case UART1:
        if (!GET_BIT(UART1_RSR_R, UART_RSR_OE) && !GET_BIT(UART1_RSR_R, UART_RSR_BE) && !GET_BIT(UART1_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART1_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART1_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    case UART2:
        if (!GET_BIT(UART2_RSR_R, UART_RSR_OE) && !GET_BIT(UART2_RSR_R, UART_RSR_BE) && !GET_BIT(UART2_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART2_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART2_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    case UART3:
        if (!GET_BIT(UART3_RSR_R, UART_RSR_OE) && !GET_BIT(UART3_RSR_R, UART_RSR_BE) && !GET_BIT(UART3_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART3_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART3_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    case UART4:
        if (!GET_BIT(UART4_RSR_R, UART_RSR_OE) && !GET_BIT(UART4_RSR_R, UART_RSR_BE) && !GET_BIT(UART4_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART4_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART4_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    case UART5:
        if (!GET_BIT(UART5_RSR_R, UART_RSR_OE) && !GET_BIT(UART5_RSR_R, UART_RSR_BE) && !GET_BIT(UART5_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART5_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART5_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    case UART6:
        if (!GET_BIT(UART6_RSR_R, UART_RSR_OE) && !GET_BIT(UART6_RSR_R, UART_RSR_BE) && !GET_BIT(UART6_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART6_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART6_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    case UART7:
        if (!GET_BIT(UART7_RSR_R, UART_RSR_OE) && !GET_BIT(UART7_RSR_R, UART_RSR_BE) && !GET_BIT(UART7_RSR_R, UART_RSR_FE))
        {
            if (!GET_BIT(UART7_FR_R, UART_FR_RXFE))
                *copy_pu8ReceivedData = UART7_DR_R;
        }
        else
        {
            Local_u8ErrorStatus = E_NOT_OK;
        }
        break;
    default:
        Local_u8ErrorStatus = E_NOT_OK;
    }
    return Local_u8ErrorStatus;
}
/****************************************< SEND_STRING_FUNCTION_IMPLEMENTATION **************************************/
Std_ReturnType UART_u8SendString(u8 copy_u8UARTNo, u8 *copy_pu8String)
{
    Std_ReturnType Local_u8ErrorStatus = E_OK;
    switch (copy_u8UARTNo)
    {
    case UART0:
        while (!GET_BIT(UART0_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART1:
        while (!GET_BIT(UART1_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART2:
        while (!GET_BIT(UART2_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART3:
        while (!GET_BIT(UART3_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART4:
        while (!GET_BIT(UART4_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART5:
        while (!GET_BIT(UART5_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART6:
        while (!GET_BIT(UART6_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    case UART7:
        while (!GET_BIT(UART7_FR_R, UART_FR_TXFF) && *copy_pu8String != '\0')
        {
            UART_u8SendByte(copy_u8UARTNo, *copy_pu8String);
            copy_pu8String++;
        }
        break;
    default:
        Local_u8ErrorStatus = E_NOT_OK;
    }
    return Local_u8ErrorStatus;
}
/**************************************< Receive_STRING_FUNCTION_IMPLEMENTATION *************************************/
Std_ReturnType UART_u8ReceiveString(u8 copy_u8UARTNo, u8 *copy_pu8StringBuffer)
{
    // you can use null terminator
    Std_ReturnType Local_u8ErrorStatus = E_OK;
    switch (copy_u8UARTNo)
    {
    case UART0:
        while (!GET_BIT(UART0_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART0, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART1:
        while (!GET_BIT(UART1_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART1, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART2:
        while (!GET_BIT(UART2_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART2, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART3:
        while (!GET_BIT(UART3_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART3, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART4:
        while (!GET_BIT(UART4_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART4, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART5:
        while (!GET_BIT(UART5_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART5, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART6:
        while (!GET_BIT(UART6_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART6, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    case UART7:
        while (!GET_BIT(UART7_FR_R, UART_FR_RXFE))
        {
            UART_u8ReceiveByte(UART7, copy_pu8StringBuffer);
            copy_pu8StringBuffer++;
        }
        break;
    default:
        Local_u8ErrorStatus = E_NOT_OK;
    }
    return Local_u8ErrorStatus;
}
