#include <Arduino.h>
#include "light_system.h"

static const uint8_t cpuLedPin = 32;
static const uint8_t wifiLedPin = 33;
static const uint8_t firebaseLedPin = 25;

static bool cpuLedState = false;
static bool wifiLedState = false;
static bool firebaseLedState = false;

void lightSystemInit()
{
    pinMode(cpuLedPin, OUTPUT);
    pinMode(wifiLedPin, OUTPUT);
    pinMode(firebaseLedPin, OUTPUT);

    for (uint8_t i = 0; i < 10; i++)
    {
        digitalWrite(cpuLedPin, HIGH);
        digitalWrite(wifiLedPin, HIGH);
        digitalWrite(firebaseLedPin, HIGH);
        delay(100);

        digitalWrite(cpuLedPin, LOW);
        digitalWrite(wifiLedPin, LOW);
        digitalWrite(firebaseLedPin, LOW);

        delay(100);
    }
}

void lightSystemCpuLedWrite(bool state)
{
    if (cpuLedState != state)
    {
        cpuLedState = state;

        if (cpuLedState)
        {
            digitalWrite(cpuLedPin, HIGH);
        }
        else
        {
            digitalWrite(cpuLedPin, LOW);
        }
    }
}

void lightSystemCpuLedUpdate()
{
    if (cpuLedState)
    {
        cpuLedState = false;
        digitalWrite(cpuLedPin, LOW);
    }
    else
    {
        cpuLedState = true;
        digitalWrite(cpuLedPin, HIGH);
    }
}

void lightSystemWifiLedWrite(bool state)
{
    if (wifiLedState != state)
    {
        wifiLedState = state;

        if (wifiLedState)
        {
            digitalWrite(wifiLedPin, HIGH);
        }
        else
        {
            digitalWrite(wifiLedPin, LOW);
        }
    }
}

void lightSystemFirebaseLedWrite(bool state)
{
    if (firebaseLedState != state)
    {
        firebaseLedState = state;

        if (firebaseLedState)
        {
            digitalWrite(firebaseLedPin, HIGH);
        }
        else
        {
            digitalWrite(firebaseLedPin, LOW);
        }
    }
}