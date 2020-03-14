#include "DHT.h"
#include <TinyGPS++.h>
#define DHTPIN 3
#define DHTTYPE DHT11
#include <SoftwareSerial.h>
static const int RXPin = 7, TXPin = 8;
static const uint32_t GPSBaud = 9600;
String msg1="",loc="";
unsigned long t1=0;
unsigned long t2=0; 
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(10, 9); //SIM800L Tx & Rx is connected to Arduino #3 & #2
int pingPin =5 ; // Trigger Pin of Ultrasonic Sensor
int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int water=2;
int vib=4;
bool flag=true;
DHT dht(DHTPIN, DHTTYPE);
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
float h,t;
void setup(){
  Serial.begin(115200);
  mySerial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(water,INPUT);
  pinMode(vib,OUTPUT);
  dht.begin();
  sendSms("Started...");
}
void loop() {
    msg1="";
   while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
    else{ 
      msg1="Location: ";
      msg1=msg1+"Invalid";
    }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println(t);
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    flag=true;
    //return;
  }
    gps1();
  //delay(2000);
  if(flag){
    t1=millis();
    
    flag=false;
  }  
  if(distance()<100||digitalRead(water)){
    digitalWrite(vib,HIGH);  
  }
  else{
    digitalWrite(vib,LOW); 
  }
  
  t2=millis();
  if(t2-t1>10000){
    flag=true;
    sendSms(msg1);
  }
  
}

void sendSms(String msg){
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+917729938148\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(msg); //text content
  updateSerial();
  mySerial.write(26);
  Serial.println("sms sent here");
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

int distance(){
  long duration,cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.println(cm);
   return cm;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
void gps1(){
   
  msg1=loc+"Temp:"+t+"Hum:"+h;
}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  { Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    loc="Location:";
    loc=loc+gps.location.lat();
    loc=loc+',';   
    loc=loc+gps.location.lng();
  }
  else
  {
    Serial.print(F("INVALID"));
    loc="Location:";
    loc=loc+"invalid";
  }
}
