#include <UTFT.h>
#include <avr/pgmspace.h>
#include <SD.h>
#include <UTFT_tinyFAT.h>
#include <tinyFAT.h>
#include<UTFT_Geometry.h>

#define T_CLK 55
#define T_CS 60
#define T_DIN 54
#define T_DOUT 8
#define T_IRQ 9

#define X_CONST 240
#define Y_CONST 320

#define PREC_TOUCH_CONST 10

#define PixSizeX  13.78
#define PixOffsX  411

#define PixSizeY  11.01
#define PixOffsY  378

int TP_X,TP_Y;


File myFile;
int kev=0;
int sum=0;
File root;
const int chipSelect = 53;


UTFTtf      myGLCD(ILI9325D_8,A5,A4,A3,A2);
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
} Menu;


  Menu coupon[6];
  word res;
  long sm, em;

int rollNum[5];
int rollPos;

void Touch_Init(void)
{
    pinMode(T_CLK,  OUTPUT);
    pinMode(T_CS,   OUTPUT);
    pinMode(T_DIN,  OUTPUT);
    pinMode(T_DOUT, INPUT);
    pinMode(T_IRQ,  INPUT);

	digitalWrite(T_CS,  HIGH);
	digitalWrite(T_CLK, HIGH);
	digitalWrite(T_DIN, HIGH);
	digitalWrite(T_CLK, HIGH);
}

void Touch_WriteData(unsigned char data)
{
	unsigned char temp;
	unsigned char nop;
	unsigned char count;

	temp=data;
	digitalWrite(T_CLK,LOW);

	for(count=0; count<8; count++)
	{
		if(temp & 0x80)
			digitalWrite(T_DIN, HIGH);
		else
			digitalWrite(T_DIN, LOW);
		temp = temp << 1; 
		digitalWrite(T_CLK, LOW);                
		nop++;
		digitalWrite(T_CLK, HIGH);
		nop++;
	}
}

unsigned int Touch_ReadData()
{
	unsigned char nop;
	unsigned int data = 0;
	unsigned char count;
	for(count=0; count<12; count++)
	{
		data <<= 1;
		digitalWrite(T_CLK, HIGH);               
		nop++;
		digitalWrite(T_CLK, LOW);
		nop++;
		if (digitalRead(T_DOUT))
			data++;
	}
	return(data);
}
void Touch_Read()
{
	unsigned long tx=0;
	unsigned long ty=0;

	digitalWrite(T_CS,LOW);                    

	for (int i=0; i<PREC_TOUCH_CONST; i++)
	{
		Touch_WriteData(0x90);        
		digitalWrite(T_CLK,HIGH);
		digitalWrite(T_CLK,LOW); 
		ty+=Touch_ReadData();

		Touch_WriteData(0xD0);      
		digitalWrite(T_CLK,HIGH);
		digitalWrite(T_CLK,LOW);
		tx+=Touch_ReadData();
	}

	digitalWrite(T_CS,HIGH);

	TP_X=tx/PREC_TOUCH_CONST;
	TP_Y=ty/PREC_TOUCH_CONST;
}

char Touch_DataAvailable()
{
  char avail;
  avail = !digitalRead(T_IRQ);
  return avail;
}

int Touch_GetX()
{
	int value;
	value = ((TP_X-PixOffsX)/PixSizeX);
	if (value < 0)
		value = 0;
	return value;
}
int Touch_GetY()
{
	int value;
	value = ((TP_Y-PixOffsY)/PixSizeY);
	if (value < 0)
		value = 0;
	return value;
}

void  printmyDigit (int rollPos)
{ 
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.setColor(255, 255, 255);
  myGLCD.printNumI(rollNum[rollPos], 32+rollPos*36, 80);
  
} 
  
