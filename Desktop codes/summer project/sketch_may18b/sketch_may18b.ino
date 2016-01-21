
#include <UTFT.h>
#include <UTouch.h>
#include <avr/pgmspace.h>
#include <SD.h>

UTFT        myGLCD(ITDB32S, 38,39,40,41);
UTouch      myTouch(6,5,4,3,2);


extern uint8_t BigFont[];



File myFile;
extern unsigned int logo[13225];
int kev=0;
int n;
int x, y;
int p;
int f;
  typedef struct menu{
  String name;
  int quant;
} Menu;


  Menu coupon[6];

void drawButtons()
{
// Draw the upper row of buttons
  
    myGLCD.setColor(0, 255, 255);
    myGLCD.fillRoundRect (10, 10, 150, 60);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (10, 10, 150, 60);
    myGLCD.print(coupon[p].name, 15, 27);
    
    myGLCD.printNumI(coupon[p].quant, 175, 27);
    myGLCD.fillCircle(230, 35, 20);
    myGLCD.fillCircle(290, 35, 20);
    
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawLine(230, 20, 230, 50);
    myGLCD.drawLine(215, 35, 245, 35);
    myGLCD.drawLine(275, 35, 305, 35);

    
    
    

    myGLCD.setColor(0, 255, 255);
    myGLCD.fillRoundRect (10, 70, 150, 120);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (10, 70, 150, 120);
    myGLCD.print(coupon[p+1].name, 15, 87);
  
    myGLCD.printNumI(coupon[p+1].quant, 175, 87);
    myGLCD.fillCircle(230, 95, 20);
    myGLCD.fillCircle(290, 95, 20);
    
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawLine(230, 80, 230, 130);
    myGLCD.drawLine(215, 95, 245, 95);
    myGLCD.drawLine(275, 95, 305, 95);
    
    
  
    myGLCD.setColor(0, 255, 255);
    myGLCD.fillRoundRect (10, 130, 150, 180);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (10, 130, 150, 180);
    myGLCD.print(coupon[p+2].name, 15, 147);
  
    myGLCD.printNumI(coupon[p+2].quant, 175, 147);
    myGLCD.fillCircle(230, 155, 20);
    myGLCD.fillCircle(290, 155, 20);
    
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawLine(230, 140, 230, 190);
    myGLCD.drawLine(215, 155, 245, 155);
    myGLCD.drawLine(275, 155, 305, 155);
    
    
  for (n=0; n<2; n++)
  {
    myGLCD.setColor(0, 255, 0);
    myGLCD.fillRoundRect (10+(n*160), 190, 150+(n*160), 235);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (10+(n*160), 190, 150+(n*160), 235);
    if ((n==0)&&(p==0)) myGLCD.print("More", 25, 207);
    if ((n==0)&&(p==3)) myGLCD.print("Back", 25, 207);
    if (n==1) myGLCD.print("Continue", 175, 207);
  }
  
}

void processScreen()
{ myGLCD.clrScr();
 myGLCD.setColor(VGA_BLACK);
 myGLCD.print( "Processing order...", 10, 100);
}

void setup(){
 
 
  
 Serial.begin(9600);
 pinMode(53, OUTPUT);
  Serial.print("Initializing SD card...");
  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
 
 f=1;
 p=0;
 coupon[0].name="Paneer";
 coupon[1].name="Egg";
 coupon[2].name="Ck Bryani";
 coupon[3].name="Aloo Fry";
 coupon[4].name="Fish";
 coupon[5].name="Chicken";


 
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
    
}

void loop()
{ myGLCD.drawBitmap (100, 100, 115, 115, logo);

  delay(1000);
  myGLCD.clrScr();
  drawButtons();
  while (true)
{
  if (myTouch.dataAvailable())
  {
  myTouch.read();
  x=myTouch.getX();
  y=myTouch.getY();
  
  
  if ((y>=10) && (y<=60))  // Upper row
      { if ((x<=250)&&(x>=210)) { coupon[0+p].quant++;}
        if ((x>=270)&&(x<=310)) { coupon[0+p].quant--;}
      }
      
   if ((y>=70) && (y<=120))  
      { if ((x<=250)&&(x>=210)) { coupon[1+p].quant++;}
        if ((x>=270)&&(x<=310)) { coupon[1+p].quant--;}
      }
      
      
    if ((y>=130) && (y<=180))  
      { if ((x<=250)&&(x>=210)) { coupon[2+p].quant++;}
        if ((x>=270)&&(x<=310)) { coupon[2+p].quant--;}
      }
      
     if ((y>=190) && (y<=240))  
      { if ((x<=150)&&(x>=10))
            { if (p==0) {p=3;}
              else if (p==3) {p=0;}}
        if ((x>=160)&&(x<=310))
      {
        processScreen();}
        myFile= SD.open("orders.txt", FILE_WRITE);
        if(myFile){Serial.println("OKKK!!");
                    while(kev<6){
                     
                      if(coupon[kev].quant){Serial.println("OKKK!!");
                                              myFile.print(coupon[kev].name);
                                              myFile.print(" * ");
                                              myFile.println(coupon[kev].quant);
                                             }
                      kev=kev+1;
                    }
                
                    myFile.println("____________________________________");  
                }
                  
                  myFile.close();
        kev=0;
      }
      
      delay(500);
 myGLCD.clrScr();
  if (f){
    drawButtons();}  
  } 
}
}
