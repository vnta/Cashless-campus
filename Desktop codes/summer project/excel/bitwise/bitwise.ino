

byte GenImgCommand[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x01 ,0x00, 0x05};
int GenImgCommandSize=12;
byte Buf[28];
int i;
void setup()
{  delay(1000);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  Serial.begin(9600);
  Serial2.begin(57600);
}

void loop() {
  Serial2.write(GenImgCommand, GenImgCommandSize);
  delay(1000);
  for (i=0;i<12;i++){ while (!Serial2.available()) ;
  Buf[i]=Serial2.read();}
  for (i=0;i<12;i++){
  Serial.println(Buf[i]);
  }
  while(1);
}
