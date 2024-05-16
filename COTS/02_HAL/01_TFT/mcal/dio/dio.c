/*
 * Dio.h
 *
 *  Created on: may 13, 2023
 *      Author: Ahmed Sallam
 */


#include "../../utils/Bit_Math.h"
#include "../../utils/STD_Types.h"
#include "../mcu_hw.h"

/*TODO: include the header file that contains register definitions */

#include "dio.h"

extern volatile PORT_RegType* Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[];

Std_levelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Std_levelType ret;
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    /*TODO: Return the level value of given Channel */
    return GET_BIT(Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId]->GPIODATA,ChannelPos);
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Std_levelType Level)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    /*TODO: Write the input value in the corresponding ChannelId */
    if(Level==STD_low)          CLR_BIT(Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId]->GPIODATA,ChannelPos);
    else if(Level==STD_high)    SET_BIT(Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId]->GPIODATA,ChannelPos);
    else
    {
        /*Do nothing*/
    }
}
uint8 Dio_ReadPort(Dio_PortType PortId )
{

    /*TODO: Return the Port Value*/
    return Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId]->GPIODATA;
}
void Dio_WritePort( Dio_PortType PortId, uint8 value)
{
    /*TODO: Write the input value in the corresponding PortId */
    Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId]->GPIODATA=value;
}
void Dio_FlipChannel( Dio_ChannelType ChannelId)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;
    /* TODO: toggle the corresponding ChannelId */
    TOGGLE_BIT(Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId]->GPIODATA,ChannelPos);

}
void Dio_FlipPort(Dio_PortType PortId)
{
    /*TODO: toggle the port value */

}



