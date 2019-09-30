#ifndef _TODOACTOR_H
#define _TODOACTOR_H

#include "caf/all.hpp"

#include "context/todocontext.h"

#include "useractorbase.h"
namespace superactor {
namespace todoactor {
class TodoActor : public caf::event_based_actor, public system::UserActorBase {
 public:
  TodoActor(caf::actor_config& cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  void run(const drogon::WebSocketConnectionPtr& wsConnPtr,
           std::string&& message, const drogon::WebSocketMessageType& type);
  nlohmann::json handleTextMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      const nlohmann::json& in) override;
  nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      std::string& message) override;

  template <typename T>
  nlohmann::json handleService(
      std::shared_ptr<websocket::todo::TodoContext> contx, nlohmann::json in) {
    try {
      T p{contx};
      auto r = p.handleEvent(in[0], 1, in[1]);
      if (!r.is_null()) return r;
      return nlohmann::json::array();
    } catch (const std::exception& e) {
      LOG_DEBUG << e.what();
      return nlohmann::json::array({{e.what()}});
    }
  }
};
}  // namespace todoactor
}  // namespace superactor
#endif
