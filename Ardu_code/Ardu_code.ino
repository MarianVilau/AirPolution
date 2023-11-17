#include "GP2Y1010AU0F.h"
#include "definitions.h"

#include <DHT.h>

GP2Y1010AU0F dustSensor(DUST_LED_PIN, DUST_MEASURE_PIN);
DHT dht(DHT_PIN, DHT_TYPE);
float dustDensity = 0;
float temperature = 0;
float humidity = 0;

void setup() {
    Serial.begin(115200);

    dustSensor.begin();
    dustSensor.begin();
    dht.begin();
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

    delay(5000);
}