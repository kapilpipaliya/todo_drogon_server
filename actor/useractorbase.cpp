#include "useractorbase.h"
#include "./wscontroller/wsfns.h"
#include "spdlogfix.h"
namespace superactor {
namespace system {
UserActorBase::UserActorBase() = default;

UserActorBase::~UserActorBase() {}

void UserActorBase::blocking_run(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &&message,
    const drogon::WebSocketMessageType &type) {
  switch (type) {
    case drogon::WebSocketMessageType::Text: {
      try {
        auto valin = nlohmann::json::parse(message);
        if (valin.is_array()) {
          nlohmann::json out(nlohmann::json::array());
          for (const auto &i : valin) {
            auto result = handleTextMessage(wsConnPtr, i);
            for (auto &i : result) {
              if (!i.is_null()) {
                out.push_back(i);
              }
            }
          }
          if (!out.empty()) {
            websocket::WsFns::sendJson(wsConnPtr, out);
          } else {
            nlohmann::json j =
                "Message cant served: maybe not valid events in batch: " +
                message;
            websocket::WsFns::sendJson(wsConnPtr, j);
          }
        } else {
          nlohmann::json j = "Invalid Message only array handled: " + message;
          websocket::WsFns::sendJson(wsConnPtr, j);
        }
      } catch (nlohmann::json::parse_error &e) {
        SPDLOG_TRACE("message: {}", e.what());
        SPDLOG_TRACE("exception id: {}", e.id);
        SPDLOG_TRACE("byte position of error:", e.byte);
        nlohmann::json j = std::string("cant parse json reason: ") + e.what();
        websocket::WsFns::sendJson(wsConnPtr, j);
      }
      break;
    }
    case drogon::WebSocketMessageType::Binary: {
      auto result = handleBinaryMessage(wsConnPtr, message);
      if (!result.is_null()) {
        websocket::WsFns::sendJson(wsConnPtr, result);
      }
      break;
    }
    default:
      break;
  }
}
}  // namespace system
}  // namespace superactor
