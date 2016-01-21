/*
	Before using this library, you should check the definitions in
	the library source header(SdcLCD.h) for the main board type and
	LCD type as well. For example, Uno/Duemilanove or their clones use

	 #define MBOARD_UNO        1

	And for the Mega/Mega1280/Mega2560, use

	 #define MBOARD_MEGA2560   1

	Both landscape mode and portrait mode are supported. So use either

	 #define DIR_LANDSCAPE     1

	or 

	 #define DIR_PORTRAIT      1

	LCD type definition is also requied

	 #define LCD_GR2400        1

	The LCD type mainly refers to the LCD controller chips and 
	characteristics of the LCD panel such as dimensions. You may
	not find much difficulties in using your own LCD if it has the 
	same controller used in the libray, such as ILI9325 or ST7781.

	For the hardware connections between your board and LCD panel, 
	please visit www.sdcontrols.net and find reference schematics.

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include <SdcLCD.h>

// initialize the SdcLCD class
SdcLCD lcd;

void setup() {
  
  // initial screen clear with red background
  lcd.clearScreen(LCD_COLOR_RED);
  
}

void loop() {

}
