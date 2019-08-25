#include "JAdminWebSock.h"

#include <unistd.h>
#include <chrono>

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "caf.h"

#include "mainactortype.h"
#include "context.h"
#include "mainactor.h"

using namespace std::literals;
using namespace  caf;
using std::endl;

EchoWebSocket::EchoWebSocket()
{

}
void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    // fprintf(stdout, "Input: %s\n", message.c_str());
    // fflush(stdout);
    // std::chrono::seconds(10)
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, run_atom::value,  MainActorType::JAdmin, wsConnPtr, std::move(message), type).receive(
            [&]() {
                fprintf(stdout, "Output: %s\n", message.c_str());
                fflush(stdout);
                return;
            },
            [&](error& err) {
                 aout(globalCAF.self) << " -> " << globalCAF.self->system().render(err) << err.code() << endl;
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
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);
    }
}
void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, exit_atom::value,  wsConnPtr);
    //LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
