#include "Bluetooth.h"
#include "MotorDrive.h"

void speed(int x){
  speedmotors = map(x, 0, 10, 0, 255);
	forthspeed = speedmotors / 4;
}
void RemoteMode() {
	if(Serial.available() > 0){
    value = Serial.read();
    Serial.println(value);
    switch (value){
      case 'F':
        forward();
        break;
      case 'R':
        right();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'S': 
        stopmotor();
        break;
      case '0':
        speed(0);
        break;
      case '1':
        speed(1);
        break;
      case '2':
        speed(2);
        break;
      case '3':
        speed(3);
        break;
      case '4':
        speed(4);
        break;
      case '5':
        speed(5);
        break;
      case '6':
        speed(6);
        break;
      case '7':
        speed(7);
        break;
      case '8':
        speed(8);
        break;
      case '9':
        speed(9);
        break;
      case 'q':
        speed(10);
        break;
      default:
        break;
    }
  }
}