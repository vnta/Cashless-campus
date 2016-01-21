/*
	This program demonstrates the use of touch library(SdcTouch). It follows
	the trajectory of your touch with a line.
 
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
	lcd.clearScreen(LCD_COLOR_YELLOW);
	lcd.setForegroundColor(LCD_COLOR_DKGREEN);
	lcd.setPenWidth(2);
}

void loop() 
{
	int16_t xp = -1, yp, xn, yn;

	while(1)
	{
		if(touch.checkTouchContinuous())
		{
			xn = touch.getScrX();
			yn = touch.getScrY();

			if(xp > 0)
				lcd.drawLine(xp, yp, xn, yn);
			
			xp = xn;
			yp = yn;
		}
		else
		{
			xp = -1;
		}
	}
}
