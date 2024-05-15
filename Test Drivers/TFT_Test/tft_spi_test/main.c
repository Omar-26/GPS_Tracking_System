
/******************************< SYSTEM ***************************/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/******************************< LIB ******************************/
#include "STD_TYPES.h"
/******************************< MCAL *****************************/
#include "GPIO_Interface.h"
#include "Sys_Tick.h"
#include "UART_Interface.h"
#include "SPI_Interface.h"  
#include "SPI.h"
/******************************< HAL ******************************/
#include "GPS_interface.h"
#include "TFT_interface.h"
/******************************< APP ******************************/
// #include "APP/APP.h"
#include "iota.h"
#define gpio_clk_enable(port)  (SYSCTL_G->RCGCGPIO|=(1<<port))  

/******************************< Global Variables *****************/
extern f64 currentLat, currentLong;
extern u8 GPS[80];
/******************************< main *****************************/
int main(){
	/******************************< init *****************************/
	//GPIO_voidInit_port_A();
	GPIO_voidInit_port_F();
	SysTick_Init();
	/*****************************<SPI *********************************/
//	SSI0_Type spi0;
//	spi0.CC = SSI0_CC_R;
//	spi0.CPSR = SSI0_CPSR_R;
//	spi0.CR0 = SSI0_CR0_R;
//	spi0.CR1 = SSI1_CR1_R;
//	spi0.DMACTL = SSI0_DMACTL_R;
//	spi0.DR = SSI0_DR_R;
//	spi0.ICR = SSI0_ICR_R;
//	spi0.IM = SSI0_IM_R;
//	spi0.MIS = SSI0_MIS_R;
//	spi0.RIS = SSI0_RIS_R;
//	spi0.SR = SSI0_SR_R;
//	
//	SPI_handler spi;
//spi.config.MasterSlaveMode=SPI_Mode_Master;
//spi.config.ClkSource=SPI_sysclk_Source;
//spi.config.FrameFormat=SPI_Freescale_Foramt;
//spi.config.ClkPolarityPhaseMode=SPI_ClkPolarityPhase_Mode_4;
//spi.config.DataSize=SPI_DataSize_8Bits;
//spi.config.PreScaler=2;
//spi.SSIx = &spi0;
//spi.PeripherlaNumber=SPI_0;
////SPI_rxDone_RegisterCB(&spi,callback);
//SPI_Init(&spi);
	/****************************<TFT **********************************/
	TFT_Config_t tft_1;	
	/**< Data/Command config ==> gpio */
	tft_1.TFT_DCPin.TFT_Port =portA;
	tft_1.TFT_DCPin.TFT_Pin = 6;
	/**< Reset pin ==> gpio */
	tft_1.TFT_RESPin.TFT_Port = portA;
	tft_1.TFT_RESPin.TFT_Pin = 7;

	/**< set gpio mode */
	SPI_Master_init();
	TFT_Init(&tft_1);
	
	// SPI_Init();
	
			// Stop Reading

//TFT_WriteChar(&tft_1, spi, 50,  50,'a', Font_7x10, TFT_COLOR_GOLD, TFT_COLOR_BLACK);
	for(;;)
	TFT_DrawLine(&tft_1, 10, 10, 100, 100, TFT_COLOR_CYAN);

}
