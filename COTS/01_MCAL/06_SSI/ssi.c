#include"../../config/ssi_cfg.h"
#include "../../utils/Std_Types.h"
#include"../mcu_hw.h"
#include <stdlib.h>
#if (SSI_Execution_Way==SSI_Execution_By_POLLING)

void SSI_INIT(void)
{
    /*SSInClk = SysClk / (CPSDVSR * (1 + SCR))*/
    SSICR1(SSI0_BASE_ADDR).B.SSE=0;
    SSICC(SSI0_BASE_ADDR)=0;
    SSICR0(SSI0_BASE_ADDR).B.SCR=str_SSI_Config.SSICR0_SCR;
    /*SSInClk = SysClk / (CPSDVSR * (1 + SCR))*/
    SSICPSR(SSI0_BASE_ADDR)=str_SSI_Config.SSICPSR_CPSDVSR; 
    /*SSI Data Size Select*/
    SSICR0(SSI0_BASE_ADDR).B.DSS=str_SSI_Config.SSICR0_DSS;
    /*Configure SPI as master*/
    SSICR1(SSI0_BASE_ADDR).B.MS=str_SSI_Config.SSICR1_MS;
    /*Enable ssi transmission on the bus*/
    SSICR1(SSI0_BASE_ADDR).B.SSE=1;
}

void SSI_SEND_BYTE(uint8 BYTE)
{
   /*Put the new data*/ 
   SSIDR(SSI0_BASE_ADDR)=BYTE;
   
   /*Wait until transmission is finished*/  
   while(SSISR(SSI0_BASE_ADDR).B.BSY==1);


 
}

void SSI_Disable_Transfer()
{
  SSICR1(SSI0_BASE_ADDR).B.SSE=0;
}

void SSI_SEND_ARRAY_OF_BYTES(uint8* Pntr_To_array,uint32 size)
{
   /*Loop until it send all bytes inside the array*/
   int i=0;
   for(;i<size;i++)
   {
       SSI_SEND_BYTE(Pntr_To_array[i]);
   }
}

 uint8* SSI_RECEIVE_BYTE(void)
 {
   
 }

#elif (SSI_Execution_Way==SSI_Execution_By_Event_Based)

 void SSI_INIT(void)
 {
   
 }
 void SSI_SEND_BYTE(uint8 BYTE)
 {
   
 }
 uint8* SSI_RECEIVE_BYTE(void)
 {
   
 }
#elif (SSI_Execution_Way==SSI_Execution_By_Time_Based) 

 void SSI_INIT(void)
 {
   
 }
 void SSI_SEND_BYTE(uint8 BYTE)
 {
   
 }
 uint8* SSI_RECEIVE_BYTE(void)
 {
   
 }
#endif 
