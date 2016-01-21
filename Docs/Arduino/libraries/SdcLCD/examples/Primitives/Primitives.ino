/*
	This program demonstrates some graphic primitives of the library
	such as drawLine, drawRectangle, drawCircle, drawEllipse, and 
	drawRoundRectangle. You can choose filled or hollow type for each
	shape.

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
 
#include <SdcLCD.h>

#define MAX_KEY_NUM    11
const int buttonPin = 12;

// declare the class on the heap
SdcLCD lcd;


void setup() {
  // initial screen clear
  lcd.clearScreen(LCD_COLOR_DKGREY);
  
  // initialize the pushbutton with internal pullup
  digitalWrite(buttonPin, 1);
  pinMode(buttonPin, INPUT);
}

const LCDCOLOR colors[12] =
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
  
void lcdTest(uint8_t index)
{
  uint16_t i,j;
  int16_t x1, y1, x2, y2, delx, dely;
  uint16_t dif_red, dif_green, dif_blue;
  uint16_t col_red, col_green, col_blue;
  
  lcd.clearScreen(LCD_COLOR_BLACK);
  delay(100);

  //
  // (0) clear screen with the specified color
  //
  if(index == 0)
  {
    for(i = 0; i < 12; i++)
    {
      lcd.clearScreen(colors[i]);
      delay(200);
    }     
  }
  //
  // (1) single pixel width lines
  //
  else if(index == 1)
  {
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
  // (2) multipixel width lines
  //
  else if(index == 2)
  {
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
  // (3) rectangles with various sizes and line thicknesses
  //
  else if(index == 3)
  {
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
  // (4) filled rectangles
  //
  else if(index == 4)
  {
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
  // (5) round rectangles
  //
  else if(index == 5)
  {   
    delx = lcd.getScreenWidth()>>4;
    dely = lcd.getScreenHeight()>>4;

    // upper left corner of the first rectangle
    x1 = delx;
    y1 = dely;
    
    // lower right corner of the first rectangle
    x2 = lcd.getScreenWidth() - delx;
    y2 = lcd.getScreenHeight() - dely;

    for(i = 0; i < 7; i++)
    {
      lcd.setPenWidth((i<<1) + 1);
      j = (i<<1) +1;
      lcd.setForegroundColor(colors[i]);
      lcd.drawRoundRectangle(x1, y1, x2, y2, j);

      x1 += delx;
      y1 += dely;
      x2 -= delx;
      y2 -= dely;
    }
  }
  //
  // (6) solid round rectangles
  //
  else if(index == 6)
  {
    delx = lcd.getScreenWidth()>>4;
    dely = lcd.getScreenHeight()>>4;

    // upper left corner of the first rectangle
    x1 = delx;
    y1 = dely;
    
    // lower right corner of the first rectangle
    x2 = lcd.getScreenWidth() - delx;
    y2 = lcd.getScreenHeight() - dely;

    for(i = 0; i < 7; i++)
    {
      j = (i<<1) +1;

      lcd.setForegroundColor(colors[i]);
      lcd.drawFilledRoundRectangle(x1, y1, x2, y2, j);

      x1 += delx;
      y1 += dely;
      x2 -= delx;
      y2 -= dely;
    }
  }  
  //
  // (7) circles with various sizes and line thickness
  //
  else if(index == 7)
  {
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
  // (8) solid circles
  //
  else if(index == 8)
  {
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
  // (9) ellipses with various sizes and line thickness
  //
  else if(index == 9)
  {
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
  // (10) solid ellipses
  //
  else if(index == 10)
  {
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
  // color contrast bars
  //
  else
  {
    delx = lcd.getScreenWidth() / 32;
    dely = lcd.getScreenHeight() / 7;

    // initial y positions
    y1 = 0;
    y2 = y1 + dely - 1;

    for( i = 0; i < 7; i++ )
    {
      // initial x positions
      x1 = 0;
      x2 = x1 + delx - 1;

      // prepare color bars
      if(i == 0)
      {
        // blue color bar
        dif_red = 0x00;
        dif_green = 0x00;
        dif_blue = ((0xFF)>>5);
      }
      else if(i == 1)
      {
        // green color bar
        dif_red = 0x00;
        dif_green = ((0xFF)>>5);
        dif_blue = 0x00;
      }
      else if(i == 2)
      {
        // cyan color bar
        dif_red = 0x00;
        dif_green = ((0xFF)>>5);
        dif_blue = ((0xFF)>>5);
      }
      else if(i == 3)
      {
        // red color bar
        dif_red = ((0xFF)>>5);
        dif_green = 0x00;
        dif_blue = 0x00;
      }
      else if(i == 4)
      {
        // magenta color bar
        dif_red = ((0xFF)>>5);
        dif_green = 0x00;
        dif_blue = ((0xFF)>>5);
      }
      else if(i == 5)
      {
        // yellow color bar
        dif_red = ((0xFF)>>5);
        dif_green = ((0xFF)>>5);
        dif_blue = 0x00;
      }
      else if(i == 6)
      {
        // white color bar
        dif_red = ((0xFF)>>5);
        dif_green = ((0xFF)>>5);
        dif_blue = ((0xFF)>>5);
      }

      // initial color value
      col_red = dif_red;
      col_green = dif_green;
      col_blue = dif_blue;

      for( j = 0; j < 32; j++ )
      {
        lcd.setForegroundColor(LCD_COLOR(col_red, col_green, col_blue));
        lcd.drawFilledRectangle(x1, y1 , x2, y2);

        // next color value
        col_red += dif_red;
        col_green += dif_green;
        col_blue += dif_blue;

        // next x position
        x1 = x2 + 1;
        x2 = x1 + delx - 1;
      }

      // advance to the next y position
      y1 = y2 + 2;
      y2 = y1 + dely -1;

      // revert x position ?
    }
  }   

  // debouncing delay
  delay(500);    
}

void loop() {
  
  static uint8_t key = 0;

  // execute the test functions one by one
  if(!digitalRead(buttonPin))
  {

    lcdTest(key++);
    if(key > MAX_KEY_NUM)key = 0;
    
    // if lcdTest does not provide enough debouncing delay 
    // then you need one here.
  }

}
