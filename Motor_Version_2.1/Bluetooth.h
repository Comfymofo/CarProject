#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>

extern char value;
extern int speedmotors;
extern int forthspeed;

int data(int y);

void speed(int x);

void readingstart();

void RemoteMode();

#endif