/*****************CODINGSTUDIO.CO.IN********************/

int sen_m=2;//metal detecting sensor pin
int sen_w=3;//moisture sensor pin
int arm1=4,arm2=5;// arm1 to open arm, arm2 to close the arm
int rotor1=6,rotor2=7;// rotor1=> Anti-clockwise, rotor2=>clockwise
int sen_obj=8;//IR sensor pin
bool flag=false;
int metal,moisture,obj;
void setup() {
  Serial.begin(9600);
  pinMode(sen_m,INPUT);
  pinMode(sen_w,INPUT);
  pinMode(obj,INPUT);
  pinMode(arm1,OUTPUT);
  pinMode(arm2,OUTPUT);
  pinMode(rotor1,OUTPUT);
  pinMode(rotor2,OUTPUT);
}

void loop() {
  obj=digitalRead(sen_obj);//Read the digital value from IR sensor to find the obstacle
  
  if(obj==LOW)//if there is some waste then obj will be LOW
  {
    flag=true;
    Serial.println("if there is some waste then obj will be LOW");
  }
  else{
    flag=false;
  }
  if(flag)//Checks whether there is some waste in the bin or its empty
  {
    delay(1000);
    metal=digitalRead(sen_m);//Read the digital value from metal detecting sensor to find the metal waste
    moisture=analogRead(sen_w);//Read the digital value from moisture sensor to find wet waste
    if(metal==LOW){
      Serial.println("metal");
      digitalWrite(arm1,HIGH);//Start opening the Arm
      delay(500);
      digitalWrite(arm1,LOW);//Stop opening the Arm
      digitalWrite(arm2,HIGH);//Start closing the Arm
      delay(550);
      digitalWrite(arm2,LOW);//Stop closing the Arm
      delay(100);
    }
    else if(moisture==HIGH){
      Serial.println("wet");
      digitalWrite(rotor1,HIGH);//Start Rotation Anti-Clockwise
      delay(250);
      digitalWrite(rotor1,LOW);//Stop Rotation Anti-Clockwise
      delay(1000);
      digitalWrite(arm1,HIGH);//Start opening the Arm
      delay(500);
      digitalWrite(arm1,LOW);//Stop opening the Arm
      digitalWrite(arm2,HIGH);//Start closing the Arm
      delay(550);
      digitalWrite(arm2,LOW);//Stop closing the Arm
      delay(100);
      digitalWrite(rotor2,HIGH);//Start Rotation Clockwise
      delay(250);
      digitalWrite(rotor2,LOW);//Stop Rotation Clockwise
    }
    else {
      Serial.println("dry");  
      digitalWrite(rotor2,HIGH);//Start Rotation Clockwise
      delay(250);
      digitalWrite(rotor2,LOW);//Stop Rotation Clockwise
      delay(1000);
      digitalWrite(arm1,HIGH);//Start opening the Arm
      delay(500);
      digitalWrite(arm1,LOW);//Stop opening the Arm
      digitalWrite(arm2,HIGH);//Start closing the Arm
      delay(550);
      digitalWrite(arm2,LOW);//Stop closing the Arm
      delay(100);
      digitalWrite(rotor1,HIGH);//Start Rotation Anti-Clockwise
      delay(250);
      digitalWrite(rotor1,LOW);//Stop Rotation Anti-Clockwise
    }    
  }
}
/*****************CODINGSTUDIO.CO.IN********************/
