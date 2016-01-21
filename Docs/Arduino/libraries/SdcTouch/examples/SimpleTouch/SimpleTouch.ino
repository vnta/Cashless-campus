/*
	This program demonstrates the use of touch library(SdcTouch). It draws a
	small cross at the point of your touch.
 
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include <SdcLCD.h>
#include <SdcTouch.h>

SdcLCD lcd;
SdcTouch touch;

void setup() 
{
	lcd.clearScreen(LCD_COLOR_RED);
	lcd.setForegroundColor(LCD_COLOR_YELLOW);
	lcd.setPenWidth(2);
}

void loop() 
{
	int16_t x, y;

	while(1)
	{
		touch.waitForSingleTouch();

		x = touch.getScrX();
		y = touch.getScrY();

		lcd.drawLine(x - 6, y, x + 6, y);
		lcd.drawLine(x, y - 6, x, y + 6);

		delay(300);
	}
}
