/*
 * Bit_Math.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */

#ifndef E15_LAB_SRC_UTILS_BIT_MATH_H_
#define E15_LAB_SRC_UTILS_BIT_MATH_H_

#include "Std_Types.h"

#define SET_BIT(u32Var,BitNo)                                    u32Var |= ((uint32)1<<BitNo)
#define CLR_BIT(u32Var,BitNo)                                    u32Var &= ~((uint32)1<<BitNo)
#define TOGGLE_BIT(u32Var,BitNo)                                 u32Var ^= ((uint32)1<<BitNo)
#define TOGGLE_PORT(u32Var)                                      u32Var ^= ((uint32)(0xFF))
#define GET_BIT(u32Var,BitNo)                                    (u32Var >> BitNo) & (uint32)0x01

#define GET_REG(BASE_ADDR, REG_TYPE, REG_OFFSET)                (*((volatile REG_TYPE*)(BASE_ADDR+REG_OFFSET)))

#endif /* E15_LAB_SRC_UTILS_BIT_MATH_H_ */
