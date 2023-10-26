#include "LineFollow.h"
#include "MotorDrive.h"


#define sensor1 10  // New sensor connected to digital pin 10
#define sensor4 11  // New sensor connected to digital pin 11

void SlaveMode() {
  int val1 = digitalRead(sensor1);
  int val2 = digitalRead(sensor4);

  if (detectObstacle() == 1) {
    Stop();
  }
  else if(val1 == 1 && val2 == 1 || val1 == 0 && val2 == 0){
    speed(2);
    forward();
  }else{
   if (val1 == 1 && val2 == 0) {
      speed(5);
      tankright();
    }
    if (val1 == 0 && val2 == 1) {
      speed(5);
      tankleft();      
    }
  }
}
