#include <Arduino.h>
#include <WiFi.h>
#include "wifi_com.h"
#include "light_system.h"
#include "button.h"
#include "settings.h"

static bool apReady = false;

static void wifiComEventsUpdate(WiFiEvent_t event, WiFiEventInfo_t info);

void wifiComInit()
{
    WiFi.disconnect();
    WiFi.onEvent(wifiComEventsUpdate);

    lightSystemWifiLedWrite(true);
    delay(3000);

    if (buttonRead())
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            lightSystemWifiLedWrite(true);
            delay(500);

            lightSystemWifiLedWrite(false);
            delay(500);
        }

        if (!WiFi.softAP(settingsDevRead(), settingsDevPwdRead()))
        {
            Serial.println("Error al iniciar el WiFi Access Point!");
            ESP.restart();
        }

        Serial.println("WiFi Access Point Listo!");
        Serial.print("Direccion IP: ");
        Serial.println(WiFi.softAPIP());

        apReady = true;
        lightSystemWifiLedWrite(true);
    }
    else
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            lightSystemWifiLedWrite(true);
            delay(100);

            lightSystemWifiLedWrite(false);
            delay(100);
        }

        Serial.print("Conectandose al WiFi...");

        WiFi.begin(settingsSsidRead(), settingsSsidPwdRead());
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);

            Serial.print(".");
        }
    }
}

bool wifiComApReadyRead()
{
    return apReady;
}

static void wifiComEventsUpdate(WiFiEvent_t event, WiFiEventInfo_t info)
{
    switch (event)
    {
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:

        Serial.println("Desconectado del WiFi!");
        Serial.print("Motivo: ");
        Serial.println(info.wifi_sta_disconnected.reason);

        lightSystemWifiLedWrite(false);
        break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:

        Serial.println("WiFi Conectado");
        Serial.print("Direccion IP: ");
        Serial.println(WiFi.localIP());

        lightSystemWifiLedWrite(true);
        break;

    default:
        break;
    }
}