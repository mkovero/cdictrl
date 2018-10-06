#include <Arduino.h>
#include <AutoPID.h>
#include "include/TeensyDelay.h"
#include "include/pins.h"
#include "include/config.h"
#include "include/sensors.h"
boolean fired = false;
int pressurePWM;
/*
    CDI engine controller
    Copyright (C) 2018 Markus Kovero <mui@mui.fi>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have  received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Big thanks to everyone taking part on 7226ctrl project allowing this to happen.
*/
   // AutoPID myPID(&curFp, &pressureLim, &pressurePWM, 0, 255, Kp, Ki, Kd);

void callback()
{
    digitalWriteFast(firedCylinder, LOW);
    if (debugEnabled)
    {
        Serial.print("Stopping inject:");
        Serial.println(firingOrder[cylinder]);
    }
    fired = false; // reset camHit state.
}
void setup()
{

    // Injectors
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);
    // Pressure regulation
    pinMode(pvalve, OUTPUT);
    pinMode(psensor, INPUT);
    // Cam signal
    pinMode(cam, INPUT);
    attachInterrupt(digitalPinToInterrupt(cam), camInterrupt, RISING);
    // Sensors
    pinMode(etemp, INPUT);
    pinMode(atemp, INPUT);
    pinMode(tps, INPUT);
    TeensyDelay::begin();                   // setup timer
    TeensyDelay::addDelayChannel(callback); // add a delay channel and attach callback function
}

void camInterrupt()
{
    camHit = true;
}

void loop()
{
    if (camHit && !fired)
    {
        fired = true;
        if (debugEnabled)
        {
            Serial.print("Injecting cylinder:");
            Serial.println(firingOrder[cylinder]);
        }
        digitalWriteFast(firingOrder[cylinder], HIGH);
        firedCylinder = firingOrder[cylinder];
        TeensyDelay::trigger(10000);

        if (cylinder < 8)
        {
            cylinder++;
        }
        else
        {
            cylinder = 0;
        }

        // detachInterrupt(cam);
        camHit = false; // reset camHit state.
        //attachInterrupt(digitalPinToInterrupt(cam), camInterrupt, RISING);
    } else if (millis() - lastTimedRun > pollInterval)
    {
        pollSystem();
    }
}

void pollSystem() { 
   // pressureCtrl();
    lastTimedRun = millis();
}

/*void pressureCtrl() {
    curFp = fpRead();
    pressureLim = readMap(pressureMap, tpsRead(), oilTempRead());

    myPID.setBangBang(100, 50);
    myPID.setTimeStep(100);
    myPID.run();
    analogWrite(pvalve, pressurePWM);
}*/
