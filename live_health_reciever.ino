// The Code is modified and written by Alok Shaw, the creator of the Youtube channel : www.youtube.com/roboshala and runs an educational blog : www.roboshala.com

#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include <LiquidCrystal.h>
#define FIREBASE_HOST "live-health-5f2ab.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "Y2hTj0Z0IFYZLyHn6KlJzwZnYie95WKl1HpQyuYI"       //Your Firebase Database Secret goes here
#define WIFI_SSID "livehealth"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "123456789"                                      //Password of your wifi network 

int bpm=0,ecg=0,t=0;
const int rs = D0, en = D1, d4 = D2, d5 = D3, d6 = D4, d7 = D5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
   lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("System Started!");
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  lcd.clear();
  lcd.print("WiFi Connected..");
  lcd.setCursor(0,1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setString("bpm","0");                     //Here the varialbe"S1","S2","S3" and "S4" needs to be the one which is used in our Firebase and MIT App Inventor
  Firebase.setString("ecg","0");
  Firebase.setString("temp","0");
  delay(2000); 
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  lcd.clear();
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
  bpm=Firebase.getString("bpm").toInt();                                        //Reading the value of the varialble Status from the firebase
  ecg=Firebase.getString("ecg").toInt();
  t=Firebase.getString("temp").toInt();
  Serial.print("BPM: ");
  Serial.println(bpm);
  Serial.print("ECG: ");
  Serial.println(ecg);
  Serial.print("T :");
  Serial.println(t);
  lcd.print("BPM: ");
  lcd.print(bpm);
  lcd.setCursor(0,1);
  lcd.print("TEMPERATURE: ");
  lcd.print((int)t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 2);
  lcd.print("ECG: ");
  lcd.print(ecg);
  delay(2000);
}
