#include "JsonCreator.h"
#include <cmath>

String JsonCreator::createJson(uint32_t stationId,unsigned int sessionId, String dateTime, float temperature, float humidity, float dustDensity) {
    StaticJsonDocument<200> doc;

    doc["SID"] = stationId;
    doc["sessionID"] = sessionId;
    doc["dateTime"] = dateTime;
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["dustDensity"] = dustDensity;

    String output;
    serializeJson(doc, output);

    return output;
}