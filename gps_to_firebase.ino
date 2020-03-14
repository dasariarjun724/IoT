#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "traffic-f8bf6.firebaseio.com"
#define FIREBASE_AUTH "XUshbEHHvLfxLnlFLHQ8ZorIljWEtIn90uewn6GE"
#define WIFI_SSID "gps"
#define WIFI_PASSWORD "123456789"


static const int RXPin = D1, TXPin =D2;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
String lati,lon;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("test","done");
   if (Firebase.failed()) {
        Serial.print("setting /test failed:");
        Serial.println(Firebase.error());  
        //return;
    }
}

void loop() {
  
   while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    /*lati=gps.location.lat();
    lon=gps.location.lng();*/
    lati=String(gps.location.lat(),6);
    lon=String(gps.location.lng(),6);
    //Latitute 
    Firebase.setString("latitude", lati);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /latitude failed:");
        Serial.println(Firebase.error());  
        return;
    }
    //Longitute
     Firebase.setString("longitude", lon);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /longitude failed:");
        Serial.println(Firebase.error());  
        return;
    }

    
    Serial.print(lati);
    Serial.print(F(","));
    Serial.print(lon);
    
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
