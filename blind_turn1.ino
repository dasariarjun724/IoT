#include <LiquidCrystal.h>
#include <SFE_BMP180.h>
#include <Wire.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SFE_BMP180 pressure;

double baseline; // baseline pressure
int sen1=8;
int sen2=9;

unsigned long t1=0;
unsigned long t2=0; 
 int g=12,r=11;
float velocity;
void setup()
{
  lcd.begin(16, 2);
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  digitalWrite(g,HIGH);
  digitalWrite(r,LOW);  
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print(" Speed Detector ");
  /*if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }*/

}

void loop() 
{
  while(digitalRead(sen1));
  while(digitalRead(sen1)==0);
  baseline = getPressure();
  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");  
  if(digitalRead(baseline>995){
      digitalWrite(g,LOW);
      digitalWrite(r,HIGH); 
      Serial.println("vehicle ahead!");   
  }
  t1=millis();
  while(digitalRead(sen2));
  digitalWrite(g,LOW);
      digitalWrite(r,HIGH); 
  t2=millis();
  velocity=t2-t1;
  velocity=velocity/1000;//convert millisecond to second
  velocity=(0.205/velocity);//v=d/t
  velocity=velocity*3600;//multiply by seconds per hr
  velocity=velocity/1000;//division by meters per Km
  for(int i=5;i>0;i--)
  {
   lcd.setCursor(3,1);
   lcd.print(velocity);
   lcd.print(" Km/hr   ");
   delay(500);
   lcd.setCursor(3,1);
   lcd.print("            ");
   delay(500);
  }  
  digitalWrite(r,LOW);
  digitalWrite(g,HIGH);
}






double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}
