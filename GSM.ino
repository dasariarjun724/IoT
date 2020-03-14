/*
 SMS receiver

 This sketch, for the Arduino GSM shield, waits for a SMS message
 and displays it through the Serial port.

 Circuit:
 * GSM shield attached to and Arduino
 * SIM card that can receive SMS messages

 created 25 Feb 2012
 by Javier Zorzano / TD

 This example is in the public domain.

 http://www.arduino.cc/en/Tutorial/GSMExamplesReceiveSMS

*/

// include the GSM library
#include <GSM.h>

// PIN Number for the SIM
#define PINNUMBER ""

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;

// Array to hold the number a SMS is retreived from
char senderNumber[20];
char txtMsg[20];
const int pingPin = 5;
const int echoPin = 6;

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);       
       
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("SMS Messages Receiver");

  // connection state
  boolean notConnected = true;

  // Start GSM connection
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");
}

void loop() {
  char c;
  itoa(distance(),txtMsg, 10);  

  
  // If there are any SMSs available()
  if (sms.available()) {
    Serial.println("Message received from:");

    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);

    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#') {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    String msg="";
    while (c = sms.read()) {
      //Serial.print(c);
      msg=msg+c;
    }
    if(msg=="q"){
      sms.beginSMS(senderNumber);
      sms.print(txtMsg);
      sms.endSMS();
    }
    Serial.println("\nEND OF MESSAGE");

    // Delete message from modem memory
    sms.flush();
    Serial.println("MESSAGE DELETED");
  }

  delay(1000);

}
int distance(){

long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   /*Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();*/
   delay(100);
   return cm;
}
long microsecondsToInches(long microseconds) 
{
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
 {
  return microseconds / 29 / 2;
}
