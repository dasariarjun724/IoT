#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
#include "secrets.h"
#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
float t=0,h=0;
int s=0;
byte mac[] = SECRET_MAC;

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2


// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 99);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

unsigned long myChannelNumber = 717580;
const char * myWriteAPIKey = "88ZI2MG361JYEJ9E";

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  dht.begin();
  mySerial.begin(9600); //Begin serial communication with Arduino and SIM800L
  Ethernet.init(10);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
    
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  sendMsg("working fine!");
}

void loop() {
  soil();
  temp();
  // set the fields with the values
  ThingSpeak.setField(1, s);
  ThingSpeak.setField(2, t);
  ThingSpeak.setField(3, h);

  
  // write to the ThingSpeak channel 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }  
  if(t>29&&t<33){
    sendMsg("brownplanthopper");
  }
  else if(t>23&&t<29){
    sendMsg("Green leaf Hopper");
  }
  else if(t>18&&t<23){
    sendMsg("Gallmidge");
  }
  delay(20000); // Wait 20 seconds to update the channel again
  Serial.println("loop");
  
}
void temp(){
  delay(1000);
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
 

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return temp();
  }
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("\n");
}
void soil(){
   s= analogRead(A0);

   s = map(s,550,0,0,100);

   Serial.print("Mositure : ");

   Serial.print(s);

   Serial.println("%");
   delay(1000);
}
void sendMsg(String msg){
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+918019099939\"");//change +91 with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(msg); //text content
  updateSerial();
  mySerial.write(26);
}
void updateSerial()   
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
