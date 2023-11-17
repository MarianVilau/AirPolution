#include "GP2Y1010AU0F.h"
#include "MyWifiConnection.h"
#include "JsonCreator.h"
#include "definitions.h"
#include <DHT.h>
#include <WiFiNINA.h>

GP2Y1010AU0F dustSensor(DUST_LED_PIN, DUST_MEASURE_PIN);
DHT dht(DHT_PIN, DHT_TYPE);
JsonCreator jsonCreator;

float dustDensity = 0;
float temperature = 0;
float humidity = 0;

void setup() {
    Serial.begin(115200);

    dustSensor.begin();
    dustSensor.begin();
    dht.begin();

    MyWifiConnection wifiConnect(WIFI_SSID, WIFI_PASS);
    wifiConnect.connect();
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

    String json = jsonCreator.createJson(STATION_ID, "1969-12-31T23:59:59", temperature, humidity, dustDensity);
    Serial.println(json);

    delay(5000);
}