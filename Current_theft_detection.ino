// include the library code:
#include <LiquidCrystal.h> //library for LCD
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #4 & #3

int rs=13,en=12,d4=7,d5=6,d6=5,d7=4; 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
//Measuring Current Using ACS712
 int relay=9,ir=11;
const int sensorIn = A0; //Connect current sensor with A0 of Arduino
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

double ecurrent = 0;// Current measuring
 
void setup() {
  mySerial.begin(9600); //Begin serial communication with Arduino and SIM800L
 //baud rate
 pinMode(relay,OUTPUT);
 Serial.begin(115200);//baud rate at which arduino communicates with Laptop/PC
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2); //LCD order
 // Print a message to the LCD.
 lcd.setCursor(0,0);//Setting cursor on LCD
 lcd.print("System Started!");//Prints on the LCD
 delay(3000);//time delay for 3 sec
 lcd.clear();//clearing the LCD display
 lcd.display();//Turning on the display again
 digitalWrite(relay,LOW);
 delay(2000);//delay for 2 sec
 sendMsg("Started!");
}
 
void loop() //method to run the source code repeatedly
{
 Voltage = getVPP();
VRMS = (Voltage/2.0) *0.707; //root 2 is 0.707
AmpsRMS = (VRMS * 1000)/mVperAmp;


 ecurrent = AmpsRMS;
//Prints on the serial port
 lcd.clear();//clears the display of LCD
 if(digitalRead(ir)==HIGH){
     if(ecurrent<0.207){
       lcd.setCursor(0,0);
       lcd.print("Voltage = ");
       lcd.setCursor(0,1);
       lcd.print(Voltage,3);
       lcd.print(" mV");//Unit for the voltages to be measured
       delay(1000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Current = ");
       lcd.setCursor(0,1);
       lcd.print(ecurrent,3);
       lcd.print(" A"); //unit for the current to be measured
       delay(1000); //delay of 2.5 sec
     }
     else{
       double temp=0;
       for(int i=0;i<2;i++){
          Voltage = getVPP();
          VRMS = (Voltage/2.0) *0.707; //root 2 is 0.707
          AmpsRMS = (VRMS * 1000)/mVperAmp;
          if(i==0){
            temp=AmpsRMS;
          }  
          if(AmpsRMS<temp){
            temp=AmpsRMS;
          }
         AmpsRMS=temp;
       }
       Serial.println(AmpsRMS);
       if(AmpsRMS>=0.205){
           digitalWrite(relay,HIGH);
           String msg="overload Detected and the supply is turned off! Current: ";
           msg=msg+AmpsRMS;
           sendMsg(msg+" A");
           delay(5000);
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("overloadDetected");
           lcd.setCursor(0,1);
           lcd.print("sms Alert sent!");
           delay(1000);
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("Supply");
           lcd.setCursor(0,1);
           lcd.print("Turned off!");
           while(true);
       }    
     }
 }
 else
 {
    digitalWrite(relay,HIGH);
       sendMsg("Meter Tamper detected and the supply is turned off!"); 
       delay(5000); 
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Meter Tampered");
       lcd.setCursor(0,1);
       lcd.print("sms Alert sent!");
       delay(1000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Supply");
       lcd.setCursor(0,1);
       lcd.print("Turned off!");
       while(true);
 }
 
}
void sendMsg(String msg){
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+918790641026\"");//change +91 with country code and xxxxxxxxxxx with phone number to sms
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

float getVPP()
{
float result;
int readValue; //value read from the sensor
int maxValue = 0; // store max value here
int minValue = 1024; // store min value here

uint32_t start_time = millis();
while((millis()-start_time) < 2000) //sample for 3 Sec
{
readValue = analogRead(sensorIn);
// see if you have a new maxValue
if (readValue > maxValue)
{
/*record the maximum sensor value*/
maxValue = readValue;
}
if (readValue < minValue)
{
/*record the minimum sensor value*/
minValue = readValue;
}
}

// Subtract min from max
result = ((maxValue - minValue)/1024.0)*5.0;
return result;
}
