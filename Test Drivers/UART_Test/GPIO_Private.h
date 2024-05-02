#include "tm4c123gh6pm.h"

// led color
#define RED_LED 0
#define BLUE_LED 1
#define GREEN_LED 2
// switches
#define SW_1 0
#define SW_2 1
// led state
#define LED_OFF 0
#define LED_ON 1
// Gpio ports
#define portA (0)
#define portB (1)
#define portC (2)
#define portD (3)
#define portE (4)
#define portF (5)
// GPIO pins
#define pin0 (1 << 0)
#define pin1 (1 << 1)
#define pin2 (1 << 2)
#define pin3 (1 << 3)
#define pin4 (1 << 4)
#define pin5 (1 << 5)
#define pin6 (1 << 6)
#define pin7 (1 << 7)
// Gpio pin data
#define Pin_High (1)
#define Pin_Low (0)
// Gpio pin direction
#define pin_out (1)
#define pin_in (0)
// keys
#define key_lock 0x4c4f434B
#define Enable_portF_pins 0x1F
#define Enable_portA_Uart_Spi 0x3F
#define PUL_R_PortF 0x11
#define PUL_R_PortA 0x33
#define Out_Leds 0x0E
#define Out_TXs 0x22
#define No_Alternate_func 0x00000000
#define Uart_Spi_PortA 0x3F