#include "EchoWebSocket.h"

// move this functionality to the class:
#include "core/service/auth/auth.h"
#include <unistd.h>
#include "caf.h"
#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include <chrono>
//using namespace drogon_model::postgres;
#include "mainactor.h"
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
   fprintf(stdout, "%s\n", message.c_str());
   fflush(stdout);
//std::chrono::seconds(10)
//    globalCAF.self.
//globalCAF.self->request(globalCAF.mainactor, caf::infinite, run_atom::value,  wsConnPtr, std::move(message), type).receive(
//            [&]() {
//       fprintf(stdout, "%s\n", message.c_str());
//       fflush(stdout);
//    return;
//            },
//            [&](error& err) {
//              aout(globalCAF.self) << " -> " << globalCAF.self->system().render(err) << err.code() << endl;
//            }
//          );
//   auto main = globalCAF.sys.spawn<MainActor>();
//   caf::scoped_actor self{globalCAF.sys};
//   auto mainactor = self->spawn<MainActor>();
//    self->request(mainactor, std::chrono::seconds(10), run_atom::value,  wsConnPtr, std::move(message), type);
//                   .then(
//               [&](double z) {
//               fprintf(stdout, "Done Message handling\n");
//               fflush(stdout);
//               },
//               [&](const caf::error& err) {
//                 fprintf(stdout, "Error Message handling %hhu\n", err.code());
//                 fflush(stdout);
//               });
   NoCAF nocaf{wsConnPtr, std::move(message), type};
   nocaf.blocking_run();
}
void EchoWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    clientPtr = drogon::app().getDbClient("sce");
    //sleep(1);
    // save the cookie in contex, because its not available on other handler
   // LOG_DEBUG << "new websocket connection!\n";
    //auto &key=req->getHeader("Sec-WebSocket-Key");
    //LOG_DEBUG << key;

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
    //LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
