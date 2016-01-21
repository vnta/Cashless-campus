// UTFT_Demo_320x240 (C)2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next line for Arduino 2009/Uno
UTFT myGLCD(ILI9325D_8,A5,A4, A3, A2);  // Remember to change the model parameter to suit your display module!

// Uncomment the next line for Arduino Mega
//UTFT myGLCD(ITDB32S,38,39,40,41);   // Remember to change the model parameter to suit your display module!

void setup()
{
  
// Setup the LCD
  myGLCD.InitLCD();
}

void loop()
{
  myGLCD.fillScr(255,0,0);
}

