/*
	This example shows how to use SdcLCD and SdcSDFS at the same time to 
	read BMP files and draw their images onto the LCD screen. It enumerates
	the BMP files on the root directory and displays them on the LCD one by 
	one.

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include <SdcSDFS.h>
#include <SdcLCD.h>
#include <ImgFormats.h>

SdcLCD lcd;	// LCD object on the heap
SdcSDFS fs;	// SD file system object on the heap

const int pushButton = 12;

#define ABS(x)			((x)>0 ? (x):(-x))

void setup()
{
	char f[4];

	// pushbutton setting
	digitalWrite(pushButton, 1);  // internal pull-up activated
	pinMode(pushButton, INPUT);  // pushbutton input
  
	// LCD initialization
	lcd.clearScreen(LCD_COLOR_DKGREY);  

	// set file search filter to search BMP files
	f[0] = 'B'; f[1] = 'M'; f[2] = 'P'; f[3] = 0x00;
	fs.setFileFilter(f);
}

void bmpDraw(void)
{
	unsigned int br;
	uint8_t buff[512];
	int32_t width, height;
	uint16_t x, y, bpp, k, pxlCount;

	PBMPHEADER pBmp;

	// a BMP file found
	if(fs.openNextFile() == FR_OK)
	{
		fs.readFile(&buff, sizeof(BMPHEADER), &br);
		pBmp = (PBMPHEADER)buff;

		// read BMP header
		if(pBmp->bfType == BMP_SIGNATURE)
		{
			width = pBmp->biWidth;
			height = pBmp->biHeight;
			bpp = pBmp->biBitCount;
		}
		// invalid BMP file
		else
		{
			return;
		}

		// only 24bpp is supported for now
		if((bpp <= 8)||(bpp == 16))
		{
			return;
		}

		width = ABS(width);
		height = ABS(height);

		// locate the image in the center of the screen
		x = (lcd.getScreenWidth() - width)>>1;
		y = (lcd.getScreenHeight() - height)>>1;

		// set block area
		lcd.setBlockArea(x, y, x + width -1, y + height -1);

		// calculate the number of the pixel to draw for each block read
		pxlCount = sizeof(buff) - (sizeof(buff))%3;

		while(1)
		{
			fs.readFile(buff, pxlCount, &br);
			lcd.drawBmpBlock(buff, br/3);

			if(br != pxlCount) break;
		}
	}
	// no more file to display
	else
	{
		// rewind the directory entry
		fs.openDirectory("/");
	}
}


void loop(void) 
{
  if(!digitalRead(pushButton))
  {
    bmpDraw();
  }
}


