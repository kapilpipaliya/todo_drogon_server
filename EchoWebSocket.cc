#include "EchoWebSocket.h"

#include <unistd.h>
#include "caf.h"
#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include <chrono>
//using namespace drogon_model::postgres;
#include "mainactor.h"
#include "context.h"
using namespace std::literals;
DbClientPtr clientPtr = nullptr;
//using run_atom = caf::atom_constant<caf::atom("run")>;
using namespace  caf;
using std::endl;
EchoWebSocket::EchoWebSocket()
{

}
void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
//   fprintf(stdout, "Input: %s\n", message.c_str());
//   fflush(stdout);
//std::chrono::seconds(10)
//    globalCAF.self.
globalCAF.self->request(globalCAF.mainactor, caf::infinite, run_atom::value,  wsConnPtr, std::move(message), type).receive(
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
   clientPtr = drogon::app().getDbClient("sce");
    // save the cookie in contex, because its not available on other handler
   // LOG_DEBUG << "new websocket connection!\n";
    //auto &key=req->getHeader("Sec-WebSocket-Key");
    //LOG_DEBUG << key;
    std::shared_ptr<Context> context =  std::make_shared<Context>(req);
    wsConnPtr->setContext(context);
    // LOG_DEBUG << req->getCookie("admin");
    for (auto i : req->cookies()) {
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);
    }
    // create connection to the database and keep it open. Will Increase Performance.
}
void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    //LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
