#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "ESPRotary.h"
#include "Button2.h"
#include "Secret.h"

#define rotatePinA 5 //D1 
#define rotatePinB 4 //D2
#define buttonPin  0  //D3

ESP8266WiFiMulti WiFiMulti;
WiFiClient  client;
HTTPClient http;

ESPRotary r = ESPRotary(rotatePinA, rotatePinB);
Button2 b = Button2(buttonPin);

String volumioEndpoint = "http://volumio.local/api/v1/commands/?cmd=";

void increaseVolume(ESPRotary &r){
  http.begin(client, volumioEndpoint + "volume&volume=plus");
  http.GET();
  Serial.println("increase");
}

void decreaseVolume(ESPRotary &r){
  http.begin(client, volumioEndpoint + "volume&volume=minus");
  http.GET();
  Serial.println("decrease");
}

void showPosition(Button2 & btn){
  Serial.println("Short press");
  http.begin(client, volumioEndpoint + "toggle");
  http.GET();
}

void resetPosition(Button2 & btn){
  Serial.println("Long press!");
}

void setup(){
  Serial.begin(115200);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(WiFi.localIP());

  //r.setChangedHandler(rotate);
  r.setLeftRotationHandler(increaseVolume);
  r.setRightRotationHandler(decreaseVolume);
  b.setClickHandler(showPosition);
  b.setLongClickHandler(resetPosition);
}

void loop(){
  r.loop();
  b.loop();
}