/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 modified 9 Apr 2012
 by David A. Mellis
 
 */

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
IPAddress server(172,24,9,207); // Google
//char page123[]= "test1";

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


String coupon_name[10],coupon_price[10];
int i,inc;

void setup() {
  // Open serial communications and wait for port to open:
  
  inc=0;
  i=0;
  Serial.begin(9600);


  // start the Ethernet connection:
  Ethernet.begin(mac, ip,dns1,gateway,subnet);
  // Serial.println("Failed to configure Ethernet using DHCP");
  // no point in carrying on, so do nothing forevermore:
  // for(;;)
  ;
  //}
  // give the Ethernet shield a second to initialize:
  
  Serial.println("connecting... wait for 30sec");
  delay(30000);

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /forarduino.php HTTP/1.0");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
    if (c == '^')

    { 
      c=client.read();
      while(c != '^')

      {

      
        coupon_name[inc]= client.readStringUntil('#') ;
        Serial.println("Read");
        Serial.println(coupon_name[inc]);
        coupon_price[inc]= client.readStringUntil('*') ;
        Serial.println(coupon_price[inc]);
        inc=inc+1;
        c=client.read();
      }
    }
  }
  
  
  

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}


