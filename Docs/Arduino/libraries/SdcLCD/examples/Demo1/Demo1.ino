/*
	This program demonstrates the use of various functions provided by the 
	library. Each function comes with brief explanation.

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
 
#include <SdcLCD.h>

#define MAX_KEY_NUM    16
const int buttonPin = 12;

// initialize the lcd
SdcLCD lcd;

void setup() {
  // initial clear
  lcd.clearScreen(LCD_COLOR_DKGREY);
  
  // choose font
  lcd.setFont(&DroidSerif_16);    
  
  // initialize the pushbutton with internal pullup
  digitalWrite(buttonPin, 1);
  pinMode(buttonPin, INPUT);
}


void fontTest(uint8_t index)
{
  uint16_t i,j;
  int16_t x1, y1, x2, y2, delx, dely;
  uint16_t dif_red, dif_green, dif_blue;
  uint16_t col_red, col_green, col_blue;
  
  LCDCOLOR colors[12] =
  {
      LCD_COLOR_RED,
      LCD_COLOR_ORANGE,
      LCD_COLOR_GREEN,
      LCD_COLOR_BLUE,
      LCD_COLOR_MAGENTA,
      LCD_COLOR_CYAN,
      LCD_COLOR_YELLOW,
      LCD_COLOR_DKGREEN,
      LCD_COLOR_WHITE,
      LCD_COLOR_LTGREY,
      LCD_COLOR_DKGREY,
      LCD_COLOR_BLACK
  };  
  
  //
  // PAGE 1: introduction (continue)
  //
  if(index == 0)
  {
    // set background
    lcd.clearScreen(LCD_COLOR_DKGREY);
    
    // select foreground and background color of the font
    lcd.setBackgroundColor(LCD_COLOR_ORANGE);
    lcd.setForegroundColor(LCD_COLOR_CYAN);
    
    // draw a string
    lcd.drawString(50,30,  "SDCLCD LIBRARY");
    
     // change foreground and background color   
    lcd.setBackgroundColor(LCD_COLOR_TRANSPARENT);   
    lcd.setForegroundColor(LCD_COLOR_GREEN);
     
    // draw more strings
    lcd.drawString(10,70,  "Introducing an open source");    
    lcd.drawString(10,110, "LCD graphics library, which");
    lcd.drawString(10,150, "you can use with your");
    lcd.drawString(10,190, "Arduino UNO/MEGA");    
  }
  //
  // PAGE 2: introduction (continued)
  //
  else if(index == 1)
  { 
    // set background
    lcd.clearScreen(LCD_COLOR_DKGREEN);
    // set foreground color of the font
    lcd.setForegroundColor(LCD_COLOR_WHITE);  
    
    // draw strings
    lcd.drawString(5,30,  "For the LCD shield, you can");
    lcd.drawString(5,70,  "build your own shield from");    
    lcd.drawString(5,110, "the scratch or you can use");    
    lcd.drawString(5,150, "off-the-shelf LCD shields");    
    lcd.drawString(5,190, "with simple modifications.");    
  } 
  //
  // PAGE 3: introduction (continued)
  //
  else if(index == 2)
  { 
    // set background
    lcd.clearScreen(LCD_COLOR_YELLOW);
    // set foreground color of the font
    lcd.setForegroundColor(LCD_COLOR_RED);  
    
    // draw strings
    lcd.drawString(5,30,  "Library comes with useful");
    lcd.drawString(5,70,  "graphic primitives and it");    
    lcd.drawString(5,110, "supports both external mem.");    
    lcd.drawString(5,150, "interface for Mega and");    
    lcd.drawString(5,190, "bit-banging for UNO.");    
  }   
  //
  // PAGE 4: introduction (continued)
  //
  else if(index == 3)
  { 
    // set background
    lcd.clearScreen(LCD_COLOR_BLUE);
    // set foreground color of the font
    lcd.setForegroundColor(LCD_COLOR_WHITE);  
    
    // draw strings
    lcd.drawString(5,30,  "You can draw lines and shpes");
    lcd.drawString(5,70,  "with various colors and line");    
    lcd.drawString(5,110, "thickness. It is easy to use.");    
    lcd.drawString(5,150, "And routines are FAST!!!");    
    lcd.drawString(5,190, "Let's see some demos.");    
  } 
  //  
  // PAGE 5: single pixel width lines
  //
  else if(index == 4)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
  
    delx = lcd.getScreenWidth()>>3;
    dely = lcd.getScreenHeight()>>3;    

    // penWidth
    lcd.setPenWidth(1);
    // foreground color
    lcd.setForegroundColor(LCD_COLOR_GREEN);

    // lines between vertical points
    x1 = delx;
    x2 = lcd.getScreenWidth() - delx;
    y1 = dely;

    for( i = 1; i < 8; i++ )
    {
      y2 = dely;
      for( j = 1; j < 8; j++ )
      {
        lcd.drawLine(x1, y1, x2, y2);
        y2 += dely;
      }
      y1 += dely;
    }

    // lines between horizontal points
    lcd.setForegroundColor(LCD_COLOR_BLUE);
    y1 = dely;
    y2 = lcd.getScreenHeight() - dely;
    x1 = delx;

    for( i = 1; i < 8; i++ )
    {
      x2 = delx;
      for( j = 1; j < 8; j++ )
      {
        lcd.drawLine(x1, y1, x2, y2);
        x2 += delx;
      }
      x1 += delx;
    }
  }
  //
  // PAGE 6:  multipixel width lines
  //
  else if(index == 5)
  {    
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    dely = (lcd.getScreenHeight() >> 3);

    x1 = 20;
    x2 = lcd.getScreenWidth() - 20;
    y1 = dely;

    for(i = 0; i < 7; i++)
    {
      lcd.setPenWidth((i<<1) + 1);
      lcd.setForegroundColor(colors[i]);
      lcd.drawLine(x1, y1, x2, y1);

      y1 += dely;
    }
  }  
  //
  // PAGE 7: rectangles with various sizes and line thicknesses
  //
  else if(index == 6)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    delx = lcd.getScreenWidth()>>4;
    dely = lcd.getScreenHeight()>>4;
    
    x1 = delx;
    y1 = dely;
    x2 = lcd.getScreenWidth() - delx;
    y2 = lcd.getScreenHeight() - dely;
    
    for(i = 0; i < 7; i++)
    {
      lcd.setPenWidth((i<<1) + 1);      
      lcd.setForegroundColor(colors[i]);
      lcd.drawRectangle(x1,y1,x2,y2);
      
      x1 += delx;
      y1 += dely;
      x2 -= delx;
      y2 -= dely;
    }
  }  
  //
  // PAGE 8: circles with various sizes and line thickness
  //
  else if(index == 7)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    if(lcd.getScreenWidth() < lcd.getScreenHeight())
    {
      delx = (lcd.getScreenWidth()>>1) - 1;
      dely = lcd.getScreenWidth()>>4;
    }
    else
    {
      delx = (lcd.getScreenHeight()>>1) - 1;
      dely = lcd.getScreenHeight()>>4;      
    }
    
    // center and radius
    x1 = lcd.getScreenWidth()>>1;
    y1 = lcd.getScreenHeight()>>1;
    y2 = delx;

    for(i = 0; i < 7; i++)
    {
      lcd.setPenWidth((i<<1) + 1);
      lcd.setForegroundColor(colors[i]);

      lcd.drawCircle(x1, y1, y2);

      y2 -= dely;
    }  
  }  
  //
  // PAGE 9: ellipses with various sizes and line thickness
  //
  else if(index == 8)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    delx = (lcd.getScreenWidth()>>4);
    dely = (lcd.getScreenHeight()>>4);
    
    // center and radius
    x1 = lcd.getScreenWidth()>>1;
    y1 = lcd.getScreenHeight()>>1;

    x2 = (lcd.getScreenWidth()>>1) - 1;
    y2 = (lcd.getScreenHeight()>>1) - 1;

    for(i = 0; i < 7; i++)
    {
      lcd.setPenWidth((i<<1) + 1);
      lcd.setForegroundColor(colors[i]);

      lcd.drawEllipse(x1, y1, x2, y2);

      x2 -= delx;
      y2 -= dely;
    }
  }  
  //
  // PAGE 10: more introduction
  //
  else if(index == 9)
  { 
    // set background
    lcd.clearScreen(LCD_COLOR_DKGREY);
    // set foreground color of the font
    lcd.setForegroundColor(LCD_COLOR_CYAN);  
    
    // draw strings
    lcd.drawString(5,30,  "Shapes also can be drawn");
    lcd.drawString(5,70,  "with filled inside.");   
    lcd.drawString(5,110, "And thanks to the algorithm");     
    lcd.drawString(5,150, "it is fast too.");     
  }  
  //
  // PAGE 11: filled rectangles
  //
  else if(index == 10)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    delx = lcd.getScreenWidth()>>4;
    dely = lcd.getScreenHeight()>>4;
    
    x1 = delx;
    y1 = dely;
    x2 = lcd.getScreenWidth() - delx;
    y2 = lcd.getScreenHeight() - dely;
    
    for(i = 0; i < 7; i++)
    {
      lcd.setForegroundColor(colors[i]);
      lcd.drawFilledRectangle(x1,y1,x2,y2);
      
      x1 += delx;
      y1 += dely;
      x2 -= delx;
      y2 -= dely;
    }
  }  
  //
  // PAGE 12: solid circles
  //
  else if(index == 11)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    if(lcd.getScreenWidth() < lcd.getScreenHeight())
    {
      delx = (lcd.getScreenWidth()>>1) - 1;
      dely = lcd.getScreenWidth()>>4;
    }
    else
    {
      delx = (lcd.getScreenHeight()>>1) - 1;
      dely = lcd.getScreenHeight()>>4;      
    }

    // center and radius
    x1 = lcd.getScreenWidth()>>1;
    y1 = lcd.getScreenHeight()>>1;
    y2 = delx;

    for(i = 0; i < 7; i++)
    {
      lcd.setForegroundColor(colors[i]);
      lcd.drawFilledCircle(x1, y1, y2);

      y2 -= dely;
    }
  }  
  //
  // PAGE 13:solid ellipses
  //
  else if(index == 12)
  {
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    delx = (lcd.getScreenWidth()>>4);
    dely = (lcd.getScreenHeight()>>4);

    // center and radius
    x1 = lcd.getScreenWidth()>>1;
    y1 = lcd.getScreenHeight()>>1;

    x2 = (lcd.getScreenWidth()>>1) - 1;
    y2 = (lcd.getScreenHeight()>>1) - 1;

    for(i = 0; i < 7; i++)
    {
      lcd.setForegroundColor(colors[i]);
      lcd.drawFilledEllipse(x1, y1, x2, y2);

      x2 -= delx;
      y2 -= dely;
    }
  }  
  //
  // PAGE 14: even more introduction
  //
  else if(index == 13)
  {
    // set background
    lcd.clearScreen(LCD_COLOR_BLACK);
    // set foreground color of the font
    lcd.setForegroundColor(LCD_COLOR_SKYBLUE);  
    
    // draw strings
    lcd.drawString(5,30,  "Did I memtion that you also");
    lcd.drawString(5,70,  "have round rectangles which");   
    lcd.drawString(5,110, "is quite useful when drawing");     
    lcd.drawString(5,150, "buttons?");       
  }
  //
  // PAGE 15: button demo
  //
  else if(index == 14)
  {
    // set background
    lcd.clearScreen(LCD_COLOR_BLACK);
    
    // draw buttons
    lcd.setForegroundColor(LCD_COLOR_DKGREEN);    
    lcd.drawFilledRoundRectangle(40,100,120,140,10);
    lcd.drawFilledRoundRectangle(200,100,280,140,10);
    
    // with boundaries
    lcd.setPenWidth(3);
    lcd.setForegroundColor(LCD_COLOR_GREEN);    
    lcd.drawRoundRectangle(40,100,120,140,10);
    lcd.drawRoundRectangle(200,100,280,140,10);
    
    // draw button text
    lcd.setBackgroundColor(LCD_COLOR_TRANSPARENT);
    lcd.setForegroundColor(LCD_COLOR_ORANGE);
    lcd.drawString(60,110,"ON");    
    lcd.setForegroundColor(LCD_COLOR_RED);    
    lcd.drawString(220,110,"OFF");    
    
  }
  //
  // PAGE 16: introduction to fonts
  //
  else if(index == 15)
  {
    lcd.clearScreen(LCD_COLOR_DKGREEN);     
      
    lcd.setBackgroundColor(LCD_COLOR_TRANSPARENT);
    lcd.setForegroundColor(LCD_COLOR_GREEN);
    
    lcd.drawString(5,30,  "When it comes to fonts, you");
    lcd.drawString(5,70,  "can convert any desktop font");   
    lcd.drawString(5,110, "into this LCD raster font");     
    lcd.drawString(5,150, "using a font conversion");      
    lcd.drawString(5,190, "utility.");    
  }
  //
  // PAGE 17: font demo
  //
  else if(index == 16)
  {    
    lcd.clearScreen(LCD_COLOR_DKGREEN);   
    
    // select foreground and background color   
    lcd.setBackgroundColor(LCD_COLOR_ORANGE);
    lcd.setForegroundColor(LCD_COLOR_CYAN);
    
    // draw string
    lcd.drawString(5,30, "This is Droid Serif font");
    
     // change foreground and background color   
    lcd.setBackgroundColor(LCD_COLOR_YELLOW);   
    lcd.setForegroundColor(LCD_COLOR_RED);
     
    // draw string
    lcd.drawString(5,70, "converted from a Linux box");    

    lcd.setForegroundColor(LCD_COLOR_WHITE);     
    lcd.setBackgroundColor(LCD_COLOR_TRANSPARENT);
    lcd.drawString(5,110, "For more information, visit");
    lcd.setForegroundColor(LCD_COLOR_YELLOW);     
    lcd.drawString(5,150, "ArduinoExplained.blogspot.ca");
    lcd.setForegroundColor(LCD_COLOR_WHITE);     
    lcd.drawString(30,190, "Thanks for watching.");        
  }  

  // debouncing delay
  delay(300);
  
}

void loop() {
  
  static uint8_t key = 0;

  // execute the test functions one by one
  if(!digitalRead(buttonPin))
  {

    fontTest(key++);
    if(key > MAX_KEY_NUM)key = 0;
    
    // if lcdTest does not provide enough debouncing delay 
    // then you need one here.
  }
}
