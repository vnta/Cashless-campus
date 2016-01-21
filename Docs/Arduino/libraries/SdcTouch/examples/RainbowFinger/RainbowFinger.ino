/*
	This program demonstrates the use of touch library(SdcTouch). It follows
	your finger with a varing color circle.
 
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
	lcd.clearScreen(LCD_COLOR_BLACK);
}

void loop() 
{
	int16_t x, y;
	int16_t r = 255, g = 0, b = 0, index = 0;

	while(1)
	{
		if(touch.checkTouchContinuous())
		{
			x = touch.getScrX();
			y = touch.getScrY();

			lcd.setForegroundColor(LCD_COLOR(r,g,b));
			lcd.drawFilledCircle(x, y, 30);

			// color rotation
			// RED to GREEN
			if(index  == 0)
			{
				r -= 10;
				g += 10;
				
				if((r < 0)||(g > 255))
				{
					r = 0;
					g = 255;
					b = 0;
					index = 1;
				}
			}
			// GREEN to BLUE
			else if(index == 1)
			{
				g -= 10;
				b += 10;

				if((g < 0)||(b > 255))
				{
					r = 0;
					g = 0;
					b = 255;
					index = 2;
				}
			}
			// BLUE to RED
			else if(index == 2)
			{
				b -= 10;
				r += 10;

				if((b < 0)||(r > 255))
				{
					r = 255;
					g = 0;
					b = 0;
					index = 0;
				}
			}
		}
	}
}
