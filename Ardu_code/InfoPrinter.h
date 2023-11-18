#ifndef INFOPRINTER_H
#define INFOPRINTER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class InfoPrinter {
public:
    InfoPrinter();
    void begin();
    void printDustDensity(float dustDensity);
private:
    Adafruit_SSD1306 display;
};

#endif