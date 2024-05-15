/***************************************************
  This is a library for the Adafruit 1.8" SPI display.
This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
  Ported to tm4c123gh6pm by Julian Fell.
 ****************************************************/

#ifndef _ST7735H_
#define _ST7735H_


//*****************************************************************************
//
// APIS Definitions
//
//*****************************************************************************
extern void ST7735_Init(void);
extern void ST7735_drawPixel(uint8 x, uint8 y, uint16 colour_16_BIT);
void ST7735_fillRect( uint16 x, uint16 y, uint16 w, uint16 h,uint16 colour);
void Define_Window(uint8 X_S ,uint8 Y_S ,uint8 X_E ,uint8 Y_E);
void ST7735_Draw_image( uint8* image_8bit_rep_pntr);
void ST7735_drawChar(uint16 x, uint16 y, unsigned char c,uint16 colour, uint16 bg, uint8 size);
void ST7735_drawString(char *c, uint16 x, uint16 y, uint16 colour, uint16 bg, uint8 size);
#endif
