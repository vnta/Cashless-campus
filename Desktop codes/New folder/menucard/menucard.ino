#include <SD.h>
File menuFile;
int noItems;  
void setup()  
{
  int day=1, meal=1, f=0, inc=0;
  Serial.begin(9600);
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
  if(day==1){
    if(meal==1){
      menuFile=SD.open("11.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("12.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("13.txt"); 
      f=1;
    }
  }
  if(day==2){
    if(meal==1){
      menuFile=SD.open("21.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("22.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("23.txt"); 
      f=1;
    }
  }

  if(day==3){
    if(meal==1){
      menuFile=SD.open("31.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("32.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("33.txt"); 
      f=1;
    }
  }

  if(day==4){
    if(meal==1){
      menuFile=SD.open("41.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("42.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("43.txt"); 
      f=1;
    }
  }

  if(day==5){
    if(meal==1){
      menuFile=SD.open("51.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("52.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("53.txt"); 
      f=1;
    }
  }

  if(day==6){
    if(meal==1){
      menuFile=SD.open("61.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("62.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("63.txt"); 
      f=1;
    }
  }

  if(day==7){
    if(meal==1){
      menuFile=SD.open("71.txt"); 
      f=1;
    }
    if(meal==2){
      menuFile=SD.open("72.txt"); 
      f=1;
    }
    if(meal==3){
      menuFile=SD.open("73.txt"); 
      f=1;
    }



  }
  if(f==1){ 
    noItems=menuFile.parseInt();   // parse doesnt read the next char (only peeks)
    menuFile.read();
    while(inc<noItems){
      coupon[inc].name=menuFile.readStringUntil(',');  // readuntil reads " , " also
      coupon[inc].rate=menuFile.parseInt();
      menuFile.read();
      coupon[inc].veg=menuFile.parseInt();
      menuFile.read();
      inc=inc+1;
    }
    menuFile.close();
    while(1);
  }
  else Serial.println("file nt made");
  while(1);






}







void loop(){
}


