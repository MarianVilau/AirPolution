#include "GP2Y1010AU0F.h"

GP2Y1010AU0F::GP2Y1010AU0F(uint8_t _dustLedPin, uint8_t _dustMeasurePin) {
  this->_dustLedPin = _dustLedPin;
  this->_dustMeasurePin = _dustMeasurePin;
}

bool GP2Y1010AU0F::begin() {
  pinMode(this->_dustLedPin, OUTPUT);
  digitalWrite(this->_dustLedPin, HIGH);  // power off the LED
  return true;
}

float GP2Y1010AU0F::read() {
  float voMeasured = 0;
  float calcVoltage = 0;
  float dustDensity = 0;

  digitalWrite(this->_dustLedPin, LOW);  // power on the LED
  delayMicroseconds(this->_samplingTime);
  voMeasured = analogRead(this->_dustMeasurePin);  // read the dust value
  delayMicroseconds(this->_deltaTime);
  digitalWrite(this->_dustLedPin, HIGH);  // turn the LED off
  delayMicroseconds(this->_sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (this->_VCC / 1024.0);
  Serial.print("Calculate voltage: ");
  Serial.println(calcVoltage);
  dustDensity = (0.17 * calcVoltage - 0.1) * 2;
  return dustDensity;
}