#include "F567.h"
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "Bluetooth.h"
#include "AutoMode.h"
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int buttonReset = 20;
int buttonSwitch = A3;   
int buttonMenu = A1;
int buttonSwitchState, buttonMenuState, buttonResetState, lastButtonState; 
int selectedOption = 2; 
int selectedMenu = 1; 
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousTime = 0;
unsigned long interval = 1000;
unsigned long savedTime;
int currentlysavedseconds, currentlysavedminutes, currentlysavedhours;
int savedseconds, savedminutes, savedhours;
int displayseconds, displayminutes, displayhours;
int savelock = 1;
int lastSpeed;
int passValue;

void readingstart()
{
  // Read initial time values from EEPROM and set up the LCD display.
  savedseconds = EEPROM.read(0);
  savedminutes = EEPROM.read(1);
  savedhours = EEPROM.read(2);
  lcd.init();
  lcd.init();
  lcd.backlight();
  pinMode(buttonSwitch, INPUT_PULLUP);
  pinMode(buttonMenu, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);
}

int Reading()
{
  int SpeedForLCD = speedmotors / 25.5;
  int direction = detectDistance();  
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval)
  {
    // Update elapsed time.
    elapsedTime = elapsedTime + (currentTime - previousTime);
    previousTime = currentTime;
  }
  // Read the button state for menu selection.
  lastButtonState = buttonMenuState;
  buttonMenuState = digitalRead(buttonMenu);
  if (buttonMenuState != lastButtonState)
  {
    if (buttonMenuState == LOW)
    {
      lcd.clear();
      selectedMenu = selectedMenu + 1;
      if (selectedMenu > 3)
      {
        selectedMenu = 1;
      }
    }
  }
  lastButtonState = buttonMenuState;
  switch (selectedMenu)
  {
    case 1:
      lastButtonState = buttonSwitchState;
      buttonSwitchState = digitalRead(buttonSwitch);
      if (buttonSwitchState != lastButtonState)
      {
        if (buttonSwitchState == LOW)
        {
          lcd.clear();
          selectedOption = selectedOption + 1;
          if (selectedOption > 3)
          {
            selectedOption = 1;
          }
        }
      }
      passValue = selectedOption;
      lastButtonState = buttonSwitchState;
      switch (selectedOption)
      {
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
          lcd.print("RCMod");  
          break;
        case 3:
          lcd.setCursor(0, 0);
          lcd.print("Select an option:");
          lcd.setCursor(0, 1);
          lcd.print("SlaveMod");
          
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
      if (value == lastSpeed)
      {
        lcd.setCursor(0, 0);
      
        switch (direction)
        {
          case 1:
            lcd.print("Direction: i");
            break;
          case 2:
            lcd.print("Direction: <");
            break;
          case 3:
            lcd.print("Direction: >");
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
        lcd.print(SpeedForLCD);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        switch (direction)
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
        lcd.print(SpeedForLCD);
      }
      break;
    case 3:
      if (savelock == 1)
      {
        currentlysavedseconds = savedseconds;
        currentlysavedminutes = savedminutes;
        currentlysavedhours = savedhours;
        savelock = 0;
      }
      displayseconds = (currentlysavedseconds + (elapsedTime / 1000)) % 60;
      displayminutes = (currentlysavedminutes + (elapsedTime / 60000)) % 60;
      displayhours = (currentlysavedhours + (elapsedTime / 3600000)) % 60;
      lcd.setCursor(4, 0);
      lcd.print(String(displayhours / 10) + String(displayhours % 10) + ":" + String(displayminutes / 10) + String(displayminutes % 10) + ":" + String(displayseconds / 10) + String(displayseconds % 10));
      if ((displayseconds % 60) == 0)
      {
        savedseconds = displayseconds;
        savedminutes = displayminutes;
        savedhours = displayhours;
        EEPROM.write(0, savedseconds);
        EEPROM.write(1, savedminutes);
        EEPROM.write(2, savedhours);
      }
      lastButtonState = buttonResetState;
      buttonResetState = digitalRead(buttonReset);
      if (buttonResetState != lastButtonState)
      {
        if (buttonResetState == LOW)
        {
          EEPROM.write(0, 0);
          EEPROM.write(1, 0);
          EEPROM.write(2, 0);
        }
      }
      lastButtonState = buttonResetState;
  }
}
lastSpeed = value;
return passValue;
}


