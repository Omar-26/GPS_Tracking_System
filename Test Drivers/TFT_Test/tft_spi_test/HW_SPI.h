#ifndef __HW_SPI_H__
#define __HW_SPI_H__
#include "data_types.h"

#define SSI0_Base 0x40008000
#define SSI1_Base 0x40009000
#define SSI2_Base 0x4000A000
#define SSI3_Base 0x4000B000

#define  SSICR0    (*((volatile U32_t*)0x40008000))
#define  SSICR1    (*((volatile U32_t*)0x40008004))
#define  SSIDR     (*((volatile U32_t*)0x40008008))
#define  SSISR     (*((volatile U32_t*)0x4000800c))
#define  SSICPSR   (*((volatile U32_t*)0x40008010))
#define  SSIIM     (*((volatile U32_t*)0x40008014))
#define  SSIRIS    (*((volatile U32_t*)0x40008018))
#define  SSIMIS    (*((volatile U32_t*)0x4000801c))
#define  SSIICR    (*((volatile U32_t*)0x40008020))
#define  SSIDMACTL (*((volatile U32_t*)0x40008024))
#define  SSICC     (*((volatile U32_t*)0x40008FC8))



#endif //__HW_SPI_H__
