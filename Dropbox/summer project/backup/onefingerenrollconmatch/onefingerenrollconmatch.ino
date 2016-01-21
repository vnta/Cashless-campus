#include <Adafruit_Fingerprint.h>
#if ARDUINO >= 100
 #include <SoftwareSerial.h>
#else
 #include <NewSoftSerial.h>
#endif



// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
#if ARDUINO >= 100
SoftwareSerial mySerial(11,10);
#else
NewSoftSerial mySerial(11,10);
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t p;

uint8_t Buf[600];
int i=0;
void setup()  
{
  Serial.begin(9600);
  Serial.println("fingertest");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
}

void loop()                     // run over and over again
{
  delay(1000);
  Serial.println("we are ready");
p= finger.getImage();
while(p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");
p= finger.image2Tz();
if (p!=FINGERPRINT_OK) {
  Serial.println("Error in Img2Tz");
}
else {
  Serial.println("img2tz ok");}
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
  Serial.println("OK OK One more Time");
  
p= finger.getImage();
while(p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");
p= finger.image2Tz(2);
if (p!=FINGERPRINT_OK) Serial.println("Error in Img2Tz");
else Serial.println("img2tz ok");

p=finger.createModel();
if (p==FINGERPRINT_OK) Serial.println("model created");

else{ if (p==FINGERPRINT_PACKETRECIEVEERR) Serial.println("Packet rec err");
else Serial.println("not same finger");}

Serial.println("please put finger to check for match");
while(1)
  {
    
    delay(100);
p= finger.getImage();
while(p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");
p= finger.image2Tz(2);
if (p!=FINGERPRINT_OK) Serial.println("Error in Img2Tz");
else Serial.println("img2tz ok");



p=finger.Match();
if (p!=FINGERPRINT_OK) Serial.println("no match");

else Serial.println("its a match");
  }
while(1){}


}
