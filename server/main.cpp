#include <iostream>

#include "sensors_server.h"

int main() {
  Server::SensorsServer server;
  server.Start();
  return 0;
}