#include<stdio.h>
#include<d:\Projects\C_projects\tm4c123gh6pm.h>
#include<GPIO_Interface.h>
#include<STD_TYPES.h>
#include<GPIO_Private.h>

/*
                                                Enable Port F Clock:
SYSCTL_RCGCGPIO_R |= 0x20; sets the bit corresponding to Port F in the System Control General-Purpose Input/Output (GPIO) Run Mode Clock Gating Control Register.
This action enables the clock for Port F.

                                                Wait for Port F to be Ready:
while ((SYSCTL_PRGPIO_R & 0x20) == 0); waits until the Port F Ready Bit is set in the System Control GPIO Peripheral Ready Register. 
This ensures that Port F is ready for configuration.
                                                Unlock Port F:
GPIO_PORTF_LOCK_R = key_lock; unlocks the Port F Lock Register using the specified key value (key_lock).
                                                Configure Port F Pins:
GPIO_PORTF_CR_R |= 0x1F;       sets the Commit Register bits for all Port F pins, allowing them to be modified.
GPIO_PORTF_AMSEL_R &= 0x00;    disables analog mode selection for all Port F pins.
GPIO_PORTF_AFSEL_R &= 0x00;    disables alternate function selection for all Port F pins.
GPIO_PORTF_PCTL_R &= No_Alternate_func;   clears the Port Control Register bits for alternate functions (assuming No_Alternate_func is a defined value).
GPIO_PORTF_DEN_R |= Enable_portF_pins;    enables digital I/O functionality for the specified Port F pins.
GPIO_PORTF_PUR_R |= PUL_R_PortF;          enables pull-up resistors for the specified Port F pins.
GPIO_PORTF_DIR_R |= Out_Leds;             sets the direction of the specified Port F pins as output (assuming Out_Leds is a defined value
*/

void init_port_f(){
    SYSCTL_RCGCGPIO_R |= 0x20 ;
    while ((SYSCTL_PRGPIO_R & 0x20)==0);
    GPIO_PORTF_LOCK_R = key_lock ;
    GPIO_PORTF_CR_R |= 0x1F;
    GPIO_PORTF_AMSEL_R &= 0x00;
    GPIO_PORTF_AFSEL_R &= 0x00;
    GPIO_PORTF_PCTL_R &= No_Alternate_func;
    GPIO_PORTF_DEN_R |= Enable_portF_pins;
    GPIO_PORTF_PUR_R |= PUL_R_PortF;
    GPIO_PORTF_DIR_R |= Out_Leds;
}


/*
                                                    Enable Port A Clock:
SYSCTL_RCGCGPIO_R |= 0x01; sets the bit corresponding to Port A in the System Control General-Purpose Input/Output (GPIO) Run Mode Clock Gating Control Register. 
This action enables the clock for Port A.
                                                    Wait for Port A to be Ready:
while ((SYSCTL_PRGPIO_R & 0x01) == 0); waits until the Port A Ready Bit is set in the System Control GPIO Peripheral Ready Register. 
This ensures that Port A is ready for configuration.
                                                    Unlock Port A:
GPIO_PORTA_LOCK_R |= key_lock; unlocks the Port A Lock Register using the specified key value (key_lock).
                                                    Configure Port A Pins:
GPIO_PORTA_CR_R |= 0xFF;      sets the Commit Register bits for all Port A pins, allowing them to be modified.
GPIO_PORTA_AMSEL_R &= 0x00;   disables analog mode selection for all Port A pins.
GPIO_PORTA_AFSEL_R &= Uart_Spi_PortA;    selectively enables alternate function selection for specific Port A pins (assuming Uart_Spi_PortA is a defined value).
GPIO_PORTA_PCTL_R &= 0x00222211;         clears the Port Control Register bits for alternate functions (assuming 0x00222211 is a specific configuration).
GPIO_PORTA_DEN_R |= Enable_portA_Uart_Spi;     enables digital I/O functionality for the specified Port A pins.
GPIO_PORTA_PUR_R |= PUL_R_PortA;         enables pull-up resistors for the specified Port A pins.
GPIO_PORTA_DIR_R |= Out_TXs;             sets the direction of the specified Port A pins as output (assuming Out_TXs is a defined value)
*/
void init_port_A(){
    SYSCTL_RCGCGPIO_R |= 0x01;
    while ((SYSCTL_PRGPIO_R & 0x01)==0);
    GPIO_PORTA_LOCK_R |= key_lock;
    GPIO_PORTA_CR_R |= 0xFF;
    GPIO_PORTA_AMSEL_R &= 0x00;
    GPIO_PORTA_AFSEL_R &= Uart_Spi_PortA;
    GPIO_PORTA_PCTL_R &= 0x00222211;
    GPIO_PORTA_DEN_R |= Enable_portA_Uart_Spi;
    GPIO_PORTA_PUR_R |= PUL_R_PortA;
    GPIO_PORTA_DIR_R |= Out_TXs;
}

