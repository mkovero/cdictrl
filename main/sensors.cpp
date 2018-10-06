#include <Arduino.h>
#include "include/calc.h"
#include "include/pins.h"

int tpsRead()
{
    int tpsPercentValue = 0;

    float tpsVoltage = analogRead(tps) * 3.30;
    tpsPercentValue = map(tpsVoltage, 1900, 800, 0, 100);

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

int fpRead()
{
    int pressurePercentValue = 0;

    float pressureVoltage = analogRead(psensor) * 3.30;
    pressurePercentValue = map(pressureVoltage, 500, 3000, 0, 100);

    if (pressurePercentValue > 100)
    {
        pressurePercentValue = 100;
    }
    if (pressurePercentValue < 0)
    {
        pressurePercentValue = 0;
    }

    return pressurePercentValue;
}

int oilTempRead()
{
  float c1 = 1.268318203e-03, c2 = 2.662206632e-04, c3 = 1.217978476e-07;
  float tempRead = analogRead(etemp);
  int R2 = 470 / (1023.0 / (float)tempRead - 1.0);
  float logR2 = log(R2);
  float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  float oilTemp = T - 273.15;
  oilTemp = oilTemp - 60;
  return oilTemp;
}
