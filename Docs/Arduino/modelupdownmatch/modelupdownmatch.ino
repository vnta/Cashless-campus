#include <Adafruit_Fingerprint.h>
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

uint8_t Buf[600];
int i=0;
byte b;


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

 delay(2000);
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
  
  Serial.print(Buf[i]);
  Serial.print(" Byte no: ");
  Serial.println(i+1);
  
} 

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
