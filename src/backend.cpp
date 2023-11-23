#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "backend.h"
#include "settings.h"
#include "temperature_sensors.h"
#include "flow_sensors.h"
#include "valve_actuators.h"

#define HTTP_PORT 80

static AsyncWebServer webServer(HTTP_PORT);

static const char savedChanges[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link type="text/css" rel="stylesheet" href="css/materialize.min.css" media="screen,projection" />
    <title>Cambios Guardados</title>
</head>

<body>

    <div class="container">
        <div class="row">
            <div class="col s12 m6">
                <ul class="collection center-align z-depth-2">
                    <li class="collection-item">Cambios Guardados!</li>
                    <li class="collection-item">
                        <a class="waves-effect waves-light btn" href="/">Volver</a>
                    </li>
                </ul>
            </div>
        </div>
    </div>

    <script type="text/javascript" src="js/materialize.min.js"></script>
    <script>
        document.addEventListener("DOMContentLoaded", () => {
            M.AutoInit();
        });
    </script>
</body>

</html>
)rawliteral";

static void backendHandleMaterializeCss(AsyncWebServerRequest *request);
static void backendHandleMaterializeJs(AsyncWebServerRequest *request);

static void backendHandleRoot(AsyncWebServerRequest *request);
static String backendProcessorRoot(const String &var);

static void backendHandleTelemetries(AsyncWebServerRequest *request);

static void backendHandleWifi(AsyncWebServerRequest *request);
static void backendHandleDevice(AsyncWebServerRequest *request);
static void backendHandleFirebase(AsyncWebServerRequest *request);
static void backendHandleSetpoints(AsyncWebServerRequest *request);
static void backendHandleConsumption(AsyncWebServerRequest *request);
static void backendHandleCommands(AsyncWebServerRequest *request);

static void backendHandleNotFound(AsyncWebServerRequest *request);

void backendInit()
{
    webServer.on("/css/materialize.min.css", HTTP_GET, backendHandleMaterializeCss);
    webServer.on("/js/materialize.min.js", HTTP_GET, backendHandleMaterializeJs);

    webServer.on("/", HTTP_GET, backendHandleRoot);
    webServer.on("/telemetries", HTTP_GET, backendHandleTelemetries);

    webServer.on("/wifi", HTTP_POST, backendHandleWifi);
    webServer.on("/device", HTTP_POST, backendHandleDevice);
    webServer.on("/firebase", HTTP_POST, backendHandleFirebase);
    webServer.on("/setpoints", HTTP_POST, backendHandleSetpoints);
    webServer.on("/consumption", HTTP_POST, backendHandleConsumption);
    webServer.on("/commands", HTTP_POST, backendHandleCommands);

    webServer.onNotFound(backendHandleNotFound);

    webServer.begin();
}

static void backendHandleMaterializeCss(AsyncWebServerRequest *request)
{
    request->send(LittleFS, "/css/materialize.min.css", "text/css");
}

static void backendHandleMaterializeJs(AsyncWebServerRequest *request)
{
    request->send(LittleFS, "/js/materialize.min.js", "application/javascript");
}

static void backendHandleRoot(AsyncWebServerRequest *request)
{
    request->send(LittleFS, "/index.html", String(), false, backendProcessorRoot);
}

