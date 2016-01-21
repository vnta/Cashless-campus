/*
	This example shows how to initialize the FatFs for SD card

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
#include <SdcSDFS.h>

// The file system should be declared as a global object
SdcSDFS fs;

void setup()
{
  uint8_t flag;
  Serial.begin(9600);  
  
  flag = fs.getLastError();

  // You supposed to see '0' on the termial if it successfully mount the 
  // file system and open the root directory.
  // For the error list, you can refer to the ff.h in the utility directory.
  Serial.println(flag);
}

void loop()
{
}

