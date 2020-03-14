#include <DS3231.h>
#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
const int pingPin = 10; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 12; // Echo Pin of Ultrasonic Sensor
float cm=0;
int m=13,p=6,o=7; //g-Green r-RED m=motor1 
String ct,cmm,chh;
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
bool flag=true,on=false;
void setup() {
 Serial.begin(115200); // Starting Serial Terminal
 mySerial.begin(9600);//Begin serial communication with Arduino and SIM800L
 pinMode(m,OUTPUT);
 pinMode(p,OUTPUT);
 pinMode(o,OUTPUT);
 pinMode(8,INPUT);
 digitalWrite(p,LOW);
 digitalWrite(o,LOW);
 digitalWrite(m,LOW);
 rtc.begin();
 sendSms("Started....");
 
 /*rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
 rtc.setTime(18, 46, 0);     // Set the time to 12:00:00 (24hr format)
 rtc.setDate(19, 3, 2019);   // Set the date to January 1st, 2014*/
}

void loop() {
 cm=distanceInCm();
 ct=rtc.getTimeStr();
 chh=ct.substring(0,2);
 cmm=ct.substring(3,5);
 Serial.println(ct);
 Serial.print(cm);
 if((cm>7)&&flag){
   String temp = "FEED IS LESS THAN 5% AT @ ";
   temp.concat(ct);
   sendSms(temp);
   flag=false;
  Serial.println(">7");
 }
 else if((cm<=7)&&(!flag)){
  Serial.println("<=7");
  flag=true;
 }
 if(cmm=="30"||!on){
  digitalWrite(m,LOW);
 }
 else if(chh=="6"||chh=="11"||chh=="16"||chh=="22"||on||digitalRead(8)||true){
   digitalWrite(m,HIGH);
   digitalWrite(o,HIGH);
   delay(100);
   digitalWrite(o,LOW);
   digitalWrite(p,HIGH);
   delay(100);
   digitalWrite(p,LOW);  
 }
 
 receiveSms();
}

float distanceInCm(){
   long duration, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   delay(100);
   return(microsecondsToCentimeters(duration));
}
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
void sendSms(String msg){
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+917997745484\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(msg); //text content
  updateSerial();
  mySerial.write(26);
}

void receiveSms(){
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
}


void del(){
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGD=1");//delete msg at index 1
  updateSerial();
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
    if(mySerial.read()=='Q'||mySerial.read()=='q'){
      Serial.println("Success");
      sendAlert();
    }
    else if(mySerial.read()=='O'||mySerial.read()=='o'){
      on=true;
    }
    else if(mySerial.read()=='F'||mySerial.read()=='f'){
      on=false;
    }
  }
}
void sendAlert(){
  if(distanceInCm()<=3){
    sendSms("More than 80% feed is remained");
  }
  else if(distanceInCm()>3&&distanceInCm()<=5){
    sendSms("50%-80% feed is remained");
  }
  else if(distanceInCm()>5&&distanceInCm()<7){
   sendSms("30%-50% feed is remained");
  }
  else if(distanceInCm()>=7){
    sendSms("Less than 5% feed is remained");
  }
  del();
}
