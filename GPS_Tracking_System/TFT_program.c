/**
 ********************************************************************************************
 * @file TFT_Displays_program.c
 * @brief This file contains the implementation of the TFT Displays module functions.
 * 
 * This module provides functions for interfacing with TFT (Thin-Film Transistor) displays
 * to control graphical user interfaces (GUIs), display images, and render text.
 ********************************************************************************************
 * @version V01
 * @author Abdulrahman Ahmed Saeed
 *
 * @note Before using this module, make sure to configure the display controller
 * and the required GPIO pins for communication and control.
 *
 * @see TFT_Displays_interface.h for the public interface and function descriptions.
 ******************************************************************************************** 
 */

/**<========================================================================================*/
/*******************************************< LIB *******************************************/
/**<========================================================================================*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stdlib.h"
/**<=========================================================================================*/
/*******************************************< MCAL *******************************************/
/**<=========================================================================================*/
#include "GPIO_interface.h"
#include "GPIO_Private.h"
#include "SPI_interface.h"
#include "Sys_Tick.h"

/**<========================================================================================*/
/*******************************************< HAL *******************************************/
/**<========================================================================================*/
#include "fonts.h"
#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"


/**<=============================================================================================================*/
/*******************************************< Functions Implementation *******************************************/
/**<=============================================================================================================*/

/**
 * @addtogroup TFT_Public_Functions
 * @{
 */

/**< Needed */
void TFT_Init(const TFT_Config_t *Copy_TftDisplay,SPI_handler Copy_SpiPeripheral)
{
    /**< Set the Reset (RES) pin to high logic level to release reset signal */
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_RESPin.TFT_Port, Copy_TftDisplay->TFT_RESPin.TFT_Pin, GPIO_HIGH);
    
    /**< Wait for a specified delay before proceeding */
    SysTick_Delay10ms(5);
    
    /**< Set the Reset (RST) pin to low logic level to assert reset signal */
   GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_RESPin.TFT_Port, Copy_TftDisplay->TFT_RESPin.TFT_Pin, GPIO_LOW);
    
    /**< Wait for a short delay */
    SysTick_Delay10ms(15);
    
    /**< Set the Reset (RES) pin to high logic level to release reset signal */
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_RESPin.TFT_Port, Copy_TftDisplay->TFT_RESPin.TFT_Pin, GPIO_HIGH);
    
    /**< Wait for a specified delay before proceeding */
    SysTick_Delay10ms(15);
    
    TFT_InitController(Copy_TftDisplay, Copy_SpiPeripheral);
}

/**< Not needed*/
void TFT_ClearScreen(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral)
{
    /**< Set the X and Y addresses */
    TFT_SetXYAddress(Copy_TftDisplay, Copy_SpiPeripheral, 0, 0);

    /**< Send the command to write data to the RAM */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_RAMWR);

    /**< Fill the screen with the default background color */
    for (u32 i = 0; i < TFT_DISPLAY_WIDTH * TFT_DISPLAY_HEIGHT; i++)
    {
        TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, (TFT_DEFAULT_BACKGROUND_COLOR >> 8) & 0xFF); /**< High byte of color */
        TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, TFT_DEFAULT_BACKGROUND_COLOR & 0xFF);        /**< Low byte of color */
    }
}

/**< Not needed*/

void TFT_DrawLine(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    int Local_dx = abs(x2 - x1);            /**< Calculate the absolute difference in X coordinates. */
    int Local_sx = x1 < x2 ? 1 : -1;        /**< Determine the X direction (positive or negative). */
    int Local_dy = -abs(y2 - y1);           /**< Calculate the negative absolute difference in Y coordinates. */
    int Local_sy = y1 < y2 ? 1 : -1;        /**< Determine the Y direction (positive or negative). */
    int Local_err = Local_dx + Local_dy;    /**< Initialize the error term for line drawing algorithm. */
    int Local_e2;                           /**< Initialize a variable for tracking another error term. */

    while (1)
    {
        /**< Draw a pixel at the current position */ 
        TFT_DrawPixel(Copy_TftDisplay, Copy_SpiPeripheral, x1, y1, color);

        /**< Check if we've reached the end point */ 
        if (x1 == x2 && y1 == y2)
            break;

        Local_e2 = 2 * Local_err;

        /**< Calculate the next position */ 
        if (Local_e2 >= Local_dy)
        {
            Local_err += Local_dy;
            x1 += Local_sx;
        }

        if (Local_e2 <= Local_dx)
        {
            Local_err += Local_dx;
            y1 += Local_sy;
        }
    }
}