/*
                                            Function Description:
The function Get_Switch takes an unsigned 8-bit integer (u8) as an argument (sw).
It returns the state of a switch based on the value of sw.
                                            Switch Cases:
The function uses a switch statement to handle different cases based on the value of sw.
If sw is equal to SW_1, it performs the following:
Reads the data from Port F (GPIO_PORTF_DATA_R).
Applies a bitwise AND operation with 0x10 (binary 00010000).
Right-shifts the result by 4 bits.
Returns the final value.
If sw is equal to SW_2, it performs a similar operation with 0x01 (binary 00000001).
If sw does not match either case, it returns 0.
                                            Usage:
This function appears to be designed to read the state of specific switches (possibly connected to Port F pins) and return their status
*/

u8 Get_Switch(u8 sw){
    switch (sw)
    {
    case SW_1 : return (GPIO_PORTF_DATA_R &= 0x10)>>4;
    break;

    case SW_2 : return (GPIO_PORTF_DATA_R &= 0x01)>>4;
    break;

    default: return 0;
        break;
    }
}

/*
                                        The function Led_controlled takes two parameters:
Switch_state: Indicates whether the LED should be turned on (Pin_High) or off (Pin_Low).
led_color: Specifies which LED color to control (e.g., RED_LED, BLUE_LED, or GREEN_LED).
                                    Inside the switch statement, the function checks the value of led_color:
If led_color is RED_LED, it modifies the GPIO_PORTF_DATA_R register to turn the red LED on or off.
If led_color is BLUE_LED, it does the same for the blue LED.
If led_color is GREEN_LED, it controls the green LED.
                                    The default case handles any other led_color values (if provided).
*/

void Led_controlled(u8 Switch_state,u8 led_color){
    switch (led_color)
    {
    case RED_LED :
        if (Switch_state == Pin_Low)
            GPIO_PORTF_DATA_R |= 0x02;
        else if (Switch_state == Pin_High)
            GPIO_PORTF_DATA_R &=~ 0x02;
            
        break;
    case BLUE_LED :
        if (Switch_state == Pin_Low)
            GPIO_PORTF_DATA_R |= 0x04;
        else if (Switch_state == Pin_High)
            GPIO_PORTF_DATA_R &=~ 0x04;
            
        break;
    case GREEN_LED :
        if (Switch_state == Pin_High)
            GPIO_PORTF_DATA_R |= 0x08;
        else if (Switch_state == Pin_Low)
            GPIO_PORTF_DATA_R &=~ 0x08;
            
        break;
    
    default:
        break;
    }
}


/*
                                            Function Description:
The function RGB_LED controls the state of an RGB LED based on the specified led_color and led_state.
It takes two arguments:
led_color: An unsigned 8-bit integer representing the desired LED color (e.g., RED_LED, BLUE_LED, or GREEN_LED).
led_state: An unsigned 8-bit integer representing the desired LED state (e.g., LED_ON or LED_OFF).
                                            LED Color and State Handling:
The function uses a nested switch statement to handle different LED colors (RED_LED, BLUE_LED, or GREEN_LED).
Within each color case, it further checks the LED state (LED_ON or LED_OFF) and performs the corresponding action:
If led_state is LED_ON, it sets the appropriate bit in the GPIO_PORTF_DATA_R register to turn on the LED.
If led_state is LED_OFF, it clears the appropriate bit in the GPIO_PORTF_DATA_R register to turn off the LED.
If led_state does not match either case, it returns 0.
                                            Usage:
This function can be used to control an RGB LED connected to Port F pins on a Tiva C Series TM4C123GH6PM microcontroller.
The specific LED color and state are determined by the input arguments
*/

void RGB_LED(u8 led_color,u8 led_state){
    switch (led_color)
    {
    case RED_LED :
     switch (led_state)
    {
    case LED_ON : GPIO_PORTF_DATA_R |= 0x02;
        break;
    case LED_OFF :GPIO_PORTF_DATA_R &=~ 0x02;     
    
    default: return 0;
        break;
    }
        break;
    case BLUE_LED : 
     switch (led_state)
    {
    case LED_ON : GPIO_PORTF_DATA_R |= 0x04;
        break;
    case LED_OFF :GPIO_PORTF_DATA_R &=~ 0x04;     
    
    default: return 0;
        break;
    } 
        break;
    case GREEN_LED : switch (led_state)
    {
    case LED_ON : GPIO_PORTF_DATA_R |= 0x08;
        break;
    case LED_OFF :GPIO_PORTF_DATA_R &=~ 0x08;     
    
    default: return 0;
        break;
    }    
        break;
    
    default: return 0;
        break;
    }
}

