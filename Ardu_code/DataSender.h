#ifndef DATASENDER_H
#define DATASENDER_H

#include <WiFi.h>

class DataSender {
public:
    DataSender();
    void sendData(String json);
private:
    WiFiClient client;
};

#endif