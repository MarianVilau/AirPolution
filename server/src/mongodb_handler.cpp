#include "mongodb_handler.h"

#include <stdexcept>
#include <memory>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

namespace Server {

MongoDBHandler::MongoDBHandler(){
  mongocxx::instance instance{};
  mongocxx::uri uri("mongodb://mongodb_server:27017");
  client_ = mongocxx::client(uri);
  db_ = client_["air_polution"];
  db_.run_command(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1)));
}

void MongoDBHandler::SendData(const std::string& json_data) {
  try {
    bsoncxx::document::value doc = bsoncxx::from_json(json_data);
    bsoncxx::document::view view = doc.view();
    mongocxx::collection collection = db_["connection_1001"];
    collection.insert_one(view);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

}  // namespace Server