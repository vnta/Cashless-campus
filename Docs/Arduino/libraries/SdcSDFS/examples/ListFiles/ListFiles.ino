/*
	This example enumerates the files in the root director of the SD card.
	It lists and counts the files in the root directory. Then it sets search
	filter for BMP files only and enumerate for the BMP files again.

	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
#include <SdcSDFS.h>

SdcSDFS fs; // file system should be a global object.

void setup()
{
	uint8_t flag;
	uint8_t i;
	char f[4];
	char* p;
  
	Serial.begin(9600);  

	// enumerate the files in the root directory
	Serial.println("List of all files in the root directory");

	i = 0;
	while(fs.openNextFile() == FR_OK)
	{
		p = fs.getFileName();
		Serial.println(p);
		i++;
	}    

	// print the result
	Serial.println("");
	Serial.print("Total number of files: "); 
	Serial.println(i);
	Serial.println("");

	// set file search filter to search only BMP files
	f[0] = 'B'; f[1] = 'M'; f[2] = 'P'; f[3] = 0x00;
	fs.setFileFilter(f);
  
	// rewind the directory entry
	fs.openDirectory("/");

	// do the enumeration again
	Serial.println("List of BMP files in the root directory");

	i = 0;
	while(fs.openNextFile() == FR_OK)
	{
		p = fs.getFileName();
		Serial.println(p);
		i++;
	}    

	// print the result
	Serial.println("");
	Serial.print("Number of BMP files: "); 
	Serial.println(i);

}

void loop()
{
}
