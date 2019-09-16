#include "wsfns.h"
namespace websocket {
WsFns::WsFns() = default;
void WsFns::sendJson(const drogon::WebSocketConnectionPtr &wsConnPtr,
                     nlohmann::json &j) {
  try {
    // LOG_DEBUG << "sending a message: {}", j.dump();
    wsConnPtr->send(j.dump());
  } catch (nlohmann::json::parse_error &e) {
    LOG_DEBUG << "message: {}", e.what();
    LOG_DEBUG << "exception id: {}", e.id;
    LOG_DEBUG << "byte position of error:", e.byte;
    nlohmann::json r =
        std::string("cant parse internal json reason: ") + e.what();
    wsConnPtr->send(r.dump());
  }
}

nlohmann::json WsFns::successJsonObject(nlohmann::json event, bool ok,
                                        const std::string &error) {
  nlohmann::json out;
  out[0] = std::move(event);

  nlohmann::json ret;
  ret["ok"] = ok;
  if (!ok) {
    ret["error"] = error;
  }
  out[1] = ret;
  return out;
}
}  // namespace websocket
