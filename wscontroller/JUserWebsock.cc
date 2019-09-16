#include "JUserWebsock.h"

#include <unistd.h>
#include <chrono>

#include "../actor/caf.h"
#include "spdlogfix.h"

#include "../actor/mainactor.h"
#include "../actor/mainactortype.h"

#include "context/jusercontext.h"
namespace websocket {
namespace juser {
void JUserWebsock::handleNewMessage(
    const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message,
    const drogon::WebSocketMessageType& type) {
  // std::chrono::seconds(10)
  superactor::system::globalCAF.communicateWithActors()
      ->request(superactor::system::globalCAF.mainActor(), caf::infinite,
                superactor::system::run_atom::value,
                superactor::system::MainActorType::JUser, wsConnPtr,
                std::move(message), type)
      .receive(
          [&]() {
            // if(!message.empty()) SPDLOG_TRACE("Output: {}", message.c_str());
          },
          [&](caf::error& err) {
            aout(superactor::system::globalCAF.communicateWithActors())
                << " -> "
                << superactor::system::globalCAF.communicateWithActors()
                       ->system()
                       .render(err)
                << err.code() << std::endl;
          });
}
void JUserWebsock::handleNewConnection(
    const drogon::HttpRequestPtr& req,
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  std::shared_ptr<JUserContext> context =
      std::make_shared<JUserContext>(req, wsConnPtr);
  wsConnPtr->setContext(context);
}
void JUserWebsock::handleConnectionClosed(
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  superactor::system::globalCAF.communicateWithActors()->request(
      superactor::system::globalCAF.mainActor(), caf::infinite,
      superactor::system::exit_atom::value, wsConnPtr);
}
}  // namespace juser
}  // namespace websocket
