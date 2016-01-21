/*
	Use this program to calibrate the touch screen. When reset, it shows three
	calibration points successively and takes user touch inputs. You can verify
	the parameters in the next screen. Calibration parameters are stored in the
	EEPROM, so you only need to run this program once.
 
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include <SdcLCD.h>
#include <SdcTouch.h>

SdcLCD lcd;
SdcTouch touch;

void calibrate()
{
	int16_t x, y;
	uint8_t index = 10;

	int32_t xt0,yt0,xt1,yt1,xt2,yt2;
	int32_t xd0,yd0,xd1,yd1,xd2,yd2;

	// draw the first calibration point
	xd0 = lcd.getScreenWidth()>>3;
	yd0 = lcd.getScreenHeight()>>3;

	lcd.setForegroundColor(LCD_COLOR_WHITE);
	lcd.drawLine(xd0-10, yd0, xd0+10, yd0);
	lcd.drawLine(xd0, yd0-10, xd0, yd0+10);

	// read the touch screen value
	touch.waitForSingleTouch();
	xt0 = (int32_t)touch.raw_x;
	yt0 = (int32_t)touch.raw_y;

	delay(200);
	
	// clean the first calibration point
	lcd.setForegroundColor(LCD_COLOR_DKGREEN);
	lcd.drawLine(xd0-10, yd0, xd0+10, yd0);
	lcd.drawLine(xd0, yd0-10, xd0, yd0+10);

	// draw the second calibration point
	xd1 = lcd.getScreenWidth()>>1;
	yd1 = lcd.getScreenHeight() - (lcd.getScreenHeight()>>3);

	lcd.setForegroundColor(LCD_COLOR_WHITE);
	lcd.drawLine(xd1-10, yd1, xd1+10, yd1);
	lcd.drawLine(xd1, yd1-10, xd1, yd1+10);

	// read the touch screen value
	touch.waitForSingleTouch();
	xt1 = (int32_t)touch.raw_x;
	yt1 = (int32_t)touch.raw_y;

	delay(200);

	// clean the second calibration point
	lcd.setForegroundColor(LCD_COLOR_DKGREEN);
	lcd.drawLine(xd1-10, yd1, xd1+10, yd1);
	lcd.drawLine(xd1, yd1-10, xd1, yd1+10);

	// draw the third calibration point
	xd2 = lcd.getScreenWidth() - (lcd.getScreenWidth()>>3);
	yd2 = lcd.getScreenHeight()>>1;

	lcd.setForegroundColor(LCD_COLOR_WHITE);
	lcd.drawLine(xd2-10, yd2, xd2+10, yd2);
	lcd.drawLine(xd2, yd2-10, xd2, yd2+10);

	// read the touch screen value
	touch.waitForSingleTouch();
	xt2 = (int32_t)touch.raw_x;
	yt2 = (int32_t)touch.raw_y;

	delay(200);

	// clean the third calibration point
	lcd.setForegroundColor(LCD_COLOR_DKGREEN);
	lcd.drawLine(xd2-10, yd2, xd2+10, yd2);
	lcd.drawLine(xd2, yd2-10, xd2, yd2+10);

	// calculate the calibrationparameters
	touch.p[0] = (xd0 - xd2)*(yt1 - yt2) - (xd1 - xd2)*(yt0 - yt2);
	touch.p[1] = (xt0 - xt2)*(xd1 - xd2) - (xd0 - xd2)*(xt1 - xt2);
	touch.p[2] = yt0*(xt2*xd1 - xt1*xd2) + yt1*(xt0*xd2 - xt2*xd0) 
		+ yt2*(xt1*xd0 - xt0*xd1);
	touch.p[3] = (yd0 - yd2)*(yt1 - yt2) - (yd1 - yd2)*(yt0 - yt2);
	touch.p[4] = (xt0 - xt2)*(yd1 - yd2) - (yd0 - yd2)*(xt1 - xt2);
	touch.p[5] = yt0*(xt2*yd1 - xt1*yd2) + yt1*(xt0*yd2 - xt2*yd0) 
		+ yt2*(xt1*yd0 - xt0*yd1);
	touch.p[6] = (xt0 - xt2)*(yt1 - yt2) - (xt1 - xt2)*(yt0 - yt2);

	// save parameters
	touch.saveParameters();

	delay(500);

	lcd.clearScreen(LCD_COLOR_RED);
	lcd.setForegroundColor(LCD_COLOR_YELLOW);

	// test 10 times
	while(index)
	{
		touch.waitForSingleTouch();

		x = touch.getScrX();
		y = touch.getScrY();

		lcd.drawLine(x-10, y, x+10, y);
		lcd.drawLine(x, y-10, x, y+10);

		delay(300);

		index--;
	}

	lcd.clearScreen(LCD_COLOR_BLACK);
}


void setup() 
{
	lcd.clearScreen(LCD_COLOR_DKGREEN);

	calibrate();
}

void loop() 
{
}
