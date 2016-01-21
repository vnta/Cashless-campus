

#include <UTFT.h>
#include <avr/pgmspace.h>
extern uint8_t SmallFont[];


UTFT myGLCD(ITDB32S,38,39,40,41);

extern unsigned int logo[39640];


void setup()
{
  myGLCD.InitLCD(POTRAIT);
  myGLCD.setFont(SmallFont);
  myGLCD.drawBitmap (0, 0, 240, 161, logo);
}


void loop()
{


}

