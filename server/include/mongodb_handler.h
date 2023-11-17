#ifndef SENSORS_RECEIVER_MONGODB_HANDLER_H_
#define SENSORS_RECEIVER_MONGODB_HANDLER_H_

#include <string>
#include <sstream>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

namespace Server{

class MongoDBHandler{
  public:
    // Defines an instance of the MongoDBHandler class
    MongoDBHandler();
    // Sends data to DB
    void SendData(const std::string& json_data);
  private:
    mongocxx::client client_;
    mongocxx::database db_;
};

}  // namesapce Server
 
#endif // SENSORS_RECEIVER_MONGODB_HANDLER_H_
