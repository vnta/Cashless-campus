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
NewSoftSerial mySerial(A11,A10);
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
  
  // see if the card is present and can be initialized:
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  
  
  
  
  
  
  
  
  
  // Check to see if the file exists: 
  if (SD.exists("C12352.txt")) {
    Serial.println("00000.txt exists.");
  //  Serial.println("Removing 00000.txt...");
 // SD.remove("00000.txt");
 // Serial.println("00000.txt removed");
  }
  else {
    Serial.println("File doesn't exist.");  
  }

  // delete the file:
  
  
  
  
  
  
  
}

void loop()                     // run over and over again
{
  
 
  logFile = SD.open("C12352.txt");
  if (logFile)
  {
    Serial.println("File  opeing successful for reading");
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  
    for(i=0;i<73;i++){ 
                // read the incoming byte:
                Buf[i] = logFile.parseInt();

                // say what you got:
                //Serial.print(i+1);
                //Serial.print("byte received: ");
                //Serial.println(Buf[i], DEC);
        }
     
    
     
     logFile.close();
     
       
   p=finger.downChar(2);
   if (p==FINGERPRINT_OK) Serial.println("ready for packet");
else Serial.println("not ready for pkt");

b= mySerial.write(Buf,73);
    
  Serial.println(b);
  
  Serial.println("down complete\n wait...");

    
    delay(100);
    Serial.println("put finger to be tested");
while(1){
p= finger.getImage();
while(p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");

p= finger.image2Tz();
if (p==FINGERPRINT_OK) Serial.println("Img2Tz ok");
else Serial.println("some err in img2tz ");


p=finger.Match();
if (p==FINGERPRINT_OK) Serial.println("Its a MATCH");


else {if (p==FINGERPRINT_PACKETRECIEVEERR)Serial.println("Pkt rec err");
else Serial.println("No match");}
}
while(1){}


}
