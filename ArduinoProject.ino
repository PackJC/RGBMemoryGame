//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:    Personal Project
//  File Name:    ArduinoProject.ino
//  Description:    RGB Brain Memory Game
//  Course:     CSCI 1200-001
//  Author:     Johnny Pack, packjc@etsu.edu, Department of Computing, East Tennessee State University
//  Created:    Friday, March 23, 2018
//  Copyright:    Johnny Pack, 2018
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <NewTone.h>           //Library Used for speaker tone

const int potPin          = A0;      //Potentiometer Pin
const int buttonPin       = 2;       //Button Pin
const int speakerPin      = 7;       //Buzzer Pin
const int redUserPin      = 6;      //Red User's RGB 
const int greenUserPin    = 5;      //Green User's RGB
const int blueUserPin     = 3;      //Blue User's RGB
const int redSystemPin    = 12;     //Red System RGB
const int greenSystemPin  = 11;     //Green System RGB
const int blueSystemPin   = 10;     //Blue System RGB

int potVal          = 0;    //Potentiometer Value
int buttonVal       = 0;    //Button Value

long randomColor    = 0;    //To assign random color
int loopAmt         = 0;    //Loop amount for display of random colors (ex: loopAmt = 6 would display a color sequence of 6
int buttonCnt       = 0;    //Amount of times a button has been pushed

int sequenceCnt     = 2;    //!!Very important value, Used to determine how many colors show in beginning sequence

String logRandomColor = ""; //Used to keep a log of the random colors the system picks and to compare to what the use chooses 
String logUserColor   = ""; //used to keep a log of the random colors the user picks and to compare to what the system chooses

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(buttonPin, OUTPUT);
  pinMode(redUserPin, OUTPUT);
  pinMode(greenUserPin, OUTPUT);
  pinMode(blueUserPin, OUTPUT);
  pinMode(redSystemPin, OUTPUT);
  pinMode(greenSystemPin, OUTPUT);
  pinMode(blueSystemPin, OUTPUT);
  randomSeed(analogRead(2)); 
}   //End setup

void loop() {
  while(loopAmt < sequenceCnt){
  randomColor = random(1,4);  //Get a random number 0 - 3 for our switch
  switch (randomColor) {  //Display a different color for each case
    case 1: //RED COLOR
      digitalWrite(redSystemPin, HIGH);
      delay(1000);
      digitalWrite(redSystemPin, LOW);
      delay(1000);
      logRandomColor += "red";
      loopAmt++;
    break;
    case 2: //GREEN COLOR
      digitalWrite(greenSystemPin, HIGH);
      delay(1000);
      digitalWrite(greenSystemPin, LOW);
      delay(1000);
      logRandomColor += "green";
      loopAmt++;
    break;
    case 3: //BLUE COLOR
      digitalWrite(blueSystemPin, HIGH);
      delay(1000);
      digitalWrite(blueSystemPin, LOW);
      delay(1000);
      logRandomColor += "blue";
      loopAmt++;
    break;
    } //End Switch
  }   //End While Loop
  detectUserColor();  
}     //End Loop()

void detectUserColor() {
    buttonVal = digitalRead(buttonPin); //get value from button
    potVal = analogRead(potPin);        //get value from potentiometer 
    if(potVal < 341 && buttonVal == HIGH){
      logUserColor += "red";
      buttonCnt++;
      delay(250);
    }
    if(potVal > 341 && potVal < 682 && buttonVal == HIGH){
      logUserColor += "green";
      buttonCnt++;
      delay(250);
    }   
    if(potVal > 682 && potVal < 1024 && buttonVal == HIGH){
      logUserColor += "blue";
      buttonCnt++;
      delay(250);
    }   
    if(potVal < 341){
      digitalWrite(redUserPin, HIGH); //red
      digitalWrite(blueUserPin, LOW);
      digitalWrite(greenUserPin, LOW);
    }
    if(potVal > 341 && potVal < 682){
      digitalWrite(greenUserPin, HIGH); //green
      digitalWrite(blueUserPin, LOW);
      digitalWrite(redUserPin, LOW);
    }
    if(potVal > 682 && potVal < 1024){  
      digitalWrite(greenUserPin, LOW);
      digitalWrite(blueUserPin, HIGH); //blue
      digitalWrite(redUserPin, LOW);
    }
    if(logUserColor == logRandomColor && buttonCnt == sequenceCnt){
      digitalWrite(greenUserPin, HIGH);
      digitalWrite(blueUserPin, LOW);
      digitalWrite(redUserPin, LOW);
      digitalWrite(greenSystemPin, HIGH);
      digitalWrite(blueSystemPin, LOW);
      digitalWrite(redSystemPin, LOW);
      tone(speakerPin,500,200);
      delay(1000);
      digitalWrite(greenSystemPin, LOW);
      digitalWrite(greenUserPin, LOW);
      sequenceCnt++; //Increase how many random colors show in a sequence because the previous answer is correct
      reset();
    }
    if(logUserColor != logRandomColor & buttonCnt == sequenceCnt){
      digitalWrite(greenUserPin, LOW);
      digitalWrite(blueUserPin, LOW);
      digitalWrite(redUserPin, HIGH);
      digitalWrite(greenSystemPin, LOW);
      digitalWrite(blueSystemPin, LOW);
      digitalWrite(redSystemPin, HIGH);
      tone(speakerPin,500,200);
      delay(1000);
      digitalWrite(redSystemPin, LOW);
      digitalWrite(redUserPin, LOW);
      sequenceCnt = 2; //Reset how many random colors show since the user got the previous answer wrong
      reset();
    }
}     //End detectUserColor()

void reset(){
  delay(250);
  logUserColor = "";
  logRandomColor = "";
  buttonCnt = 0;
  loopAmt = 0;
}   //End reset()



