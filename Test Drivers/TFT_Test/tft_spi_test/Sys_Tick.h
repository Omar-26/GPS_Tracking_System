/******************************************************************
* @Title : System tick timer (systik)
* @Filename : Sys_Tick.h
* @Author : Mohamed Atta ElSayed
* @Version : 1.0
********************************************************************/
#ifndef _SYSTICK_H_
#define _SYSTICK_H_

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
void SysTick_Delay10ms(uint32_t delay);
void delay_ms(uint32_t delay);
uint32_t get_SysTick_Ticks(int Time_ms);
void SysTick_Init();
void SysTick_Delay(uint32_t delay);

//****************************************************************************************//
//********************** implementation**********************//



#endif
//****************************************************************************************//


