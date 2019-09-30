#ifndef DGRAPHSEED_H
#define DGRAPHSEED_H
#include "../../../../wscontroller/context/todocontext.h"

#include "core/sql/query.h"

namespace todo {
namespace service {
class DGraphSeed {
 public:
  DGraphSeed();
  void setupTable();
  void handleEvent(const drogon::WebSocketConnectionPtr &wsConnPtr,
                   nlohmann::json event, unsigned long next,
                   nlohmann::json args);

 private:
  // std::shared_ptr<websocket::todo::TodoContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace todo
#endif  // DGRAPHSEED_H
