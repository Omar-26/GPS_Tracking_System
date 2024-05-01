#include<stdio.h>
#include<d:\Projects\C_projects\tm4c123gh6pm.h>

//function prototypes
void init_port_f();
void init_port_A();
u8 Get_Switch(u8 sw);
void RGB_LED(u8 led_color,u8 led_state);
void Set_Pin_value(u8 port,u8 pin,u8 pin_value);
void Toggle_pin(u8 port, u8 pin);
void Led_controlled(u8 Switch_state,u8 led_color);
u8 Get_Pin_Value(u8 port,u8 pin,u8 *pin_value);