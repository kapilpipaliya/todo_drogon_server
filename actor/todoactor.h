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
  void handleTextMessage(const drogon::WebSocketConnectionPtr& wsConnPtr,
                         const nlohmann::json& in);
  nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr, std::string& message);

  template <typename T>
  void handleService(const drogon::WebSocketConnectionPtr& wsConnPtr,
                     std::shared_ptr<websocket::todo::TodoContext> contx,
                     nlohmann::json in) {
    try {
      T p{wsConnPtr, contx, in};
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
