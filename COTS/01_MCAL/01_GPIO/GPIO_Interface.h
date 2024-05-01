#include<stdio.h>
#include<d:\Projects\C_projects\tm4c123gh6pm.h>

#define RED_LED 0
#define BLUE_LED 1
#define GREEN_LED 2
#define SW_1 0
#define SW_2 1
#define LED_OFF 0
#define LED_ON 1
#define portF 1
#define portA 0
//GPIO pins
#define pin0 (1<<0)
#define pin1 (1<<1)
#define pin2 (1<<2)     
#define pin3 (1<<3)
#define pin4 (1<<4)
#define pin5 (1<<5)
#define pin6 (1<<6)
#define pin7 (1<<7)
//Gpio pin data
#define Pin_High (1)
#define Pin_Low  (0)
//Gpio pin direction
#define pin_out (1)
#define pin_in  (0)
void init_port_f();
void init_port_A();
unsigned char Get_Switch(unsigned char sw);
void RGB_LED(unsigned char led_color,unsigned char led_state);
void Set_Pin_value(unsigned char port,unsigned char pin,unsigned char pin_value);
void Toggle_pin(unsigned char port, unsigned char pin);