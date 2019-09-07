#include <Arduino.h>

 #define outputA 4 //D1 
 #define outputB 5 //D2

 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   //pinMode (outputA,INPUT);
   //pinMode (outputB,INPUT);
   
   Serial.begin (115200);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA); 
   Serial.print("Setup");  
 } 

 void loop() { 
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