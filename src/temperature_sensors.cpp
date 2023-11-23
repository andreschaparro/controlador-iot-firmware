#include <Arduino.h>
#include "temperature_sensors.h"
#include "settings.h"

static const uint8_t adcBits = 12;

static const uint8_t t1Pin = 36;
static const uint8_t t2Pin = 39;
static const uint8_t t3Pin = 34;
static const uint8_t t4Pin = 35;

static const uint8_t numOfAvgSamples = 10;

static const float minMV = 400.0;
static const float maxMV = 2000.0;
static const float minT = 0.0;
static const float maxT = 100.0;
static const float scale = (maxT - minT) / (maxMV - minMV);
static const float offset = maxT - (scale * maxMV);

static uint8_t numOfSample = 0;

static float t1 = 0.0;
static float t2 = 0.0;
static float t3 = 0.0;
static float t4 = 0.0;

static float t1Sum = 0.0;
static float t2Sum = 0.0;
static float t3Sum = 0.0;
static float t4Sum = 0.0;

void temperatureSensorsInit()
{
    analogReadResolution(adcBits);
}

void temperatureSensorsUpdate()
{
    if (numOfSample >= numOfAvgSamples)
    {
        numOfSample = 0;
        t1 = t1Sum / numOfAvgSamples;
        t2 = t2Sum / numOfAvgSamples;
        t3 = t3Sum / numOfAvgSamples;
        t4 = t4Sum / numOfAvgSamples;
        t1 = (scale * t1) + offset;
        t2 = (scale * t2) + offset;
        t3 = (scale * t3) + offset;
        t4 = (scale * t4) + offset;
        t1Sum = 0.0;
        t2Sum = 0.0;
        t3Sum = 0.0;
        t4Sum = 0.0;
    }
    else
    {
        numOfSample++;
        t1Sum += static_cast<float>(analogReadMilliVolts(t1Pin));
        t2Sum += static_cast<float>(analogReadMilliVolts(t2Pin));
        t3Sum += static_cast<float>(analogReadMilliVolts(t3Pin));
        t4Sum += static_cast<float>(analogReadMilliVolts(t4Pin));
    }
}

float temperatureSensorsT1Read()
{
    return t1;
}

float temperatureSensorsT2Read()
{
    return t2;
}

float temperatureSensorsT3Read()
{
    return t3;
}

float temperatureSensorsT4Read()
{
    return t4;
}