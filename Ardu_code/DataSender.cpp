#include "DataSender.h"
#include "definitions.h"

DataSender::DataSender() {}

void DataSender::sendData(String json) {
    if (client.connect(SERVER_DNS, SERVER_PORT)) {
        client.println("POST / HTTP/1.1");
        client.println("Host: " + String(SERVER_DNS));
        client.println("Content-Type: application/json");
        client.println("Connection: close");
        client.println("Content-Length: " + String(json.length()));
        client.println();
        client.println(json);
    }
    client.stop();
}