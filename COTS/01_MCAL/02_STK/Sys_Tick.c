/******************************************************************
* @Title : System tick timer (systik)
* @Filename : Sys_Tick.h
* @Author : Mohamed Atta ElSayed
* @Version : 1.0
********************************************************************/
#include <stdint.h> 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

typedef struct{

volatile uint32_t CTRL;	
volatile uint32_t LOAD;
volatile uint32_t VALUE; 
volatile uint32_t CAL;


}SysTick_Type;

#define SysTick_Base 0xE000E010UL
#define SysTick ( (SysTick_Type *) SysTick_Base) //explicit casting to structure 

//********************** SysTick Control and Status Register**********************//

#define SysTick_CTRL_Enable_Pos 0U
#define SysTick_CTRL_Enable_Msk (1UL<<SysTick_CTRL_Enable_Pos)

#define SysTick_CTRL_TICKINT_Pos 1U
#define SysTick_CTRL_TICKINT_Msk (1UL<<SysTick_CTRL_TICKINT_Pos)

#define SysTick_CTRL_CLKSOURCE_Pos 2U
#define SysTick_CTRL_CLKSOURCE_Msk (1UL<<SysTick_CTRL_CLKSOURCE_Pos)

#define SysTick_CTRL_COUNTFLAG_Pos 16U
#define SysTick_CTRL_COUNTFLAG_Msk (1UL<<SysTick_CTRL_COUNTFLAG_Pos)

//****************************************************************************************//
//********************** SysTick Reload Value Register**********************//

#define SysTick_LOAD_RELOAD_Pos 0U
#define SysTick_LOAD_RELOAD_Msk (0x00FFFFFFUL<<SysTick_LOAD_RELOAD_Pos)

//****************************************************************************************//
//**********************SysTick Current Value Register**********************//

#define SysTick_VALUE_CURRENT_Pos 0U
#define SysTick_VALUE_CURRENT_Msk (0x00FFFFFFUL<<SysTick_VALUE_CURRENT_Pos)

//****************************************************************************************//
//********************** SysTick Calibration Value Register**********************//

#define SysTick_CAL_TENMS_Pos 0U
#define SysTick_CAL_TENMS_Msk (0x00FFFFFFUL<<SysTick_CAL_TENMS_Pos)

#define SysTick_CAL_SKEW_Pos 30U
#define SysTick_CAL_SKEW_Msk (1UL<<SysTick_CAL_SKEW_Pos)

#define SysTick_CAL_NOREF_Pos 31U
#define SysTick_CAL_NOREF_Msk (1UL<<SysTick_CAL_NOREF_Pos)

//****************************************************************************************//
//********************** Prototypes**********************//

void MCAL_STK_SetReloadValue(uint32_t Copy_ReloadValue);
void MCAL_STK_SetDelay_ms(f32 Copy_Milliseconds);
void delay_ms(uint32_t delay);
uint32_t get_SysTick_Ticks(int Time_ms);
void SysTick_init(uint32_t SysTick_Ticks );
void SysTick_Delay (uint32_t Systick_Ticks);

//****************************************************************************************//
//********************** implementation**********************//

void MCAL_STK_SetReloadValue(uint32_t Copy_ReloadValue){
	
	SysTick ->LOAD = Copy_ReloadValue;
	
}
void MCAL_STK_SetDelay_ms(f32 Copy_Milliseconds){	
	
	uint32_t Copy_ReloadValue = (16000000 * Copy_Milliseconds * 0.001) - 1 ;	//16MHz
	MCAL_STK_SetReloadValue(Copy_ReloadValue);
	
}


uint32_t get_SysTick_Ticks(int Time_ms){	

	uint32_t SysTick_Ticks = ( (16000000 * ( Time_ms / 1000 ) ) - 1 ) ;	//16MHz Clock
	return SysTick_Ticks;
	
}

void SysTick_init(uint32_t SysTick_Ticks ){
	//disable systick timer
	CLR_BIT(SysTick->CTRL,SysTick_CTRL_Enable_Msk);
	
	//set reload register to systick ticks
	SysTick->LOAD=SysTick_Ticks;
	
	//reset counter current value
	SysTick->VALUE = 0;
	
	//choose processor clock
	SET_BIT(SysTick->CTRL,SysTick_CTRL_CLKSOURCE_Msk);
	
	//enable interrupt
	SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
	
	//enable Systick timer
	SET_BIT(SysTick->CTRL,SysTick_CTRL_Enable_Msk);
	
		
}

void SysTick_Delay (uint32_t Systick_Ticks){

	//set reload register to systick ticks 
	SysTick->LOAD=Systick_Ticks;
	
	//enable systick counter 
	SET_BIT( SysTick->CTRL,SysTick_CTRL_Enable_Msk);
	
	//wait untill count flag returns 1
	while(GET_BIT(SysTick->CTRL,SysTick_CTRL_COUNTFLAG_Msk) == 0);
	
	//when counter flag is equal 1 disable the counter
	CLR_BIT(SysTick->CTRL,SysTick_CTRL_Enable_Msk);
	
	//reset the reload register
	SysTick->LOAD =0;
	
	//disable the counter value
	SysTick->VALUE =0;
}


//****************************************************************************************//


