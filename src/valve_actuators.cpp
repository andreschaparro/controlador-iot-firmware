#include <Arduino.h>
#include "valve_actuators.h"
#include "settings.h"

#define TEST_TIME_MS 3000

static const uint8_t v1Pin = 23;
static const uint8_t v2Pin = 22;
static const uint8_t v3Pin = 21;
static const uint8_t v4Pin = 19;

void valveActuatorsInit()
{
    pinMode(v1Pin, OUTPUT);
    pinMode(v2Pin, OUTPUT);
    pinMode(v3Pin, OUTPUT);
    pinMode(v4Pin, OUTPUT);

    digitalWrite(v1Pin, LOW);
    digitalWrite(v2Pin, LOW);
    digitalWrite(v3Pin, LOW);
    digitalWrite(v4Pin, LOW);

    delay(3000);

    digitalWrite(v1Pin, HIGH);
    digitalWrite(v2Pin, HIGH);
    digitalWrite(v3Pin, HIGH);
    digitalWrite(v4Pin, HIGH);

    delay(3000);

    if (settingsV1StateRead())
    {
        digitalWrite(v1Pin, LOW);
    }
    else
    {
        digitalWrite(v1Pin, HIGH);
    }

    if (settingsV2StateRead())
    {
        digitalWrite(v2Pin, LOW);
    }
    else
    {
        digitalWrite(v2Pin, HIGH);
    }

    if (settingsV3StateRead())
    {
        digitalWrite(v3Pin, LOW);
    }
    else
    {
        digitalWrite(v3Pin, HIGH);
    }

    if (settingsV4StateRead())
    {
        digitalWrite(v4Pin, LOW);
    }
    else
    {
        digitalWrite(v4Pin, HIGH);
    }
}

void valveActuatorsV1Write(bool state)
{
    if (settingsV1StateRead() != state)
    {
        settingsV1StateWrite(state);
        if (settingsV1StateRead())
        {
            digitalWrite(v1Pin, LOW);
        }
        else
        {
            digitalWrite(v1Pin, HIGH);
        }
    }
}

void valveActuatorsV2Write(bool state)
{
    if (settingsV2StateRead() != state)
    {
        settingsV2StateWrite(state);
        if (settingsV2StateRead())
        {
            digitalWrite(v2Pin, LOW);
        }
        else
        {
            digitalWrite(v2Pin, HIGH);
        }
    }
}

void valveActuatorsV3Write(bool state)
{
    if (settingsV3StateRead() != state)
    {
        settingsV3StateWrite(state);
        ;
        if (settingsV3StateRead())
        {
            digitalWrite(v3Pin, LOW);
        }
        else
        {
            digitalWrite(v3Pin, HIGH);
        }
    }
}

void valveActuatorsV4Write(bool state)
{
    if (settingsV4StateRead() != state)
    {
        settingsV4StateWrite(state);
        if (settingsV4StateRead())
        {
            digitalWrite(v4Pin, LOW);
        }
        else
        {
            digitalWrite(v4Pin, HIGH);
        }
    }
}