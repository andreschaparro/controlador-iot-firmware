#include <Arduino.h>
#include "flow_sensors.h"
#include "settings.h"

static const uint8_t f1Pin = 27;

static const float scale = 11.0;
static const float offset = 0.0;

static volatile uint32_t cntF1 = 0;

static float f1 = 0.0;

static void ARDUINO_ISR_ATTR flowSensorsF1ISR();

void flowSensorsInit()
{
    pinMode(f1Pin, INPUT_PULLUP);
    attachInterrupt(f1Pin, flowSensorsF1ISR, FALLING);
}

static void ARDUINO_ISR_ATTR flowSensorsF1ISR()
{
    cntF1++;
}

void flowSensorsUpdate()
{
    f1 = (static_cast<float>(cntF1) - offset) / scale;
    cntF1 = 0;

    if (f1 < 0.0)
    {
        f1 = 0.0;
    }

    settingsConsF1Write(settingsConsF1Read() + (f1 / 60.0));
}

float flowSensorsF1Read()
{
    return f1;
}
