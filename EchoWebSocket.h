#pragma once

#include <drogon/WebSocketController.h>
#include <vector>

using namespace drogon;
extern std::map<std::string, std::function<Json::Value(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr,
                                                Json::Value in)> > fns;
extern std::map<std::string, std::function<Json::Value(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr,
                                                std::string &message)> > fns_bin;

static void defineFns();

class EchoWebSocket : public drogon::WebSocketController<EchoWebSocket> {
public:
    inline EchoWebSocket() {
        defineFns();
    }

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
    int i = 1;
    std::map<std::string, WebSocketConnectionPtr> _clientsMap; //UserID--->connection
    std::mutex _mapMtx;
//    var clients = new List<IWebSocketConnection>;

};
// && - rvalue reference
