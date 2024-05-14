
/******************************************************************
* @Title : Serial Peripheral interface (SPI)
* @Filename : SPI.h
* @Author : Abdulrahman Ahmed Saeed
* @Version : 1.0
********************************************************************/
#ifndef __SPI__H
#define __SPI__H
#include "GPIO_interface.h"

//*******************************************************************
//            (1) Macros for SPI module
//*******************************************************************

//SPI master/slave select 
#define SPI_Mode_Master (0)
#define SPI_Mode_Slave  (1)
#define SPI_MasterSlave_Bit (1<<2)   //0 configured as a master 1 as a slave

//SPI frame format   
#define SPI_Freescale_Foramt         (0x0)
#define SPI_TI_Foramt                (0x1)
#define SPI_MicroWire_Foramt         (0x2)
#define SPI_Freescale_Foramt_set     (0x0<<4)
#define SPI_TI_Foramt_set            (0x1<<4)
#define SPI_MicroWire_Foramt_set     (0x2<<4)
#define SPI_Format_Bits              (1<<4|1<<5)

//SPI free-scale format modes 
#define SPI_ClkPolarityPhase_Mode_1 (1)   //clock not inverted sample on leading edge 
#define SPI_ClkPolarityPhase_Mode_2 (2)   //clock not inverted saple on trailing edge
#define SPI_ClkPolarityPhase_Mode_3 (3)   //clock inverted sample on leading edge
#define SPI_ClkPolarityPhase_Mode_4 (4)   //clock not inverted saple on trailing edge
#define SPI_ClkPolarityPhase_Mode_1_set (0<<7|0<<6)     //clock not inverted sample on leading edge 
#define SPI_ClkPolarityPhase_Mode_2_set (0<<7|1<<6)     //clock not inverted saple on trailing edge
#define SPI_ClkPolarityPhase_Mode_3_set (1<<7|0<<6)     //clock inverted sample on leading edge
#define SPI_ClkPolarityPhase_Mode_4_set (1<<7|1<<6)     //clock not inverted saple on trailing edge
#define SPI_ClockPhase_Bit    (1<<7)    //clock pahse bit position
#define SPI_ClockPolarity_Bit (1<<6)   //clock polarity bit position  sh8l pull up 3l pin lw set



//SPI available data size
#define SPI_DataSize_4Bits  (0x3)
#define SPI_DataSize_5Bits  (0x4)
#define SPI_DataSize_6Bits  (0x5)
#define SPI_DataSize_7Bits  (0x6)
#define SPI_DataSize_8Bits  (0x7)
#define SPI_DataSize_9Bits  (0x8)
#define SPI_DataSize_10Bits (0x9)
#define SPI_DataSize_11Bits (0xA)
#define SPI_DataSize_12Bits (0xB)
#define SPI_DataSize_13Bits (0xC)
#define SPI_DataSize_14Bits (0xD)
#define SPI_DataSize_15Bits (0xE)
#define SPI_DataSize_16Bits (0xF)



//spi clock select options
#define SPI_sysclk_Source    (0x0)
#define SPI_Piosc_Source     (0x5)



//SPI EOT 
#define SPI_EndOfTrasnmission_Bit (1<<4)


//Spi enable/disable
#define SPI_EnableDisable_Bit (1<<1)

//spi status masks
#define SPI_Bus_isBusy       (1<<4)
#define SPI_RxFIFO_isFUll    (1<<3)
#define SPI_RxFIFO_isEmpty   (1<<2)
#define SPI_TxFIFO_isFUll    (1<<1)
#define SPI_TxFIFO_isEmpty   (1<<0)

//SPI interrupt masks
#define SPI_TxFifo_bit  (1<<3)
#define SPI_RxFifo_bit  (1<<2)
#define SPI_Timeout_bit (1<<1)
#define SPI_Overrun_bit (1<<0)


//Spi interrupt status 
#define SPI_TxFifo_InterruptStatus   (1<<3)
#define SPI_RxFifo_InterruptStatus   (1<<2)
#define SPI_Timeout_InterruptStatus  (1<<1)
#define SPI_Overrun_InterruptStatus  (1<<0)

//mask 
#define SPI_InterrupMasked    (0)
#define SPI_InterruptUnMasked (1)



//SPI interrupt Clear 
#define SPI_Timeout_INT_clear (1<<1)
#define SPI_OverRun_INT_clear (1<<0)



//spi enable module clock 
#define SPI_Clock_enable(module) (SYSCTL_RCGCSSI_R|=(1<<module))

//Spi peripheral number
#define SPI_0  (0)
#define SPI_1  (1)
#define SPI_2  (2)
#define SPI_3  (3)

#define FifoSize (8)

//*******************************************************************




//******************************************************************
//      (2)Data structures for spi module
//******************************************************************

