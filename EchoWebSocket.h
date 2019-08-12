#pragma once

#include <drogon/WebSocketController.h>
#include <vector>
#include "messagehandle.h"

using namespace drogon;

class EchoWebSocket : public drogon::WebSocketController<EchoWebSocket> {
public:
    void handleNewMessage(const WebSocketConnectionPtr &,
                                  std::string &&,
                                  const WebSocketMessageType &) override;

    virtual void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr &) override;

    void handleConnectionClosed(const WebSocketConnectionPtr &) override;

    WS_PATH_LIST_BEGIN
        //list path definitions here;
        //WS_PATH_ADD("/path","filter1","filter2",...);
        WS_PATH_ADD("/echo");
    WS_PATH_LIST_END

private:
    std::map<std::string, WebSocketConnectionPtr> _clientsMap; //UserID--->connection
    std::mutex _mapMtx;
//    var clients = new List<IWebSocketConnection>;

};
// && - rvalue reference
