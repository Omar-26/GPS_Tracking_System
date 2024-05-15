/*
 * SysCtr.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#include "../../utils/STD_Types.h"
#include "../../utils/Bit_Math.h"
#include"../../mcal/SysCtr/SysCtr.h"
/*TODO include SysCtr_cfg.h*/
#include"../../config/SysCtr_cfg.h"
#include "../mcu_hw.h"

extern uint8 au8_RCG_INDEX[];

void SysCtr_init(void)
{
    /*TODO Enable configured Peripherals CLock gates*/
    uint8 u8_index=0;
    for(;u8_index<NO_OF_GATES_FOR_PHERIPHERALS; u8_index++ )
    {
        SysCtr_Open_Clock_REG(au8_RCG_INDEX[u8_index],gSysCtr_cfg.pu8a_Gate_Peripheral[u8_index]);
    }
    /*TODO Set System CLock Source as configured*/
    RCC2.USERCC2=ENABLE_CONFIG_USING_RCC2;/*1*/
    RCC2.OSCSRC2=gSysCtr_cfg.u8_System_Clock_Source;/*0*/
    /*TODO set CLock Frequency as configured -
     *
     * use Figure 5-5. Main Clock Tree Page.222 in DATASHEET as reference.
     * */

    RCC2.BYPASS2=RCC2_USING_PHASE_LOCKED_LOOP;/*0*/
    RCC2.SYSDIV2=gSysCtr_cfg.u8_System_Clock_Frequency;/*3*/
}

uint32 SysCtr_getSysClockFreq(void)
{
    /*TODO return the current system clock frequency */
    return gSysCtr_cfg.u8_System_Clock_Frequency;

}

