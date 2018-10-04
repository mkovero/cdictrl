#include <Arduino.h>
#include "include/calc.h"

int tpsRead()
{
    int tpsPercentValue = 0;

    float tpsVoltage = analogRead(tps) * 3.30;
    tpsPercentValue = readTPSVoltage(tpsVoltage);

    if (tpsPercentValue > 100)
    {
        tpsPercentValue = 100;
    }
    if (tpsPercentValue < 0)
    {
        tpsPercentValue = 0;
    }

    else
    {
        tpsPercentValue = 0;
    }
    return tpsPercentValue;
}