static String backendProcessorRoot(const String &var)
{
    char buffer[SHORT_STR_SIZE] = "";
    unsigned long value = 0;

    if (var.equals("DEV_TYPE"))
    {
        return settingsDevTypeRead();
    }
    else if (var.equals("FW_VERSION"))
    {
        return settingsFwVersionRead();
    }
    else if (var.equals("HW_VERSION"))
    {
        return settingsHwVersionRead();
    }
    else if (var.equals("AUTHOR"))
    {
        return settingsAuthorRead();
    }
    else if (var.equals("SSID"))
    {
        return settingsSsidRead();
    }
    else if (var.equals("SSID_PWD"))
    {
        return settingsSsidPwdRead();
    }
    else if (var.equals("DEV"))
    {
        return settingsDevRead();
    }
    else if (var.equals("DEV_PWD"))
    {
        return settingsDevPwdRead();
    }
    else if (var.equals("API_KEY"))
    {
        return settingsApiKeyRead();
    }
    else if (var.equals("DB_URL"))
    {
        return settingsDbURLRead();
    }
    else if (var.equals("INTERVAL"))
    {
        value = settingsIntervalRead();
        value /= 1000;
        ultoa(value, buffer, 10);
        return buffer;
    }
    else if (var.equals("USER_EMAIL"))
    {
        return settingsUserEmailRead();
    }
    else if (var.equals("USER_PWD"))
    {
        return settingsUserPwdRead();
    }
    else if (var.equals("SP_T1"))
    {
        dtostrf(settingsSpT1Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("SP_T2"))
    {
        dtostrf(settingsSpT2Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("CONS_F1"))
    {
        dtostrf(settingsConsF1Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("T1"))
    {
        dtostrf(temperatureSensorsT1Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("T2"))
    {
        dtostrf(temperatureSensorsT2Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("T3"))
    {
        dtostrf(temperatureSensorsT3Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("T4"))
    {
        dtostrf(temperatureSensorsT4Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("F1"))
    {
        dtostrf(flowSensorsF1Read(), 3, 1, buffer);
        return buffer;
    }
    else if (var.equals("V1"))
    {
        if (settingsV1StateRead())
        {
            return "checked";
        }
    }
    else if (var.equals("V2"))
    {
        if (settingsV2StateRead())
        {
            return "checked";
        }
    }
    else if (var.equals("V3"))
    {
        if (settingsV3StateRead())
        {
            return "checked";
        }
    }
    else if (var.equals("V4"))
    {
        if (settingsV4StateRead())
        {
            return "checked";
        }
    }
    else if (var.equals("CTRL"))
    {
        if (settingsCtrlStateRead())
        {
            return "checked";
        }
    }
    return "";
}

static void backendHandleTelemetries(AsyncWebServerRequest *request)
{
    char bufferTelemetryId[SHORT_STR_SIZE] = "";
    char bufferTelemetryResponse[SHORT_STR_SIZE] = "";
    char bufferTelemetryValue[SHORT_STR_SIZE] = "";

    if (request->hasParam("id"))
    {
        strcpy(bufferTelemetryId, request->getParam("id")->value().c_str());

        if (strcmp(bufferTelemetryId, "t1") == 0)
        {
            dtostrf(temperatureSensorsT1Read(), 3, 1, bufferTelemetryValue);
        }
        else if (strcmp(bufferTelemetryId, "t2") == 0)
        {
            dtostrf(temperatureSensorsT2Read(), 3, 1, bufferTelemetryValue);
        }
        else if (strcmp(bufferTelemetryId, "t3") == 0)
        {
            dtostrf(temperatureSensorsT3Read(), 3, 1, bufferTelemetryValue);
        }
        else if (strcmp(bufferTelemetryId, "t4") == 0)
        {
            dtostrf(temperatureSensorsT4Read(), 3, 1, bufferTelemetryValue);
        }
        else if (strcmp(bufferTelemetryId, "f1") == 0)
        {
            dtostrf(flowSensorsF1Read(), 3, 1, bufferTelemetryValue);
        }
        else if (strcmp(bufferTelemetryId, "consF1") == 0)
        {
            dtostrf(settingsConsF1Read(), 3, 1, bufferTelemetryValue);
        }

        strcpy(bufferTelemetryResponse, "{\"");
        strcat(bufferTelemetryResponse, bufferTelemetryId);
        strcat(bufferTelemetryResponse, "\":\"");
        strcat(bufferTelemetryResponse, bufferTelemetryValue);
        strcat(bufferTelemetryResponse, "\"}");

        request->send(200, "application/json", bufferTelemetryResponse);
    }
    else
    {
        request->send(400, "text/plain", "Bad Request");
    }
}

static void backendHandleWifi(AsyncWebServerRequest *request)
{
    char buffer[SHORT_STR_SIZE] = "";

    strcpy(buffer, request->arg("ssid").c_str());
    settingsSsidWrite(buffer);

    strcpy(buffer, request->arg("ssidPwd").c_str());
    settingsSsidPwdWrite(buffer);

    request->send(200, "text/html", savedChanges);
}

static void backendHandleDevice(AsyncWebServerRequest *request)
{
    char buffer[SHORT_STR_SIZE] = "";

    strcpy(buffer, request->arg("dev").c_str());
    settingsDevWrite(buffer);

    strcpy(buffer, request->arg("devPwd").c_str());
    settingsDevPwdWrite(buffer);

    request->send(200, "text/html", savedChanges);
}

static void backendHandleFirebase(AsyncWebServerRequest *request)
{
    char buffer[LONG_STR_SIZE] = "";
    unsigned long value = 0;

    strcpy(buffer, request->arg("apiKey").c_str());
    settingsApiKeyWrite(buffer);

    strcpy(buffer, request->arg("dbURL").c_str());
    settingsDbURLWrite(buffer);

    strcpy(buffer, request->arg("userEmail").c_str());
    settingsUserEmailWrite(buffer);

    strcpy(buffer, request->arg("userPwd").c_str());
    settingsUserPwdWrite(buffer);

    value = request->arg("interval").toInt();
    value *= 1000;

    settingsIntervalWrite(value);

    request->send(200, "text/html", savedChanges);
}

static void backendHandleSetpoints(AsyncWebServerRequest *request)
{
    float value = request->arg("spT1").toFloat();
    settingsSpT1Write(value);

    value = request->arg("spT2").toFloat();
    settingsSpT2Write(request->arg("spT2").toFloat());

    request->send(200, "text/html", savedChanges);
}

static void backendHandleConsumption(AsyncWebServerRequest *request)
{
    settingsConsF1Write(0.0);

    request->send(200, "text/html", savedChanges);
}

static void backendHandleCommands(AsyncWebServerRequest *request)
{
    char bufferCommandId[SHORT_STR_SIZE] = "";
    char bufferCommandChecked[SHORT_STR_SIZE] = "";

    if ((request->hasParam("id", true)) && (request->hasParam("checked", true)))
    {
        strcpy(bufferCommandId, request->getParam("id", true)->value().c_str());
        strcpy(bufferCommandChecked, request->getParam("checked", true)->value().c_str());

        if (strcmp(bufferCommandId, "ctrl") == 0)
        {
            if (strcmp(bufferCommandChecked, "true") == 0)
            {
                settingsCtrlStateWrite(true);
            }
            else
            {
                settingsCtrlStateWrite(false);
            }
        }
        else if (!settingsCtrlStateRead())
        {
            if (strcmp(bufferCommandId, "v1") == 0)
            {
                if (strcmp(bufferCommandChecked, "true") == 0)
                {
                    valveActuatorsV1Write(true);
                }
                else
                {
                    valveActuatorsV1Write(false);
                }
            }
            else if (strcmp(bufferCommandId, "v2") == 0)
            {
                if (strcmp(bufferCommandChecked, "true") == 0)
                {
                    valveActuatorsV2Write(true);
                }
                else
                {
                    valveActuatorsV2Write(false);
                }
            }
            else if (strcmp(bufferCommandId, "v3") == 0)
            {
                if (strcmp(bufferCommandChecked, "true") == 0)
                {
                    valveActuatorsV3Write(true);
                }
                else
                {
                    valveActuatorsV3Write(false);
                }
            }
            else if (strcmp(bufferCommandId, "v4") == 0)
            {
                if (strcmp(bufferCommandChecked, "true") == 0)
                {
                    valveActuatorsV4Write(true);
                }
                else
                {
                    valveActuatorsV4Write(false);
                }
            }
        }
        request->send(200);
    }
    else
    {
        request->send(400, "text/plain", "Bad Request");
    }
}

static void backendHandleNotFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "El recurso solicitado no existe");
}