/*
                                                Function Description:
The function Set_Pin_value is designed to set the value (high or low) of a specific pin on a specified GPIO port.
It takes three arguments:
port: An unsigned 8-bit integer representing the GPIO port (e.g., portA, portB, etc.).
pin: An unsigned 8-bit integer representing the pin number within the specified port.
pin_value: An unsigned 8-bit integer representing the desired value (high or low) for the pin.
                                                Pin Value Setting:
The function uses a switch statement to handle different GPIO ports (portA, portB, etc.).
Within each port case, it checks the pin_value and performs the corresponding action:
If pin_value is Pin_High, it sets the specified bit in the GPIO_PORTx_DATA_R register (where x corresponds to the selected port).
If pin_value is Pin_Low, it clears the specified bit in the GPIO_PORTx_DATA_R register.
If port does not match any case, it does nothing (default case).
                                                Usage:
This function can be used to control individual pins on the Tiva C Series TM4C123GH6PM microcontroller.
The specific GPIO port and pin are determined by the input arguments.
Ensure that the GPIO_PORTx_DATA_R registers are correctly mapped according to your hardware platform
*/

void Set_Pin_value(u8 port,u8 pin,u8 pin_value){
    switch (port)
    {
    case portA :
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1<<pin);
        else if(pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &=~ (1<<pin); 
        break;
    case portB :
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1<<pin);
        else if(pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &=~ (1<<pin); 
        break;
    case portC :
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1<<pin);
        else if(pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &=~ (1<<pin); 
        break;
    case portD :
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1<<pin);
        else if(pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &=~ (1<<pin); 
        break;
    case portE :
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1<<pin);
        else if(pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &=~ (1<<pin); 
        break;
    case portF :
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1<<pin);
        else if(pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &=~ (1<<pin); 
        break;
    
    default:
        break;
    }          
}

/*
                                                    Function Description:
The Toggle_pin function is designed to toggle the state (high to low or low to high) of a specific pin on a specified GPIO port.
It takes two arguments:
port: An unsigned 8-bit integer representing the GPIO port (e.g., portA, portB, etc.).
pin: An unsigned 8-bit integer representing the pin number within the specified port.
                                                    Pin Toggling Logic:
The function uses a switch statement to handle different GPIO ports (portA, portB, etc.).
Within each port case, it performs a bitwise XOR operation on the specified pin in the GPIO_PORTx_DATA_R register (where x corresponds to the selected port).
If the pin was previously high, this operation sets it low.
If the pin was previously low, this operation sets it high.
If port does not match any case, it does nothing (default case).
                                                    Usage:
This function can be used to toggle individual pins on the Tiva C Series TM4C123GH6PM microcontroller.
The specific GPIO port and pin are determined by the input arguments.
Ensure that the GPIO_PORTx_DATA_R registers are correctly mapped according to your hardware platform
*/

void Toggle_pin(u8 port, u8 pin){
    switch (port)
    {
    case portA : GPIO_PORTA_DATA_R ^= (1<<pin);
        break;
    case portB : GPIO_PORTF_DATA_R ^= (1<<pin);
        break;
    case portC : GPIO_PORTF_DATA_R ^= (1<<pin);
        break;
    case portD : GPIO_PORTF_DATA_R ^= (1<<pin);
        break;
    case portE : GPIO_PORTF_DATA_R ^= (1<<pin);
        break;
    case portF : GPIO_PORTF_DATA_R ^= (1<<pin);
        break;
    default:
        break;
    }
}

/*
                                        Function Description:
The Get_Pin_Value function reads the value of a specific pin on a specified GPIO port.
It takes three arguments:
port: An unsigned 8-bit integer representing the GPIO port (e.g., portA, portB, etc.).
pin: An unsigned 8-bit integer representing the pin number within the specified port.
pin_value: A pointer to an unsigned 8-bit integer where the read value will be stored.
                                        Pin Value Reading Logic:
The function uses a switch statement to handle different GPIO ports (portA, portB, etc.).
Within each port case, it performs the following:
Reads the data from the corresponding GPIO_PORTx_DATA_R register (where x corresponds to the selected port).
Applies a bitwise AND operation with (1 << pin) to isolate the specific pin.
Right-shifts the result by pin bits to obtain the actual pin value.
Stores the pin value in the memory location pointed to by pin_value.
                                        Usage:
This function allows you to read the state of individual pins on the Tiva C Series TM4C123GH6PM microcontroller.
The specific GPIO port and pin are determined by the input arguments.
Ensure that the GPIO_PORTx_DATA_R registers are correctly mapped according to your hardware platform
*/

u8 Get_Pin_Value(u8 port,u8 pin,u8 *pin_value){
    switch (port)
    {
    case portA :*pin_value = (GPIO_PORTA_DATA_R & (1<<pin))>>pin;
        break;
    case portB :*pin_value = (GPIO_PORTB_DATA_R & (1<<pin))>>pin;
        break;
    case portC :*pin_value = (GPIO_PORTC_DATA_R & (1<<pin))>>pin;
        break;
    case portD :*pin_value = (GPIO_PORTD_DATA_R & (1<<pin))>>pin;
        break;
    case portE :*pin_value = (GPIO_PORTE_DATA_R & (1<<pin))>>pin;
        break;
    case portF :*pin_value = (GPIO_PORTF_DATA_R & (1<<pin))>>pin;
        break;
    default:
        break;
    }
}
