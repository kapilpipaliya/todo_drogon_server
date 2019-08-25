#pragma once
#include <drogon/WebSocketController.h>
#include "../actor/mainactor.h"
class EchoWebSocket : public drogon::WebSocketController<EchoWebSocket> {
public:
    virtual void handleNewMessage(const WebSocketConnectionPtr &, std::string &&, const WebSocketMessageType &) override;
    virtual void handleNewConnection(const HttpRequestPtr &, const WebSocketConnectionPtr &) override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr &) override;
    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/jadmin");
    WS_PATH_LIST_END
};
