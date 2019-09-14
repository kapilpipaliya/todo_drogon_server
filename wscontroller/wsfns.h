#ifndef WSFNS_H
#define WSFNS_H
#include <drogon/WebSocketController.h>
#include "json.hpp"
#include "spdlogfix.h"
namespace websocket {
class WsFns {
 public:
  WsFns();

  static void sendJson(const drogon::WebSocketConnectionPtr &wsConnPtr,
                       nlohmann::json &j);
  static nlohmann::json successJsonObject(nlohmann::json event, bool ok,
                                          const std::string &error);
};
}  // namespace websocket
#endif  // WSFNS_H
