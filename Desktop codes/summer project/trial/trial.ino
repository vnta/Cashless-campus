#include <UTFT.h>

UTFT myGLCD(ILI9325D_8,A5,A4,A3,A2);

void setup()
{
  myGLCD.InitLCD();
}

void loop()
{  myGLCD.fillScr(255, 0, 0);
  while(true) ;
  
}
