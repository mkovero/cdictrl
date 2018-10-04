#include <Arduino.h>
#define PRIDELAY = 2000; // primary injection delay 2ms.
boolean camHit = false;
boolean debugEnabled = true; // debug
byte nrCylinders = 8; // number of cylinders
byte firingOrder = [in1,in3,in2,in5,in4,in8,in7]; // Firing order
byte nextCylinder,firedCylinder = 1;
