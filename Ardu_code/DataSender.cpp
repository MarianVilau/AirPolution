#include "DataSender.h"
#include "definitions.h"

DataSender::DataSender() {}

void DataSender::sendData(String json) {
    if (client.connect(SERVER_DNS, SERVER_PORT)) {
        client.println(json);
    }
    client.stop();
}