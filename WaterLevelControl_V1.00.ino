
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <FirebaseHttpClient.h>

#define FIREBASE_HOST "YourFirebaseHost"
#define FIREBASE_AUTH "YourFirebaseAuthenticationCode"
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPW"


String sensorData;
char rdata;
int trigPin = 2;
int echoPin = 14;
int firstVal;
long duration;int distance;


void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(16, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("distance", 0);

}

void loop() {

digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration/58;

Serial.print("Distance: ");
Serial.println(distance);
Firebase.setInt("distance",distance);
delay(2000);

}
