#include "F567.h"
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "Bluetooth.h"

unsigned long previousMillis1 = 0;  
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousTime = 0;
unsigned long interval = 1000;
const int buttonReset = 13;
int buttonState,lastButtonState; 
int selectedOption = 1; 
int selectedMenu = 1;
int directionMovement;
int seconds, minutes, hours;
const int buttonSwitch = A0;   
const int buttonMenu = A1;

LiquidCrystal_I2C lcd(0x27,16,2); 

void readingstart(){
  seconds = EEPROM.read(0);
  minutes = EEPROM.read(1);
  hours = EEPROM.read(2);
  lcd.init();
  lcd.init();
  lcd.backlight(); 
  pinMode(buttonSwitch, INPUT_PULLUP);
  pinMode(buttonMenu, INPUT_PULLUP);   
}

int Reading() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) 
  {
    elapsedTime = elapsedTime + (currentTime - previousTime);
    previousTime = currentTime;
  }
  // delay(100);
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonMenu);
  if (buttonState != lastButtonState)
  {
    if (buttonState == LOW)
    {
      lcd.clear();
      selectedMenu = selectedMenu + 1;
      if (selectedMenu > 3)
      {
        selectedMenu = 1;
      }
    }
  }
  lastButtonState = buttonState;
  switch (selectedMenu){
    case 1: 
    // delay(100);
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonSwitch);
    if (buttonState != lastButtonState) 
    {
      if (buttonState == LOW)
      { 
        lcd.clear();
        selectedOption = selectedOption + 1;    
        if( selectedOption > 3)
        {
          selectedOption = 1;
        }
      }
    }
    lastButtonState = buttonState;
    switch (selectedOption) {
      case 1:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("AutoMod");
      break;
      case 2:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("SlaveMod");
      break;
      case 3:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("RadMod");
      break;
      default:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("sww");
      break;
    }
    break;
    case 2:
    lcd.setCursor(0, 0);
    switch (directionMovement)
    {
      case 1:
      lcd.print("Direction: <");
      break;
      case 2:
      lcd.print("Direction: >");
      break;
      case 3:
      lcd.print("Direction: i");
      break;
      case 4:
      lcd.print("Direction: !");
      break;
      default:
      lcd.print("Direction: -");
      break;
    }
    lcd.setCursor(0, 1);
    lcd.print("Speed:");
    // lcd.print();
    break;
    case 3:
    seconds = (seconds + (elapsedTime / 1000)) % 60;
    minutes = (minutes + (elapsedTime / 60000)) % 60;
    hours = (hours + (elapsedTime / 3600000)) % 24;
    lcd.setCursor(4, 0);
    lcd.print(String(hours / 10) + String(hours % 10) + ":" + String(minutes / 10) + String(minutes % 10) + ":" + String(seconds / 10) + String(seconds % 10));
    break;
  }
  return selectedOption;
}