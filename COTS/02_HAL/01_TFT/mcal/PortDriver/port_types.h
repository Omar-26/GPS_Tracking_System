/*
 * port_types.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#ifndef E15_ARM_REPO_MCAL_PORT_DRIVER_PORT_TYPES_H_
#define E15_ARM_REPO_MCAL_PORT_DRIVER_PORT_TYPES_H_


#include "../../utils/Std_Types.h"
typedef enum
{
    Port_Channel_A0,
    Port_Channel_A1,
    Port_Channel_A2,
    Port_Channel_A3,
    Port_Channel_A4,
    Port_Channel_A5,
    Port_Channel_A6,
    Port_Channel_A7,

    Port_Channel_B0,
    Port_Channel_B1,
    Port_Channel_B2,
    Port_Channel_B3,
    Port_Channel_B4,
    Port_Channel_B5,
    Port_Channel_B6,
    Port_Channel_B7,

    Port_Channel_C0,
    Port_Channel_C1,
    Port_Channel_C2,
    Port_Channel_C3,
    Port_Channel_C4,
    Port_Channel_C5,
    Port_Channel_C6,
    Port_Channel_C7,

    Port_Channel_D0,
    Port_Channel_D1,
    Port_Channel_D2,
    Port_Channel_D3,
    Port_Channel_D4,
    Port_Channel_D5,
    Port_Channel_D6,
    Port_Channel_D7,

    Port_Channel_E0,
    Port_Channel_E1,
    Port_Channel_E2,
    Port_Channel_E3,
    Port_Channel_E4,
    Port_Channel_E5,
    Port_Channel_E6_NotExist,
    Port_Channel_E7_NotExist,

    Port_Channel_F0,
    Port_Channel_F1,
    Port_Channel_F2,
    Port_Channel_F3,
    Port_Channel_F4,

    Port_Channel_MaxNum
}Port_ChIdType;

typedef enum
{
    Port_Id_A=0,
    Port_Id_B,
    Port_Id_C,
    Port_Id_D,
    Port_Id_E,
    Port_Id_F
}Port_IdType;

typedef enum
{
    port_Dir_Input,
    port_Dir_Output
}Port_DirType;

typedef enum
{
    Port_IntDisable,
    Port_IntFallingEdge,
    Port_IntRisingEdge,
    Port_IntBothEdges
}Port_IntCtrType;

typedef enum
{
    Port_Mode_DIO,
    Port_Mode_UART_Tx,
    Port_Mode_UART_Rx,
    Port_Mode_SSI_Clk,
    Port_Mode_SSI_Fss,
    Port_Mode_SSI_Rx,
    Port_Mode_SSI_Tx,
    Port_Mode_I2C_Scl,
    Port_Mode_I2C_Sda,
    Port_Mode_PWM,
    Port_Mode_CCP,
    Port_Mode_AIN,
    Port_Mode_CAN_Rx,
    Port_Mode_CAN_Tx
}Port_ModeType;

typedef enum
{
    Port_Unlocked,
    Port_locked
}Port_LockStatusType;


typedef enum
{
    Port_InternalAttach_NA,
    Port_InternalAttach_PullUpRes,
    Port_InternalAttach_PullDownRes,
    Port_InternalAttach_OpenDrain,

}Port_InternalAttachType;

typedef enum
{
    Port_CurrDrive_2mA,
    Port_CurrDrive_4mA,
    Port_CurrDrive_8mA,
}Port_CurrDriveType;


typedef struct
{
    Port_ChIdType           Channel;
    Port_DirType            Dir;
    uint32                  Mode;
    Port_IntCtrType         Interrupt;
    Port_InternalAttachType AttachedRes;
    Port_CurrDriveType      CurrentDrive;
    Port_LockStatusType     LockStatus;
}Port_CfgType;

#endif /* E15_ARM_REPO_MCAL_PORT_DRIVER_PORT_TYPES_H_ */
