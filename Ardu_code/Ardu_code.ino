#include "GP2Y1010AU0F.h"
#include "definitions.h"

GP2Y1010AU0F dustSensor(DUST_LED_PIN, DUST_MEASURE_PIN);
float dustDensity = 0;

void setup() {
  Serial.begin(115200);
  
  dustSensor.begin();
}

void loop() {
  dustDensity = dustSensor.read();
  
  Serial.print("Dust Density = ");
  Serial.print(dustDensity);
  Serial.println(" ug/m3");

  delay(5000);
}