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


String roll,bill;
int i;

void setup() {
  // Open serial communications and wait for port to open:


  i=0;
  Serial.begin(9600);


  // start the Ethernet connection:
  Ethernet.begin(mac, ip,dns1,gateway,subnet);
  // Serial.println("Failed to configure Ethernet using DHCP");
  // no point in carrying on, so do nothing forevermore:
  // for(;;)

  //}
  // give the Ethernet shield a second to initialize:



  // if you get a connection, report back via serial:
}


void loop()
{
  Serial.println("connecting... wait for 30sec");
  delay(30000); 
  if (client.connect(server, 80)) 
  {
    Serial.println("connected");
    // Make a HTTP request:

   /* for(i=0; i<2; i++)                               // as long as "i" ( chosen number, starts at 0) is smaller than
      //"numSensors" (number of sensors) do the "for" cycle
    {
      Serial.print("Enter roll ");
      roll=Serial.readString();
      delay(2000);
      Serial.println(roll);
      Serial.print("Enter bill ");
      bill=Serial.readString();
      delay(2000);
      // just to see if the reading was succesful in serial console
      Serial.println(bill);
      Serial.println("Sending to Server: ");                    // all the "Serial.print" is for debugging and to show other people what arduino does
      client.print("GET /update_bill.php?t");            // send this to apache on server to call the script "writetemplocalserv.php"
      Serial.print("GET /update_bill.php?t");            //
      client.print("Roll");                                          // give it the temp on sensor "i" to the script
      Serial.print("Roll");
      client.print("=");
      Serial.print("=");
      client.print(roll);
      Serial.print(roll);
      client.print("&&");
      Serial.print("&&");
      client.print("Bill");                                          // give it the temp on sensor "i" to the script
      Serial.print("Bill");
      client.print("=");
      Serial.print("=");
      client.print(bill);
      Serial.print(bill);


      client.println(" HTTP/1.1");                  //
      Serial.println(" HTTP/1.1");                  //
      client.println("Host: 172.24.9.207");    //
      Serial.println("Host: 172.24.9.207");    //
      client.println("User-Agent: Arduino");        // ethernet related stuff
      Serial.println("User-Agent: Arduino");        //
      client.println("Accept: text/html");          //
      Serial.println("Accept: text/html");          //
      //client.println("Connection: close");        //
      //Serial.println("Connection: close");        //
      client.println();                             //
      Serial.println();
      delay(500);                                           
    }*/
  }

else {
  // kf you didn't get a connection to the server:
  Serial.println("connection failed");
}
 client.print("GET /sitealpha/edit.php?t");

// if there are incoming bytes available 
// from the server, read them and print them:
delay(500);                                               
while (client.connected() && client.available()) {        
  char c = client.read();                                   // read the answer of the server and
  Serial.print(c);                                          // print it to serial port
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




