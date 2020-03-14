#include<SoftwareSerial.h>
#include <TinyGPS++.h>
/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,11); /* (Rx,Tx) */  
static const int RXPin = A1, TXPin = A0;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

#define r1 3
#define g1 4
#define r2 5
#define g2 6
#define r3 7
#define g3 8
String message="",cmd="";
  int s1,s2,s3;
  float v1,v2,v3;
  char character;
void setup() {
   bt.begin(9600); /* Define baud rate for software serial communication */
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(9, INPUT);
    Serial.begin(115200);
     ss.begin(GPSBaud);
}

void loop() {
   priority();
    s1 = digitalRead(13);
    s2 = digitalRead(12);
    s3 = digitalRead(9);
    Serial.println(s1);
    Serial.println(s2);
    Serial.println(s3);
 if(s1 == 1 && s2 == 1 && s3 == 1) {
digitalWrite(g1, HIGH);
digitalWrite(r2, HIGH);
digitalWrite(r3, HIGH);
digitalWrite(r1, LOW);
digitalWrite(g2, LOW);
digitalWrite(g3, LOW);
traffic();
delay(5000);
digitalWrite(g2, HIGH);
digitalWrite(r1, HIGH);
digitalWrite(r3, HIGH);
digitalWrite(r2, LOW);
digitalWrite(g1, LOW);
digitalWrite(g3, LOW);
traffic();
delay(5000);
digitalWrite(g3, HIGH);
digitalWrite(r1, HIGH);
digitalWrite(r2, HIGH);
digitalWrite(r3, LOW);
digitalWrite(g1, LOW);
digitalWrite(g2, LOW);
traffic();
delay(5000);
 }
 else{
  traffic();

 }

 while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }


  
}
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
void traffic(){
  priority();
  Serial.println("----------");
  Serial.println(message);
  message.trim();
  if(message.substring(0,1).toFloat()==1){
    v1=message.substring(2,7).toFloat();
    message="";
  }
  else if(message.substring(0,1).toFloat()==2){
    v2=message.substring(2,7).toFloat();
    message="";
  }
  else if(message.substring(0,1).toFloat()==3){
    v3=message.substring(2,7).toFloat();
    message="";
  }
  else Serial.println("nothing");
  Serial.println("----------");
  Serial.println(v1);
  Serial.println(v2);
  Serial.println(v3);
  Serial.println("----------");
   s1 = digitalRead(13);
   s2 = digitalRead(12);
   s3 = digitalRead(9);
 if (s1 == 0&&s2==1&&s3==1)
 {
    Serial.println("Position Acquired at 1");
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(g1, HIGH);
    digitalWrite(g2, LOW);
    digitalWrite(g3, LOW);
    digitalWrite(r1, LOW);
    
    delay(5000);
    traffic();
}

else if (s1==1&&s2 == 0&&s3==1)
{
    Serial.println("Position Acquired at 2");
    digitalWrite(r1, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(g2, HIGH);
    digitalWrite(r2, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(g3, LOW);
    delay(5000);
    traffic();
  
}
else if(s1==1&&s2==1&&s3 == 0)
{
    Serial.println("Position Acquired at 3");
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(g3, HIGH);
    digitalWrite(r3, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(g2, LOW);
    delay(5000);
    traffic();
}
else if(s1==0&&s2==0&&s3==1){
  if(v1>v2){
    Serial.println("Position Acquired at 1");
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(g1, HIGH);
    digitalWrite(g2, LOW);
    digitalWrite(g3, LOW);
    digitalWrite(r1, LOW);
    
    delay(5000);
    traffic();
  }
  else{
    Serial.println("Position Acquired at 2");
    digitalWrite(r1, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(g2, HIGH);
    digitalWrite(r2, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(g3, LOW);
    delay(5000);
    traffic();
  }
}
else if(s1==0&&s2==1&&s3==0){
  if(v1>v3){
    Serial.println("Position Acquired at 1");
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(g1, HIGH);
    digitalWrite(g2, LOW);
    digitalWrite(g3, LOW);
    digitalWrite(r1, LOW);
    
    delay(5000);
    traffic();
  }
  else{
    Serial.println("Position Acquired at 3");
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(g3, HIGH);
    digitalWrite(r3, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(g2, LOW);
    delay(5000);
    traffic();
  }
}
else if(s1==1&&s2==0&&s3==0){
  if(v2>v3){
    Serial.println("Position Acquired at 2");
    digitalWrite(r1, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(g2, HIGH);
    digitalWrite(r2, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(g3, LOW);
    delay(5000);
    traffic();
  }
  else{
    Serial.println("Position Acquired at 3");
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(g3, HIGH);
    digitalWrite(r3, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(g2, LOW);
    delay(5000);
    traffic();
  }
}
}
void priority(){
  while(bt.available()){
    character = bt.read();
    
   if(character == '#'){ // if end of message received
     Serial.print(cmd); //display message and
     message=cmd;
     cmd = ""; //clear buffer
     Serial.println();
  }
  else cmd.concat(character);
   }
}
