/******************************************************************
* @Title : System tick timer (systik)
* @Filename : Sys_Tick.h
* @Author : Mohamed Atta ElSayed
* @Version : 1.0
********************************************************************/

#include "Sys_Tick.h"
#include "tm4c123gh6pm.h"
//****************************************************************************************//
//********************** implementation**********************//

void MCAL_STK_SetReloadValue(uint32_t Copy_ReloadValue){
	
	SysTick ->LOAD = Copy_ReloadValue;
	
}
void SysTick_Delay10ms(uint32_t delay){//delay *10ms
 unsigned long i;
 for(i=0 ;i<delay ; i++){
	 SysTick_Delay(160000);
 }
}


uint32_t get_SysTick_Ticks(int Time_ms){	

	uint32_t SysTick_Ticks = ( (16000000 * ( Time_ms / 1000 ) ) - 1 ) ;	//16MHz Clock
	return SysTick_Ticks;
	
}

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R =0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000005;	
}
	
		


void SysTick_Delay(uint32_t delay){
 NVIC_ST_RELOAD_R=delay-1;
 NVIC_ST_CURRENT_R= 0;
 while((NVIC_ST_CTRL_R&0x00010000)==0){
 }
}


//****************************************************************************************//


