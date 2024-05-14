#include "IO.h"
#include "EEPROM_Interface.h"
#include "tm4c123gh6pm.h"
int k = 0;
float latitudee[20] ;
float longitudee[20] ;
float latit[20];
float longit[20];
void RGBLED_Init(void){
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
void SW_Init(int sw){
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R |= sw;
GPIO_PORTF_AMSEL_R &= ~sw;
GPIO_PORTF_AFSEL_R &= ~sw;
GPIO_PORTF_PCTL_R &= ~0x000F0000;
GPIO_PORTF_DIR_R &= ~sw;
GPIO_PORTF_DEN_R |= sw;
GPIO_PORTF_PUR_R = sw;
}
unsigned char SW_Input(int sw) {
return ~GPIO_PORTF_DATA_R & sw;
}
void LEDS_output(unsigned char data){
GPIO_PORTF_DATA_R &= ~0x0E;
GPIO_PORTF_DATA_R |= data;
}
unsigned char sw1_in;
unsigned char sw2_in;
unsigned char sw1_prev;
unsigned char sw2_prev;
int main() {
RGBLED_Init();
SW_Init(PF_SW1_mask);
SW_Init(PF_SW2_mask);
longitudee[7]=20;
latitudee[19]=5;
init_EEPROM();
	

    


write_Array_EEPROM(latitudee, longitudee, 20);
read_Array_EEPROM(latit, longit, 20);
		
while(1){
sw1_in= SW_Input(PF_SW1_mask);
sw2_in = SW_Input(PF_SW2_mask);
	
	
	
		
//if(sw1_prev != sw1_in || sw2_prev != sw2_in){
if(longit[8]== 20){
LEDS_output(BLUE);
}
else if( latit[19]==5){
LEDS_output(GREEN);
}
else if ( latit[5]== 0){
LEDS_output(RED);
}
else {
LEDS_output(0);
}
sw1_prev = sw1_in;
sw2_prev = sw2_in;
}
}
//}
