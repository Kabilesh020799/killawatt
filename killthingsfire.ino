#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>
#define FIREBASE_HOST "tester-c6840.firebaseio.com"
#define FIREBASE_AUTH "hZdTRhD48UzhNJ2TUjP1AFmkOjE1cNLKLOcr1Z5o"
#define WIFI_SSID "kabilesh"  
#define WIFI_PASSWORD "8056609157"
SoftwareSerial s(D6,D5);
#include <ESP8266HTTPClient.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

void setup() 
{
  Serial.begin(9600);
  s.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
  float n = 0,one,two;
  char bu[20];
  String str,str1;
  char stro[5],stro1[5];

  void loop() 
  {
    // set value
    s.write("s");
    if(s.available()>0)
    {
     str=s.readString();
     str.toCharArray(bu,20);
     sscanf(bu,"%f,%f",&one,&two);
     Serial.println(one);
     Serial.println(two);
     Firebase.setFloat("unit", one);
     Firebase.setFloat("rate",two);
    if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());  
    return;
    }
     dtostrf(one, 2, 2, stro);
    str=(String)stro;
    dtostrf(two,2,2,stro1);
    str1=(String)stro1;

    if (client.connect("api.thingspeak.com",80)) {
      
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "IUFOA57UKBMIH975";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += (String)str;
      request_string += "&field2";
      request_string += "=";
      request_string += (String)str1;
      http.begin(request_string);
      http.GET();
      http.end();
    }
    delay(1000);
  }}
