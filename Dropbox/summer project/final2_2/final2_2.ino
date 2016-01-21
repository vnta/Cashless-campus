#include <UTFT.h>
#include <UTouch.h>
#include <avr/pgmspace.h>
#include <SD.h>
#include <UTFT_tinyFAT.h>
#include <tinyFAT.h>
#include<UTFT_Geometry.h>

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


File myFile;
int kev=0;
int sum=0;
File root;
const int chipSelect = 53;


UTFTtf      myGLCD(ITDB32S, 38,39,40,41);
UTouch      myTouch(6,5,4,3,2);
UTFT_Geometry geo(&myGLCD);



extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t SmallFont[];


int picsize_x, picsize_y;
boolean display_rendertime=false;  // Set this to true if you want the rendertime to be displayed after a picture is loaded
boolean display_filename=false;  // Set this to false to disable showing of filename

int currCoupon;
int totCoupon;
int x, y;

int k=0;

typedef struct menu{
  String name;
  int quant;
  int rate;
  int veg;        //veg=1 for veg, veg=0 for non-veg
} 
Menu;


Menu coupon[6];
word res;
long sm, em;

int rollNum[5], RollNo;
int rollPos;

void drawDays()
{
myGLCD.setColor(255, 255, 255);
myGLCD.fillCircle(120, 160, 30);
myGLCD.fillCircle(60, 160, 30);
myGLCD.fillCircle(180, 160, 30);
myGLCD.fillCircle(150, 212, 30);
myGLCD.fillCircle(90, 212, 30);
myGLCD.fillCircle(150, 108, 30);
myGLCD.fillCircle(90, 108, 30);

myGLCD.setColor(0, 0, 0);
myGLCD.setBackColor(255, 255, 255);
myGLCD.setFont(BigFont);
myGLCD.print("Sun", 96, 152);
myGLCD.print("Mon", 36, 152);
myGLCD.print("Thu", 156, 152);
myGLCD.print("Wed", 126, 206);
myGLCD.print("Tue", 66, 206);
myGLCD.print("Fri", 126, 100);
myGLCD.print("Sat", 66, 100);

}

