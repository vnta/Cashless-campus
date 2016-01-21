/*
	This program demonstrates the use of touch library(SdcTouch). It realize
	an extremely simple drawing program with points, free-drawing lines, and
	color balls. 
 
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include <SdcLCD.h>
#include <SdcTouch.h>

#define COLOR_SCR_BACKGROUND		LCD_COLOR_BLACK
#define COLOR_MENU_BACKGROUND1		LCD_COLOR_BLACK
#define COLOR_MENU_BACKGROUND2		LCD_COLOR_DKGREY
#define COLOR_MENU_BORDER			LCD_COLOR_GREEN
#define COLOR_POINT					LCD_COLOR_RED
#define COLOR_LINE					LCD_COLOR_YELLOW
#define PENWIDTH_POINT				(2)
#define PENWIDTH_LINE				(2)
#define RADIUS_POINT				(6)
#define RADIUS_CIRCLE				(30)


SdcLCD lcd;
SdcTouch touch;

int16_t menu_vline, menu_hline1, menu_hline2;
int16_t x, y;

void drawMenu(uint8_t index)
{
	int16_t tx, ty;

	tx = lcd.getScreenWidth() - 1;
	ty = lcd.getScreenHeight() - 1;

	// background
	lcd.setForegroundColor(COLOR_MENU_BACKGROUND1);
	lcd.drawFilledRectangle(menu_vline, 0, tx, ty);


	lcd.setForegroundColor(COLOR_MENU_BACKGROUND2);
	if(index == 1)
	{
		lcd.drawFilledRectangle(menu_vline, 0, tx, menu_hline1);
	}
	else if(index == 2)
	{
		lcd.drawFilledRectangle(menu_vline, menu_hline1, tx, menu_hline2);
	}
	else if(index == 3)
	{
		lcd.drawFilledRectangle(menu_vline, menu_hline2, tx, ty);
	}


	// border lines
	lcd.setPenWidth(2);
	lcd.setForegroundColor(COLOR_MENU_BORDER);
	lcd.drawLine(menu_vline, 0, menu_vline, ty);
	lcd.drawLine(menu_vline, menu_hline1, tx, menu_hline1);
	lcd.drawLine(menu_vline, menu_hline2, tx, menu_hline2);

	// the first menu
	tx = menu_vline + ((tx - menu_vline)>>1);
	ty = (menu_hline1>>1);

	lcd.setPenWidth(PENWIDTH_POINT);
	lcd.setForegroundColor(COLOR_POINT);
	lcd.drawLine(tx - RADIUS_POINT, ty, tx + RADIUS_POINT, ty);
	lcd.drawLine(tx, ty - RADIUS_POINT, tx, ty + RADIUS_POINT);

	// the second menu
	lcd.setPenWidth(PENWIDTH_LINE);
	lcd.setForegroundColor(COLOR_LINE);
	lcd.drawLine(menu_vline + 15, menu_hline1 + 15,
		lcd.getScreenWidth() - 15, menu_hline2 - 15);

	// the third menu
	ty = ty + menu_hline2;
	lcd.setForegroundColor(LCD_COLOR_SKYBLUE);
	lcd.drawFilledCircle(tx, ty, (RADIUS_CIRCLE>>1));
}

void drawPoint()
{
	lcd.setPenWidth(PENWIDTH_POINT);
	lcd.setForegroundColor(COLOR_POINT);

	while(1)
	{
		touch.waitForSingleTouch();

		x = touch.getScrX();
		y = touch.getScrY();

		// menu touched. back to the loop();
		if(x > menu_vline) return;

		lcd.drawLine(x - RADIUS_POINT, y, x + RADIUS_POINT, y);
		lcd.drawLine(x, y - RADIUS_POINT, x, y + RADIUS_POINT);

		delay(200);
	}
}

void drawLine()
{
	int16_t xp = -1, yp;

	lcd.setPenWidth(PENWIDTH_LINE);
	lcd.setForegroundColor(COLOR_LINE);

	while(1)
	{
		if(touch.checkTouchContinuous())
		{
			x = touch.getScrX();
			y = touch.getScrY();
		
			// menu touched. back to the loop();
			if(x > menu_vline) return;

			if(xp > 0)
				lcd.drawLine(xp, yp, x, y);
			
			xp = x;
			yp = y;
		}
		else
		{
			xp = -1;
		}
	}
}

void drawRainbow()
{
	int16_t r = 255, g = 0, b = 0, index = 0;

	while(1)
	{
		if(touch.checkTouchContinuous())
		{
			x = touch.getScrX();
			y = touch.getScrY();

			// menu touched. back to the loop();
			if(x > menu_vline) return;
			
			lcd.setForegroundColor(LCD_COLOR(r,g,b));
			lcd.drawFilledCircle(x, y, RADIUS_CIRCLE);

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

void setup() 
{
	lcd.clearScreen(COLOR_SCR_BACKGROUND);

	// menu vertical line
	menu_vline = lcd.getScreenWidth() - 60;

	// menu horizontal lines
	menu_hline1 = lcd.getScreenHeight() / 3;
	menu_hline2 = menu_hline1 + menu_hline1;

	// screen untouched
	x = y = 0;

	drawMenu(0);
}


void loop() 
{
	// wait for menu touch
	while(x < menu_vline)
	{
		touch.waitForSingleTouch();

		x = touch.getScrX();
		y = touch.getScrY();
	}

	// clear screen
	lcd.clearScreen(COLOR_SCR_BACKGROUND);

	// draw menu and jump to the routine
	if(y < menu_hline1)
	{
		drawMenu(1);
		drawPoint();
	}
	else if(y < menu_hline2)
	{
		drawMenu(2);
		drawLine();
	}
	else 
	{
		drawMenu(3);
		drawRainbow();
	}
}
