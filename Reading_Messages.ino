#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
char character;
String message="",cmd="";
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
}

void loop()
{
  updateSerial();
  
}

void updateSerial()
{
  int i=0;
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  bool f=false;
  while(mySerial.available()) 
  {
    //Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
   // msg[i]=mySerial.read();
   /*if(mySerial.read()=='Q'){
      Serial.println("success");
    }*/
    character = mySerial.read();
    
   if(character == '#'){ // if end of message received
     Serial.print(cmd); //display message and
     message=cmd;
     cmd = ""; //clear buffer
     Serial.println();
  }
  else if(character == '*')
    f=true;
  else if(f) cmd.concat(character);
   }
  }
