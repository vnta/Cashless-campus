#include <Ethernet.h>           //library for ethernet functions
#include <Client.h>             //library for client functions



// Ethernet settings
uint8_t hwaddr[6] = {  
  0x90, 0xA2, 0xDA, 0x0E, 0x99, 0x4D }; // mac-adress of arduino
uint8_t ipaddr[4] = {172, 24, 9, 206};                    // IP-adress of arduino
uint8_t gwaddr[4] = {172, 24, 15, 254 };                     // IP-adress of gateway ( for later DNS implementation)
uint8_t subnet[4] = {255, 255, 248, 0};                   // subnetmask           ( for later DNS implementation)
uint8_t serverip[4] = {172, 24, 9, 207};                   // IP-adress of server arduino sends data to

uint8_t serverport = 80;                                  // the port the arduino talks to

EthernetClient client;                     // make a new instance from type "Client" named "client", giving it
                                                          // serverip and serverport                                   // yes-no variable (boolean) to store if the arduino is connected to the server
String bill,roll;                                                // variable to count the sendings to the server

void setup(void)                                          // setup-function runs at the startup of the arduino
{

Serial.begin(9600);                                       // start the serial port

Serial.println("Initializing Ethernet.");

Ethernet. begin(hwaddr, ipaddr);                          // start up ethernet
}                                       // start up the library



          // store the number of sensors to the variable numSensors,
// "sensors.getDeviceCount" is a function in the library

void loop()                                           // loop function runs over and over again
{
if(!client.connected)   {                                        // if "not" connected print: not connected ;)
Serial.println("Not connected");

if (client.connect()){                                    // if connected, set variable connected to "true" and
connected = true;
sensors.requestTemperatures();                            // send the request for temperature to sensors (all sensors)

for(i=0; i<100; i++)                               // as long as "i" ( chosen number, starts at 0) is smaller than
                                                          //"numSensors" (number of sensors) do the "for" cycle
{
                  // take temperature reading from sensor "i" and store it to the variable "temp"
Serial.print("Enter roll ");
roll=Serial.read();                                  // just to see if the reading was succesful in serial console
Serial.println(roll);
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
Serial.print("&&"):
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
delay(599500);                                            // send the temperature every 10 minutes 599500 + 500 milliseconds (down below)
}
}
else{
Serial.println("Cannot connect to Server");               //  else block if the server connection fails (debugging)

}
}
else {

delay(500);                                               //
while (client.connected() && client.available()) {        // when connected and availabe:
char c = client.read();                                   // read the answer of the server and
Serial.print(c);                                          // print it to serial port
}                                                         //
Serial.println();                                         //
client.stop();                                            //  stop the connection and set
connected = false;                                        //  "connected" to false

}
}

