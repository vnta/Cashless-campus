/*
	This demonstrate SD file handling and block write operation on LCD. First,
	BMP files on the SD card are enumerated and displayed on the LCD one by
	one. Then the same operation is repeated to the LNF(LCD Native Format) 
	image files. At the end of each slideshow, elapsed time is displayed to
	compare the speed of the two operation.

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
#define	ABS(x)			(((x)>0)?(x):(-x))

void setup()
{

	// pushbutton setting
	digitalWrite(pushButton, 1);  // internal pull-up activated
	pinMode(pushButton, INPUT);  // pushbutton input
  
	// LCD initialization
	lcd.clearScreen(LCD_COLOR_DKGREY);  

	// Select font
	lcd.setFont(&Ubuntu_16);
	lcd.setForegroundColor(LCD_COLOR_YELLOW);
	lcd.setBackgroundColor(LCD_COLOR_TRANSPARENT);
}

uint8_t bmpDraw(void)
{
	char f[4];
	unsigned int br;
	uint8_t buff[512], icount;
	int32_t width, height;
	uint16_t x, y, bpp, k, pxlCount;

	PBMPHEADER pBmp;

	// set file search filter to search BMP files
	f[0] = 'B'; f[1] = 'M'; f[2] = 'P'; f[3] = 0x00;
	fs.setFileFilter(f);

	// rewind the directory entry
	fs.openDirectory("/");

	// enumerate BMP files
	icount = 0;
	while(fs.openNextFile() == FR_OK)
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
			return 0;
		}

		// only 24bpp is supported for now
		if((bpp <= 8)||(bpp == 16))
		{
			return 0;
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
		icount++;
	}

	return icount;
}

uint8_t imgDraw(void)
{
	char f[4];
	unsigned int br;
	uint8_t buff[512], icount;
	int32_t width, height;
	uint16_t x, y, bpp, k, pxlCount;
	PLNFHEADER pLnf;

	// set file search filter to search IMG files
	f[0] = 'I'; f[1] = 'M'; f[2] = 'G'; f[3] = 0x00;
	fs.setFileFilter(f);

	// rewind the directory entry
	fs.openDirectory("/");

	// enumerate IMG files
	icount = 0;
	while(fs.openNextFile() == FR_OK)
	{
		fs.readFile(&buff, sizeof(LNFHEADER), &br);
		pLnf = (PLNFHEADER)buff;

		// read LNF header
		if(pLnf->lnfID == LNF_SIGNATURE)
		{
			width = pLnf->width;
			height = pLnf->height;;
		}
		// invalid IMG file
		else
		{
			return 0;
		}

		// locate the image in the center of the screen
		x = (lcd.getScreenWidth() - width)>>1;
		y = (lcd.getScreenHeight() - height)>>1;

		// set block area
		lcd.setBlockArea(x, y, x + width -1, y + height -1);

		// read the first (partial) block, this will keep the following
		// block reading aligned with both FatFs block boundary as well
		// as SD card block boundary.
		fs.readFile(buff, sizeof(buff) - sizeof(LNFHEADER), &br);
		lcd.drawRawBlock(buff, (br>>1));

		// repeat it till the end of file
		while(1)
		{
			fs.readFile(buff, sizeof(buff), &br);
			lcd.drawRawBlock(buff, (br>>1));

			if(br != sizeof(buff)) break;
		}

		icount++;
	}

	return icount;
}



void loop(void) 
{
	uint8_t num;
	static uint8_t flag = 0;
	unsigned long time, delta;
	char digit, str[10] = {0x00};

	if(!digitalRead(pushButton))
	{
		time = millis();

		if(flag%2)
		{
			num = imgDraw();
			delta = millis() - time;
			lcd.clearScreen(LCD_COLOR_DKGREEN);
			lcd.drawString(30, 50, "LNF image displayed:");
		}
		else
		{
			num = bmpDraw();
			delta = millis() - time;
			lcd.clearScreen(LCD_COLOR_DKGREEN);
			lcd.drawString(30, 50, "BMP image displayed:");
		}

		lcd.drawNumber(250, 50, num);

		lcd.drawString(30, 100, "Time elapsed(msec):");
		lcd.drawNumber(240, 100, delta);

		flag++;
	}
}


