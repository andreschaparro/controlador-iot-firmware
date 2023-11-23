#include <Arduino.h>
#include "button.h"

static const uint8_t buttonPin = 26;
static const uint32_t debounceButtonTimeMS = 40;

void buttonInit()
{
    pinMode(buttonPin, INPUT_PULLUP);
}

bool buttonRead()
{
    if (!digitalRead(buttonPin))
    {
        delay(debounceButtonTimeMS);

        if (!digitalRead(buttonPin))
        {
            return true;
        }
    }
    return false;
}