#define     SSI0    0x40008000U
#define     SSI1    0x40009000U
#define     SSI2    0x4000A000U
#define     SSI3    0x4000B000U

typedef struct {
    volatile u32 CR0;           /**< Control register 0. */
    volatile u32 CR1;           /**< Control register 1. */
    volatile u32 DR;            /**< Data register. */
    volatile u32 SR;            /**< Status register. */
    volatile u32 CPSR;          /**< Clock Prescale. */
    volatile u32 IM;            /**< Interrupt mask. */
    volatile u32 RIS;           /**< Raw interrupt status. */
    volatile u32 MIS;           /**< Masked interrupt statusr. */
    volatile u32 ICR;           /**< Interrupt clear. */
    volatile u32 DMACTL;        /**< DMA control. */
    volatile u32 CC;           /**< Clock configuration . */
    volatile u32 PeriphID0;     /**< Peripheral identification 0. */
    volatile u32 PeriphID1;     /**< Peripheral identification 1. */
    volatile u32 PeriphID2;     /**< Peripheral identification 2. */
    volatile u32 PeriphID3;     /**< Peripheral identification 3. */
    volatile u32 PeriphID4;     /**< Peripheral identification 4. */
    volatile u32 PeriphID5;     /**< Peripheral identification 5. */
    volatile u32 PeriphID6;     /**< Peripheral identification 6. */
    volatile u32 PeriphID7;     /**< Peripheral identification 7. */
    volatile u32 PCellID0;      /**< PrimeCell identification 0. */
    volatile u32 PCellID1;      /**< PrimeCell identification 1. */

} SSI0_Type;

typedef enum
{
Idle,
Busy
}SPI_Bus_State;

typedef enum
{
Full,
Empty,
NotFullOrEmpty
}SPI_Fifo_State;

typedef struct 
{
	u8  MasterSlaveMode;
	u8  FrameFormat;
	u8  ClkPolarityPhaseMode;
	u8  DataSize;
	u8  ClkSource;
	u8  PreScaler;
}SPI_configParameters;


typedef struct 
{
SSI0_Type *SSIx;
u8   PeripherlaNumber;
SPI_configParameters config;
char *pTx;
u8 Txcounter;
u8 Tx_length;
char *pRx;
u8 Rx_length;
u8 RxCounter;
void (*DataTransmitted_CallBack) (void* spihandler,char* txBuff);
void (*DataReceived_CallBack)    (void* spihandler,char* rxBuff);
}SPI_handler;
//*********************************************************************




//**********************************************************************
//                      (3) SPI API
//**********************************************************************
void SPI_Init(SPI_handler *spiHandler);
void SPI_Enable(SPI_handler *spiHandler);
void SPI_Disable(SPI_handler *spiHandler);

/*Blocking APIS*/
void SPI_Slave_Transmit (SPI_handler *spiHandler,char* pTxBuffer,u8 dataLength);
void SPI_Master_Transmit(SPI_handler *spiHandler,char* pTxBuffer,u8 dataLength);
void SPI_Master_Receive (SPI_handler *spiHandler,char* pRxBuffer,u8 dataLength);
void SPI_Slave_Receive  (SPI_handler *spiHandler,char* pRxBuffer,u8 dataLength);

/* interrupts APIs Non blocking*/
void SPI_Interrupt_Enable  (SPI_handler *spiHandler);
void SPI_Interrupt_Disable (SPI_handler *spiHandler);

void SPI_Master_Start_Receive (SPI_handler *spiHandler,char* pRxBuffer,u8 dataLength);
void SPI_Master_Start_Trasnmit(SPI_handler *spiHandler,char* pTxBuffer,u8 dataLength);
void SPI_Slave_Start_Receive  (SPI_handler *spiHandler,char* pRxBuffer,u8 dataLength);
void SPI_Slave_Start_Transmit (SPI_handler *spiHandler,char* pTxBuffer,u8 dataLength);



void MastersendFromInterrupt(SPI_handler *spiHandler);
void MasterReceiveFromInterrupt(SPI_handler *spiHandler);
void SlaveReceiveFromInterrupt(SPI_handler *spiHandler);
void SlaveTransmitFromInterrupt(SPI_handler *spiHandler);

void SPI_txDone_RegsiterCB(SPI_handler *spiHandler ,void (*DataTransmitted_CallBack) (void* spihandler,char* txBuff) );
void SPI_rxDone_RegisterCB(SPI_handler *spiHandler ,void (*DataReceived_CallBack) (void* spihandler,char* rxBuff) );


void SPI_txDone_UnRegsiterCB(SPI_handler *spiHandler  );
void SPI_rxDone_UnRegisterCB(SPI_handler *spiHandler  );

//*************************************************************************



#endif