void getRollNum()

 {  myGLCD.setFont(SevenSegNumFont);
    
    res=myGLCD.loadBitmap(0, 0, 240, 320, "login2.raw");
  
  
 rollPos=0;
 while(1)
{
    
  if (Touch_DataAvailable())  {
      Touch_Read();
      x=Touch_GetX();
      y=Touch_GetY();
  
 
  
  
  if (((y>=160) && (y<=200))&&(rollPos<5))
    {
      if ((x>=0) && (x<=80))
        { rollNum[rollPos]=1;
          printmyDigit(rollPos);
          rollPos++;
           }
          
       if ((x>=80) && (x<=160))
        { rollNum[rollPos]=2;
          printmyDigit(rollPos);
          rollPos++;
            }
          
        if ((x>=160) && (x<=240))
        { rollNum[rollPos]=3;
          printmyDigit(rollPos);
          rollPos++;
            }
     }
     
     if (((y>=200) && (y<=240))&&(rollPos<5))
    {
      if ((x>=0) && (x<=80))
        { rollNum[rollPos]=4;
          printmyDigit(rollPos);
          rollPos++;
          }
          
       if ((x>=80) && (x<=160))
        { rollNum[rollPos]=5;
          printmyDigit(rollPos);
          rollPos++;
         }
          
        if ((x>=160) && (x<=240))
        { rollNum[rollPos]=6;
          printmyDigit(rollPos);
          rollPos++;
          }
     }
     
     
      if (((y>=240) && (y<=280))&&(rollPos<5))
    {
      if ((x>=0) && (x<=80))
        { rollNum[rollPos]=7;
          printmyDigit(rollPos);
          rollPos++;
           }
          
       if ((x>=80) && (x<=160))
        { rollNum[rollPos]=8;
          printmyDigit(rollPos);
          rollPos++;
          }
          
        if ((x>=160) && (x<=240))
        { rollNum[rollPos]=9;
          printmyDigit(rollPos);
          rollPos++;
          }
     }
     
     if ((y>=280) && (y<=320))
    {
      if ((x>=0) && (x<=80))
        { if (rollPos>4) {break;}
          
          
           }
          
       if (((x>=80) && (x<=160))&&(rollPos<5))
        { rollNum[rollPos]=0;
          printmyDigit(rollPos);
          rollPos++;
          }
          
        if ((x>=160) && (x<=240))
        { 
          if (rollPos>0) {
            myGLCD.setColor(0, 98, 125);
            rollPos--;
            myGLCD.fillRect(32+rollPos*36, 80, 68+rollPos*36, 130);
             
          }
          
       }
    }
    
   
  
   }
   delay(100);
 }
}
 
 void drawCoupon(int currCoupon)
 {myGLCD.setFont(BigFont);
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
  
  
  if (coupon[currCoupon].veg==1) {myGLCD.setColor(59, 159, 5);}    //drawing the green veg symbol
  else {myGLCD.setColor(212, 0, 0);} 
  myGLCD.fillRect(160, 100, 210, 150);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(165, 105, 205, 145);
  if (coupon[currCoupon].veg==1) {myGLCD.setColor(59, 159, 5);}    //drawing the green veg symbol
  else {myGLCD.setColor(212, 0, 0);}
  myGLCD.fillCircle(185, 125, 15);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 98, 125);
  myGLCD.print("You will take", 20, 170);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(coupon[currCoupon].quant, 95, 190);
  
 }
 
void drawButts() 
  { myGLCD.setColor(255, 255, 255);       //draw the +/- buttons
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
       
    if (Touch_DataAvailable())  {
      Touch_Read();
      x=Touch_GetX();
      y=Touch_GetY();
      
      if ((y<=300)&&(y>=240))  {
        
        if ((x>=10)&&(x<=110))  {
          myGLCD.fillScr(0, 98, 125);
          selectCoupons();
          break;  }
          
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
  
   if (Touch_DataAvailable())  {
      Touch_Read();
      x=Touch_GetX();
      y=Touch_GetY();
  
  if ((y>=260)&&(y<=310))  {
    if ((x<=70)&&(x>=20)) {
      if (currCoupon>0) currCoupon--;
      else currCoupon=5;
    }
    
    if ((x>=80)&&(x<=130))  {
      if (currCoupon!=(totCoupon-1))
          {currCoupon++;}
       else {currCoupon=0;}
    }
  
  if ((x>=150)&&(x<=240))  {
    grandTotal();
    confirmScr();
    break;}
  }
  
    
    if ((y>=190)&&(y<=240))  {
    if((x>=30)&&(x<=80))
        { if (coupon[currCoupon].quant>0)
          coupon[currCoupon].quant--;}
    if (( x>=165)&&(x<=210))
      {coupon[currCoupon].quant++;}
}
    drawCoupon(currCoupon);

}delay(100);
}}

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
        if(myFile){Serial.println("OKKK!!");
        
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
          {coupon[k].quant=0;}
 
          sum=0;
}

void grandTotal()
{  sum=0;
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
  myGLCD.setFont(SevenSegNumFont);
  if (!SD.begin(chipSelect)) {
    return;
  }
  res=file.initFAT();
  myGLCD.setColor(255,255,255);

  Touch_Init();
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



void loop()
{ 
 // getRollNum();
 // verifyFinger();
  //res=myGLCD.loadBitmap(0, 0, 240, 320, "ready.raw");
  delay(1000);
  myGLCD.fillScr(0, 98,125);
  selectCoupons();
   

  savetoSD();
  reset();
}
