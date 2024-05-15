/*
 * NViclcfg.c
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#include "nvic_cfg.h"
#include "../mcal/nvic/nvic_types.h"



   /*TODO Configure each Enabled Interrupt */

const NVIC_CfgType NVIC_CfgArr[NVIC_NUM_OF_ENABLED_INT]={ {0,1,1,1}
                                                         ,{1,0,2,1}
                                                         ,{2,0,3,1}
                                                         ,{3,1,4,1}
                                                         ,{63,1,5,1}  };



