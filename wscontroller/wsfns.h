#ifndef WSFNS_H
#define WSFNS_H
#include <drogon/WebSocketController.h>
#include "json.hpp"
#include "spdlogfix.h"

class WsFns {
 public:
  WsFns();

  static void sendJson(const drogon::WebSocketConnectionPtr &wsConnPtr,
                       nlohmann::json &j);
};

#endif  // WSFNS_H
