#include <Arduino.h>
#include <LittleFS.h>
#include "node_iot.h"
#include "light_system.h"
#include "button.h"
#include "factory_reset.h"
#include "wifi_com.h"
#include "backend.h"
#include "valve_actuators.h"
#include "temperature_sensors.h"
#include "flow_sensors.h"
#include "non_blocking_delay.h"
#include "controller.h"
#include "firebase_com.h"
#include "settings.h"

static const bool formatOnFail = true;
static const unsigned long serialBaudRate = 115200;
static const unsigned long lightSystemNBDDurationMS = 1000;
static const unsigned long temperatureSensorsNBDDurationMS = 100;
static const unsigned long flowSensorsNBDDurationMS = 1000;

static nonBlockingDelay_t lightSystemNBD;
static nonBlockingDelay_t temperatureSensorsNBD;
static nonBlockingDelay_t flowSensorsNBD;
static nonBlockingDelay_t firebaseNBD;

void nodeIoTInit()
{
    Serial.begin(serialBaudRate);

    if (!LittleFS.begin(formatOnFail))
    {
        Serial.println("Falla de Montaje de LittleFS!");
        ESP.restart();
    }

    lightSystemInit();

    buttonInit();

    factoryResetInit();

    wifiComInit();

    if (wifiComApReadyRead())
    {
        backendInit();
    }
    else
    {
        firebaseComInit();
    }

    valveActuatorsInit();

    temperatureSensorsInit();

    flowSensorsInit();

    nonBlockingDelayInit(&lightSystemNBD, lightSystemNBDDurationMS);
    nonBlockingDelayInit(&temperatureSensorsNBD, temperatureSensorsNBDDurationMS);
    nonBlockingDelayInit(&flowSensorsNBD, flowSensorsNBDDurationMS);
    nonBlockingDelayInit(&firebaseNBD, settingsIntervalRead());
}

void nodeIoTUpdate()
{
    if (nonBlockingDelayUpdate(&lightSystemNBD))
    {
        lightSystemCpuLedUpdate();
    }

    if (nonBlockingDelayUpdate(&temperatureSensorsNBD))
    {
        temperatureSensorsUpdate();
        controllerUpdate();
    }

    if (nonBlockingDelayUpdate(&flowSensorsNBD))
    {
        flowSensorsUpdate();
    }

    if (nonBlockingDelayUpdate(&firebaseNBD))
    {
        firebaseComWrite();
    }
}