#include <UTFT.h>
#include <UTouch.h>
#include <avr/pgmspace.h>
#include <SD.h>
#include <UTFT_tinyFAT.h>
#include <tinyFAT.h>
#include<UTFT_Geometry.h>

UTFTtf      myGLCD(ITDB32S, 38, 39, 40, 41);
UTouch      myTouch(6, 5, 4, 3, 2);
UTFT_Geometry geo(&myGLCD);
int rollNum[5], rollPos, x, y,picsize_x,picsize_y;
word res;
const int chipSelect = 53;

extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t SmallFont[];



void  printmyDigit (int rollPos)
{ 
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.setColor(255, 255, 255);
  myGLCD.printNumI(rollNum[rollPos], 32+rollPos*36, 80);
  
} 
  
void getRollNum()

 {  myGLCD.fillScr(0, 98, 125);
    myGLCD.setFont(SevenSegNumFont);
    picsize_x=myGLCD.getDisplayXSize();
    picsize_y=myGLCD.getDisplayYSize();
    res=myGLCD.loadBitmap(0, 0, 240, 320, "login2.raw");
  
  
 rollPos=0;
 while(1)
{
    if (myTouch.dataAvailable())
  {
  myTouch.read();
  x=myTouch.getX();
  y=myTouch.getY();
  
  
  x=myTouch.getX();
  y=myTouch.getY();
  
  
  if (((y>=120) && (y<=170))&&(rollPos<5))
    {
      if ((x>=0) && (x<=80))
        { rollNum[rollPos]=1;
          printmyDigit(rollPos);
          rollPos++;
           }
          
       if ((x>=80) && (x<=160))
        { rollNum[rollPos]=2;
          printmyDigit(rollPos);
          rollPos++;
            }
          
        if ((x>=160) && (x<=240))
        { rollNum[rollPos]=3;
          printmyDigit(rollPos);
          rollPos++;
            }
     }
     
     if (((y>=170) && (y<=220))&&(rollPos<5))
    {
      if ((x>=0) && (x<=80))
        { rollNum[rollPos]=4;
          printmyDigit(rollPos);
          rollPos++;
          }
          
       if ((x>=80) && (x<=160))
        { rollNum[rollPos]=5;
          printmyDigit(rollPos);
          rollPos++;
         }
          
        if ((x>=160) && (x<=240))
        { rollNum[rollPos]=6;
          printmyDigit(rollPos);
          rollPos++;
          }
     }
     
     
      if (((y>=220) && (y<=270))&&(rollPos<5))
    {
      if ((x>=0) && (x<=80))
        { rollNum[rollPos]=7;
          printmyDigit(rollPos);
          rollPos++;
           }
          
       if ((x>=80) && (x<=160))
        { rollNum[rollPos]=8;
          printmyDigit(rollPos);
          rollPos++;
          }
          
        if ((x>=160) && (x<=240))
        { rollNum[rollPos]=9;
          printmyDigit(rollPos);
          rollPos++;
          }
     }
     
     if ((y>=270) && (y<=320))
    {
      if ((x>=0) && (x<=80))
        { if (rollPos>4) {break;}
          
          
           }
          
       if (((x>=80) && (x<=160))&&(rollPos<5))
        { rollNum[rollPos]=0;
          printmyDigit(rollPos);
          rollPos++;
          }
          
        if ((x>=160) && (x<=240))
        { 
          if (rollPos>0) {
            myGLCD.setColor(0, 98, 125);
            rollPos--;
            myGLCD.fillRect(32+rollPos*36, 80, 68+rollPos*36, 130);
             
          }
          
       }
    }
    
   
  
   }
   delay(100);
 }
}

void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myTouch.InitTouch(0);
  myTouch.setPrecision(PREC_MEDIUM);
  getRollNum();
}

void loop()  {
  
}


