#include "wsfns.h"

WsFns::WsFns() = default;

void WsFns::sendJson(const WebSocketConnectionPtr &wsConnPtr,
                     nlohmann::json &j) {
  try {
    // SPDLOG_TRACE("sending a message: {}", j.dump());
    wsConnPtr->send(j.dump());
  } catch (json::parse_error &e) {
    SPDLOG_TRACE("message: {}", e.what());
    SPDLOG_TRACE("exception id: {}", e.id);
    SPDLOG_TRACE("byte position of error:", e.byte);
    json r = std::string("cant parse internal json reason: ") + e.what();
    wsConnPtr->send(r.dump());
  }
}
