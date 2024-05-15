
/*
 * port.c
 *
 *  Created on: MAY 14, 2023
 *      Author: Ahmed Sallam
 */
#define MAX_NUM_OF_CH_IN_PORT       8

#include "../../utils/processor/processor.h"
#include "../../utils/Std_Types.h"
#include "../../utils/Bit_Math.h"
#include "../../config/port_cfg.h"
#include "../mcu_hw.h"
#include "port_types.h"
#include "port.h"

extern volatile PORT_RegType* Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[MAX_NUM_OF_PORTS];
void PORT_init(void)
{
    uint8 CfgArrIndex;
    Port_IdType PortId;
    Port_ChIdType ChannelId;
    uint8 ChannelPosInPort;
    volatile PORT_RegType* GPI0_APB_BaseAddr;
    GPI0_APB_BaseAddr = Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[0];    
    /*
    GPI0_APB_BaseAddr->GPIODIR=0;
    GPI0_APB_BaseAddr->GPIOAFSEL=0;
    GPI0_APB_BaseAddr->GPIOPCTL=0;
    GPI0_APB_BaseAddr->GPIODEN=0;
    GPI0_APB_BaseAddr->GPIODR2R=0;
    */
    for (CfgArrIndex = 0; CfgArrIndex < PORT_NUM_OF_ACTIVATED_CH; ++CfgArrIndex)
    {

        /*get channelID from CfgIndex*/
        ChannelId = PortCfgArr[CfgArrIndex].Channel;

        /*get PORTId using ChannelId*/
        PortId = ChannelId / MAX_NUM_OF_CH_IN_PORT;

        /*get GPI0_APB_BaseAddress using PortId*/
        GPI0_APB_BaseAddr = Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[PortId];

        /*get Channel Position in PortGroup using ChannelId */
        ChannelPosInPort = ChannelId % MAX_NUM_OF_CH_IN_PORT;

        /*NOTE use channel position in Group to write in corresponding bit in Desired Register */
        if( (PortId==Port_Id_C )&&( ChannelPosInPort<=Port_Channel_C3))
        {
            GPI0_APB_BaseAddr->GPIOLOCK=GPIO_COMMIT_LOCK;
            GPI0_APB_BaseAddr->GPIOCR|=0XFF;

        }
        else if( (PortId==Port_Id_D) &&( ChannelPosInPort==Port_Channel_D7))
        {

            GPI0_APB_BaseAddr->GPIOLOCK=GPIO_COMMIT_LOCK;
            GPI0_APB_BaseAddr->GPIOCR|=0XFF;

        }
        else if(  (PortId==Port_Id_F) &&( ChannelPosInPort==Port_Channel_F0))
        {

            GPI0_APB_BaseAddr->GPIOLOCK=GPIO_COMMIT_LOCK;
            GPI0_APB_BaseAddr->GPIOCR|=0XFF;

        }
        else
        {
            /*Do nothing*/
        }
        /*TODO: set channel direction */
        if(PortCfgArr[CfgArrIndex].Dir==port_Dir_Input)
        {
            CLR_BIT(GPI0_APB_BaseAddr->GPIODIR,ChannelPosInPort);
        }
        else if(PortCfgArr[CfgArrIndex].Dir==port_Dir_Output)
        {
            SET_BIT(GPI0_APB_BaseAddr->GPIODIR,ChannelPosInPort);
        }
        else
        {
            /*Do nothing*/
        }
        /*TODO: set channel mode */

        if(PortCfgArr[CfgArrIndex].Mode==PORT_MODE_PIN_X_DIO)
        {
            CLR_BIT(GPI0_APB_BaseAddr->GPIOAFSEL,ChannelPosInPort);
        }
        else 
        {
            SET_BIT(GPI0_APB_BaseAddr->GPIOAFSEL,ChannelPosInPort);
            GPI0_APB_BaseAddr->GPIOPCTL|=PortCfgArr[CfgArrIndex].Mode;
        }

        /*TODO: set Interrupt configuration */
        if(PortCfgArr[CfgArrIndex].Interrupt == Port_IntDisable)
        {

        }
        else
        {


        }

        /*TODO: set Internal Attachment configuration */


        /*TODO: set current strength configuration */
        if(PortCfgArr[CfgArrIndex].CurrentDrive==Port_CurrDrive_2mA)
        {
             SET_BIT(GPI0_APB_BaseAddr->GPIODR2R,ChannelPosInPort);             
        }
        else if(PortCfgArr[CfgArrIndex].CurrentDrive==Port_CurrDrive_4mA)
        {
             SET_BIT(GPI0_APB_BaseAddr->GPIODR4R,ChannelPosInPort);              
        }
        else if(PortCfgArr[CfgArrIndex].CurrentDrive==Port_CurrDrive_8mA)
        {
             SET_BIT(GPI0_APB_BaseAddr->GPIODR8R,ChannelPosInPort);          
        }
        /*Check if analog functionality is required*/
        if(PortCfgArr[CfgArrIndex].Mode != Port_Mode_AIN )
        {
            /*TODO: enable digital and disable ADC  */
            SET_BIT(GPI0_APB_BaseAddr->GPIODEN,ChannelPosInPort);
        }
        else
        {
            /*TODO: disable digital and enable ADC */
            CLR_BIT(GPI0_APB_BaseAddr->GPIODEN,ChannelPosInPort);
        }
    }

}
