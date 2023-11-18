#include "InfoPrinter.h"
#include "definitions.h"
InfoPrinter::InfoPrinter()
        : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
    Wire.begin(SCREEN_SDA, SCREEN_SCL);
}

void InfoPrinter::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.display();
}

void InfoPrinter::printDustDensity(float dustDensity) {
    display.clearDisplay();

    // Print "RxMAD" on the left with small font
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.println("RxMAD");

    // Print dust density on the right with large font
    display.setTextSize(3);
    display.setCursor(70, 0);
    display.println(dustDensity);

    display.display();
}