#ifndef JSONCREATOR_H
#define JSONCREATOR_H

#include <ArduinoJson.h>

class JsonCreator {
public:
    String createJson(uint32_t stationId, const char* dateTime, float temperature, float humidity, float dustDensity);
};

#endif