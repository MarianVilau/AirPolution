#include "MyClockTimer.h"

MyClockTimer::MyClockTimer() : myWire(RTC_DATA_PIN, RTC_CLOCK_PIN, RTC_RESET_PIN), realTimeClock(myWire) {}

void MyClockTimer::begin() {
    realTimeClock.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!realTimeClock.IsDateTimeValid()) {
        Serial.println("RTC lost confidence in the DateTime!");
        realTimeClock.SetDateTime(compiled);
    }

    if (realTimeClock.GetIsWriteProtected()) {
        Serial.println("RTC was write protected, enabling writing now");
        realTimeClock.SetIsWriteProtected(false);
    }

    if (!realTimeClock.GetIsRunning()) {
        Serial.println("RTC was not actively running, starting now");
        realTimeClock.SetIsRunning(true);
    }

    RtcDateTime now = realTimeClock.GetDateTime();
    if (now < compiled) {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        realTimeClock.SetDateTime(compiled);
    }
    else if (now > compiled)
        Serial.println("RTC is newer than compile time. (this is expected)");
    else
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
}

String MyClockTimer::getCurrentDateTime() {
    RtcDateTime now = realTimeClock.GetDateTime();
    printDateTime(now);
    if (!now.IsValid()) {
        Serial.println("RTC lost confidence in the DateTime!");
    }
    char dateString[20];
    snprintf_P(dateString,
               sizeof(dateString),
               PSTR("%04u-%02u-%02uT%02u:%02u:%02u"),
               now.Year(),
               now.Month(),
               now.Day(),
               now.Hour(),
               now.Minute(),
               now.Second() );
    return String(dateString);
}

void MyClockTimer::printDateTime(const RtcDateTime& dt) {
    char dateString[20];
    snprintf_P(dateString,
               sizeof(dateString),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               dt.Month(), dt.Day(), dt.Year(),
               dt.Hour(), dt.Minute(), dt.Second() );
    Serial.println(dateString);
}