#ifndef MYWIFICONNECTION_H
#define MYWIFICONNECTION_H

#include <Arduino.h>
#include <WiFiNINA.h>

class MyWifiConnection {
private:
    const char* ssid;
    const char* password;

public:
    MyWifiConnection(const char* ssid, const char* password);
    void connect();
};

#endif