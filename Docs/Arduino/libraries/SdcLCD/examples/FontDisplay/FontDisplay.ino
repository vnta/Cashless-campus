/*
	This program demonstrates the use of fonts. You can find the information
	about how to create your own fonts in the blog:ArduinoExplained.blogspot.com

	WARNING: Due to the memory limitation, this routine may not work on UNO
	or any other ATmega328 based board.

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
 
#include <SdcLCD.h>

#define MAX_KEY_NUM    1
const int buttonPin = 12;

// initialize the class
SdcLCD lcd;

void setup() {
  // initial screen clear with dark grey color background
  lcd.clearScreen(LCD_COLOR_DKGREY);
  
  // choose a font: due to the limited memory of ATmega, you can use
  // only one font.
  lcd.setFont(&DroidSerif_16);  
    
  // initialize the pushbutton with internal pullup
  digitalWrite(buttonPin, 1);
  pinMode(buttonPin, INPUT);
}

void fontTest(uint8_t index)
{
  
  //
  // the first page
  //
  if(index == 0)
  {
    lcd.clearScreen(LCD_COLOR_DKGREEN);
  
    // select foreground and background color   
    lcd.setBackgroundColor(LCD_COLOR_ORANGE);
    lcd.setForegroundColor(LCD_COLOR_CYAN);
    
    // draw string
    lcd.drawString(10,30, "Droid Serif 16 point font");

     // change foreground and background color   
    lcd.setBackgroundColor(LCD_COLOR_GREEN);   
    lcd.setForegroundColor(LCD_COLOR_RED);
     
    // draw string
    lcd.drawString(10,70, "converted from Linux box");    
    
     // change foreground and background color   
    lcd.setBackgroundColor(LCD_COLOR_BLUE);   
    lcd.setForegroundColor(LCD_COLOR_YELLOW);
     
    // draw string
    lcd.drawString(10,110, "with various fg / bg colors");
    
    // transparent background is possible    
    lcd.setBackgroundColor(LCD_COLOR_TRANSPARENT);
    lcd.setForegroundColor(LCD_COLOR_GREEN);
    
    // looks nice
    lcd.drawString(10,150, "Transparent background is");
    lcd.drawString(10,190, "also available.");    
   
  }
  //
  // 2nd page
  //
  else if(index == 1)
  { 
    lcd.clearScreen(LCD_COLOR_DKGREY);
    
    lcd.setForegroundColor(LCD_COLOR_WHITE);    
    // draw more string
    lcd.drawString(5,30, "You can convert any desktop");
    lcd.drawString(5,70, "font into this LCD raster font");    
    lcd.drawString(5,110, "For more information, visit");
    lcd.setForegroundColor(LCD_COLOR_YELLOW);     
    lcd.drawString(5,150, "ArduinoExplained.blogspot.ca");
    lcd.setForegroundColor(LCD_COLOR_WHITE);     
    lcd.drawString(5,190, "Thanks for watching.");    
  } 
  
  // this delay is for the key debouncing
  delay(300);
  
}

void loop() {
  
  static uint8_t key = 0;

  // execute the test functions one at a time
  if(!digitalRead(buttonPin))
  {

    fontTest(key++);
    if(key > MAX_KEY_NUM)key = 0;
    
    // if lcdTest does not provide enough debouncing delay 
    // then you need one here.
  }

}
