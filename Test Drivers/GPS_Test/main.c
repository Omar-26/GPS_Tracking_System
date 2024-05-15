#include "tm4c123gh6pm.h"
#include "UART_Interface.h"
#include "GPS_interface.h"
#include "STD_TYPES.h"


#define UART_NO 0
#define BAUD_RATE 9600
#define DATA_BITS 8
#define PARITY 0
#define STOP_BITS 1

extern f32 currentLat, currentLong;
extern u8 GPS_Formatted[12][20];

void UART_Init(void);
void UART_PrintString(u8 *str);

int main(void) {
    UART_Init();
    
    while (1) {
        GPS_Read(); // Read data from GPS module

        // Print the formatted GPS data via UART
        UART_PrintString((u8 *)"Received GPS data:\n");
        UART_PrintString(GPS_Formatted[2]);
				UART_PrintString(", ");
        UART_PrintString(GPS_Formatted[4]);
    }
}

void UART_Init(void) {
    // Initialize UART0 with the specified parameters
    UART_u8Init(UART_NO, BAUD_RATE, DATA_BITS, PARITY, STOP_BITS);
}

void UART_PrintString(u8 *str) {
    while (*str) {
        UART_u8SendByte(UART_NO, *str++);
    }
}