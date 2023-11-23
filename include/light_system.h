#ifndef LIGHT_SYSTEM_H
#define LIGHT_SYSTEM_H

void lightSystemInit();

void lightSystemCpuLedWrite(bool state);
void lightSystemCpuLedUpdate();

void lightSystemWifiLedWrite(bool state);

void lightSystemFirebaseLedWrite(bool state);

#endif /* LIGHT_SYSTEM_H */