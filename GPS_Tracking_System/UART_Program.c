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
/*****<tft *******************/
#include "mcal/nvic/nvic.h"
#include "mcal/SysCtr/SysCtr.h"
#include "mcal/dio/dio_types.h"
#include "mcal/PortDriver/port.h"
#include "mcal/dio/dio.h"
#include "mcal/mcu_hw.h"
#include "Service/Delay_ms/Delay_ms.h"
#include "mcal/ssi/ssi.h"
#include "TFT/ST7735.h"
#include "Sys_Tick.h"
/*****<tft *******************/
/******************************************< UART_FUNCTIONS_IMPLEMENTATION ******************************************/
/******************************************< INIT_FUNCTION_IMPLEMENTATION *******************************************/
void UART_u8Init(u8 copy_u8UARTNo, u32 copy_u32BaudRate, u8 copy_u8WordLength, u8 copy_u8Parity, u8 copy_u8StopBits)
{
    switch (copy_u8UARTNo)
    {
        f32 Local_f32Divisor = UART_CLK / (16 * copy_u32BaudRate);
        f32 Local_f32Fraction = (Local_f32Divisor - (u32)Local_f32Divisor) * 64 + 0.5;
    case UART0:
        /**< Enable MCAL_UART Clock */
        SET_BIT(SYSCTL_RCGCUART_R, copy_u8UARTNo);
        /**< Wait for UART Clock Stabilization */
        while ((SYSCTL_PRGPIO_R & 0x01) == 0)
            ;
        /**< Enable MCAL_GPIO Clock */
        SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTA);
        /**< Wait for GPIO Clock Stabilization */
        while (!GET_BIT(SYSCTL_PRGPIO_R, UART_PORTA))
            ;
        /**< Unlock GPIO Port */
        GPIO_PORTA_LOCK_R |= GPIO_LOCK_KEY;
        /**< Commit Changes */
        GPIO_PORTA_CR_R |= 0xFF;
        GPIO_PORTA_AMSEL_R &= 0x00;
        /**< Set Alternate Function */
        SET_BIT(GPIO_PORTA_AFSEL_R, GPIO_PA0_U0RX);
        SET_BIT(GPIO_PORTA_AFSEL_R, GPIO_PA1_U0TX);
        /**< Set Port Control */
        // SET_BIT(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA0_U0RX);
        // SET_BIT(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA1_U0TX);
        GPIO_PORTA_PCTL_R |= (GPIO_PORTA_PCTL_R & ~0XFF) + (0X11);
        /**< Set pin Direction */
        // CLR_BIT(GPIO_PORTA_DIR_R, GPIO_PA0_U0RX); // RX (Input)
        // SET_BIT(GPIO_PORTA_DIR_R, GPIO_PA1_U0TX); // TX (Output)
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
        /**< Configure Stop Bits */
        if (copy_u8StopBits == UART_STOP_BIT_1)
        {
            CLR_BIT(UART0_LCRH_R, UART_LCRH_STP2);
        }
        else if (copy_u8StopBits == UART_STOP_BIT_2)
        {
            SET_BIT(UART0_LCRH_R, UART_LCRH_STP2);
				}
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
            /**< Commit Changes*/
            GPIO_PORTA_CR_R |= 0xFF;
            GPIO_PORTA_AMSEL_R &= 0x00;
            /**< Set Alternate Function */
            SET_BIT(GPIO_PORTB_AFSEL_R, GPIO_PB0_U1RX);
            SET_BIT(GPIO_PORTB_AFSEL_R, GPIO_PB1_U1TX);
            /**< Set Port Control */
            SET_BIT(GPIO_PORTB_PCTL_R, GPIO_PCTL_PB0_U1RX);
            SET_BIT(GPIO_PORTB_PCTL_R, GPIO_PCTL_PB1_U1TX);
            /**< Set Bin Direction */
            CLR_BIT(GPIO_PORTB_DIR_R, GPIO_PB0_U1RX); // RX (Input)
            SET_BIT(GPIO_PORTB_DIR_R, GPIO_PB1_U1TX); // TX (Output
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
    }
	}
    /****************************************< SEND_BYTE_FUNCTION_IMPLEMENTATION ****************************************/
    void UART_u8SendByte(u8 copy_u8UARTNo, u8 copy_u8Data)
    {
        switch (copy_u8UARTNo)
        {
        case UART0:
					while((UART0_FR_R & 0x20)!=0);
					UART0_DR_R = copy_u8Data;
            break;
        case UART1:
            while ((UART1_FR_R & 0x20) != 0)
            ;
            UART1_DR_R = copy_u8Data;
            break;
        }
    }
    /***************************************< Receive_BYTE_FUNCTION_IMPLEMENTATION **************************************/
    char UART_u8ReceiveByte(u8 copy_u8UARTNo)
    {
        u8 local_u8ReceivedData;
        switch (copy_u8UARTNo)
        {
        case UART0:
            while((UART0_FR_R&0X10) != 0)
							;
            local_u8ReceivedData = UART0_DR_R;
            break;
        case UART1:
            while((UART1_FR_R&0x10) != 0)
								;
            local_u8ReceivedData = UART1_DR_R;
            break;
        }
        return (char) local_u8ReceivedData;
    }
    /****************************************< SEND_STRING_FUNCTION_IMPLEMENTATION **************************************/
    void UART_u8SendString(u8 copy_u8UARTNo, char * copy_pu8String)
    {
        switch (copy_u8UARTNo)
        {
            while(*copy_pu8String){
						UART_u8SendByte(copy_u8UARTNo, * copy_pu8String);
            copy_pu8String++;
          }
            break;
        case UART1:
            while(*copy_pu8String){
						UART_u8SendByte(copy_u8UARTNo, * copy_pu8String);
            copy_pu8String++;
          }
        }
    }
    /**************************************< Receive_STRING_FUNCTION_IMPLEMENTATION *************************************/
    void UART_u8ReceiveString(u8 copy_u8UARTNo, u8 * string, uint32_t length)
    {
        u8 local_u8receivedByte;
        uint32_t i;
        for (i = 0; i < length; i++)
        {
            local_u8receivedByte = UART_u8ReceiveByte(copy_u8UARTNo);
            if (local_u8receivedByte != 0x2A)
						{ 
							string[i] = local_u8receivedByte;
						}
            else if (local_u8receivedByte == 0x2A || i == length)
            {
                break;
            }
        }
    }