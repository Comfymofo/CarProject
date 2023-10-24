#include "AutoMode.h"
#include "MotorDrive.h"

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

#define straight 1
#define turnleft 2
#define turnright 3
#define backwards 4

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 2, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. //sonar[0]=sensor right side
  NewPing(4, 4, MAX_DISTANCE),  //sonar[1] = sensor left side
  NewPing(7, 7, MAX_DISTANCE)  //sonar[2] = sensor front side
};

unsigned long previousMilliSensor = 0;

//detect function
int detectDistance(){            //retrun detection in int, whitch 1=go straight, 2=turn left, 3=turn right, 4=go backward.
  int distance[SONAR_NUM]={0};   //put result in an array.
  int threshold = 25;            //determinde for the minimal distance to react.
  delay(50);                     //Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and store the result in distance[] array.
        distance[i] = sonar[i].ping_cm();
  }

    // if-else statement to determinde whitch derection has obstical.
    if((distance[0]<threshold)&&(distance[0]!=0)){    //right detected 
      if((distance[1]<threshold)&&(distance[1]!=0)){  //left detects
          return backwards; //both detect, go backwards
        }
      else{
        return turnleft;                 //right detects, so turn left.
      }
    }
    else{                         //right doesn't detects
      if((distance[1]<threshold)&&(distance[1]!=0)){  //only left detects, so turn right.
        return turnright;
      }
      else{                       // both don't detect, check for sensor in the front
        if((distance[2]<threshold)&&(distance[2]!=0)){ //front detects, go backwards
          return backwards; 
        }
        else{
          return straight;
        }
      }
    }
}

void AutoMode(){
  int direction = detectDistance();
  // Serial.print("direction = ");
  // Serial.println(direction);
  switch(direction){
    case straight:
      speed(7);
      forward();
      break;
    case turnleft:
      speed(3);
      left();
      break;
    case turnright:
      speed(3);    
      right();
      break;
    case backwards:
      speed(7);    
      backward();
      break;
  }
}