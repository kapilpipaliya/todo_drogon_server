
#include "todolistactor.h"

#include "todolistservices.h"
namespace superactor {
TodoListActor::TodoListActor(caf::actor_config &cfg)
    : caf::event_based_actor(cfg) {}

caf::behavior TodoListActor::make_behavior() {
  return {
      [this](const drogon::WebSocketConnectionPtr &wsConnPtr,
             std::string message,
             const drogon::WebSocketMessageType &type) -> caf::result<void> {
        blocking_run(wsConnPtr, std::move(message), type);
        return {};
      },
      [this](exit_atom) -> caf::result<void> {
        quit();
        return {};
      }};
}

nlohmann::json TodoListActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, const nlohmann::json &in) {
  return nlohmann::json::array();
}

nlohmann::json TodoListActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  return nlohmann::json::array();
}

}  // namespace superactor
