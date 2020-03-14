#include <Servo.h>
int door=8,d_e=6,d_t=7;
int tank=3,t_e=5,t_t=4;
int ldr=A0,ldr_l=11,light=0;
int s_s=12,f_s=A1,r_led=10;
Servo door_servo; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr_l,OUTPUT);
  pinMode(r_led,OUTPUT);
  pinMode(s_s,INPUT);
  digitalWrite(ldr_l,LOW);
  digitalWrite(r_led,LOW);
  door_servo.attach(door);
  door_servo.write(180);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(distance(d_t,d_e));
  if(distance(d_t,d_e)<15){
    door_servo.write(0);
  }
  else{
    door_servo.write(180);
  }
  if(distance(t_t,t_e)<5){
    digitalWrite(tank,HIGH);
  }
  else{
    digitalWrite(tank,LOW);
  }
  if(10>analogRead(ldr)){
    digitalWrite(ldr_l,HIGH);
  }
  else{
    digitalWrite(ldr_l,LOW);
  }
  if(analogRead(f_s)>600 || digitalRead(s_s)){
    digitalWrite(r_led,HIGH);
  }
  else{
    digitalWrite(r_led,LOW);
  }
}


long distance(int pingPin,int echoPin){
   long duration, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   return  cm;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
