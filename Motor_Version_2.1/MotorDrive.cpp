#include "MotorDrive.h"
#include "Bluetooth.h"
#define LeftdirPin1 3
#define LeftdirPin2 5
#define RightdirPin1 6
#define RightdirPin2 9
#define ledLeftPin A2
#define ledRightPin 8


void MotorStart() {
  pinMode(ledLeftPin, OUTPUT);
  pinMode(ledRightPin, OUTPUT);
  pinMode(LeftdirPin1, OUTPUT);
  pinMode(LeftdirPin2, OUTPUT);
  pinMode(RightdirPin1, OUTPUT);
  pinMode(RightdirPin2, OUTPUT);
}

void left(){
  digitalWrite(ledLeftPin, HIGH);
  digitalWrite(ledRightPin, LOW);
  analogWrite(RightdirPin1, speedmotors);
  digitalWrite(RightdirPin2, 0);  
  analogWrite(LeftdirPin1, forthspeed);
  digitalWrite(LeftdirPin2, 0); 
}

void right(){ 
  digitalWrite(ledLeftPin, LOW);
  digitalWrite(ledRightPin, HIGH);
  analogWrite(RightdirPin1, forthspeed);
  digitalWrite(RightdirPin2, 0);  
  analogWrite(LeftdirPin1, speedmotors);
  digitalWrite(LeftdirPin2, 0); 
}

void forward(){
  digitalWrite(ledLeftPin, LOW);
  digitalWrite(ledRightPin, LOW);
  analogWrite(RightdirPin1, speedmotors);
  digitalWrite(RightdirPin2, 0);  
  analogWrite(LeftdirPin1, speedmotors);
  digitalWrite(LeftdirPin2, 0);  
}

void backward(){  
  digitalWrite(ledLeftPin, LOW);
  digitalWrite(ledRightPin, LOW);
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, speedmotors);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, speedmotors);  
}

void backLeft() {  
  digitalWrite(ledLeftPin, HIGH);
  digitalWrite(ledRightPin, LOW);
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, forthspeed);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, speedmotors); 
}

void backRight() {  
  digitalWrite(ledLeftPin, LOW);
  digitalWrite(ledRightPin, HIGH);
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, speedmotors);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, forthspeed); 
}
void tankleft(){
  digitalWrite(ledLeftPin, HIGH);
  digitalWrite(ledRightPin, LOW);
  analogWrite(RightdirPin1, speedmotors);
  digitalWrite(RightdirPin2, 0);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, speedmotors); 
}

void tankright(){
  digitalWrite(ledLeftPin, LOW);
  digitalWrite(ledRightPin, HIGH);
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, speedmotors);  
  analogWrite(LeftdirPin1, speedmotors);
  digitalWrite(LeftdirPin2, 0); 
} 
void stopmotor(){
  digitalWrite(ledLeftPin, LOW);
  digitalWrite(ledRightPin, LOW);
  digitalWrite(RightdirPin1, 0);
  digitalWrite(RightdirPin2, 0);  
  digitalWrite(LeftdirPin1, 0);
  digitalWrite(LeftdirPin2, 0); 
}
void Stop() {
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, 0);
  analogWrite(LeftdirPin1, 0);
  digitalWrite(LeftdirPin2, 0); 
}