#ifndef _TODOLISTACTOR_H
#define _TODOLISTACTOR_H

#include "caf/all.hpp"

#include "useractorbase.h"
namespace superactor {
namespace todoactor {
class TodoListActor : public caf::event_based_actor,
                      public system::UserActorBase {
 public:
  TodoListActor(caf::actor_config& cfg);
  virtual caf::behavior make_behavior();

 protected:
  virtual nlohmann::json handleTextMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      const nlohmann::json& in);
  virtual nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr, std::string& message);
};
}  // namespace todoactor
}  // namespace superactor
#endif
