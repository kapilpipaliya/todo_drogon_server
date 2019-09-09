#pragma once
#include <drogon/WebSocketController.h>
using namespace drogon;
class JUserWebsock : public drogon::WebSocketController<JUserWebsock> {
 public:
  void handleNewMessage(const WebSocketConnectionPtr &, std::string &&,
                        const WebSocketMessageType &) override;
  void handleNewConnection(const HttpRequestPtr &,
                           const WebSocketConnectionPtr &) override;
  void handleConnectionClosed(const WebSocketConnectionPtr &) override;
  WS_PATH_LIST_BEGIN
  WS_PATH_ADD("/juser");
  WS_PATH_LIST_END
};
