#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include "firebase_com.h"
#include "settings.h"
#include "light_system.h"
#include "temperature_sensors.h"
#include "flow_sensors.h"
#include "valve_actuators.h"

static FirebaseData fbdo;
static FirebaseAuth auth;
static FirebaseConfig config;
static FirebaseJson json;
static FirebaseData stream;

static const int daylightOffsetSec = 0;
static const long gmtOffsetSec = (-3) * (60 * 60);

static char uid[LONG_STR_SIZE] = "";
static char telemetriesPath[LONG_STR_SIZE] = "";
static char entryPath[LONG_STR_SIZE] = "";
static char bufferTs[LONG_STR_SIZE] = "";
static char commandsPath[LONG_STR_SIZE] = "";
static char dataPath[SHORT_STR_SIZE] = "";

static time_t ts = 0;

static float p = 0.0;

static time_t getTime();

static void firebaseComStreamCallback(FirebaseStream data);
static void firebaseComStreamTimeoutCallback(bool timeout);

void firebaseComInit()
{
    Serial.print("Cliente Firebase v");
    Serial.println(FIREBASE_CLIENT_VERSION);

    config.api_key = settingsApiKeyRead();

    auth.user.email = settingsUserEmailRead();
    auth.user.password = settingsUserPwdRead();

    config.database_url = settingsDbURLRead();

    config.token_status_callback = tokenStatusCallback;

    fbdo.setBSSLBufferSize(2048, 1024);
    stream.setBSSLBufferSize(2048, 1024);

    Firebase.begin(&config, &auth);

    Firebase.reconnectNetwork(true);

    Serial.print("Conectandose a Firebase...");

    while ((auth.token.uid) == "")
    {
        delay(500);
        Serial.print(".");
    }

    strcpy(uid, auth.token.uid.c_str());

    Serial.print("UUID del usuario: ");
    Serial.println(uid);

    configTime(gmtOffsetSec, daylightOffsetSec, settingsNtpServerRead());

    strcpy(telemetriesPath, "/telemetries/");
    strcat(telemetriesPath, uid);
    strcat(telemetriesPath, "/");

    lightSystemFirebaseLedWrite(true);

    strcpy(commandsPath, "/commands/");
    strcat(commandsPath, uid);

    stream.keepAlive(5, 5, 1);

    if (!Firebase.RTDB.beginStream(&stream, commandsPath))
    {
        Serial.print("Error al inicializar el Listener: ");
        Serial.println(stream.errorReason().c_str());
    }

    Firebase.RTDB.setStreamCallback(&stream, firebaseComStreamCallback, firebaseComStreamTimeoutCallback);
}

void firebaseComWrite()
{
    if (Firebase.ready())
    {
        lightSystemFirebaseLedWrite(true);

        ts = getTime();

        strcpy(entryPath, telemetriesPath);

        ltoa(ts, bufferTs, 10);

        strcat(entryPath, bufferTs);

        Serial.print("Telemetry Entry: ");
        Serial.println(entryPath);

        json.set("t1", temperatureSensorsT1Read());
        json.set("t2", temperatureSensorsT2Read());
        json.set("t3", temperatureSensorsT3Read());
        json.set("t4", temperatureSensorsT4Read());

        json.set("spT1", settingsSpT1Read());
        json.set("spT2", settingsSpT2Read());

        json.set("f1", flowSensorsF1Read());
        json.set("consF1", settingsConsF1Read());

        if (temperatureSensorsT3Read() > temperatureSensorsT4Read())
        {
            p = (temperatureSensorsT3Read() - temperatureSensorsT4Read()) * flowSensorsF1Read();
        }
        else
        {
            p = 0.0;
        }

        json.set("p", p);

        json.set("ctrl", settingsCtrlStateRead());
        json.set("v1", settingsV1StateRead());
        json.set("v2", settingsV2StateRead());
        json.set("v3", settingsV3StateRead());
        json.set("v4", settingsV4StateRead());

        json.set("ts", ts);

        Serial.print("Write Json to Firebase...");

        stream.keepAlive(5, 5, 1);

        if (Firebase.RTDB.setJSON(&fbdo, entryPath, &json))
        {
            Serial.println("Ok");
        }
        else
        {
            Serial.println(fbdo.errorReason().c_str());
        }
    }
    else
    {
        lightSystemFirebaseLedWrite(false);
    }
}

static time_t getTime()
{
    time_t now;

    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("No se pudo obtener la Fecha y Hora!");
        return 0;
    }

    time(&now);

    return now;
}

static void firebaseComStreamCallback(FirebaseStream data)
{
    strcpy(dataPath, data.dataPath().c_str());

    Serial.print("Command entry: ");
    Serial.println(dataPath);

    if (data.dataTypeEnum() == fb_esp_rtdb_data_type_boolean)
    {
        bool state = data.boolData();

        Serial.print("State Read from Firebase: ");
        Serial.println(state);

        if (strcmp(dataPath, "/ctrl") == 0)
        {
            settingsCtrlStateWrite(state);
        }
        else if (!settingsCtrlStateRead())
        {
            if (strcmp(dataPath, "/v1") == 0)
            {
                valveActuatorsV1Write(state);
            }
            else if (strcmp(dataPath, "/v2") == 0)
            {
                valveActuatorsV2Write(state);
            }
            else if (strcmp(dataPath, "/v3") == 0)
            {
                valveActuatorsV3Write(state);
            }
            else if (strcmp(dataPath, "/v4") == 0)
            {
                valveActuatorsV4Write(state);
            }
        }
    }
    else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_float)
    {
        float value = data.floatData();

        Serial.print("Value Read from Firebase: ");
        Serial.println(value);

        if (strcmp(dataPath, "/spT1") == 0)
        {
            settingsSpT1Write(value);
        }
        else if (strcmp(dataPath, "/spT2") == 0)
        {
            settingsSpT2Write(value);
        }
        else if (strcmp(dataPath, "/consF1") == 0)
        {
            settingsConsF1Write(value);
        }
    }
    else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_integer)
    {
        float value = static_cast<float>(data.intData());

        Serial.print("Value Read from Firebase: ");
        Serial.println(value);

        if (strcmp(dataPath, "/spT1") == 0)
        {
            settingsSpT1Write(value);
        }
        else if (strcmp(dataPath, "/spT2") == 0)
        {
            settingsSpT2Write(value);
        }
        else if (strcmp(dataPath, "/consF1") == 0)
        {
            settingsConsF1Write(value);
        }
    }
}

static void firebaseComStreamTimeoutCallback(bool timeout)
{
    if (timeout)
    {
        Serial.println("Timeout del Listener, reanudando..");
    }

    if (!stream.httpConnected())
    {
        Serial.print("Codigo de Error: ");
        Serial.println(stream.httpCode());
        Serial.print("Causa: ");
        Serial.println(stream.errorReason().c_str());
    }
}