/*
 * processor.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#ifndef TM4C123_FIRMWARE_UTILS_PROCESSOR_PROCESSOR_H_
#define TM4C123_FIRMWARE_UTILS_PROCESSOR_PROCESSOR_H_

#include "../Std_Types.h"

typedef uint8 PROCESSOR_ModeType;
#define PROCESSOR_ModePrivilege                 (uint8)1
#define PROCESSOR_ModeNonPrivilege              (uint8)0

extern void PROCESSOR_switchMode(PROCESSOR_ModeType Mode);

extern void PROCESSOR_enableGlobalInt(void);

extern void PROCESSOR_disableGlobalInt(void);

extern void PROCESSOR_SvcHandler(void);

#endif /* TM4C123_FIRMWARE_UTILS_PROCESSOR_PROCESSOR_H_ */
