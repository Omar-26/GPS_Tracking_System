#include "../../utils/Std_Types.h"
/*SSInClk = SysClk / (CPSDVSR * (1 + SCR))*/
typedef struct 
{
  uint8 SSICR0_SCR;     /*24*//*to acheive 1MHZ*/
  uint8 SSICR0_SPH;     /*0*/
  uint8 SSICR0_SPO;     /*0*/
  uint8 SSICR0_DSS;     /*8*/
  uint8 SSICR1_MS;      /*1->master*/
  uint8 SSICPSR_CPSDVSR;/*2*//*to acheive 1MHZ*/
}str_SSI_Config_t;
/*
SSICR1
SSICPSR
SSICR0
*/      