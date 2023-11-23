#include <Arduino.h>
#include <Preferences.h>
#include "settings.h"

static Preferences prefs;

static const bool rw = false;
static const bool ro = true;

static const char *ntpServer = "pool.ntp.org";
static const char *fwVersion = "1.0.0";
static const char *hwVersion = "1.0.0";
static const char *devType = "Termotanques Solares Cocina";
static const char *author = "Ing. Andres Chaparro";

static bool v1State = false;
static bool v2State = false;
static bool v3State = false;
static bool v4State = false;
static bool ctrlState = false;

static float spT1 = 65.0;
static float spT2 = 65.0;
static float consF1 = 0.0;

static char ssid[SHORT_STR_SIZE] = "";
static char ssidPwd[SHORT_STR_SIZE] = "";
static char dev[SHORT_STR_SIZE] = "NodoIoT";
static char devPwd[SHORT_STR_SIZE] = "0123456789";

static char apiKey[LONG_STR_SIZE] = "";
static char dbURL[LONG_STR_SIZE] = "";
static char userEmail[SHORT_STR_SIZE] = "";
static char userPwd[SHORT_STR_SIZE] = "";

static unsigned long interval = 60 * 1000;

void settingsRead()
{
    prefs.begin("settings", ro);

    if (prefs.isKey("v1State"))
    {
        v1State = prefs.getBool("v1State");
    }

    if (prefs.isKey("v2State"))
    {
        v2State = prefs.getBool("v2State");
    }

    if (prefs.isKey("v3State"))
    {
        v3State = prefs.getBool("v3State");
    }

    if (prefs.isKey("v4State"))
    {
        v4State = prefs.getBool("v4State");
    }

    if (prefs.isKey("ctrlState"))
    {
        ctrlState = prefs.getBool("ctrlState");
    }

    if (prefs.isKey("spT1"))
    {
        spT1 = prefs.getFloat("spT1");
    }

    if (prefs.isKey("spT2"))
    {
        spT2 = prefs.getFloat("spT2");
    }

    if (prefs.isKey("consF1"))
    {
        consF1 = prefs.getFloat("consF1");
    }

    if (prefs.isKey("ssid"))
    {
        prefs.getString("ssid", ssid, SHORT_STR_SIZE);
    }

    if (prefs.isKey("ssidPwd"))
    {
        prefs.getString("ssidPwd", ssidPwd, SHORT_STR_SIZE);
    }

    if (prefs.isKey("dev"))
    {
        prefs.getString("dev", dev, SHORT_STR_SIZE);
    }

    if (prefs.isKey("devPwd"))
    {
        prefs.getString("devPwd", devPwd, SHORT_STR_SIZE);
    }

    if (prefs.isKey("apiKey"))
    {
        prefs.getString("apiKey", apiKey, LONG_STR_SIZE);
    }

    if (prefs.isKey("dbURL"))
    {
        prefs.getString("dbURL", dbURL, LONG_STR_SIZE);
    }

    if (prefs.isKey("userEmail"))
    {
        prefs.getString("userEmail", userEmail, SHORT_STR_SIZE);
    }

    if (prefs.isKey("userPwd"))
    {
        prefs.getString("userPwd", userPwd, SHORT_STR_SIZE);
    }

    if (prefs.isKey("interval"))
    {
        interval = prefs.getULong("interval");
    }

    prefs.end();

    Serial.print("Tipo de Dispositivo: ");
    Serial.println(devType);

    Serial.print("Version del Firmware: ");
    Serial.println(fwVersion);

    Serial.print("Version del Hardware: ");
    Serial.println(hwVersion);

    Serial.print("Autor: ");
    Serial.println(author);

    Serial.print("NTP Server: ");
    Serial.println(ntpServer);

    Serial.print("SSID: ");
    Serial.println(ssid);

    Serial.print("SSID Password: ");
    Serial.println(ssidPwd);

    Serial.print("Nombre del Dispositivo: ");
    Serial.println(dev);

    Serial.print("Password del Dispositivo: ");
    Serial.println(devPwd);

    Serial.print("API Key de Firebase: ");
    Serial.println(apiKey);

    Serial.print("Database URL de Firebase: ");
    Serial.println(dbURL);

    Serial.print("User Email de Firebase: ");
    Serial.println(userEmail);

    Serial.print("User Password de Firebase: ");
    Serial.println(userPwd);

    Serial.print("Intervalo de Tiempo entre envio de Telemetrias: ");
    Serial.println(interval);

    Serial.print("Setpoint del Sensor T1: ");
    Serial.println(spT1);

    Serial.print("Setpoint del Sensor T2: ");
    Serial.println(spT2);

    Serial.print("Consumo de Agua F1: ");
    Serial.println(consF1);

    Serial.print("Estado de la Valvula V1: ");
    Serial.println(v1State);

    Serial.print("Estado de la Valvula V2: ");
    Serial.println(v2State);

    Serial.print("Estado de la Valvula V3: ");
    Serial.println(v3State);

    Serial.print("Estado de la Valvula V4: ");
    Serial.println(v4State);

    Serial.print("Estado del controlador: ");
    Serial.println(ctrlState);
}

void settingsWrite()
{
    prefs.begin("settings", rw);

    prefs.putUChar("v1State", v1State);
    prefs.putUChar("v2State", v2State);
    prefs.putUChar("v3State", v3State);
    prefs.putUChar("v4State", v4State);
    prefs.putUChar("ctrlState", ctrlState);

    prefs.putFloat("spT1", spT1);
    prefs.putFloat("spT2", spT2);
    prefs.putFloat("consF1", consF1);

    prefs.putString("ssid", ssid);
    prefs.putString("ssidPwd", ssidPwd);
    prefs.putString("dev", dev);
    prefs.putString("devPwd", devPwd);

    prefs.putString("apiKey", apiKey);
    prefs.putString("dbURL", dbURL);
    prefs.putString("userEmail", userEmail);
    prefs.putString("userPwd", userPwd);

    prefs.putULong("interval", interval);

    prefs.end();
}

