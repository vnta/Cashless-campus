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
int day; //1 for monday, 2 for sunda and so on...
int x, y;
void drawDays()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillCircle(120, 160, 30);
  myGLCD.fillCircle(60, 160, 30);
  myGLCD.fillCircle(180, 160, 30);
  myGLCD.fillCircle(150, 212, 30);
  myGLCD.fillCircle(90, 212, 30);
  myGLCD.fillCircle(150, 108, 30);
  myGLCD.fillCircle(90, 108, 30);
  
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setFont(BigFont);
  myGLCD.print("Sun", 96, 152);
  myGLCD.print("Mon", 36, 152);
  myGLCD.print("Thu", 156, 152);
  myGLCD.print("Wed", 126, 206);
  myGLCD.print("Tue", 66, 206);
  myGLCD.print("Fri", 126, 100);
  myGLCD.print("Sat", 66, 100);
  
}
void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myTouch.InitTouch(0);
  myTouch.setPrecision(PREC_MEDIUM);
  
  myGLCD.setFont(BigFont);
  myGLCD.fillScr(0, 98, 125);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.print("Select Day", 20, 20);
  
  drawDays();
  myGLCD.setColor( 255, 255, 255);
  myGLCD.drawRoundRect(20, 230, 200, 270);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("Continue", 40, 250);
  
  myGLCD.setColor(212, 0, 0);
  
  while(1)  {  myGLCD.setColor(212, 0, 0);
    
  if(myTouch.dataAvailable())  {
    
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    //while (myTouch.dataAvailable()) ;  //uncomment this later to test
    
    if ((y>=78)&&(y<=138))  {  drawDays();
      
      if ((x<=120)&&(x>=60))  { day=7; myGLCD.fillCircle(90, 108, 30); myGLCD.print("Sat", 66, 100);}
      if ((x>=120)&&(x<=180)) { day=6; myGLCD.fillCircle(150, 108, 30); myGLCD.print("Fri", 126, 100);}
      
    }
    
    if ((y>=182)&&(y<=242))  {  drawDays();
      
      if ((x<=120)&&(x>=60))  { day=3; myGLCD.fillCircle(90, 212, 30); myGLCD.print("Tue", 66, 206);}
      if ((x>=120)&&(x<=180)) { day=4; myGLCD.fillCircle(150, 212, 30); myGLCD.print("Wed", 126, 206); }
      
    }
    
    if ((y>138)&&(y<182))  {  drawDays();
      
      if ((x<=150)&&(x>=90))  { day=1; myGLCD.fillCircle(120, 160, 30);  myGLCD.print("Sun", 96, 152);}
      if ((x>=30)&&(x<=90)) { day=2; myGLCD.fillCircle(60, 160, 30);  myGLCD.print("Mon", 36, 152); }
      if ((x>=150)&&(x<=210)) { day=5; myGLCD.fillCircle(180, 160, 30);  myGLCD.print("Thu", 156, 152); }
    }
    
  }
  }
    
}

void loop()
{}
  
