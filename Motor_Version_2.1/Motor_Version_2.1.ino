#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "MotorDrive.h"
#include "LineFollow.h"
#include "F567.h"
#include "Bluetooth.h"
#include "AutoMode.h"

int option; //  option for the main switch case

void setup() {
  MotorStart();
  readingstart();
  speed(0);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  option = Reading();
 // Serial.println(option);
	switch(option)
  {
    case 1: // Auto mode  
      AutoMode();
      break;
    case 2: // Remote control
      RemoteMode();
      break;
    case 3: //  slave mode 
      SlaveMode();
      break;
    default: // Await input
      break;
  } 
}