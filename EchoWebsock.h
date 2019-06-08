#pragma once
#include <drogon/WebSocketController.h>
using namespace drogon;
extern std::map<std::string, std::function<Json::Value(Json::Value in)> > fns;
class EchoWebsock:public drogon::WebSocketController<EchoWebsock>
{
public:
    inline EchoWebsock()
    {
        defineFns();
    }
    void defineFns();
    virtual void handleNewMessage(const WebSocketConnectionPtr&,
                                  std::string &&,
                                  const WebSocketMessageType &) override;
    virtual void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr&)override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr&)override;
    WS_PATH_LIST_BEGIN
    //list path definitions here;
    //WS_PATH_ADD("/path","filter1","filter2",...);
    WS_PATH_ADD("/echo");
    WS_PATH_LIST_END



    int var= 2;
};
