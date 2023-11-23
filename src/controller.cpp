#include <Arduino.h>
#include "controller.h"
#include "settings.h"
#include "temperature_sensors.h"
#include "valve_actuators.h"

void controllerUpdate()
{
    if (settingsCtrlStateRead())
    {
        if (temperatureSensorsT1Read() > settingsSpT1Read())
        {
            valveActuatorsV1Write(true);
        }
        else
        {
            valveActuatorsV1Write(false);
        }

        if (temperatureSensorsT2Read() > settingsSpT2Read())
        {
            valveActuatorsV2Write(true);
        }
        else
        {
            valveActuatorsV2Write(false);
        }

        if ((!settingsV1StateRead()) || (!settingsV2StateRead()))
        {
            valveActuatorsV3Write(false);
            valveActuatorsV4Write(true);
        }
        else
        {
            valveActuatorsV3Write(true);
            valveActuatorsV4Write(false);
        }
    }
}