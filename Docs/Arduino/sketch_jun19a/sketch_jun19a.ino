#include <SD.h>
#include <string.h>


char filename[] = "00001111.TXT";
File myFile;

void setup()
{
Serial.begin(9600);
Serial.print("Initializing SD card...");
filename[0]='K';
filename[1]='E';

pinMode(53, OUTPUT);
pinMode(4, OUTPUT);

if (!SD.begin(4)) {
Serial.println("initialization failed!");
return;
}
Serial.println("initialization done.");
}

void loop()
{

//getFileName();
createFileName();
while(1);
delay(3000);

}

/*void getFileName(){

DateTime now = RTC.now();

filename[0] = (now.year()/1000)%10 + '0'; //To get 1st digit from year()
filename[1] = (now.year()/100)%10 + '0'; //To get 2nd digit from year()
filename[2] = (now.year()/10)%10 + '0'; //To get 3rd digit from year()
filename[3] = now.year()%10 + '0'; //To get 4th digit from year()
filename[4] = now.month()/10 + '0'; //To get 1st digit from month()
filename[5] = now.month()%10 + '0'; //To get 2nd digit from month()
filename[6] = now.day()/10 + '0'; //To get 1st digit from day()
filename[7] = now.day()%10 + '0'; //To get 2nd digit from day()
}*/

void createFileName(){
myFile = SD.open(filename, FILE_WRITE);
myFile.println("hi");
myFile.close();
}
