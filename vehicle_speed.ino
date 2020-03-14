#include <LiquidCrystal.h>
const int rs = 43, en = 45, d4 = 47, d5 = 49, d6 = 51, d7 = 53;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int sen1=16;
int sen2=15;
unsigned long t1=0;
unsigned long t2=0; 
float velocity;
void setup()
{
  lcd.begin(16, 2);
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print(" Speed Detector ");
}

void loop() 
{
  while(digitalRead(sen1));
  while(digitalRead(sen1)==0);
  t1=millis();
  while(digitalRead(sen2));
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
  
}
