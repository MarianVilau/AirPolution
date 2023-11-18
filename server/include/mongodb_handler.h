#ifndef SENSORS_RECEIVER_MONGODB_HANDLER_H_
#define SENSORS_RECEIVER_MONGODB_HANDLER_H_

#include <cstdint>
#include <string>
#include <sstream>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

namespace Server {

class MongoDBHandler{
  public:
    // Defines an instance of the MongoDBHandler class
    MongoDBHandler(const std::string& database_host, 
                  const uint32_t port,
                  const std::string& database_name = "air_polution");
    // Sends data to database
    void SendData(const std::string& json_data);
  private:
    // Checks if a collection exists
    bool CollectionExist(mongocxx::collection& collection);
    // Parses the JSON data
    bsoncxx::document::view ParseJson(const std::string& json_data);
    // Gets the collection
    mongocxx::collection GetCollection(const std::string& collection_name);
    // Defines the MongoDB client
    mongocxx::client client_;
    // Defines the database
    mongocxx::database db_;
};

}  // namespace Server
 
#endif // SENSORS_RECEIVER_MONGODB_HANDLER_H_
