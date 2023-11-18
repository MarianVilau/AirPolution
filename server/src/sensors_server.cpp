#include "sensors_server.h"

#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#include "thread_poll.h"

namespace Server{

SensorsServer::SensorsServer(int port_number)
    : port_(port_number), mongodb_({"mongodb_server", 27017}) {
  try {
    CreateDescriptor();
  } catch (const std::exception& e) {
    std::cout << "SensorsServer: "  << e.what();
  }
}

void SensorsServer::Start() {
  try{
    CreateAddress();
    Bind();
    Listen(1);
    // Defines thread poll
    ThreadPoll thread_poll(2);
    // Starts server loop
    while(true) {
      int client_descriptor = AcceptConnection();
      thread_poll.AddTask([client_descriptor, this] {
        HandleRequest(client_descriptor);
      });
    }
  } catch (const std::exception& e){
    std::cout << "SensorsServer: " << e.what();
    close(server_descriptor_);
  }
}

void SensorsServer::CreateDescriptor() {
  server_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
  if (server_descriptor_ == -1) {
    throw std::invalid_argument("Failed to create the server descriptor.");
  }
}

void SensorsServer::CreateAddress() {
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_addr.s_addr = INADDR_ANY;
  server_addr_.sin_port = htons(port_);
}

void SensorsServer::Bind() {
  int flag = bind(server_descriptor_, (struct sockaddr *)&server_addr_, sizeof(server_addr_));
  if (flag == -1) {
    throw std::invalid_argument("Failed to bind the server descriptor to server address.");
  } 
}

void SensorsServer::Listen(int queue_length) {
  int flag = listen(server_descriptor_, queue_length);
  if (flag == -1) {
    throw std::invalid_argument("Failed to start the listen process.");
  }
}

int SensorsServer::AcceptConnection() {
  ssize_t addr_len = sizeof(server_addr_); 
  int client_descriptor = accept(server_descriptor_, (struct sockaddr *)&server_addr_, (socklen_t*)&addr_len);
  if (client_descriptor == -1) {
    throw std::invalid_argument("Failed to establish a connection with the client.");
  }
  return client_descriptor;
}

void SensorsServer::HandleRequest(int client_descriptor) {
  try {
  while(true) {
    char buffer[buffer_size_] = {0};
    ssize_t request_size = read(client_descriptor, buffer, buffer_size_);
    // Checks if client is connected
    if (request_size <= 0) {
      std::cout << "Connection with client closed by the client.";
      break;
    }
    std::cout << buffer << std::endl;
    std::string received_data(buffer, request_size);
    mongodb_.SendData(received_data);
  }
  } catch (const std::exception& e) {
    std::cerr << "SensorsServer: " << e.what() << std::endl;
  }
}

}