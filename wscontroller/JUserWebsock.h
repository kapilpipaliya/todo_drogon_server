#pragma once
#include <drogon/WebSocketController.h>
namespace websocket {
class JUserWebsock : public drogon::WebSocketController<JUserWebsock> {
 public:
  void handleNewMessage(const drogon::WebSocketConnectionPtr &, std::string &&,
                        const drogon::WebSocketMessageType &) override;
  void handleNewConnection(const drogon::HttpRequestPtr &,
                           const drogon::WebSocketConnectionPtr &) override;
  void handleConnectionClosed(const drogon::WebSocketConnectionPtr &) override;
  WS_PATH_LIST_BEGIN
  WS_PATH_ADD("/juser");
  WS_PATH_LIST_END
};
}  // namespace websocket
