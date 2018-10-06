#include <Arduino.h>
extern boolean camHit,debugEnabled;
extern byte firingOrder[8], nextCylinder, firedCylinder, cylinder, nrCylinders;
extern double lastTimedRun, pollInterval, Kp, Ki, Kd;
extern int curFp,pressureLim;
#define PRIDELAY 2000 // primary injection delay 2ms.