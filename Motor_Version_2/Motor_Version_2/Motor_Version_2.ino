#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "MotorDrive.h"
#include "LineFollow.h"
#include "F567.h"
#include "Bluetooth.h"
#include "AutoMode.h"

int option = 2; //  option for the main switch case
int mode = 99;
int reading;

const int ledLeft = A2;
const int ledRight = A3;

void setup() {
  MotorStart();
  readingstart();
  Serial.begin(9600);  
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   option = Reading();
	switch(option){
    case 1: // Auto mode
      speed(7); // set the speed at the predertermint speed    
      AutoMode();
      break;
    case 2: // Remote contro
      RemoteMode();
      break;
    case 3: //  slave mode
      speed(7); // set the speed at the predertermint speed    
      SlaveMode();
      break;
    default: // Await input
      DefaultMode();
      break;
  } 
}

//detect function for uatra sonic sensor
void DefaultMode() {
  Reading();
}

void MakeLed(int make) {
  if(make == 1) {
    digitalWrite(ledLeft, HIGH);
  }
  if(make == 2) {
    digitalWrite(ledRight, HIGH);
  }
}
