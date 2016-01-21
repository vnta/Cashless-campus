
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
//char page123[]= "test1";
typedef struct menu{
  String name;
  int quant;
  int rate;
  int veg;        //veg=1 for veg, veg=0 for non-veg
} 
Menu;


Menu coupon[10];

typedef struct person  {
  String name;
  int rollNumber;
  int ID;
}
Person;
EthernetClient client;

int totCoupon;
int i;
int inc;

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

}
  

void setup() {
  
  inc=0;
  
  Serial.begin(9600);
  Ethernet.begin(mac, ip,dns1,gateway,subnet);
  Serial.println("connecting... wait for 30sec");
  delay(1000);

  
 
}

void loop()
{
  
}


