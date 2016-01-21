/**
	\defgroup	ARDUINO_SDCLCD
	\ingroup	ARDUINO
	\brief		LCD interface for Arduino Mega and Uno
	\author		Sungjune Lee
	\date		Thu May 10 16:41:12 EDT 2012

	\verbatim
	Programming Example
	==============================================================================
	// initialization
	SDCLCD	lcd;
	
	// clear screen with black background
	lcd.clearScreen(LCD_COLOR_BLACK);

	// set pen width
	lcd.setPenWidth(2);

	// set foreground color
	lcd.setForegroundColor(LCDCOLOR(200, 120, 40));

	// set background color
	lcd.setBackgroundColor(LCD_COLOR_CYAN);

	// draw a shape
	lcd.drawFilledRoundRectangle(10, 10, 200, 100, 5);

	// select a font
	lcd.setFont(&DroidSerif_16);

	// draw a string
	lcd.drawString(20, 25, "Droid Serif 16 point");


	Version History
	==============================================================================
	v0.4: (28 May 2012) drawNumber() function added.
						setBlockArea() function added.
						drawBmpBlock() function added.
						drawRawBlock() function added.
	v0.3: (16 May 2012) Font related files are moved to the utility directory
						No dependency on Arduino code is confirmed.	
						Image display routine added(SDCSD class).
						Change class name and directory name.
	v0.2: (10 May 2012) Initial release.

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
#ifndef SDCLCD_h
#define SDCLCD_h

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <utility/lcdfonts.h>
#include "ImgFormats.h"

// main board: this regards the interface for the LCD panel.
//#define MBOARD_UNO					1	// 8bit bit-banging
#define MBOARD_MEGA2560				1	// 8bit memory interface
//#define MBOARD_CMEGA128				1	// 8bit memory interface
//#define MBOARD_CKMAX32				1	// 16bit memory interface

// LCD type: each LCD panel has its own parameters
//#define LCD_GR2400					1	// 2.4inch - ILI9325
#define LCD_FGD280					1	// 2.8inch - ST7781
//#define LCD_S40109					1	// 4.3inch - SSD1963

// display direction: LCD controller can change display direction 
//#define DIR_LANDSCAPE				1
#define DIR_PORTRAIT				1

// LCD type
#if LCD_GR2400 // sunyee 2.4 + ili9325
  #if DIR_PORTRAIT
  #define SCR_WIDTH					240
  #define SCR_HEIGHT				320
  #elif DIR_LANDSCAPE
  #define SCR_WIDTH					320
  #define SCR_HEIGHT				240
  #endif
  #define ILI9325					1
  #define TOUCH_SENSOR				1
#elif LCD_FGD280 // unknown 2.8 + st7781
  #if DIR_PORTRAIT
  #define SCR_WIDTH					240
  #define SCR_HEIGHT				320
  #elif DIR_LANDSCAPE
  #define SCR_WIDTH					320
  #define SCR_HEIGHT				240
  #endif
  #define ST7781					1
  #define TOUCH_SENSOR				1
#elif LCD_S40109 // innolux 4.3 + ssd1963
  #define SCR_WIDTH					480
  #define SCR_HEIGHT				272
  #define SSD1963					1
  #define TOUCH_SENSOR				1
#endif


class SdcLCD {
public:
	// constructor
	SdcLCD():_penWidth(1),\
			_foregroundColor(LCD_COLOR_WHITE),\
			_backgroundColor(LCD_COLOR_BLACK),\
			_screenWidth(SCR_WIDTH),\
			_screenHeight(SCR_HEIGHT),\
			_font(0)
	{
		initLCD();
	};

	void backlightOn(bool flag);
	void clearScreen(LCDCOLOR color);
	void setColors(LCDCOLOR color);
	void setForegroundColor(LCDCOLOR color);
	void setBackgroundColor(LCDCOLOR color);
	void setPenWidth(int16_t width);
	void drawPixel(int16_t x,int16_t y);
	void drawPixel(int16_t x,int16_t y, LCDCOLOR color);
	void drawLine(int16_t x1,int16_t y1,int16_t x2,int16_t y2);
	void drawRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2);
	void drawFilledRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2);
	void drawCircle(int16_t x,int16_t y,int16_t r);
	void drawFilledCircle(int16_t x,int16_t y,int16_t r);
	void drawEllipse(int16_t x,int16_t y,int16_t a,int16_t b);
	void drawFilledEllipse(int16_t x,int16_t y,int16_t a,int16_t b);
	void drawQuadrant(int16_t x,int16_t y,int16_t r,int16_t quad);
	void drawFilledQuadrant(int16_t x,int16_t y,int16_t r,int16_t quad);
	void drawRoundRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t r);
	void drawFilledRoundRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t r);

	int16_t getScreenWidth(void);
	int16_t getScreenHeight(void);
	void setFont(LCDFONT *pFont);

	LCDFONT* getFont(void);
	uint16_t drawCharacter(int16_t x, int16_t y, char ch);
	uint16_t drawString(int16_t x, int16_t y, char *str);
	uint16_t drawNumber(int16_t x, int16_t y, unsigned long num);

	void setBlockArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void drawBmpBlock(uint8_t* buff, uint16_t nPixel);
	void drawRawBlock(uint8_t* buff, uint16_t nPixel);

private:
	int16_t _penWidth;
	const int16_t _screenWidth;
	const int16_t _screenHeight;
	LCDCOLOR _foregroundColor;
	LCDCOLOR _backgroundColor;
	LCDFONT* _font;

	void initLCD(void);
	uint16_t drawGlyph(int16_t x, int16_t y, const uint8_t *idx);
};

#endif	// SDCLCD_h


/**
	\}
 */

