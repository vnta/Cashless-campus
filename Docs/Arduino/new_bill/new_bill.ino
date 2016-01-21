#include <SPI.h>
#include <Ethernet.h>

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

String roll, bill;



void setup()  {
  
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dnsl, gateway, subnet);
  
  
  Serial.println("connecting... wait for 30sec");
  delay(30000);
  
  if (client.connect(server, 80)) {
    Serial.println("connected");  }
    
    
   else 
   {
     Serial.println("Connection Failed");
     
     while(1) ;
     
   }
   
   
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
      client.print("GET /update_bill.php?");            // send this to apache on server to call the script "writetemplocalserv.php"
      Serial.print("GET /update_bill.php?");            //
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
   
         
         
}h


void loop() {}
