#include "AutoMode.h"
#include "MotorDrive.h"

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

#define straight 1
#define turnleft 2
#define turnright 3
#define backwards 4

unsigned long previousMilliSensor = 0;
unsigned long previousMilliSensor_F = 0;  
int distance;
int threshold = 20;  // Adjust the threshold as needed

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 2, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. //sonar[0]=sensor right side
  NewPing(4, 4, MAX_DISTANCE),  //sonar[1] = sensor left side
  NewPing(7, 7, MAX_DISTANCE)  //sonar[2] = sensor front side
};

//detect function
int detectDistance()  //retrun detection in int, whitch 1=go straight, 2=turn left, 3=turn right, 4=go backward.
{            
  int distance_result[SONAR_NUM]={0};   //put result in an array.
  int threshold = 25;            //determinde for the minimal distance to react.
  delay(50);                     //Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  for (uint8_t i = 0; i < SONAR_NUM; i++) // Loop through each sensor and store the result in distance_result[] array.
  { 
        distance_result[i] = sonar[i].ping_cm();
  }
    // if-else statement to determinde whitch derection has obstical.
    if((distance_result[0]<threshold)&&(distance_result[0]!=0))
    {    //right detected 
      if((distance_result[1]<threshold)&&(distance_result[1]!=0))
      {  //left detects
          return turnleft; //both detect, go turn
      }
      else
      {
        return turnright;                 //right detects, so turn left.
      }
    }
    else        //right doesn't detects
    {                   
      if((distance_result[1]<threshold)&&(distance_result[1]!=0)) //only left detects, so turn right.
      {  
        return turnleft;
      }
      else
      {                       // both don't detect, check for sensor in the front
        if((distance_result[2]<threshold)&&(distance_result[2]!=0))
        { //front detects, go backwards
          return turnleft; 
        }
        else
        {
          return straight;
        }
      }
    }
}

void AutoMode(){
  int direction = detectDistance();
  switch(direction){
    case straight:
      speed(3);
      forward();
      break;
    case turnleft:
      speed(5);
      tankleft();      
      //left();
      break;
    case turnright:
      speed(5);    
      tankright();
      //right();
      break;
    case backwards:
      speed(5);    
      backward();
      break;
  }
}
int detectObstacle() {
  NewPing sonar(7, 7, MAX_DISTANCE);
  unsigned long currentMilliSensor_F = millis();
  if (currentMilliSensor_F - previousMilliSensor_F > 50) {
    previousMilliSensor_F = currentMilliSensor_F;
    distance = sonar.ping_cm();
    if (distance < threshold && distance > 0) {
      return 1;  // Obstacle detected, take action
    } else {
      return 0;  // No obstacle
    }
  }
}