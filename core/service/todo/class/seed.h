#pragma once
#include "../../../../wscontroller/context/todocontext.h"

#include "core/sql/query.h"

namespace todo {
namespace service {
class Seed {
 public:
  Seed(std::shared_ptr<websocket::todo::TodoContext>);
  void setupTable();
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  std::shared_ptr<websocket::todo::TodoContext> context;
  sql::Query query;
  void printsummery();
};
}  // namespace service
}  // namespace todo
