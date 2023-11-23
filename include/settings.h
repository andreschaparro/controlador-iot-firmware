#ifndef SETTINGS_H
#define SETTINGS_H

#define SHORT_STR_SIZE 30
#define LONG_STR_SIZE 170

void settingsRead();
void settingsWrite();

const char *settingsNtpServerRead();
const char *settingsFwVersionRead();
const char *settingsHwVersionRead();
const char *settingsDevTypeRead();
const char *settingsAuthorRead();

bool settingsV1StateRead();
bool settingsV2StateRead();
bool settingsV3StateRead();
bool settingsV4StateRead();
bool settingsCtrlStateRead();

float settingsSpT1Read();
float settingsSpT2Read();
float settingsConsF1Read();

const char *settingsSsidRead();
const char *settingsSsidPwdRead();
const char *settingsDevRead();
const char *settingsDevPwdRead();

const char *settingsApiKeyRead();
const char *settingsDbURLRead();
const char *settingsUserEmailRead();
const char *settingsUserPwdRead();

unsigned long settingsIntervalRead();

void settingsV1StateWrite(bool state);
void settingsV2StateWrite(bool state);
void settingsV3StateWrite(bool state);
void settingsV4StateWrite(bool state);
void settingsCtrlStateWrite(bool state);

void settingsSpT1Write(float value);
void settingsSpT2Write(float value);
void settingsConsF1Write(float value);

void settingsSsidWrite(const char *str);
void settingsSsidPwdWrite(const char *str);
void settingsDevWrite(const char *str);
void settingsDevPwdWrite(const char *str);

void settingsApiKeyWrite(const char *str);
void settingsDbURLWrite(const char *str);
void settingsUserEmailWrite(const char *str);
void settingsUserPwdWrite(const char *str);

void settingsIntervalWrite(unsigned long value);

#endif /* SETTINGS_H */