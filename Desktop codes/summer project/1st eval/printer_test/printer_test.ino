/*************************************************************************
  This is an Arduino library for the Adafruit Thermal Printer.
  Pick one up at --> http://www.adafruit.com/products/597
  These printers use TTL serial to communicate, 2 pins are required.

  Adafruit invests time and resources providing this open source code.
  Please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution.
 *************************************************************************/

// If you're using Arduino 1.0 uncomment the next line:
#include "SoftwareSerial.h"
// If you're using Arduino 23 or earlier, uncomment the next line:
//#include "NewSoftSerial.h"

#include "Adafruit_Thermal.h"
#include <avr/pgmspace.h>

int printer_RX_Pin = 5;  // This is the green wire
int printer_TX_Pin = 6;  // This is the yellow wire

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

void setup(){
  Serial.begin(9600);
  pinMode(7, OUTPUT); digitalWrite(7, LOW); // To also work w/IoTP printer
  printer.begin();

  // The following function calls are in setup(), but do not need to be.
  // Use them anywhere!  They're just here so they're run only one time
  // and not printed over and over.
  // Some functions will feed a line when called to 'solidify' setting.
  // This is normal.

 

  // Test character double-height on & off
 /* printer.doubleHeightOn();
  printer.println("Double Height ON");
  printer.doubleHeightOff();*/

  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  printer.justify('R');

 /* printer.justify('C');
  printer.println("Center justified");
  printer.justify('L');
  printer.println("Left justified");*/

  // Test more styles
  printer.boldOn();

 // printer.boldOff();
  printer.justify('C');
  printer.underlineOn(); 
  printer.println("Mess Coupons");
  printer.println("            ");
  
  printer.underlineOff();
  printer.boldOff();

   // Print line
  printer.setSize('M');
  printer.print("/n");
  for(i=0;i<totCoupon;i++)
  { 
  printer.print(coupon[i].name);
  printer.print("   X");
  printer.print(coupon[i].quant);
  printer.print("/n");
  }

  printer.setSize('L');
  printer.print(" GRAND TOTAL= ");
  printer.print(sum);
  printer.print("/n");
  printer.justify('C');
  printer.println("____________________");
  
  printer.sleep();      // Tell printer to sleep
  printer.wake();       // MUST call wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
}

void loop() {
}
