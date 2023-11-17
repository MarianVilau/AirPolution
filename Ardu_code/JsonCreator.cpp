#include "JsonCreator.h"

String JsonCreator::createJson(uint32_t stationId, const char* dateTime, float temperature, float humidity, float dustDensity) {
    StaticJsonDocument<200> doc;

    doc["station_id"] = stationId;
    doc["date_time"] = dateTime;
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["dust_density"] = dustDensity;

    String output;
    serializeJson(doc, output);

    return output;
}