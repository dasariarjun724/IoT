#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Arduino.h>
#include "DHT.h"
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#define DHTPIN D2
//#define DHTTYPE DHT22 
#define FIREBASE_HOST "mq-135-40f3b.firebaseio.com"
#define FIREBASE_AUTH "22JxXstGXZshIWtFtHZGPPFgdlCuXj3QOmEdiS6Z"
#define WIFI_SSID "xxxxx"   //Enter your SSID here
#define WIFI_PASSWORD "xxxxxx"   //Enter your Password here
#define ga A0
#define gasPin D1
String ip="xxxxxx"; //Enter Your IP here
int gass,co;
int temp;
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  Serial.println(WiFi.macAddress());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
int n=0;
void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  gass=gas();
  co=digitalRead(gasPin);
// set value
  Firebase.setString("temp", (String)t);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /temp failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set value
  Firebase.setString("air", (String)gass);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /gas failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

 // set value
  Firebase.setString("humidity", (String)h);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /humidity failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set value
  Firebase.setString("co2", (String)co);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /co2 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
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
  delay(1000);
  if(n%20==0){
    notify("Air Quality","Open the App");
    n=0;
  }
  n++;
  Serial.println(n);
  if(co==LOW){
    notify("Smoke Detected!","Alert Dangerous Gas");
  }
}
int gas()
{     
   int moisture=(float)analogRead(ga);
   return (((1023.0-moisture)/1023.0)*100); 
}
void notify(String title,String msg){

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://"+ip+"/air%20quality/notify.php?a=s&title="+title+"&message="+msg)) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }

  delay(10000);
}
