const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 3; // Echo Pin of Ultrasonic Sensor

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(4,INPUT);
   digitalWrite(4,LOW);
   pinMode(5,OUTPUT);
}

void loop() {
   long duration, inches, cm;
   if(digitalRead(4)){
       pinMode(pingPin, OUTPUT);
       digitalWrite(pingPin, LOW);
       delayMicroseconds(2);
       digitalWrite(pingPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(pingPin, LOW);
       pinMode(echoPin, INPUT);
       duration = pulseIn(echoPin, HIGH);
       //inches = microsecondsToInches(duration);
       cm = microsecondsToCentimeters(duration);
       /*Serial.print(inches);
       Serial.print("in, ");*/
       Serial.print(cm);
       Serial.print("cm");
       Serial.println();
       delay(100);
       if(cm<=20){
        Serial.println("d");
        digitalWrite(5,HIGH);
       }
       else{
        digitalWrite(5,LOW);
        Serial.println("n");
       }
   }
   else{
    digitalWrite(5,LOW);
    Serial.println("n");
   }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
