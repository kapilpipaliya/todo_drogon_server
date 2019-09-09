#pragma once
#include <drogon/WebSocketController.h>
#include "../actor/mainactor.h"
class EchoWebSocket : public drogon::WebSocketController<EchoWebSocket> {
 public:
  void handleNewMessage(const WebSocketConnectionPtr &, std::string &&,
                        const WebSocketMessageType &) override;
  void handleNewConnection(const HttpRequestPtr &,
                           const WebSocketConnectionPtr &) override;
  void handleConnectionClosed(const WebSocketConnectionPtr &) override;
  WS_PATH_LIST_BEGIN
  WS_PATH_ADD("/jadmin");
  WS_PATH_LIST_END
};