void getDay()  {
myGLCD.setFont(BigFont);
myGLCD.fillScr(0, 98, 125);

myGLCD.setColor(255, 255, 255);
myGLCD.setBackColor(0, 98, 125);
myGLCD.print("Select Day", 35, 20);

drawDays();
myGLCD.setColor( 255, 255, 255);
myGLCD.fillRoundRect(20, 250, 220, 290);
myGLCD.setColor(0, 0, 0);
myGLCD.drawRoundRect(20, 250, 220, 290);
myGLCD.setBackColor(255, 255, 255);
myGLCD.setColor(0, 0, 0);
myGLCD.setFont(BigFont);
myGLCD.print("Continue", 50, 260);
 
while(1) { myGLCD.setColor(0, 200, 255);

if(myTouch.dataAvailable()) {

myTouch.read();
x=myTouch.getX();
y=myTouch.getY();
while (myTouch.dataAvailable()) ; //uncomment this later to test

if ((y>=78)&&(y<=138)) { drawDays(); myGLCD.setColor(9, 200, 255);

  if ((x<=120)&&(x>=60)) { 
    day=7; 
    myGLCD.fillCircle(90, 108, 30); 
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Sat", 66, 100);
  }
  if ((x>=120)&&(x<=180)) { 
    day=6; 
    myGLCD.fillCircle(150, 108, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Fri", 126, 100);}

}

if ((y>=182)&&(y<=242)) { drawDays();  myGLCD.setColor(9, 200, 255);

  if ((x<=120)&&(x>=60)) { 
    day=3; 
    myGLCD.fillCircle(90, 212, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Tue", 66, 206);
    }
if ((x>=120)&&(x<=180)) { 
    day=4; myGLCD.fillCircle(150, 212, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Wed", 126, 206); 
    }

}

if ((y>138)&&(y<182)) { drawDays();  myGLCD.setColor(9, 200, 255);

  if ((x<=150)&&(x>=90)) { 
     day=1; 
     myGLCD.fillCircle(120, 160, 30);
     myGLCD.setColor(0, 0, 0);
     myGLCD.setBackColor(0, 200, 255);
     myGLCD.print("Sun", 96, 152);
     }
     
  if ((x>=30)&&(x<=90)) 
  { 
    day=2; 
    myGLCD.fillCircle(60, 160, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255);
    myGLCD.print("Mon", 36, 152); 
  }
  if ((x>=150)&&(x<=210)) 
  { day=5; 
    myGLCD.fillCircle(180, 160, 30);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(0, 200, 255); 
    myGLCD.print("Thu", 156, 152); 
    }
}
  
  if (((y>=250)&&(y<=290))&&((x>=20)&&(x<=220)))
    {break;}

}
}
}

void drawMeal()  {
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillCircle(70, 100, 50);
  myGLCD.fillCircle(170, 100, 50);
  myGLCD.fillCircle(120, 187, 50);
  
  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.print("Lunch", 30, 92);
  myGLCD.print("Dinner", 122, 92);
  myGLCD.print("Break",80, 171);
  myGLCD.print("Fast", 88, 187);
  
}
  
void getMeal() {
  myGLCD.fillScr(0, 98, 125);
  drawMeal();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.print("Select Meal", 20, 20);
 
  myGLCD.setColor( 255, 255, 255);
  myGLCD.fillRoundRect(20, 250, 220, 290);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect(20, 250, 220, 290);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("Continue", 50, 260);
  
  while (true)  {
    
      if (myTouch.dataAvailable())    {
      
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      
      while(myTouch.dataAvailable())  {;}
      
      if ((y>=50)&&(y<=150))  {
      
      if ((x>=20)&&(x<=120))   {
       meal=2;
      drawMeal();
      myGLCD.setColor(0, 200, 255);
      myGLCD.fillCircle(70, 100, 50);
      myGLCD.setColor(0, 0, 0);
      myGLCD.setBackColor(0, 200, 255);
      myGLCD.print("Lunch", 30, 92);
      
      }
      
      if ((x>=120)&&(x<=220))   {
       meal=3;
      drawMeal();
      myGLCD.setColor(0, 200, 255);
      myGLCD.fillCircle(170, 100, 50);
      myGLCD.setColor(0, 0, 0);
      myGLCD.setBackColor(0, 200, 255);
      myGLCD.print("Dinner", 122, 92);
      
      }
      
      }
      
      if (((y>=150)&&(y<=250))&&((x>=70)&&(x<=170)))  {
        meal=1;
        drawMeal();
        myGLCD.setColor(0, 200, 255);
        myGLCD.fillCircle(120, 187, 50);
        myGLCD.setColor(0, 0, 0);
        myGLCD.setBackColor(0, 200, 255);
        myGLCD.print("Break",80, 171);
        myGLCD.print("Fast", 88, 187);
        
      }
      
      if (((y>=250)&&(y<=290))&&((x>=20)&&(x<=220)))
    {break;}
        
     }  
      
      
   }
     
}
   
   

void  printmyDigit (int rollPos)
{ 
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.setColor(255, 255, 255);
  myGLCD.printNumI(rollNum[rollPos], 32+rollPos*36, 60);

} 

void getRollNum()

{  
  myGLCD.setFont(SevenSegNumFont);
  picsize_x=myGLCD.getDisplayXSize();
  picsize_y=myGLCD.getDisplayYSize();
  res=myGLCD.loadBitmap(0, 0, 240, 320, "login2.raw");


  rollPos=0;
  while(1)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();


      x=myTouch.getX();
      y=myTouch.getY();


      if (((y>=120) && (y<=170))&&(rollPos<5))
      {
        if ((x>=0) && (x<=80))
        { 
          rollNum[rollPos]=1;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=80) && (x<=160))
        { 
          rollNum[rollPos]=2;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          rollNum[rollPos]=3;
          printmyDigit(rollPos);
          rollPos++;
        }
      }

      if (((y>=170) && (y<=220))&&(rollPos<5))
      {
        if ((x>=0) && (x<=80))
        { 
          rollNum[rollPos]=4;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=80) && (x<=160))
        { 
          rollNum[rollPos]=5;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          rollNum[rollPos]=6;
          printmyDigit(rollPos);
          rollPos++;
        }
      }


      if (((y>=220) && (y<=270))&&(rollPos<5))
      {
        if ((x>=0) && (x<=80))
        { 
          rollNum[rollPos]=7;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=80) && (x<=160))
        { 
          rollNum[rollPos]=8;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=160) && (x<=240))
        { 
          rollNum[rollPos]=9;
          printmyDigit(rollPos);
          rollPos++;
        }
      }

      if ((y>=270) && (y<=320))
      {
        if ((x>=160) && (x<=240))
        { 
          if (rollPos>4) {
            break;
          }


        }

        if (((x>=80) && (x<=160))&&(rollPos<5))
        { 
          rollNum[rollPos]=0;
          printmyDigit(rollPos);
          rollPos++;
        }

        if ((x>=0) && (x<=80))
        { 
          if (rollPos>0) {
            myGLCD.setColor(0, 98, 125);
            rollPos--;
            myGLCD.fillRect(32+rollPos*36, 60, 68+rollPos*36, 110);

          }

        }
      }



    }
    delay(100);
  }
}

