
int xPin=A2;
int yPin=A1;

int LB=5;     //Left Back
int LF=6;     //Left Forward
int RF=7;    //Right Forward
int RB=8;    //Right Back

void setup(){
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  Serial.begin(9600);
  pinMode(LB,OUTPUT);
  pinMode(LF,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RB,OUTPUT);
}


void loop() 
{
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);
  
  if ((xval>294 && xval<340) && (yval>294 && yval<340)) //stop
  {
    digitalWrite(LB,LOW);  
    digitalWrite(LF,LOW);   
    digitalWrite(RF,LOW);   
    digitalWrite(RB,LOW);
    Serial.println("stop");
  } 

  else 
  { 
    if ((xval>340 && xval<380) && (yval>294 && yval<340)) //forward
   {
     digitalWrite(LF,LOW);  
     digitalWrite(LB,HIGH);   
     digitalWrite(RF,LOW);  
     digitalWrite(RB,HIGH);
     Serial.println("forward"); 
    }
    if ((xval>260 && xval<294) && (yval>294 && yval<350)) //backward
  {
   digitalWrite(LB,LOW);   
   digitalWrite(LF,HIGH);  
   digitalWrite(RB,LOW);   
   digitalWrite(RF,HIGH);
   Serial.println("backward");    
    }   

    if ((xval>294 && xval<340) && (yval>340 && yval<380)) //left
    {
      digitalWrite(LF,LOW);  
      digitalWrite(LB,HIGH);   
      digitalWrite(RF,LOW);   
      digitalWrite(RB,LOW);
      Serial.println("left"); 
     }


    if ((xval>294 && xval<340) && (yval<294 && yval>260))//right
    {
      digitalWrite(RF,LOW);  
      digitalWrite(RB,HIGH);   
      digitalWrite(LF,LOW);   
      digitalWrite(LB,LOW);   
      Serial.println("right"); 
    }
  }
}
