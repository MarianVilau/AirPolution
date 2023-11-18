#ifndef MYCLOCKTIMER_H
#define MYCLOCKTIMER_H

#include <RtcDS1302.h>
#include "definitions.h"

class MyClockTimer {
public:
    MyClockTimer();
    void begin();
    String getCurrentDateTime();
private:
    ThreeWire myWire;
    RtcDS1302<ThreeWire> realTimeClock;
    void printDateTime(const RtcDateTime& dt);
};

#endif