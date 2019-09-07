#include <Arduino.h>
#include <Bounce2.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "Secret.h"

#define outputA 4 //D1 
#define outputB 5 //D2
#define buttonPin 0 //D3

int buttonState = 0;
int counter = 0; 
int aState;
int aLastState;
boolean play = true;
Bounce button;
ESP8266WiFiMulti WiFiMulti;
WiFiClient  client;
HTTPClient http;

String volIncrease = "http://volumio.local/api/v1/commands/?cmd=volume&volume=plus";

void setup(){
  Serial.begin (115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connect WiFi");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
  button.attach(buttonPin, INPUT_PULLUP);
}

inline void togglePlay(){
  button.update();
  if(button.fell()){
    http.begin(client, "http://volumio.local/api/v1/commands/?cmd=toggle");
    http.GET();
    Serial.println("toggle play/pause");
  }
}

void loop() { 
  togglePlay();
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState){     
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) { 
      counter ++;
      http.begin(client, volIncrease);
      http.GET();
    } else {
      counter --;
      http.begin(client, "http://volumio.local/api/v1/commands/?cmd=volume&volume=minus");
      http.GET();
    }
    Serial.print("Position: ");
    Serial.println(counter);
  } 
  aLastState = aState; // Updates the previous state of the outputA with the current state
}