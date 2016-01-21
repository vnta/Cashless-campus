

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0x90, 0xA2, 0xDA, 0x0E, 0x99, 0x4D };
byte ip[] ={ 
  172, 24, 9, 206 };
byte dns1[] ={ 
  172, 31, 1, 1 };
byte gateway[] ={ 
  172, 24, 15, 254 };
byte subnet[] ={ 
  255, 255, 248, 0 };
IPAddress server(172,24,9,207);
EthernetClient client;
int i;
int inc;
int totCoupon;


unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop

typedef struct person  {
  String name;
  int rollNumber;
  int ID;
}
Person;

Person student[10]; 

typedef struct menu{
  String name;
  int quant;
  int rate;
  int veg;        //veg=1 for veg, veg=0 for non-veg
} 
Menu;


Menu coupon[6];

void getMenuWeb()  {
  
  if (client.connect(server, 80)) {
    Serial.println("connected");
   
client.println("GET /sitealpha/forarduino.php HTTP/1.0");
client.println();
while(1)  {
  if (client.available())
  { 
    char c = client.read();
    if (c == '^')

    { 
      c=client.read();
      while(c != '^')

      {
        coupon[inc].name= client.readStringUntil('#') ;
        coupon[inc].rate= client.parseInt();
        coupon[inc].veg=client.parseInt();
        inc=inc+1;
        c=client.read();
      }
      totCoupon=inc-1;
      break;
    }
  }
  

    }
  }
  
   else {
    Serial.println("connection failed");
  }
  
  delay(1000);
  
      
      if (client.connected()) {
       client.stop();}
       
}



void updateBillEthernet(int roll, int bill)  {
  
 
  if (client.connect(server, 80)) 
  {
    Serial.println("connected");
    
    Serial.println("Sending to Server: ");                    // all the "Serial.print" is for debugging and to show other people what arduino does
      client.print("GET /sitealpha/update_bill.php?");            // send this to apache on server to call the script "writetemplocalserv.php"
      Serial.print("GET /sitealpha/update_bill.php?");            //
      client.print("Roll");                                          // give it the temp on sensor "i" to the script
      Serial.print("Roll");
      client.print("=");
      Serial.print("=");
      client.print(roll);
      Serial.print(roll);
      client.print("&");
      Serial.print("&");
      client.print("Bill");                                          // give it the temp on sensor "i" to the script
      Serial.print("Bill");
      client.print("=");
      Serial.print("=");
      client.print(bill);
      Serial.print(bill);


     client.println(" HTTP/1.1");                  //
      Serial.println(" HTTP/1.1");
      client.println("Host: 172.24.9.207");         //
      Serial.println("Host: 172.24.9.207");         //
      client.println("User-Agent: Arduino");        // ethernet related stuff
      Serial.println("User-Agent: Arduino");        //
      client.println("Accept: text/html");          //
      Serial.println("Accept: text/html");          //
      client.println("Connection: close");        //
      Serial.println("Connection: close");        //
      client.println();                             //
      Serial.println();
      
    
  }

  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }   
  
  delay(1000);
  
      if(client.available())  {
        char c= client.read();
        Serial.print(c);
      }
      
      if (client.connected()) {
        Serial.println("flag");
       client.stop();}
}


void setup() {
  // Open serial communications and wait for port to open:


  i=0;
  inc=0;
  Serial.begin(9600);
  pinMode(53, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
   
  Ethernet.begin(mac, ip,dns1,gateway,subnet);
  Serial.println("Connecting... wait for 30sec");
  delay(30000); 
  
}


void loop()
{ getMenuWeb();
  delay(1000);
  updateBillEthernet(12177, 100);
  delay(1000);
  updateBillEthernet(12810, 100);
  delay(1000);
  updateBillEthernet(12810, 500);
  while(1);
}





