#pragma once

#include <drogon/WebSocketController.h>
#include <vector>
#include "mainactor.h"

#include "caf/all.hpp"

using namespace drogon;
using namespace drogon::orm;
extern DbClientPtr clientPtr;

class EchoWebSocket : public drogon::WebSocketController<EchoWebSocket> {
public:
    EchoWebSocket();
    void handleNewMessage(const WebSocketConnectionPtr &,
                                  std::string &&,
                                  const WebSocketMessageType &) override;

    virtual void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr &) override;

    void handleConnectionClosed(const WebSocketConnectionPtr &) override;

    WS_PATH_LIST_BEGIN
        //WS_PATH_ADD("/path","filter1","filter2",..);
        WS_PATH_ADD("/jadmin");
    WS_PATH_LIST_END

private:
    std::map<std::string, WebSocketConnectionPtr> _clientsMap; //UserID--->connection
    std::mutex _mapMtx;
};
