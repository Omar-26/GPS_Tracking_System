/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "tm4c123gh6pm.h"
/**< MCAL_GPIO */
#include "GPIO_Private.h"
#include "GPIO_Interface.h"
#include "GPIO_Config.h"
void GPIO_voidInit_port_F()
{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0)
        ;
    GPIO_PORTF_LOCK_R = key_lock;
    GPIO_PORTF_CR_R |= 0x1F;
    GPIO_PORTF_AMSEL_R &= 0x00;
    GPIO_PORTF_AFSEL_R &= 0x00;
    GPIO_PORTF_PCTL_R &= No_Alternate_func;
    GPIO_PORTF_DEN_R |= Enable_portF_pins;
    GPIO_PORTF_PUR_R |= PUL_R_PortF;
    GPIO_PORTF_DIR_R |= Out_Leds;
}

void GPIO_voidInit_port_A()
{
    SYSCTL_RCGCGPIO_R |= 0x01;
    while ((SYSCTL_PRGPIO_R & 0x01) == 0)
        ;
    GPIO_PORTA_LOCK_R |= key_lock;
    GPIO_PORTA_CR_R |= 0xFF;
    GPIO_PORTA_AMSEL_R &= 0x00;
    GPIO_PORTA_AFSEL_R &= Uart_Spi_PortA;
    GPIO_PORTA_PCTL_R &= 0x00222211;
    GPIO_PORTA_DEN_R |= Enable_portA_Uart_Spi;
    GPIO_PORTA_PUR_R |= PUL_R_PortA;
    GPIO_PORTA_DIR_R |= Out_TXs;
}

u8 GPIO_u8Get_Switch(u8 sw)
{
    switch (sw)
    {
    case SW_1:
        return (GPIO_PORTF_DATA_R &= 0x10) >> 4;
        break;

    case SW_2:
        return (GPIO_PORTF_DATA_R &= 0x01) >> 4;
        break;

    default:
        return 0;
        break;
    }
}

void Led_controlled(u8 Switch_state, u8 led_color)
{
    switch (led_color)
    {
    case RED_LED:
        if (Switch_state == Pin_Low)
            GPIO_PORTF_DATA_R |= 0x02;
        else if (Switch_state == Pin_High)
            GPIO_PORTF_DATA_R &= ~0x02;

        break;
    case BLUE_LED:
        if (Switch_state == Pin_Low)
            GPIO_PORTF_DATA_R |= 0x04;
        else if (Switch_state == Pin_High)
            GPIO_PORTF_DATA_R &= ~0x04;

        break;
    case GREEN_LED:
        if (Switch_state == Pin_High)
            GPIO_PORTF_DATA_R |= 0x08;
        else if (Switch_state == Pin_Low)
            GPIO_PORTF_DATA_R &= ~0x08;

        break;

    default:
        break;
    }
}

void GPIO_voidRGB_LED(u8 led_color, u8 led_state)
{
    switch (led_color)
    {
    case RED_LED:
        switch (led_state)
        {
        case LED_ON:
            GPIO_PORTF_DATA_R |= 0x02;
            break;
        case LED_OFF:
            GPIO_PORTF_DATA_R &= ~0x02;

        default:
            break;
        }
        break;
    case BLUE_LED:
        switch (led_state)
        {
        case LED_ON:
            GPIO_PORTF_DATA_R |= 0x04;
            break;
        case LED_OFF:
            GPIO_PORTF_DATA_R &= ~0x04;

        default:
            
            break;
        }
        break;
    case GREEN_LED:
        switch (led_state)
        {
        case LED_ON:
            GPIO_PORTF_DATA_R |= 0x08;
            break;
        case LED_OFF:
            GPIO_PORTF_DATA_R &= ~0x08;

        default:
            
            break;
        }
        break;

    default:
        break;
    }
}

void GPIO_voidSet_Pin_value(u8 port, u8 pin, u8 pin_value)
{
    switch (port)
    {
    case portA:
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1 << pin);
        else if (pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &= ~(1 << pin);
        break;
    case portB:
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1 << pin);
        else if (pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &= ~(1 << pin);
        break;
    case portC:
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1 << pin);
        else if (pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &= ~(1 << pin);
        break;
    case portD:
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1 << pin);
        else if (pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &= ~(1 << pin);
        break;
    case portE:
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1 << pin);
        else if (pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &= ~(1 << pin);
        break;
    case portF:
        if (pin_value == Pin_High)
            GPIO_PORTA_DATA_R |= (1 << pin);
        else if (pin_value == Pin_Low)
            GPIO_PORTA_DATA_R &= ~(1 << pin);
        break;

    default:
        break;
    }
}

void GPIO_voidToggle_pin(u8 port, u8 pin)
{
    switch (port)
    {
    case portA:
        GPIO_PORTA_DATA_R ^= (1 << pin);
        break;
    case portB:
        GPIO_PORTF_DATA_R ^= (1 << pin);
        break;
    case portC:
        GPIO_PORTF_DATA_R ^= (1 << pin);
        break;
    case portD:
        GPIO_PORTF_DATA_R ^= (1 << pin);
        break;
    case portE:
        GPIO_PORTF_DATA_R ^= (1 << pin);
        break;
    case portF:
        GPIO_PORTF_DATA_R ^= (1 << pin);
        break;
    default:
        break;
    }
}

void GPIO_voidGet_Pin_Value(u8 port, u8 pin, u8 *pin_value)
{
    switch (port)
    {
    case portA:
        *pin_value = (GPIO_PORTA_DATA_R & (1 << pin)) >> pin;
        break;
    case portB:
        *pin_value = (GPIO_PORTB_DATA_R & (1 << pin)) >> pin;
        break;
    case portC:
        *pin_value = (GPIO_PORTC_DATA_R & (1 << pin)) >> pin;
        break;
    case portD:
        *pin_value = (GPIO_PORTD_DATA_R & (1 << pin)) >> pin;
        break;
    case portE:
        *pin_value = (GPIO_PORTE_DATA_R & (1 << pin)) >> pin;
        break;
    case portF:
        *pin_value = (GPIO_PORTF_DATA_R & (1 << pin)) >> pin;
        break;
    default:
        break;
    }
}