/**< Needed*/
void TFT_DisplayImage(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, const u16 *Copy_Image)
{
    /*******************************************< Set the X and Y addresses for drawing pixels *******************************************/ 
	
    /**< Calculate the high and low bytes of the end X coordinates */
    u8 xEndHigh = ((TFT_DISPLAY_WIDTH-1) >> 8) & 0xFF;
    u8 xEndLow = (TFT_DISPLAY_HEIGHT-1) & 0xFF;

	/**< Send the commands to set the X addresses */
	TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_CASET);      /**< Send column address command */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0);                 /**< Send high byte of start X address */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0);                 /**< Send low byte of start X address */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, xEndHigh);          /**< Send high byte of end X address */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, xEndLow);           /**< Send low byte of end X address */

    /**< Calculate the high and low bytes of the end Y coordinates */
    u8 yEndHigh = ((TFT_DISPLAY_HEIGHT-1) >> 8) & 0xFF;
    u8 yEndLow = (TFT_DISPLAY_HEIGHT-1) & 0xFF;

	/**< Send the commands to set the Y addresses */
	TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_RASET); /**< Send row address command */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0);        /**< Send high byte of start Y address */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0);         /**< Send low byte of start Y address */
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, yEndHigh);     /**< Send high byte of end Y address */       
	TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, yEndLow);      /**< Send high byte of end Y address */


    /*******************************************< Send the command to write data to the RAM *******************************************/
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_RAMWR);

    /*******************************************< Loop through the image pixels *******************************************/ 
    for (u16 Local_Counter = 0; Local_Counter < TFT_DISPLAY_HEIGHT * TFT_DISPLAY_WIDTH; Local_Counter++)
    {
		/**< Send the pixel color data */
		TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, (Copy_Image[Local_Counter] >> 8) & 0xFF); /**< High byte of color */
		TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, Copy_Image[Local_Counter] & 0xFF);        /**< Low byte of color */
    }
}

/**
 * @brief Displays text on the TFT screen.
 *
 * This function displays text at the specified (x, y) coordinates with the given color.
 *
 * @param[in] x The X-coordinate where the text will be displayed.
 * @param[in] y The Y-coordinate where the text will be displayed.
 * @param[in] text Pointer to the text string to be displayed.
 * @param[in] font The font size and style to use for rendering the text.
 * @param[in] color The color of the text in 16-bit RGB565 format.
 * @retval None
 */
//void TFT_voidDisplayText(u16 x, u16 y, const char* text, const Font_t* font, u16 color)
//{
//    /**< Implement the TFT text display function */
//
//}

/**
 * @} TFT_Public_Functions
 */

/**
 * @addtogroup TFT_Private_Functions
 * @{
 */
