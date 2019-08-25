#pragma once
#include <drogon/WebSocketController.h>
using namespace drogon;
class JUserWebsock:public drogon::WebSocketController<JUserWebsock>
{
public:
    virtual void handleNewMessage(const WebSocketConnectionPtr&, std::string &&, const WebSocketMessageType &) override;
    virtual void handleNewConnection(const HttpRequestPtr &, const WebSocketConnectionPtr&)override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr&)override;
    WS_PATH_LIST_BEGIN
    //WS_PATH_ADD("/path","filter1","filter2",...);
    WS_PATH_ADD("/juser");
    WS_PATH_LIST_END
};
