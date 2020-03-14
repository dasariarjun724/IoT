int a1=12,a2=11,a3=10,a4=9,rmb=8,rmf=7,lmf=6,lmb=5,echoPin=2,pingPin=3;
long cm;
void setup() {
  Serial.begin(9600);
  pinMode(a1,INPUT);
  pinMode(a2,INPUT);
  pinMode(a3,INPUT);
  pinMode(a4,INPUT);
  pinMode(rmf,OUTPUT);
  pinMode(rmb,OUTPUT);
  pinMode(lmf,OUTPUT);
  pinMode(lmb,OUTPUT);
}

void loop() {
  cm=distance();
  Serial.println(cm);
  Serial.print(digitalRead(a1));
  Serial.print(digitalRead(a2));
  Serial.print(digitalRead(a3));
  Serial.println(digitalRead(a4));
  if(cm>40){
      if(digitalRead(a1)==HIGH&&digitalRead(a2)==HIGH&&digitalRead(a3)==HIGH&&digitalRead(a4)==HIGH){
        digitalWrite(rmf,LOW);
        digitalWrite(rmb,LOW);
        digitalWrite(lmf,LOW);
        digitalWrite(lmb,LOW);
      }
      else if(digitalRead(a1)==HIGH&&digitalRead(a2)==HIGH&&digitalRead(a3)==LOW&&digitalRead(a4)==HIGH){//Forward
        digitalWrite(rmf,HIGH);
        digitalWrite(rmb,LOW);
        digitalWrite(lmf,HIGH);
        digitalWrite(lmb,LOW);
      }
      else if(digitalRead(a1)==HIGH&&digitalRead(a2)==LOW&&digitalRead(a3)==HIGH&&digitalRead(a4)==HIGH){//back
        digitalWrite(rmf,LOW);
        digitalWrite(rmb,HIGH);
        digitalWrite(lmf,LOW);
        digitalWrite(lmb,HIGH);
      } 
      else if(digitalRead(a1)==HIGH&&digitalRead(a2)==HIGH&&digitalRead(a3)==HIGH&&digitalRead(a4)==LOW){//right
        digitalWrite(rmf,LOW);
        digitalWrite(rmb,HIGH);
        digitalWrite(lmf,HIGH);
        digitalWrite(lmb,LOW);
      } 
      else if(digitalRead(a1)==LOW&&digitalRead(a2)==HIGH&&digitalRead(a3)==HIGH&&digitalRead(a4)==HIGH){//left
        digitalWrite(rmf,HIGH);
        digitalWrite(rmb,LOW);
        digitalWrite(lmf,LOW);
        digitalWrite(lmb,HIGH);
      }
  }
  else{
    analogWrite(rmf,15*cm);
    digitalWrite(rmb,LOW);
    analogWrite(lmf,15*cm);
    digitalWrite(lmb,LOW);
  }
}

long distance(){
  long duration,dis;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   dis = microsecondsToCentimeters(duration);
   /*Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();*/
   delay(100);
   return dis;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
} 
