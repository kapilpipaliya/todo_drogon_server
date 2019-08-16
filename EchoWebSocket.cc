#include "EchoWebSocket.h"

// move this functionality to the class:
#include "core/service/auth/auth.h"

using namespace std::literals;
EchoWebSocket::EchoWebSocket(): sys(cfg)
{
}
void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    // fprintf(stdout, "%s\n", message.c_str());
    // fflush(stdout);
    caf::scoped_actor self{sys};
   auto msgHandle = self->spawn<MessageHandle>(wsConnPtr, std::move(message), type);
}
void EchoWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    // save the cookie in contex, because its not available on other handler
    LOG_DEBUG << "new websocket connection!\n";
    auto &key=req->getHeader("Sec-WebSocket-Key");
    LOG_DEBUG << key;

    std::shared_ptr<std::map<std::string, std::vector<int> >> k(new std::map<std::string, std::vector<int> >);
    k->insert(std::pair<std::string, std::vector<int> >("admin"s, {0}));
    k->insert(std::pair<std::string, std::vector<int> >("user"s, {0}));
    wsConnPtr->setContext(k);
    auto adminContext = generateContext(req, wsConnPtr, "admin");
    setAdminContext(wsConnPtr, adminContext);
    auto userContext = generateContext(req, wsConnPtr, "user");
    setUserContext(wsConnPtr, userContext);
    // LOG_DEBUG << req->getCookie("admin");
    for (auto i : req->cookies()) {
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);
    }
    // create connection to the database and keep it open. Will Increase Performance.
}
void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
