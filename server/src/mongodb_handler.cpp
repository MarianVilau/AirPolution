#include "mongodb_handler.h"

#include <cstring>
#include <stdexcept>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

namespace Server {

MongoDBHandler::MongoDBHandler(const std::string& database_host, 
                               const uint32_t port,
                               const std::string& database_name) {
  mongocxx::instance instance{};
  // Defines new database connection
  mongocxx::uri uri("mongodb://" + database_host + ":" + std::to_string(port));
  client_ = mongocxx::client(uri);
  db_ = client_[database_name];
  // Checks the database connection
  db_.run_command(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1)));
}

void MongoDBHandler::SendData(const std::string& json_data) {
  try {
    bsoncxx::document::view view = ParseJson(json_data);
    int sensor_id = view["SID"].get_int32();
    std::string collection_name = "connection_" + std::to_string(sensor_id);
    mongocxx::collection collection = GetCollection(collection_name);
    collection.insert_one(view);
  } catch (const std::exception& e) {
    std::cerr << "MongoDB: " << e.what() << std::endl;
  }
}

bool MongoDBHandler::CollectionExist(mongocxx::collection& collection) {
  auto cursor = collection.list_indexes();
  return cursor.begin() != cursor.end();
}

bsoncxx::document::view MongoDBHandler::ParseJson(const std::string& json_data) {
  bsoncxx::document::value doc = bsoncxx::from_json(json_data);
  return doc.view();
}

mongocxx::collection MongoDBHandler::GetCollection(const std::string& collection_name) {
  mongocxx::collection collection = db_[collection_name];
  if (!CollectionExist(collection)) {
    db_.create_collection(collection_name);
  }
  return collection;
}

}  // namespace Server