void drawCoupon(int currCoupon)
{
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Select Coupons", 20, 20);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(20, 40, 220, 160);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print(coupon[currCoupon].name, 25, 45);
  myGLCD.print("Rs.", 25, 65);
  myGLCD.printNumI(coupon[currCoupon].rate, 55, 65);


  if (coupon[currCoupon].veg==1) {
    myGLCD.setColor(59, 159, 5);
  }    //drawing the green veg symbol
  else {
    myGLCD.setColor(212, 0, 0);
  } 
  myGLCD.fillRect(160, 100, 210, 150);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(165, 105, 205, 145);
  if (coupon[currCoupon].veg==1) {
    myGLCD.setColor(59, 159, 5);
  }    //drawing the green veg symbol
  else {
    myGLCD.setColor(212, 0, 0);
  }
  myGLCD.fillCircle(185, 125, 15);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.print("You will take", 20, 170);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(coupon[currCoupon].quant, 95, 190);

}

void drawButts() 
{ 
  myGLCD.setColor(255, 255, 255);       //draw the +/- buttons
  myGLCD.fillCircle(55, 215, 25);
  myGLCD.fillCircle(185, 215, 25);
  myGLCD.setColor(0, 98, 125);
  myGLCD.fillRect(35, 210, 75, 220);
  myGLCD.fillRect(165, 210, 205, 220);
  myGLCD.fillRect(180,195 , 190, 235);

  myGLCD.setColor(255, 255, 255);
  geo.fillTriangle( 20, 285, 70, 260, 70, 310);
  geo.fillTriangle( 130, 285, 80, 260, 80, 310);

  myGLCD.fillRoundRect(150, 260, 230, 310);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setFont(BigFont);

  myGLCD.print("Final", 150, 270);
  myGLCD.print("Order", 150, 290);


}



void confirmScr() {

  myGLCD.fillScr(0, 98, 125);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.print("Confirm Order", 20, 20);

  int i;
  for(i=0;i<6;i++)
  {   
    myGLCD.print(coupon[i].name, 20, 60 + (20*i));
    myGLCD.print("X", 160, 60+20*i);
    myGLCD.printNumI(coupon[i].quant, 200, 60+(20*i));

  }

  myGLCD.print("Total: Rs.", 20, 200);
  myGLCD.printNumI(sum, 180, 200);

  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(10, 240, 110, 300);
  myGLCD.fillRoundRect(130, 240, 230, 300);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.print("Back", 20, 260);
  myGLCD.print("Final", 130, 260);

  while(true)  {

    if (myTouch.dataAvailable())  {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();

      if ((y<=300)&&(y>=240))  {

        if ((x>=10)&&(x<=110))  {
          myGLCD.fillScr(0, 98, 125);
          selectCoupons();
          break;  
        }

        if ((x>=130)&&(x<=230))  {
          myGLCD.fillScr(0, 98, 125);
          myGLCD.setColor(255, 255, 255);
          myGLCD.setBackColor(0, 98, 125);
          myGLCD.print("Thank You", 20, 20);
          delay(1000);
          break;
        }


      }


      delay(100);
    }        
  }
}

void selectCoupons()  {
  drawCoupon(currCoupon);

  drawButts();

  while(1)
  {

    if (myTouch.dataAvailable())
    {
      myTouch.read(); 
      x=myTouch.getX();
      y=myTouch.getY();

      if ((y>=260)&&(y<=310))  {
        if ((x<=70)&&(x>=20)) {
          if (currCoupon>0) currCoupon--;
          else currCoupon=5;
        }

        if ((x>=80)&&(x<=130))  {
          if (currCoupon!=(totCoupon-1))
          {
            currCoupon++;
          }
          else {
            currCoupon=0;
          }
        }

        if ((x>=150)&&(x<=240))  {
          grandTotal();
          confirmScr();
          break;
        }
      }


      if ((y>=190)&&(y<=240))  {
        if((x>=30)&&(x<=80))
        { 
          if (coupon[currCoupon].quant>0)
            coupon[currCoupon].quant--;
        }
        if (( x>=165)&&(x<=210))
        {
          coupon[currCoupon].quant++;
        }
      }
      drawCoupon(currCoupon);

    }
    delay(100);
  }
}

