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
int b;
uint8_t Buf[600];
int i=0,z=0,counter=0;
void setup()  
{
  Serial.begin(9600);
  Serial.println("fingertest");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  

  Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
{
  delay(1000);
  counter=0;
  Serial.println("we are here");
p= finger.getImage();
while (p!=FINGERPRINT_OK) p= finger.getImage();
Serial.println("getimg ok");
p= finger.image2Tz();
if (p!=FINGERPRINT_OK) {
  Serial.println("Error in Img2Tz");
}
else {
  Serial.println("img2tz ok");
   p= finger.upChar();
if (p!=FINGERPRINT_OK) Serial.println("Error in UpChar");
else Serial.println("Upchar ok");}


  
   for (i=0;i<73;i++){
    while (!mySerial.available());
   Buf[i]=mySerial.read();
  
  Serial.print(Buf[i]);
  Serial.print(" Byte no: ");
  Serial.println(i+1);
  
} 

   p=finger.downChar(2);
   if (p!=FINGERPRINT_OK) Serial.println("Error in downChar");
else Serial.println("ready download data packet");

b= mySerial.write(Buf,74);
    
  Serial.println(b);
  
  Serial.println("down complete");

   
/*for (i=0;i<512;i++)
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
 /*
 delay(5000);
  Serial.println("OK OK One more Time");
  
p= finger.getImage();
if (p!=FINGERPRINT_OK) Serial.println("Error in getimage");
else Serial.println("getimg ok");
p= finger.image2Tz(2);
if (p!=FINGERPRINT_OK) Serial.println("Error in Img2Tz");
else Serial.println("img2tz ok");
*/

p=finger.Match();
if (p!=FINGERPRINT_OK) Serial.println("madarchod chud gy");

else Serial.println("okey ok mila hai, ab hilao");



}
