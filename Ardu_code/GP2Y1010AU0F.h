#ifndef GP2Y1010AU0F_H
#define GP2Y1010AU0F_H

#include <Arduino.h>

class GP2Y1010AU0F {
private:
  uint8_t _dustLedPin;
  uint8_t _dustMeasurePin;
  int _samplingTime = 280;
  int _deltaTime = 40;
  int _sleepTime = 9680;
  float _VCC = 5.0;

public:
  GP2Y1010AU0F(uint8_t _dustLedPin, uint8_t _dustMeasurePin);
  bool begin();
  float read();
};

#endif