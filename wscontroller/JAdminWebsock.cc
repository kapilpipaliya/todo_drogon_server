#include "JAdminWebsock.h"

#include <unistd.h>
#include <chrono>

#include "../actor/caf.h"
#include "spdlogfix.h"

#include "../actor/mainactor.h"
#include "../actor/mainactortype.h"

#include "context/jadmincontext.h"
namespace websocket {
void EchoWebSocket::handleNewMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &&message,
    const drogon::WebSocketMessageType &type) {
  // std::chrono::seconds(10)
  superactor::globalCAF.communicateWithActors()
      ->request(superactor::globalCAF.mainActor(), caf::infinite,
                run_atom::value, MainActorType::JAdmin, wsConnPtr,
                std::move(message), type)
      .receive(
          [&]() {
            // if(!message.empty()) SPDLOG_TRACE("Output: {}", message.c_str());
          },
          [&](caf::error &err) {
            aout(superactor::globalCAF.communicateWithActors())
                << " -> "
                << superactor::globalCAF.communicateWithActors()
                       ->system()
                       .render(err)
                << err.code() << std::endl;
          });
}
void EchoWebSocket::handleNewConnection(
    const drogon::HttpRequestPtr &req,
    const drogon::WebSocketConnectionPtr &wsConnPtr) {
  std::shared_ptr<websocket::JAdminContext> context =
      std::make_shared<JAdminContext>(req, wsConnPtr);
  wsConnPtr->setContext(context);
}
void EchoWebSocket::handleConnectionClosed(
    const drogon::WebSocketConnectionPtr &wsConnPtr) {
  superactor::globalCAF.communicateWithActors()->request(
      superactor::globalCAF.mainActor(), caf::infinite, exit_atom::value,
      wsConnPtr);
  // LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
}  // namespace websocket
