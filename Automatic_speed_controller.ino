#define s 7
void setup() {
  Serial.begin(9600);
pinMode(s,OUTPUT);
digitalWrite(s,LOW);//ON
}

void loop() {
  delay(10000);
 digitalWrite(s,HIGH);//ON
 delay(10000);
  digitalWrite(s,LOW);//LOW 
}
