#ifndef SENSORS_RECEIVER_SERVER_H_
#define SENSORS_RECEIVER_SERVER_H_

#include <netinet/in.h>

#include "mongodb_handler.h"

namespace Server {

class SensorsServer {
  public:
    // Creates an instance of Server class.
    SensorsServer(int port_number=33245, int buffer_size=1024);
    // Starts the server processes.
    void Start();
    // Sets the size of the buffer
    inline void SetBuffer(int buffer_size) { buffer_size_ = buffer_size; };
  private:
    // Defines the server socket descriptor
    void CreateDescriptor();
    // Defines server address.
    void CreateAddress();
    // Binds the server socket with the server address. 
    void Bind();
    // Starts the listen with define queue lenght.
    void Listen(int queue_length);
    // Returns the descriptor of new incoming connection.
    int AcceptConnection();
    // Handles the requests
    void HandleRequest(int client_descriptor);
    // Defines the running port of the server.
    int port_;
    // Defines the buffer size
    int buffer_size_;
    // Defines the server socket descriptor
    int server_descriptor_;
    // Defines the server address.
    struct sockaddr_in server_addr_; 
    // Defines database connection
    MongoDBHandler mongodb_;
};

} // namespace Server

#endif // SENSORS_RECEIVER_SERVER_H_