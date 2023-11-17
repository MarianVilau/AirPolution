#ifndef JSONCREATOR_H
#define JSONCREATOR_H

#include <ArduinoJson.h>

class JsonCreator {
public:
    String createJson(uint32_t stationId,unsigned int sessionId,String dateTime, float temperature, float humidity, float dustDensity);
};

#endif