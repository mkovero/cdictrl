#include <Arduino.h>
#include "include/pins.h"
boolean camHit = false;
boolean debugEnabled = true; // debug
const byte nrCylinders = 8; // number of cylinders
byte firingOrder[8] = { in2,in3,in1,in5,in4,in8,in7,in6 }; // firing order
byte nextCylinder,firedCylinder,cylinder = 0;
double pollInterval = 100;
double lastTimedRun = 0;
const double Kp = 7; //80,21 Pid Proporional Gain. Initial ramp up i.e Spool, Lower if over boost
double Ki = 20;      //40,7 Pid Integral Gain. Overall change while near Target Boost, higher value means less change, possible boost spikes
const double Kd = 0; //100, 1 Pid Derivative Gain.
int curFp,pressureLim;
