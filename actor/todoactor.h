#ifndef _TODOACTOR_H
#define _TODOACTOR_H

#include "caf/all.hpp"
#include "context/todocontext.h"
#include "json.hpp"
namespace superactor {
namespace todoactor {
class TodoActor : public caf::event_based_actor {
 public:
  TodoActor(caf::actor_config& cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  void run(const drogon::WebSocketConnectionPtr& wsConnPtr,
           std::string&& message, const drogon::WebSocketMessageType& type);
  nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message);

  template <typename T>
  void handleService(int event1, int event2,
                     const drogon::WebSocketConnectionPtr& wsConnPtr,
                     std::shared_ptr<websocket::todo::TodoContext> contx,
                     std::string&& message) {
    try {
      T p{event1, event2, wsConnPtr, contx, std::move(message)};
      p.run();
      // if (!r.is_null()) return r;
      // return nlohmann::json::array();
    } catch (const std::exception& e) {
      LOG_DEBUG << e.what();
      // return nlohmann::json::array({{e.what()}});
    }
  }
};
}  // namespace todoactor
}  // namespace superactor
#endif
