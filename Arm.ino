/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo s1,s2,s3;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup() {
  s1.attach(5);  // attaches the servo on pin 9 to the servo object
  s2.attach(6);
  s3.attach(4);
  /*s2.write(90);
  delay(1000);
  s1.write(0);
  
  s1.write(180);
  s2.write(90);
  delay(1000);
  s2.write(0);*/
  s3.write(0);
}

void loop() {
 
}