void SDHeaders()
{

  File logFile = SD.open("orders.csv", FILE_WRITE);
  if (logFile)
  {
    logFile.println("-,-,-,-,-,-,-"); //Just a leading blank line, incase there was previous data
    String header = coupon[0].name + "," +coupon[1].name + "," +coupon[2].name + "," +coupon[3].name + "," +coupon[4].name + "," +coupon[5].name +","+"Grand Total";
    logFile.println(header);
    logFile.close();
    Serial.println(header);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }

}

void savetoSD()
{
  myFile= SD.open("orders.csv", FILE_WRITE);
  if(myFile){
    Serial.println("OKKK!!");

    while(kev<6){

      Serial.println("OKKK!!");

      myFile.print(coupon[kev].quant);
      myFile.print(",");
      kev=kev+1;
    }
    myFile.println(sum);
    //myFile.print("\nGrand Total : Rs."); myFile.println(sum);
    // myFile.println("____________________________________");  
  }

  myFile.close();
  kev=0;
  for (k=0;k<6;k++)
  {
    coupon[k].quant=0;
  }

  sum=0;
}

void grandTotal()
{  
  sum=0;
  int k;
  for (k=0;k<6;k++)
  {
    sum = sum + coupon[k].rate*coupon[k].quant ;
  }
}

void reset()
{
  k=0;
  for (k=0;k<6;k++)
  {
    coupon[k].quant=0;
  }

  k=0;
}

void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.fillScr(0, 98, 125);
  getDay();
  getMeal();
  myGLCD.setFont(SevenSegNumFont);
  if (!SD.begin(chipSelect)) {
    return;
  }
  res=file.initFAT();
  myGLCD.setColor(255,255,255);
  myTouch.InitTouch(0);
  myTouch.setPrecision(PREC_MEDIUM);
  currCoupon=0;
  totCoupon=6;

  coupon[0].name="Paneer";
  coupon[0].veg=1;

  coupon[1].name="Egg";
  coupon[1].veg=0;

  coupon[2].name="Biriyani";
  coupon[2].veg=1;

  coupon[3].name="Aloo Fry";
  coupon[3].veg=1;

  coupon[4].name="Fish";
  coupon[4].veg=0;

  coupon[5].name="Chicken";
  coupon[5].veg=0;


  coupon[0].rate=20;
  coupon[1].rate=5;
  coupon[2].rate=50;
  coupon[3].rate=5;
  coupon[4].rate=35;
  coupon[5].rate=45;
  SDHeaders();

}

void verifyFinger(){



uint8_t p;
File charIDs;
byte Buf[80];
int testRoll=00000, b, i;
Serial.println(RollNo);
  charIDs=SD.open("chararrs.txt");
  if(charIDs){
    Serial.println("char id file open");
  }
  else Serial.println("nah not open");
 
  while(!(testRoll==RollNo)){
    Serial.println("here");
    charIDs.readStringUntil('<');
    testRoll=charIDs.parseInt();
  }

  if(charIDs.read()=='>')Serial.println("ok");
  else Serial.println("not a roll no");
  charIDs.read();

  for(i=0;i<73;i++){ 
    // read the incoming byte:
    Buf[i] = charIDs.parseInt();

    // say what you got:
    Serial.print(i+1);
    Serial.print("byte received: ");
    Serial.println(Buf[i], DEC);
  }
  charIDs.close();




  p=finger.downChar(2);
  if (p==FINGERPRINT_OK) Serial.println("ready for packet");
  else Serial.println("not ready for pkt");

  b= mySerial.write(Buf,73);

  Serial.println(b);

  Serial.println("down complete\n wait...");


  delay(100);
  Serial.println("put finger to be tested");
  b=0;
  while(b==0){
    p= finger.getImage();
    while(p!=FINGERPRINT_OK) p= finger.getImage();
    Serial.println("getimg ok");

    p= finger.image2Tz();
    if (p==FINGERPRINT_OK) Serial.println("Img2Tz ok");
    else Serial.println("some err in img2tz ");


    p=finger.Match();
    if (p==FINGERPRINT_OK) {Serial.println("Its a MATCH"); b=1;}


    else {
      if (p==FINGERPRINT_PACKETRECIEVEERR)Serial.println("Pkt rec err");
      else Serial.println("No match");
    }
  }





}

void loop()
{ 
  getRollNum();
  RollNo=rollNum[0]*10000+rollNum[1]*1000+rollNum[3]*100+rollNum[4]*10+rollNum[5];
  
  res=myGLCD.loadBitmap(0, 0, 240, 320, "ready.raw");
  delay(1000);
  verifyFinger();
  
  myGLCD.fillScr(0, 98,125);
  selectCoupons();
  savetoSD();
  reset();
}


