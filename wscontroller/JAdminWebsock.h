#pragma once
#include <drogon/WebSocketController.h>
#include "../actor/mainactor.h"
namespace websocket {
namespace jadmin {

class JAdminWebSocket : public drogon::WebSocketController<JAdminWebSocket> {
 public:
  void handleNewMessage(const drogon::WebSocketConnectionPtr &, std::string &&,
                        const drogon::WebSocketMessageType &) override;
  void handleNewConnection(const drogon::HttpRequestPtr &,
                           const drogon::WebSocketConnectionPtr &) override;
  void handleConnectionClosed(const drogon::WebSocketConnectionPtr &) override;
  WS_PATH_LIST_BEGIN
  WS_PATH_ADD("/jadmin");
  WS_PATH_LIST_END
};
}  // namespace jadmin
}  // namespace websocket
