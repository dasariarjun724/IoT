#include<SoftwareSerial.h>
#include <Servo.h>

Servo s1,s2,s3; 
bool flag=true;
// The serial connection to the GPS device

int input='0';
int pbuz=3,pmetal=2;
int metal;
void setup()
{
pinMode(11,OUTPUT);
pinMode(9,OUTPUT);
pinMode(8,OUTPUT);
pinMode(10,OUTPUT);
pinMode(pbuz,OUTPUT);
Serial.begin(9600);
s1.attach(5); 
  s2.attach(6);
  s3.attach(4);
  s3.write(0);
  s2.write(90);
  delay(1000);
  s1.write(0);


}
void loop()
{
  digitalWrite(pbuz,LOW);
  metal=digitalRead(pmetal);
if(Serial.available()>0)
{
input = Serial.read();
Serial.println(input);
}
  if(metal==HIGH){
     digitalWrite(pbuz,LOW);
      if(input == '4') //Front
      {
      digitalWrite(11,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(10,HIGH);
      }
      else if(input == '3') //Back
      {
      digitalWrite(11,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(10,LOW);
      
      }
      
      //right
      else if(input == '2')
      {
      digitalWrite(11,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(10,LOW);
      }
      
      //left
      else if(input == '1')
      {
      digitalWrite(11,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(10,HIGH);
      }
       else if(input=='5'){ //up
        Serial.print("up");
        s2.write(90);
        delay(1000);
        s1.write(0);
        delay(500);
      }
      else if(input=='6'){//down
        Serial.print("down");
        s1.write(180);
        s2.write(90);
        delay(1000);
        s2.write(0);
        delay(500);
      }
     else if(input=='7'){//open
      Serial.print("open");
      s3.write(90);
      delay(500);
     }
      else if(input=='8'){//close
        Serial.print("close");
      s3.write(0);
      delay(500);
     }
      else if(input == '0')
      {
      digitalWrite(11,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(10,LOW);
      
      }
      Serial.print("0");
      Serial.print("|");
      flag=true;
  }
  else if(metal==LOW){
      flag=false;
      digitalWrite(pbuz,HIGH);
      
      if(input == '4') //Front
      {
      digitalWrite(11,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(10,HIGH);
      }
      else if(input == '3') //Back
      {
      digitalWrite(11,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(10,LOW);
      
      }
      
      //right
      else if(input == '2')
      {
      digitalWrite(11,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(10,LOW);
      }
      
      //left
      else if(input == '1')
      {
      digitalWrite(11,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(10,HIGH);
      }
      
      
      else if(input=='5'){ //up
        s2.write(90);
        delay(1000);
        s1.write(0);
        delay(500);
      }
      else if(input=='6'){//down
        s1.write(180);
        s2.write(90);
        delay(1000);
        s2.write(0);
        delay(500);
      }
     else if(input=='7'){//open
      s3.write(90);
      delay(500);
     }
      else if(input=='8'){//close
      s3.write(0);
      delay(500);
     }
     else if(input=='0'){
      Serial.println("0");
     }
  
}
}
