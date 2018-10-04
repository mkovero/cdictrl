#include <Arduino.h>
#include "TeensyDelay/src/TeensyDelay.h"
#include "include/pins.h"
#include "include/config.h"
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
}

void camInterrupt()
{
    camHit = true;
}

void callback() { digitalWrite(firedCylinder, LOW); }

void loop()
{
    if (camHit)
    {
        if (debugEnabled)
        {
            Serial.print("Injecting cylinder:");
            Serial.println(firingOrder[cylinder]);
        }
        digitalWrite(firingOrder[cylinder], HIGH);
        firedCylinder = firingOrder[cylinder];
        TeensyDelay::trigger(PRIDELAY);
        
        if (cylinder <= nrCylinders)
        {
            cylinder++;
        }
        else
        {
            cylinder = 1;
        }

        detachInterrupt(cam);
        camHit = false; // reset camHit state.
        attachInterrupt(digitalPinToInterrupt(cam), camInterrupt, RISING);
    }

    int curTps = tpsRead();
    if ( curTps < 20 ) { curTps = 20; } // bit hackery to allow pressure valve to stay bit open for testing, this should be normally be maintained by temperature and line pressure.

    int pctrl = map(curTps, 0, 100, 255, 0);
    analogWrite(pvalve, pctrl);
}
