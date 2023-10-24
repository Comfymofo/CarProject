#ifndef MOTORDRIVE_H
#define MOTORDRIVE_H

#include <Arduino.h>

#define LeftdirPin1 3
#define LeftdirPin2 5
#define RightdirPin1 6
#define RightdirPin2 9

void MotorStart();

void speed(int x);

void left();

void right();

void forward();

void backward();

void backLeft();

void backRight();

void tankleft();

void tankright();
void stopmotor();

#endif
