#include <Arduino.h>
#include "factory_reset.h"
#include "light_system.h"
#include "button.h"
#include "settings.h"

void factoryResetInit()
{
    lightSystemCpuLedWrite(true);
    delay(3000);

    if (buttonRead())
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            lightSystemCpuLedWrite(true);
            delay(100);

            lightSystemCpuLedWrite(false);
            delay(100);
        }

        settingsWrite();
        Serial.println("Reset a Fabrica!");
    }
    else
    {
        lightSystemCpuLedWrite(false);
    }

    settingsRead();
}