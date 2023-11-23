#include <Arduino.h>
#include "non_blocking_delay.h"

void nonBlockingDelayInit(nonBlockingDelay_t *p, unsigned long duration)
{
    p->duration = duration;
    p->startTime = millis();
}

bool nonBlockingDelayUpdate(nonBlockingDelay_t *p)
{
    if ((millis() - p->startTime) >= p->duration)
    {
        p->startTime = millis();
        return true;
    }

    return false;
}