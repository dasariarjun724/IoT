const int rmf = 9;                        
const int rmb = 10;                       
const int lmf = 5;                       
const int lmb = 3;                       
const int trigPin_l = 11;                 //right sensor trigger pin
const int echoPin_l = 12;                //right sensor echo pin
const int trigPin_r = 7;                  //left sensor trigger pin
const int echoPin_r = 6;                 //sraight sensor echo pin
const int trigPin_s = 4;                  //straight sensor trigger pin
const int echoPin_s = 8;                 //left sensor echo pin
long duration_r, cm_r, duration_l, cm_l, duration_s, cm_s;  //establish variables for duration of the ping, and the distance result in cm
int lm_status, rm_status;         //left motor status, right motor status, 0 = none , 1 = forward, -1 = backward 

void setup() {
  Serial.begin(9600);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(trigPin_l, OUTPUT);
  pinMode(trigPin_s, OUTPUT);
  pinMode(trigPin_r, OUTPUT);
  pinMode(echoPin_l, INPUT);
  pinMode(echoPin_s, INPUT);
  pinMode(echoPin_r, INPUT);
}

void loop() {
  
  digitalWrite(trigPin_l, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_l, LOW);
  duration_l = pulseIn(echoPin_l, HIGH);
  cm_l = microsecondsToCentimeters(duration_l);
  if(cm_l > 500){
    cm_l = 0;
  }

  digitalWrite(trigPin_r, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_r, LOW);
  duration_r = pulseIn(echoPin_r, HIGH);
  cm_r = microsecondsToCentimeters(duration_r);
  if(cm_r > 500){
    cm_r = 0;
  }

  digitalWrite(trigPin_s, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_s, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_s, LOW);
  duration_s = pulseIn(echoPin_s, HIGH);
  cm_s = microsecondsToCentimeters(duration_s);
  if(cm_s>1000){
    cm_s=0;
  }
  Serial.println(cm_s);
  Serial.println(cm_l);
  Serial.println(cm_r);
  Serial.println("-----------");
  delay(100);
  /*leftTurn(1200);
  stopBot();
  while(true);
  */
  
  if(cm_l<6&&cm_r<6&&cm_s<6){
    rightTurn(1200);
    stopBot();
    rightTurn(1200);
    stopBot();
  }
  else if(cm_l<6&&cm_r<6&&cm_s>6){
    forward();
  }
  else if(cm_l<6&&cm_r>6&&cm_s<6){
    rightTurn(1200);
    stopBot();
    forward();
    stopBot();
  }
  else if(cm_l<6&&cm_r>6&&cm_s>6){
    forward();
  }
  else if(cm_l>6&&cm_r<6&&cm_s<6){
    leftTurn(1200);
    stopBot();
    forward();
    stopBot();
  }
  else if(cm_l>6&&cm_r<6&&cm_s>6){
    forward_s(500);
    leftTurn(1200);
    stopBot();
    forward_s(1200);
    stopBot();
  }
  else if(cm_l>6&&cm_r>6&&cm_s<6){
    leftTurn(1200);
    stopBot();
    forward_s(1200);
    stopBot();
  }
  else if(cm_l>6&&cm_r>6&&cm_s>6){
    leftTurn(1200);
    stopBot();
    forward_s(1200);
    stopBot();
  }
  /*
  if(cm_l > 15){ 
  
    leftTurn(70);
    forward_s(80);
    stopBot();
  }
  else if(cm_s < 15 && cm_r > 15){
    rightTurn(70);
    forward_s(70); 
    
  }
  else{
    forward();   
  }
  */
  
}

void leftTurn(int time) {
  analogWrite(lmf, 0);
  analogWrite(rmb, 0);
  analogWrite(lmb, 190);
  analogWrite(rmf, 190);
  delay(time);
}

void rightTurn(int time) {
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(lmf, 180);
  analogWrite(rmb, 180);
  delay(time);
}

void forward_s(int time){
  analogWrite(lmb, 0);
  analogWrite(rmb, 0);
  analogWrite(lmf, 150);
  analogWrite(rmf, 150);
  delay(time);
}

void forward() {  
  analogWrite(lmb, 0);
  analogWrite(rmb, 0);
  analogWrite(lmf, 165);
  analogWrite(rmf, 150);
  //stopBot();
  
  digitalWrite(trigPin_l, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_l, LOW);
  duration_l = pulseIn(echoPin_l, HIGH);
  cm_l = microsecondsToCentimeters(duration_l);
  if(cm_l > 500){
    cm_l = 0;
  }

  digitalWrite(trigPin_s, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_s, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_s, LOW);
  duration_s = pulseIn(echoPin_s, HIGH);
  cm_s = microsecondsToCentimeters(duration_s);

  if(cm_s<5){
    stopBot();
  }
  else if(cm_l>10){
    stopBot();
  }
  else{
    forward();
  }
}

void stopBot(){
  analogWrite(lmb, 0);
  analogWrite(rmb, 0);
  analogWrite(lmf, 0);
  analogWrite(rmf, 0);
  digitalWrite(2,HIGH);
  //Serial.print("Deadlock");
}
long microsecondsToCentimeters(long microseconds){
    return microseconds / 29 / 2;
  }
