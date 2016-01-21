#include <Ethernet.h>           //library for ethernet functions
#include <Client.h>             //library for client functions
#include <DallasTemperature.h>  //library for temperature sensors
//#include <stdint.h>
#include <OneWire.h>            //library for the onewire bus

#define ONE_WIRE_BUS     7      //the onewire bus is connected to pin 7 on arduino
#define TEMPERATURE_PRECISION  10 //resolution of the sensors is set to 10bit

// Ethernet settings
uint8_t hwaddr[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xBE}; // mac-adress of arduino
uint8_t ipaddr[4] = {192, 168, 0, 17};                    // IP-adress of arduino
uint8_t gwaddr[4] = {192, 168, 0, 1};                     // IP-adress of gateway ( for later DNS implementation)
uint8_t subnet[4] = {255, 255, 255, 0};                   // subnetmask           ( for later DNS implementation)
uint8_t serverip[4] = {192, 168, 0, 4};                   // IP-adress of server arduino sends data to

uint8_t serverport = 80;                                  // the port the arduino talks to

Client client(serverip, serverport);                      // make a new instance from type "Client" named "client", giving it
                                                          // serverip and serverport

OneWire oneWire(ONE_WIRE_BUS);                            // setup a oneWire instance to communicate with any OneWire devices
                                                          // (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire);                      // Pass our oneWire reference to Dallas Temperature

int numSensors;                                           // variable to store the number of sensors

bool connected = false;                                   // yes-no variable (boolean) to store if the arduino is connected to the server
int i = 0;                                                // variable to count the sendings to the server

void setup(void)                                          // setup-function runs at the startup of the arduino
{

Serial.begin(9600);                                       // start the serial port
Serial.println("I2C-to-Ethernet Bridge.");
Serial.println("Initializing Ethernet.");

Ethernet. begin(hwaddr, ipaddr);                          // start up ethernet
sensors.begin();                                          // start up the library

Serial.println("Enumerating and scanning for I2C sensors.");

numSensors = sensors.getDeviceCount();                    // store the number of sensors to the variable numSensors,
// "sensors.getDeviceCount" is a function in the library

if(numSensors > 0)                                        // if there is at least one sensor:
{
Serial.print("Enumerated ");                              //print the number of sensors to serial port
Serial.print(numSensors);
Serial.println( " sensors.");

}
else                                                      //if there is no sensor:
{
Serial.println("No sensors enumerated.");                 // tell the serial port
}

}

void loop(void)                                           // loop function runs over and over again
{
if(!connected)   {                                        // if "not" connected print: not connected ;)
Serial.println("Not connected");

if (client.connect()){                                    // if connected, set variable connected to "true" and
connected = true;
sensors.requestTemperatures();                            // send the request for temperature to sensors (all sensors)

for(i=0; i<numSensors; i++)                               // as long as "i" ( chosen number, starts at 0) is smaller than
                                                          //"numSensors" (number of sensors) do the "for" cycle
{
int temp = sensors.getTempCByIndex(i);                    // take temperature reading from sensor "i" and store it to the variable "temp"
Serial.print("Temp is ");                                 // just to see if the reading was succesful in serial console
Serial.println(temp);
Serial.println("Sending to Server: ");                    // all the "Serial.print" is for debugging and to show other people what arduino does
client.print("GET /writetemplocalserv.php?t");            // send this to apache on server to call the script "writetemplocalserv.php"
Serial.print("GET /writetemplocalserv.php?t");            //
client.print(i);                                          // give it the temp on sensor "i" to the script
Serial.print(i);
client.print("=");
Serial.print("=");
client.print(temp);
Serial.print(temp);
client.println(" HTTP/1.1");                  //
Serial.println(" HTTP/1.1");                  //
client.println("Host: www.jfkreuter.com");    //
Serial.println("Host: www.jfkreuter.com");    //
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