/**< Needed*/
static void TFT_SendCommand(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, u8 Copy_Command)
{
    /**< Temp variable to receive the data in */
    u8 Local_u8ReceivedData = 0;

    /**<  Set CS (Chip Select) pin low to select the TFT display for communication */
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_CSPin.TFT_Port, Copy_TftDisplay->TFT_CSPin.TFT_Pin, GPIO_LOW); 

    /**< Set DC (Data/Command Control) pin low to indicate command mode */ 
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_DCPin.TFT_Port, Copy_TftDisplay->TFT_DCPin.TFT_Pin, GPIO_LOW); 

    /**< Perform SPI data transfer to send the command byte */ 
    SPI_Master_Transmit (&Copy_SpiPeripheral,&Copy_Command,1);


    /**< Set CS pin high to release the TFT display */ 
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_CSPin.TFT_Port, Copy_TftDisplay->TFT_CSPin.TFT_Pin, GPIO_HIGH); 
}
/**< Needed*/
static void TFT_SendData(const TFT_Config_t *Copy_TftDisplay,SPI_handler Copy_SpiPeripheral, u8 Copy_Data)
{
    /**< Temp variable to receive the data in */
    u8 Local_u8ReceivedData = 0;

    /**<  Set CS (Chip Select) pin low to select the TFT display for communication */
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_CSPin.TFT_Port, Copy_TftDisplay->TFT_CSPin.TFT_Pin, GPIO_LOW); 

    /**< Set DC (Data/Command Control) pin low to indicate command mode */ 
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_DCPin.TFT_Port, Copy_TftDisplay->TFT_DCPin.TFT_Pin, GPIO_HIGH); 

    /**< Perform SPI data transfer to send the command byte */ 
    SPI_Master_Transmit (&Copy_SpiPeripheral,&Copy_Data,1);

    /**< Set CS pin high to release the TFT display */ 
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_CSPin.TFT_Port, Copy_TftDisplay->TFT_CSPin.TFT_Pin,GPIO_HIGH); 
}
/**< Not needed*/
static void TFT_DrawPixel(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, u16 Copy_XPosition, u16 Copy_YPosition, u16 color) 
{
    /**< Set the X and Y addresses */
    TFT_SetXYAddress(Copy_TftDisplay, Copy_SpiPeripheral, Copy_XPosition, Copy_YPosition);

    /**< Send the command to write data to the RAM */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_RAMWR);

    /**< Send the pixel color data */
    TFT_SendData(Copy_TftDisplay,Copy_SpiPeripheral, (color >> 8) & 0xFF); /**< High byte of color */ 
    TFT_SendData(Copy_TftDisplay,Copy_SpiPeripheral, color & 0xFF);        /**< Low byte of color */
}
/**< Not needed*/
static void TFT_SetXAddress(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, u16 Copy_XPosition)
 {
    /**< Calculate the high and low bytes of the X coordinate */ 
    u8 xHigh = (Copy_XPosition >> 8) & 0xFF;
    u8 xLow = Copy_XPosition & 0xFF;

    /**< Send the commands to set the X address */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_CASET);  /**< Send column address command */ 
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, xHigh);         /**< Send high byte of X address */ 
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, xLow);          /**< Send low byte of X address */
}
/**< Not needed*/
static void TFT_SetYAddress(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, u16 Copy_YPosition) 
{
    // Calculate the high and low bytes of the Y coordinate
    u8 yHigh = (Copy_YPosition >> 8) & 0xFF;
    u8 yLow = Copy_YPosition & 0xFF;

    // Send the commands to set the Y address
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_RASET); /**< Send row address command */ 
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, yHigh);        /**< Send high byte of Y address */
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, yLow);         /**< Send low byte of Y address */ 
}
/**< Not needed*/
static void TFT_SetXYAddress(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, u16 Copy_XPosition, u16 Copy_YPosition) 
{
    /**< Calculate the high and low bytes of the X coordinates */ 
    u8 xHigh = (Copy_XPosition >> 8) & 0xFF;
    u8 xLow = Copy_XPosition & 0xFF;

    /**< Calculate the high and low bytes of the Y coordinates */ 
    u8 yHigh = (Copy_YPosition >> 8) & 0xFF;
    u8 yLow = Copy_YPosition & 0xFF;

    /**< Send the commands to set the X addresses */ 
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_CASET); /**< Send column address command */   
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, xHigh);         /**< Send high byte of X address */   
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, xLow);          /**< Send low byte of X address */

    /**< Send the commands to set the Y addresses */ 
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, TFT_RASET); /**< Send row address command */
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, yHigh);        /**< Send high byte of Y address */
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, yLow);         /**< Send low byte of Y address */
}
/**< Needed*/
static void TFT_InitController(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral)
{
    /**<==============================================================================================================*/
    /*******************************************< Configure ST7735S display *******************************************/ 
    /**<==============================================================================================================*/
    /**< Send command for software reset */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x01);
    SysTick_Delay10ms(15);

    /**< Send command to exit sleep mode */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x11);
    SysTick_Delay10ms(50);

    /**< Send command to configure frame rate control - normal mode */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xB1);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x01);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2C);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2D);

    /**< Send command to configure frame rate control - idle mode */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xB2);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x01);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2C);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2D);

    /**< Send command to configure frame rate control - partial mode */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xB3);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x01);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2C);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2D);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x01);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2C);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2D);

    /**< Send command to configure display inversion control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xB4);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x07);

    /**< Send command to configure power control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xC0);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0xA2);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x02);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x84);

    /**< Send command to configure power control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xC1);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0xC5);

    /**< Send command to configure power control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xC2);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x0A);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);

    /**< Send command to configure power control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xC3);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x8A);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2A);

    /**< Send command to configure power control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xC4);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x8A);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0xEE);

    /**< Send command to configure power control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xC5);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x0E);

    /**< Send command to disable display inversion */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x20);

    /**< Send command to configure memory access control */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x36);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0xC0);

    /**< Send command to set pixel format */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x3A);
    #if (TFT_DISPLAY_COLORS == _3BIT_PER_PIXEL) || (TFT_DISPLAY_COLORS == _16BIT_PER_PIXEL) || (TFT_DISPLAY_COLORS == _18BIT_PER_PIXEL)
        TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, TFT_DISPLAY_COLORS);
    #else
        TFT_SendCommand(Copy_TftDisplay, 0x21);
    #endif

    /**< Set column address */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x2A);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x7F);

    /**< Set row address */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x2B);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x7F);

    /**< Configure magical unicorn dust settings - Part 1 */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xE0);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x02);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x1C);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x07);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x12);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x37);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x32);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x29);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2D);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x29);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x25);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2B);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x39);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x01);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x03);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x10);

    /**< Configure sparkles and rainbows settings - Part 1 */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0xE1);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x03);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x1D);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x07);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x06);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2E);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2C);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x29);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2D);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2E);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x2E);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x37);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x3F);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x00);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x02);
    TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral, 0x10);

    /**< Turn off inversion */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x13);
    SysTick_Delay10ms(10);

    /**< Turn on display */
    TFT_SendCommand(Copy_TftDisplay, Copy_SpiPeripheral, 0x29);
    SysTick_Delay10ms(10);
    /**<=========================================================================================================================*/
    /*******************************************< End of ST7735S display configuration *******************************************/
    /**<=========================================================================================================================*/
}
/*Tft display char */
void TFT_WriteChar(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral, 
uint16_t Copy_XPosition, uint16_t Copy_YPosition, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;

    TFT_SetXYAddress(Copy_TftDisplay, Copy_SpiPeripheral,Copy_XPosition, Copy_YPosition);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[] = { color >> 8, color & 0xFF };
                TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral,*data);
            } else {
                uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
                TFT_SendData(Copy_TftDisplay, Copy_SpiPeripheral,*data);
            }
        }
    }
}
void TFT_Unselect(const TFT_Config_t *Copy_TftDisplay) {
    GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_CSPin.TFT_Port, Copy_TftDisplay->TFT_CSPin.TFT_Pin, GPIO_LOW); 
}
static void TFT_Select(const TFT_Config_t *Copy_TftDisplay) {
     GPIO_voidSet_Pin_value(Copy_TftDisplay->TFT_CSPin.TFT_Port, Copy_TftDisplay->TFT_CSPin.TFT_Pin, GPIO_HIGH); 
}
void TFT_WriteString(const TFT_Config_t *Copy_TftDisplay, SPI_handler Copy_SpiPeripheral,
uint16_t Copy_XPosition, uint16_t Copy_YPosition, char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
    TFT_Select(Copy_TftDisplay);

    while(*str) {
        if(Copy_XPosition + font.width >= TFT_DISPLAY_WIDTH) {
            Copy_XPosition = 0;
            Copy_YPosition += font.height;
            if(Copy_YPosition + font.height >= TFT_DISPLAY_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        TFT_WriteChar(Copy_TftDisplay, Copy_SpiPeripheral, Copy_XPosition,*str, Copy_YPosition,font, color, bgcolor);
        Copy_XPosition += font.width;
        str++;
    }

    TFT_Unselect(Copy_TftDisplay);
}

/**
 * @} TFT_Private_Functions
 */

/**<====================================================================================================================*/
/*******************************************< End of Functions Implementation *******************************************/
/**<====================================================================================================================*/

/** @} */ // End of TFT_Displays_program.c module.