const char *settingsNtpServerRead()
{
    return ntpServer;
}

const char *settingsFwVersionRead()
{
    return fwVersion;
}

const char *settingsHwVersionRead()
{
    return hwVersion;
}

const char *settingsDevTypeRead()
{
    return devType;
}

const char *settingsAuthorRead()
{
    return author;
}

bool settingsV1StateRead()
{
    return v1State;
}

bool settingsV2StateRead()
{
    return v2State;
}

bool settingsV3StateRead()
{
    return v3State;
}

bool settingsV4StateRead()
{
    return v4State;
}

bool settingsCtrlStateRead()
{
    return ctrlState;
}

float settingsSpT1Read()
{
    return spT1;
}

float settingsSpT2Read()
{
    return spT2;
}

float settingsConsF1Read()
{
    return consF1;
}

const char *settingsSsidRead()
{
    return ssid;
}

const char *settingsSsidPwdRead()
{
    return ssidPwd;
}

const char *settingsDevRead()
{
    return dev;
}

const char *settingsDevPwdRead()
{
    return devPwd;
}

const char *settingsApiKeyRead()
{
    return apiKey;
}

const char *settingsDbURLRead()
{
    return dbURL;
}

const char *settingsUserEmailRead()
{
    return userEmail;
}

const char *settingsUserPwdRead()
{
    return userPwd;
}

unsigned long settingsIntervalRead()
{
    return interval;
}

void settingsV1StateWrite(bool state)
{
    if (v1State != state)
    {
        v1State = state;

        prefs.begin("settings", rw);
        prefs.putBool("v1State", v1State);
        prefs.end();
    }
}

void settingsV2StateWrite(bool state)
{
    if (v2State != state)
    {
        v2State = state;

        prefs.begin("settings", rw);
        prefs.putBool("v2State", v2State);
        prefs.end();
    }
}

void settingsV3StateWrite(bool state)
{
    if (v3State != state)
    {
        v3State = state;

        prefs.begin("settings", rw);
        prefs.putBool("v3State", v3State);
        prefs.end();
    }
}

void settingsV4StateWrite(bool state)
{
    if (v4State != state)
    {
        v4State = state;

        prefs.begin("settings", rw);
        prefs.putBool("v4State", v4State);
        prefs.end();
    }
}

void settingsCtrlStateWrite(bool state)
{
    if (ctrlState != state)
    {
        ctrlState = state;

        prefs.begin("settings", rw);
        prefs.putBool("ctrlState", ctrlState);
        prefs.end();
    }
}

void settingsSpT1Write(float value)
{
    if (spT1 != value)
    {
        spT1 = value;

        prefs.begin("settings", rw);
        prefs.putFloat("spT1", spT1);
        prefs.end();
    }
}

void settingsSpT2Write(float value)
{
    if (spT2 != value)
    {
        spT2 = value;

        prefs.begin("settings", rw);
        prefs.putFloat("spT2", spT2);
        prefs.end();
    }
}

void settingsConsF1Write(float value)
{
    if (consF1 != value)
    {
        consF1 = value;

        prefs.begin("settings", rw);
        prefs.putFloat("consF1", consF1);
        prefs.end();
    }
}

void settingsSsidWrite(const char *str)
{
    if (strcmp(ssid, str) != 0)
    {
        strcpy(ssid, str);

        prefs.begin("settings", rw);
        prefs.putString("ssid", ssid);
        prefs.end();
    }
}

void settingsSsidPwdWrite(const char *str)
{
    if (strcmp(ssidPwd, str) != 0)
    {
        strcpy(ssidPwd, str);

        prefs.begin("settings", rw);
        prefs.putString("ssidPwd", ssidPwd);
        prefs.end();
    }
}

void settingsDevWrite(const char *str)
{
    if (strcmp(dev, str) != 0)
    {
        strcpy(dev, str);

        prefs.begin("settings", rw);
        prefs.putString("dev", dev);
        prefs.end();
    }
}

void settingsDevPwdWrite(const char *str)
{
    if (strcmp(devPwd, str) != 0)
    {
        strcpy(devPwd, str);

        prefs.begin("settings", rw);
        prefs.putString("devPwd", devPwd);
        prefs.end();
    }
}

void settingsApiKeyWrite(const char *str)
{
    if (strcmp(apiKey, str) != 0)
    {
        strcpy(apiKey, str);

        prefs.begin("settings", rw);
        prefs.putString("apiKey", apiKey);
        prefs.end();
    }
}

void settingsDbURLWrite(const char *str)
{
    if (strcmp(dbURL, str) != 0)
    {
        strcpy(dbURL, str);

        prefs.begin("settings", rw);
        prefs.putString("dbURL", dbURL);
        prefs.end();
    }
}

void settingsUserEmailWrite(const char *str)
{
    if (strcmp(userEmail, str) != 0)
    {
        strcpy(userEmail, str);

        prefs.begin("settings", rw);
        prefs.putString("userEmail", userEmail);
        prefs.end();
    }
}

void settingsUserPwdWrite(const char *str)
{
    if (strcmp(userPwd, str) != 0)
    {
        strcpy(userPwd, str);

        prefs.begin("settings", rw);
        prefs.putString("userPwd", userPwd);
        prefs.end();
    }
}

void settingsIntervalWrite(unsigned long value)
{
    if (interval != value)
    {
        interval = value;

        prefs.begin("settings", rw);
        prefs.putULong("interval", interval);
        prefs.end();
    }
}