#ifndef TEMPERATURE_SENSORS_H
#define TEMPERATURE_SENSORS_H

void temperatureSensorsInit();
void temperatureSensorsUpdate();

float temperatureSensorsT1Read();
float temperatureSensorsT2Read();
float temperatureSensorsT3Read();
float temperatureSensorsT4Read();

#endif /* TEMPERATURE_SENSORS_H */