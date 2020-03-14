#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal.h>
#define FIREBASE_HOST "live-health-5f2ab.firebaseio.com"
#define FIREBASE_AUTH "Y2hTj0Z0IFYZLyHn6KlJzwZnYie95WKl1HpQyuYI"
#define WIFI_SSID "codingstudio"
#define WIFI_PASSWORD "FuckYou5*"


#define heartratePin D5
#include "DFRobot_Heartrate.h"
#include "DHT.h"

#define DHTPIN D8   
#define DHTTYPE DHT11
const int heartPin = A0;
DFRobot_Heartrate heartrate(DIGITAL_MODE); ///< ANALOG_MODE or DIGITAL_MODE
int bpm=0,ecg=0;
DHT dht(DHTPIN, DHTTYPE);
const int rs = D0, en = D1, d4 = D2, d5 = D3, d6 = D4, d7 = D6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(115200);
  // connect to wifi.
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("System Started!");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  lcd.clear();
  lcd.print("WiFi Connected..");
  lcd.setCursor(0,1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());
  dht.begin();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(2000);
}

int n = 0;
void loop() {
  //delay();
  lcd.clear();
  //lcd.setCursor(0, 0);
  uint8_t rateValue;
  heartrate.getValue(heartratePin); ///< A1 foot sampled values
  rateValue = heartrate.getRate(); ///< Get heart rate value 
  Serial.print("BPM: ");
  if(rateValue)  {
    Serial.println(rateValue);
    
     if(rateValue>60&&rateValue<120){
       bpm=rateValue;
    }
    
  }
  else{
    Serial.println("done!");
  }
  lcd.print("BPM: ");
  lcd.print(bpm);
  Serial.println();
  
  
  delay(50);
  int heartValue = analogRead(heartPin);
  ecg=heartValue;
  //Serial.println(heartValue);
  
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    //return;
    t=0;
  }
  
  lcd.print(" T: ");
  lcd.print((int)t);
  lcd.print((char)223);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("ECG: ");
  lcd.print(ecg);
  
   // set bpm value
  Firebase.setString("bpm", (String)bpm);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /bmp failed:");
      Serial.println(Firebase.error());  
      return;
  }
  //delay(1000);

   // set ecg value
  Firebase.setString("ecg", (String)ecg);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /ecg failed:");
      Serial.println(Firebase.error());  
      return;
  }
  //delay(1000);

  // set temperature value
  Firebase.setString("temp", (String)t);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /temp failed:");
      Serial.println(Firebase.error());  
      return;
  }
  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  //delay(1000);
  //delay(20);
}
