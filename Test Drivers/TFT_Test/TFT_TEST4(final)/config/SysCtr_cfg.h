/*
 * SysCtr_cfg.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */

#ifndef E15_ARM_REPO_CONFIG_SYSCTR_CFG_H_
#define E15_ARM_REPO_CONFIG_SYSCTR_CFG_H_

#include"../mcal/SysCtr/SysCtr_types.h"
#include"../utils/STD_types.h"


#define Open_All_Gates_Of_GPIO_Peripheral_Value ((uint8)(0X3F))
#define Close_Gate_Peripheral_Value             ((uint8)(0   ))
#define Open_Gate_Of_SSI_Module_ONE             1
#define Open_Gate_Of_SSI_Module_TWO             2
#define Open_Gate_Of_SSI_Module_THREE           4
#define Open_Gate_Of_SSI_Module_FOUR            8

/**System Clock Source**/
#define u8_Main_Oscillator                                             0
#define u8_Precision_Internal_Oscillator                               1

/**System Clock Frequency**/
#define u8_System_Clock_66_P_67_MHz                                    2
#define u8_System_Clock_50_MHz                                         3

#define ENABLE_CONFIG_USING_RCC2                                       1
#define RCC2_USING_PHASE_LOCKED_LOOP                                   0

/*TODO implement suitable container to store the followings
 *
 * which Gate_Peripheral clock gate Enabled
 * Desired System clock Source
 * Desired System CLock Frequency
 * */
typedef struct
{
    uint8 *pu8a_Gate_Peripheral;
    uint8 u8_System_Clock_Source;
    uint8 u8_System_Clock_Frequency;
}SysCtr_cfg_t;

extern const SysCtr_cfg_t gSysCtr_cfg;

#endif /* E15_ARM_REPO_CONFIG_SYSCTR_CFG_H_ */
