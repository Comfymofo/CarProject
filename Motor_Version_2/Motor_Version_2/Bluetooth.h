#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>

extern int speedmotors = 0;
extern int forthspeed = 0;
extern char value;

void speed(int x);

void RemoteMode();

#endif