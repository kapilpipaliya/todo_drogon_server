#include "JAdminWebsock.h"

#include <unistd.h>
#include <chrono>

#include "caf.h"
#include "spdlog/spdlog.h"

#include "mainactortype.h"
#include "context.h"
#include "mainactor.h"

using namespace std::literals;
using namespace  caf;

void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    // spdlog::info("Input: %s\n", message.c_str());
    // std::chrono::seconds(10)
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, run_atom::value,  MainActorType::JAdmin, wsConnPtr, std::move(message), type).receive(
            [&]() {
                //if(!message.empty()) spdlog::info("Output: {}\n", message.c_str());
                return;
            },
            [&](error& err) {
                 aout(globalCAF.self) << " -> " << globalCAF.self->system().render(err) << err.code() << std::endl;
            }
          );
}
void EchoWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    // LOG_DEBUG << "new websocket connection!\n";
    // auto &key=req->getHeader("Sec-WebSocket-Key");
    // LOG_DEBUG << key;
    // use cookie to set context
    // LOG_DEBUG << req->getCookie("admin");
    std::shared_ptr<Context> context =  std::make_shared<Context>(req);
    wsConnPtr->setContext(context);
    for (auto i : req->cookies()) {
        spdlog::info("{1}, {2}", i.first.c_str(), i.second.c_str());
    }
}
void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, exit_atom::value,  wsConnPtr);
    //LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
