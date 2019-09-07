#include <Arduino.h>
#include <Bounce2.h>

#define outputA 4 //D1 
#define outputB 5 //D2
#define buttonPin 0 //D3

int buttonState = 0;
int counter = 0; 
int aState;
int aLastState;
boolean play = true;
Bounce button;

void setup() { 
  //pinMode (outputA,INPUT);
  //pinMode (outputB,INPUT);
  
  Serial.begin (115200);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
  button.attach(buttonPin, INPUT_PULLUP);
  Serial.print("Setup");  
} 
inline void togglePlay(){
  button.update();
  if(button.fell()){
    play = !play;
    if(play){
      Serial.println("play");
    }
    else{
      Serial.println("pause");
    }
    
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
    } else {
      counter --;
    }
    Serial.print("Position: ");
    Serial.println(counter);
  } 
  aLastState = aState; // Updates the previous state of the outputA with the current state
}

