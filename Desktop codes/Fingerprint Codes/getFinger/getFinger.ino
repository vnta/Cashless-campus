#include <Adafruit_Fingerprint.h>
#if ARDUINO >= 100
 #include <SoftwareSerial.h>
#else
 #include <NewSoftSerial.h>
#endif

#if ARDUINO >= 100
SoftwareSerial mySerial(A11, A10);
#else
NewSoftSerial mySerial(A11, A10);
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int totalStudents;
int i;
int getFingerprintIDez();

typedef struct person  {
  String name;
  int rollNumber;
  int ID;
}
Person;

Person student[10]; 


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with Roll Number: ");
  Serial.print(student[finger.fingerID-1].rollNumber);
  Serial.print("whose name is ");
  Serial.print(student[finger.fingerID-1].name);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}


void setup()  
{
  Serial.begin(9600);
  
  //Assigning Names, IDs and roll Numbers
  student[0].name="Avi";
  student[1].name="Kevin";
  student[2].name="Vineet";
  student[3].name="Prawal";
  
  for(i=0;i<totalStudents;i++)
  {
   student[i].ID=i+1;
  }
  
  student[0].rollNumber=12177;
  student[1].rollNumber=12352;
  student[2].rollNumber=12810;
  student[3].rollNumber=12510;
  
  // Assigning ends here
  
  Serial.println("fingertest");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  Serial.println("Waiting for valid finger...");
}

void loop() {

getFingerprintIDez();
}
