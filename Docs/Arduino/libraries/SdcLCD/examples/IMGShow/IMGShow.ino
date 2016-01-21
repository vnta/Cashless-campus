/*
	This example shows how to use SdcLCD and SdcSDFS at the same time to 
	read native image files(IMG) and draw their images onto the LCD screen.
	Since there is no bitmap conversion (24bit to 16bit) involved, this native
	format is more efficient in both size and speed.

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

void setup()
{
	char f[4];

	// pushbutton setting
	digitalWrite(pushButton, 1);  // internal pull-up activated
	pinMode(pushButton, INPUT);  // pushbutton input
  
	// LCD initialization
	lcd.clearScreen(LCD_COLOR_DKGREY);  

	// set file search filter to search IMG files
	f[0] = 'I'; f[1] = 'M'; f[2] = 'G'; f[3] = 0x00;
	fs.setFileFilter(f);
}

void imgDraw(void)
{
	unsigned int br;
	uint8_t buff[512]; // this number is important
	int32_t width, height;
	uint16_t x, y, bpp, k, pxlCount;
	PLNFHEADER pLnf;

	// IMG file found
	if(fs.openNextFile() == FR_OK)
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
			return;
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
    imgDraw();
  }
}


