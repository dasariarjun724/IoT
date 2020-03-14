// include the library code:
#include <LiquidCrystal.h> //library for LCD
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 7, 6, 5, 4);
 
//Measuring Current Using ACS712
 
const int analogchannel = 0; //Connect current sensor with A0 of Arduino
int sensitivity = 185; // use 100 for 20A Module and 66 for 30A Module
float adcvalue= 0;
int offsetvoltage = 2500; 
double Voltage = 0; //voltage measuring
double ecurrent = 0;// Current measuring
 
void setup() {
 //baud rate
 Serial.begin(9600);//baud rate at which arduino communicates with Laptop/PC
 // set up the LCD's number of columns and rows:
 lcd.begin(20, 4); //LCD order
 // Print a message to the LCD.
 lcd.setCursor(1,1);//Setting cursor on LCD
 lcd.print("MICROCONTROLLERSLAB");//Prints on the LCD
 lcd.setCursor(4,2);
 lcd.print(".com");
 delay(3000);//time delay for 3 sec
 lcd.clear();//clearing the LCD display
 lcd.display();//Turning on the display again
 lcd.setCursor(1,0);//setting LCD cursor
 lcd.print("Reading Values from");//prints on LCD
 lcd.setCursor(1,1);
 lcd.print("DC Current Sensor");
 lcd.setCursor(5,2);
 lcd.print("ACS 712");
 delay(2000);//delay for 2 sec
}
 
void loop() //method to run the source code repeatedly
{
 unsigned int temp=0;
 float maxpoint = 0;
 int i=0;
 for(i=0;i<500;i++)
 {
 if(temp = analogRead(analogchannel),temp>maxpoint)
 {
 maxpoint = temp;
 }
 }
 adcvalue = maxpoint; 
 Voltage = (adcvalue / 1024.0) * 5000; // Gets you mV
 ecurrent = ((Voltage - offsetvoltage) / sensitivity);
 ecurrent = ( ecurrent ) / ( sqrt(2) );
//Prints on the serial port
 Serial.print("Raw Value = " ); // prints on the serial monitor
 Serial.print(adcvalue); //prints the results on the serial monitor
 
 lcd.clear();//clears the display of LCD
 delay(1000);//delay of 1 sec
 lcd.display();
 lcd.setCursor(1,0);
 lcd.print("adc Value = ");
 lcd.setCursor(13,0);
 lcd.print(adcvalue);
 
 Serial.print("\t mV = "); // shows the voltage measured 
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 
 lcd.setCursor(1,1);
 lcd.print("Voltage = ");
 lcd.setCursor(11,1);
 lcd.print(Voltage,3);
 lcd.setCursor(17,1);
 lcd.print("mV");//Unit for the voltages to be measured
 
 Serial.print("\t ecurrent = "); // shows the voltage measured 
 Serial.println(ecurrent,3);// the '3' after voltage allows you to display 3 digits after decimal point
 
 lcd.setCursor(1,2);
 lcd.print("ac Current = ");
 lcd.setCursor(11,2);
 lcd.print(ecurrent,3);
 lcd.setCursor(16,2);
 lcd.print("A"); //unit for the current to be measured
 delay(2500); //delay of 2.5 sec
}
