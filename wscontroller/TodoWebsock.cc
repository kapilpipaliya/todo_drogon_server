#include "TodoWebsock.h"

#include <unistd.h>

#include <chrono>

#include "../actor/caf.h"
#include "../actor/mainactor.h"
#include "../actor/mainactortype.h"
#include "context/todocontext.h"
namespace websocket {
namespace todo {
void TodoWebsock::handleNewMessage(
    const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message,
    const drogon::WebSocketMessageType& type) {
  // std::chrono::seconds(10)
  superactor::system::globalCAF.communicateWithActors()
      ->request(superactor::system::globalCAF.mainActor(), caf::infinite,
                superactor::system::run_atom::value,
                superactor::system::MainActorType::Todo, wsConnPtr,
                std::move(message), type)
      .receive(
          [&]() {
            // LOG_DEBUG << "Output: {}", message.c_str();
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
void TodoWebsock::handleNewConnection(
    const drogon::HttpRequestPtr& req,
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  std::shared_ptr<websocket::todo::TodoContext> context =
      std::make_shared<todo::TodoContext>(req, wsConnPtr);
  wsConnPtr->setContext(context);
}
void TodoWebsock::handleConnectionClosed(
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  superactor::system::globalCAF.communicateWithActors()->request(
      superactor::system::globalCAF.mainActor(), caf::infinite,
      superactor::system::exit_atom::value, wsConnPtr);
}
}  // namespace todo
}  // namespace websocket
