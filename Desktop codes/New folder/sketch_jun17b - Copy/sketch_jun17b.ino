#include <UTFT.h>
#include <UTouch.h>
#include <avr/pgmspace.h>
#include <SD.h>
#include <UTFT_tinyFAT.h>
#include <tinyFAT.h>
#include<UTFT_Geometry.h>


UTFT      myGLCD(ITDB32S, 38, 39, 40, 41);
UTouch    myTouch(6, 5, 4, 3, 2);

extern uint8_t BigFont[];

int rollNum[5];
int rollPos;
int x;
int y;
void  printmyDigit (int rollPos)
{ 
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.setColor(255, 255, 255);
  myGLCD.printNumI(rollNum[rollPos], 32+rollPos*16, 2);

} 

void printKey()  {



  myGLCD.setColor(255, 255, 255);
  myGLCD.fillCircle( 40, 280, 35);
  myGLCD.fillCircle( 40, 205, 35);
  myGLCD.fillCircle( 40, 130, 35);
  myGLCD.fillCircle( 40, 55, 35);

  myGLCD.fillCircle( 115, 280, 35);
  myGLCD.fillCircle( 115, 205, 35);
  myGLCD.fillCircle( 115, 130, 35);
  myGLCD.fillCircle( 115, 55, 35);

  myGLCD.fillCircle( 190, 280, 35);
  myGLCD.fillCircle( 190, 205, 35);
  myGLCD.fillCircle( 190, 130, 35);
  myGLCD.fillCircle( 190, 55, 35);

  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.print("1", 32, 47);
  myGLCD.print("2", 107, 47);
  myGLCD.print("3", 182, 47);
  myGLCD.print("4", 32, 122);
  myGLCD.print("5", 107, 122);
  myGLCD.print("6", 182, 122);
  myGLCD.print("7", 32, 197);
  myGLCD.print("8", 107, 197);
  myGLCD.print("9", 182, 197);
  myGLCD.print("Back", 8, 272);
  myGLCD.print("0", 107, 272);
  myGLCD.print("Next", 150, 272);

}



void getRollNum()

{  
  printKey();


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


      if (((y>=20) && (y<=90))&&(rollPos<5))
      {
        if ((x>=0) && (x<=80))
        { 
          rollNum[rollPos]=1;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=80) && (x<=160))
        { 
          rollNum[rollPos]=2;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          rollNum[rollPos]=3;
          printmyDigit(rollPos);
          rollPos++;
        }
      }

      if (((y>=95) && (y<=165))&&(rollPos<5))
      {
        if ((x>=0) && (x<=80))
        { 
          rollNum[rollPos]=4;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=80) && (x<=160))
        { 
          rollNum[rollPos]=5;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          rollNum[rollPos]=6;
          printmyDigit(rollPos);
          rollPos++;
        }
      }


      if (((y>=170) && (y<=240))&&(rollPos<5))
      {
        if ((x>=0) && (x<=80))
        { 
          rollNum[rollPos]=7;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=80) && (x<=160))
        { 
          rollNum[rollPos]=8;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          rollNum[rollPos]=9;
          printmyDigit(rollPos);
          rollPos++;
        }
      }

      if ((y>=245) && (y<=315))
      {
        if ((x>=0) && (x<=80))
        { 
          if (rollPos>4) {
            break;
          }


        }

        if (((x>=80) && (x<=160))&&(rollPos<5))
        { 
          rollNum[rollPos]=0;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          if (rollPos>0) {
            myGLCD.setColor(0, 98, 125);
            rollPos--;
            myGLCD.fillRect(32+rollPos*16, 2, 48+rollPos*16, 20);

          }

        }
      }



    }
    delay(100);
  }
}


void  setup()  {
  
  myGLCD.InitLCD(PORTRAIT);
  myTouch.InitTouch(0);
  myGLCD.fillScr(0, 98, 125);
  getRollNum();
  
}


void loop ()  {
  
}
