#include <DS3231.h>
#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
const int pingPin = 10; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 12; // Echo Pin of Ultrasonic Sensor
float cm=0;
int g=6,r=7,m=8; //g-Green r-RED m=motor1 
String ct,cmm,chh;
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
bool flag=true;
void setup() {
 Serial.begin(115200); // Starting Serial Terminal
 mySerial.begin(9600);//Begin serial communication with Arduino and SIM800L
 pinMode(g,OUTPUT);
 pinMode(r,OUTPUT);
 pinMode(m,OUTPUT);
 digitalWrite(g,HIGH);
 digitalWrite(m,LOW);
 digitalWrite(r,LOW);
 rtc.begin();
 /*rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
 rtc.setTime(0, 30, 0);     // Set the time to 12:00:00 (24hr format)
 rtc.setDate(15, 3, 2019);   // Set the date to January 1st, 2014*/
}

void loop() {
 cm=distanceInCm();
 ct=rtc.getTimeStr();
 chh=ct.substring(0,2);
 cmm=ct.substring(3,5);
 Serial.println(ct);
 Serial.print(cm);
 if((cm>=30)&&flag){
   String temp = "FEED IS LESS THAN 15% AT @ ";
   temp.concat(ct);
   sendSms(temp);
   digitalWrite(r,HIGH);
   digitalWrite(g,LOW);
   flag=false;
   Serial.println(">30");
 }
 else if((cm<30)&&(!flag)){
  Serial.println("<30");
  flag=true;
 }
 if(chh=="6"||chh=="11"||chh=="16"||chh=="22"){
   digitalWrite(m,HIGH); 
 }
 if(cmm=="30"){
  digitalWrite(m,LOW);
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
  mySerial.println("AT+CMGS=\"+919703210148\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
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
    if(mySerial.read()=='Q'){
      Serial.println("Success");
      sendAlert();
    }
  }
}
void sendAlert(){
  if(distanceInCm()<=10){
    sendSms("More than 80% feed is remained");
  }
  else if(distanceInCm()>10&&distanceInCm()<=20){
    sendSms("50%-80% feed is remained");
  }
  else if(distanceInCm()>20&&distanceInCm()<30){
   sendSms("30%-50% feed is remained");
  }
  else if(distanceInCm()>=30){
    sendSms("Less than 15% feed is remained");
  }
  del();
}
