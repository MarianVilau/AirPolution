#include "MyWifiConnection.h"

MyWifiConnection::MyWifiConnection(const char* ssid, const char* password) {
    this->ssid = ssid;
    this->password = password;
}

void MyWifiConnection::connect() {
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}