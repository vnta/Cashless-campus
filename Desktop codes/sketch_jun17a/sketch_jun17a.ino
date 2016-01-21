#include <UTFT.h>
#include <UTouch.h>
#include <avr/pgmspace.h>
#include <SD.h>
#include <UTFT_tinyFAT.h>
#include <tinyFAT.h>
#include<UTFT_Geometry.h>
UTFT myGLCD(ITDB32S, 38, 39, 40, 41);
UTouch myTouch(6, 5, 4, 3, 2);
extern uint8_t BigFont[];
int day; //1 for monday, 2 for sunday and so on...
int meal;// 1 for breakfast, 2 for lunch and so on...
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

void getDay()  {
myGLCD.setFont(BigFont);
myGLCD.fillScr(0, 98, 125);

myGLCD.setColor(255, 255, 255);
myGLCD.setBackColor(0, 98, 125);
myGLCD.print("Select Day", 35, 20);

drawDays();
myGLCD.setColor( 255, 255, 255);
myGLCD.fillRoundRect(20, 250, 220, 290);
myGLCD.setColor(0, 0, 0);
myGLCD.drawRoundRect(20, 250, 220, 290);
myGLCD.setBackColor(255, 255, 255);
myGLCD.setColor(0, 0, 0);
myGLCD.setFont(BigFont);
myGLCD.print("Continue", 50, 260);
 
while(1) { myGLCD.setColor(0, 200, 255);

if(myTouch.dataAvailable()) {

myTouch.read();
x=myTouch.getX();
y=myTouch.getY();
while (myTouch.dataAvailable()) ; //uncomment this later to test

if ((y>=78)&&(y<=138)) { drawDays(); myGLCD.setColor(9, 200, 255);

  if ((x<=120)&&(x>=60)) { 
    day=7; 
    myGLCD.fillCircle(90, 108, 30); 
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Sat", 66, 100);
  }
  if ((x>=120)&&(x<=180)) { 
    day=6; 
    myGLCD.fillCircle(150, 108, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Fri", 126, 100);}

}

if ((y>=182)&&(y<=242)) { drawDays();  myGLCD.setColor(9, 200, 255);

  if ((x<=120)&&(x>=60)) { 
    day=3; 
    myGLCD.fillCircle(90, 212, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Tue", 66, 206);
    }
if ((x>=120)&&(x<=180)) { 
    day=4; myGLCD.fillCircle(150, 212, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Wed", 126, 206); 
    }

}

if ((y>138)&&(y<182)) { drawDays();  myGLCD.setColor(9, 200, 255);

  if ((x<=150)&&(x>=90)) { 
     day=1; 
     myGLCD.fillCircle(120, 160, 30);
     myGLCD.setColor(0, 0, 0);
     myGLCD.setBackColor(0, 200, 255);
     myGLCD.print("Sun", 96, 152);
     }
     
  if ((x>=30)&&(x<=90)) 
  { 
    day=2; 
    myGLCD.fillCircle(60, 160, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Mon", 36, 152); 
  }
  if ((x>=150)&&(x<=210)) 
  { day=5; 
    myGLCD.fillCircle(180, 160, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255); 
    myGLCD.print("Thu", 156, 152); 
    }
}
  
  if (((y>=250)&&(y<=290))&&((x>=20)&&(x<=220)))
    {break;}

}
}
}

void drawMeal()  {
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillCircle(70, 100, 50);
  myGLCD.fillCircle(170, 100, 50);
  myGLCD.fillCircle(120, 187, 50);
  
  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.print("Lunch", 30, 92);
  myGLCD.print("Dinner", 122, 92);
  myGLCD.print("Break",80, 171);
  myGLCD.print("Fast", 88, 187);
  
}
  
void getMeal() {
  myGLCD.fillScr(0, 98, 125);
  drawMeal();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.print("Select Meal", 20, 20);
 
  myGLCD.setColor( 255, 255, 255);
  myGLCD.fillRoundRect(20, 250, 220, 290);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect(20, 250, 220, 290);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("Continue", 50, 260);
  
  while (true)  {
    
      if (myTouch.dataAvailable())    {
      
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      
      while(myTouch.dataAvailable())  {;}
      
      if ((y>=50)&&(y<=150))  {
      
      if ((x>=20)&&(x<=120))   {
       meal=2;
      drawMeal();
      myGLCD.setColor(0, 200, 255);
      myGLCD.fillCircle(70, 100, 50);
      myGLCD.setColor(0, 0, 0);
      myGLCD.setBackColor(0, 200, 255);
      myGLCD.print("Lunch", 30, 92);
      
      }
      
      if ((x>=120)&&(x<=220))   {
       meal=3;
      drawMeal();
      myGLCD.setColor(0, 200, 255);
      myGLCD.fillCircle(170, 100, 50);
      myGLCD.setColor(0, 0, 0);
      myGLCD.setBackColor(0, 200, 255);
      myGLCD.print("Dinner", 122, 92);
      
      }
      
      }
      
      if (((y>=150)&&(y<=250))&&((x>=70)&&(x<=170)))  {
        meal=1;
        drawMeal();
        myGLCD.setColor(0, 200, 255);
        myGLCD.fillCircle(120, 187, 50);
        myGLCD.setColor(0, 0, 0);
        myGLCD.setBackColor(0, 200, 255);
        myGLCD.print("Break",80, 171);
        myGLCD.print("Fast", 88, 187);
        
      }
        
     }  
      
      
   }
     
}
   
   
void setup()
{
myGLCD.InitLCD(PORTRAIT);
myTouch.InitTouch(0);
myTouch.setPrecision(PREC_MEDIUM);
//getDay();
getMeal();


}
void loop()
{}
