/*
 * port_lcfg.c
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#include "port_cfg.h"

Port_CfgType PortCfgArr[PORT_NUM_OF_ACTIVATED_CH] = {

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*    Channel                   Direction                Mode                          External Interrupt      Attached_Resistor                      Current_Drive_Strength      Lock_Status    */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


{     Port_Channel_A2,          port_Dir_Output,          PORT_MODE_PIN_A2_SSI0Clk,     Port_IntDisable,        Port_InternalAttach_NA,                Port_CurrDrive_2mA,         Port_Unlocked     },
{     Port_Channel_A3,/*CS*/    port_Dir_Output,          PORT_MODE_PIN_A3_SSI0Fss,     Port_IntDisable,        Port_InternalAttach_PullDownRes,       Port_CurrDrive_2mA,         Port_Unlocked     },
{     Port_Channel_A4,          port_Dir_Input ,          PORT_MODE_PIN_A4_SSI0Rx,      Port_IntDisable,        Port_InternalAttach_NA,                Port_CurrDrive_2mA,         Port_Unlocked     },
{     Port_Channel_A5,          port_Dir_Output,          PORT_MODE_PIN_A5_SSI0Tx,      Port_IntDisable,        Port_InternalAttach_NA,                Port_CurrDrive_2mA,         Port_Unlocked     },
{     Port_Channel_A6,/*DC*/    port_Dir_Output ,         PORT_MODE_PIN_X_DIO,          Port_IntDisable,        Port_InternalAttach_NA,                Port_CurrDrive_2mA,         Port_Unlocked     },
{     Port_Channel_A7,/*RES*/   port_Dir_Output ,         PORT_MODE_PIN_X_DIO,          Port_IntDisable,        Port_InternalAttach_NA,                Port_CurrDrive_2mA,         Port_Unlocked     }



};
