#include <LiquidCrystal.h>


#define gasPin A0


void setup() {
 Serial.begin(9600);

}

void loop() {
  
int gasSensor = analogRead(gasPin);

  if (gasSensor > 350)
  {
     
     Serial.print("Value : "); 
     Serial.print(gasSensor);
     Serial.print("\t");
     Serial.print(map(gasSensor,0,1023,0,100));
     Serial.print("\t");
     Serial.println("Gas is Detected");   
     delay(300); 
  }
  else if (gasSensor < 350)
  {
    
     Serial.println("No Gas");   
     delay(300);
  }
  
}
