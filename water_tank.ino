int s=4,t0=5,t1=6,t2=7;
int m1=2,m2=3;
bool f=true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(s,INPUT_PULLUP);
  pinMode(t0,INPUT_PULLUP);
  pinMode(t1,INPUT_PULLUP);
  pinMode(t2,INPUT_PULLUP);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(t0));
  Serial.print(digitalRead(t1));
  Serial.print(digitalRead(t2));
  Serial.print(digitalRead(s));
  Serial.println("");
  if(digitalRead(t2)==LOW){
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
  }
  else{
    Serial.println("1");
    if(digitalRead(s)==LOW&digitalRead(t0)==LOW)
    {
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
    }
    else if(digitalRead(s)==LOW&digitalRead(t0)==HIGH){ //sump
       if(f){       
          f=false; 
          digitalWrite(m1,HIGH);
          digitalWrite(m2,LOW);
          while(true){
            if(digitalRead(t2)==LOW){
              digitalWrite(m1,LOW);
              digitalWrite(m2,LOW);
              break;
            }
            else if(digitalRead(s)==HIGH&digitalRead(t0)==HIGH){
              digitalWrite(m1,LOW);
              digitalWrite(m2,HIGH);
              while(true){
                 if(digitalRead(t2)==LOW){
                  digitalWrite(m1,LOW);
                  digitalWrite(m2,LOW);
                  break;
                }
              }
              break;
            }
          }
       }
       else{
        f=true;
          digitalWrite(m1,LOW);
          digitalWrite(m2,HIGH);
          while(true){
             if(digitalRead(t2)==LOW){
              Serial.println("B");
              digitalWrite(m1,LOW);
              digitalWrite(m2,LOW);
              break;
              }
      }
       }
    }
    else if(digitalRead(s)==HIGH&digitalRead(t0)==HIGH){//bore
      Serial.println("A");
      digitalWrite(m1,LOW);
      digitalWrite(m2,HIGH);
      while(true){
             if(digitalRead(t2)==LOW){
              Serial.println("B");
              digitalWrite(m1,LOW);
              digitalWrite(m2,LOW);
              break;
              }
      }
    }
  }
}
