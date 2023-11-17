#include "GP2Y1010AU0F.h"
#include "JsonCreator.h"
#include "MyClockTimer.h"
#include "DataSender.h"
#include "SessionManager.h"

#include "definitions.h"
#include <DHT.h>
#include <WiFi.h>

GP2Y1010AU0F dustSensor(DUST_LED_PIN, DUST_MEASURE_PIN);
DHT dht(DHT_PIN, DHT_TYPE);
JsonCreator jsonCreator;
MyClockTimer myClockTimer;
DataSender dataSender;
SessionManager sessionManager;

float dustDensity = 0;
float temperature = 0;
float humidity = 0;

void setup() {
    Serial.begin(115200);

    dustSensor.begin();
    dht.begin();
    myClockTimer.begin();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {
    dustDensity = dustSensor.read();
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    Serial.print("Dust Density = ");
    Serial.print(dustDensity);
    Serial.println(" ug/m3");

    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity = ");
    Serial.print(humidity);
    Serial.println(" %\n");

    unsigned int currentSessionId = sessionManager.getSessionId();
    String currentDateTime = myClockTimer.getCurrentDateTime();
    String json = jsonCreator.createJson(STATION_ID, currentSessionId, currentDateTime, temperature, humidity, dustDensity);
    Serial.println(json);

    dataSender.sendData(json);

    delay(5000);
}