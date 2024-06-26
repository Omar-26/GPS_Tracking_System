/*
 * Dio.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#ifndef E15_ARM_REPO_MCAL_DIO_DIO_H_
#define E15_ARM_REPO_MCAL_DIO_DIO_H_

#include "../../utils/Std_Types.h"
#include "DIO_types.h"

/*=========================================
 * FUNCTIONS PROTOTYPES
 =========================================*/
Std_levelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Std_levelType Level);
uint8 Dio_ReadPort(Dio_PortType PortId );
void Dio_WritePort( Dio_PortType PortId, uint8 Level);
void Dio_FlipChannel( Dio_ChannelType ChannelId);
void Dio_FlipPort(Dio_PortType PortId);



#endif /* E15_ARM_REPO_MCAL_DIO_DIO_H_ */
