#include<MemoryFree.h>
#include <Adafruit_Fingerprint.h>
#include <SD.h>
#if ARDUINO >= 100
 #include <SoftwareSerial.h>
#else
 #include <NewSoftSerial.h>
#endif
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
#if ARDUINO >= 100
SoftwareSerial mySerial(A11,A10);
#else
NewSoftSerial mySerial(A12,A10);
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t p;

byte Buf[80];
int i=0;
byte b, iB;
File logFile;

void setup()  
{
  Serial.begin(9600);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(4, OUTPUT);
  pinMode(53, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  
  
  
  
  
  
  
  
  
  // Check to see if the file exists: 
  if (SD.exists("00000.txt")) {
    Serial.println("00000.txt exists.");
    Serial.println("Removing 00000.txt...");
  SD.remove("00000.txt");
  Serial.println("00000.txt removed");
  }
  else {
    Serial.println("00000.txt doesn't exist.");  
  }

  // delete the file:
  
  
  
  
  
  
  
}

void loop()                     // run over and over again
{
  delay(1000);
  Serial.println("Ready, put finger");
p= finger.getImage();
while(p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");
p= finger.image2Tz();
if (p==FINGERPRINT_OK) {
  Serial.println("Img2Tz ok");
}
else {
  Serial.println("some err in img2tz");}
/*   p= finger.upChar();
if (p!=FINGERPRINT_OK) Serial.println("Error in UpChar");
else Serial.println("Upchar ok");}


  
   for (i=0;i<151;i++){
    while (!mySerial.available()); 
   Buf[i]=mySerial.read();}
  for (i=0;i<151;i++){
  Serial.print(Buf[i]);
  Serial.print("\n");
  }
for (i=0;i<512;i++)
  { //Serial.println("helloh!");
  while (!mySerial.available())
 {
  if (i >511)
 {
   break;
 }
 } 
  Buf[i]=mySerial.read();
  }
  
  for (i=0;i<512;i++)
  {Serial.println(Buf[i]);}*/
 delay(1000);
 
  Serial.println("OK Once more");
  
p= finger.getImage();
while(p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");
p= finger.image2Tz(2);
if (p==FINGERPRINT_OK) Serial.println("Img2Tz ok");
else Serial.println("some err in img2tz");

p=finger.createModel();
if (p==FINGERPRINT_OK) Serial.println("model created");

else{ if (p==FINGERPRINT_PACKETRECIEVEERR) Serial.println("Packet rec err");
else Serial.println("not same finger");}

p= finger.upChar();
if (p==FINGERPRINT_OK) Serial.println("UpChar ok");
else Serial.println("some err in Upchar");


  
   for(i=0;i<73;i++)
   {
    while (!mySerial.available());
   Buf[i]=mySerial.read();
  
 // Serial.print(Buf[i]);
 // Serial.print(" Byte no: ");
 // Serial.println(i+1);
  
}
Serial.println("got em all");


  logFile = SD.open("VR1.txt", FILE_WRITE);
  if (logFile)
  {
    Serial.println("File 00000.txt opeing successful for writing");
  }
  else
  {
    Serial.println("Couldn't open file");
  }
  


 for(i=0;i<73;i++)
   {
     logFile.println((int)Buf[i]);
   //  Serial.print("writing ok byte no:");
   //  Serial.println(i+1);
     delay(1);
   }
Serial.println("all printed onto card");
Serial.println("ready to close file");
 logFile.close();
 Serial.println("file closed");
 
 
 
 
while(1){}


}
