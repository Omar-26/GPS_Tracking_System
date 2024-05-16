/*
 * port_cfg.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */

#ifndef E15_ARM_REPO_CONFIG_PORT_CFG_H_
#define E15_ARM_REPO_CONFIG_PORT_CFG_H_

#include "../mcal/PortDriver/port_types.h"


#define PORT_MODE_PIN_X_DIO                 0

#define PORT_MODE_PIN_B0_U1RX               1
#define PORT_MODE_PIN_B1_U1TX               1

#define PORT_MODE_PIN_A2_SSI0Clk            512
#define PORT_MODE_PIN_A3_SSI0Fss            8192
#define PORT_MODE_PIN_A4_SSI0Rx             131072
#define PORT_MODE_PIN_A5_SSI0Tx             2097152

#define PORT_MODE_PIN_B4_SSI2Clk            2
#define PORT_MODE_PIN_B5_SSI2Fss            2
#define PORT_MODE_PIN_B6_SSI2Rx             2
#define PORT_MODE_PIN_B7_SSI2Tx             2

#define PORT_MODE_PIN_D0_SSI1Clk            2
#define PORT_MODE_PIN_D1_SSI1Fss            2
#define PORT_MODE_PIN_D2_SSI1Rx             2
#define PORT_MODE_PIN_D3_SSI1Tx             2

#define PORT_MODE_PIN_D0_SSI3Clk            1
#define PORT_MODE_PIN_D1_SSI3Fss            1
#define PORT_MODE_PIN_D2_SSI3Rx             1
#define PORT_MODE_PIN_D3_SSI3Tx             1

#define PORT_MODE_PIN_F0_SSI1Clk            2
#define PORT_MODE_PIN_F1_SSI1Fss            2
#define PORT_MODE_PIN_F2_SSI1Rx             2
#define PORT_MODE_PIN_F3_SSI1Tx             2

#define PORT_MODE_PIN_B2_I2C0SCL            3
#define PORT_MODE_PIN_B3_I2C0SDA            3

#define PORT_MODE_PIN_A6_I2C1SCL            3
#define PORT_MODE_PIN_A7_I2C1SDA            3

#define PORT_MODE_PIN_E4_I2C2SCL            3
#define PORT_MODE_PIN_E5_I2C2SDA            3

#define PORT_MODE_PIN_D0_I2C3SCL            3
#define PORT_MODE_PIN_D1_I2C3SDA            3
#define PORT_NO_MODE_POSSIBLITY             4
/*TODO Enter number of activated channel */
#define PORT_NUM_OF_ACTIVATED_CH        ((uint8)(6))

extern Port_CfgType PortCfgArr[PORT_NUM_OF_ACTIVATED_CH];



#endif /* E15_ARM_REPO_CONFIG_PORT_CFG_H_ */
