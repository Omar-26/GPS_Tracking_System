#include "EEPROM_Interface.h"
#include "tm4c123gh6pm.h"
#include "IO.h"

uint32_t i = 0;

f32 write_latitude[50] ;
f32 write_longitude[50] ;
f32 read_latitude[50];
f32 read_longitude[50];

void init_RGBLEDs(void){
SYSCTL_RCGCGPIO_R |= PF_mask;
while((SYSCTL_PRGPIO_R & 0x20)==0 )
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R = 0x0E;
GPIO_PORTF_AMSEL_R &= ~PF123_mask;
GPIO_PORTF_AFSEL_R &= ~PF123_mask;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTF_DIR_R |= PF123_mask;
GPIO_PORTF_DEN_R |= PF123_mask;
GPIO_PORTF_DATA_R &= ~PF123_mask;
}

void LEDs_output(u8 data){
GPIO_PORTF_DATA_R &= ~0x0E;
GPIO_PORTF_DATA_R |= data;
}

int main() {
init_RGBLEDs();
init_EEPROM();
write_latitude[10] = 4;
write_longitude[4] = 10;

write_Array_EEPROM(write_latitude, write_longitude, 50);
read_Array_EEPROM(read_latitude, read_longitude, 50);
		
while(1){
if(read_latitude[10] == 4){
LEDs_output(RED);
}
else if(read_longitude[4] == 10){
LEDs_output(BLUE);
}
else if (read_latitude[5] == 0){
LEDs_output(GREEN);
}
else {
LEDs_output(0);
}
}
}
