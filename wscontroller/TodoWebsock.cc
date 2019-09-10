#include "TodoWebsock.h"

#include <unistd.h>
#include <chrono>

#include "../actor/caf.h"
#include "spdlogfix.h"

#include "../actor/mainactor.h"
#include "../actor/mainactortype.h"

#include "context/todocontext.h"

void TodoWebsock::handleNewMessage(
    const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message,
    const drogon::WebSocketMessageType& type) {
  // std::chrono::seconds(10)
  globalCAF.communicateWithActors()
      ->request(globalCAF.mainActor(), caf::infinite, run_atom::value,
                MainActorType::TODO, wsConnPtr, std::move(message), type)
      .receive(
          [&]() {
            // SPDLOG_TRACE("Output: {}", message.c_str());
          },
          [&](caf::error& err) {
            aout(globalCAF.communicateWithActors())
                << " -> "
                << globalCAF.communicateWithActors()->system().render(err)
                << err.code() << std::endl;
          });
}
void TodoWebsock::handleNewConnection(
    const drogon::HttpRequestPtr& req,
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  std::shared_ptr<todo::TodoContext> context =
      std::make_shared<todo::TodoContext>(req, wsConnPtr);
  wsConnPtr->setContext(context);
}
void TodoWebsock::handleConnectionClosed(
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  globalCAF.communicateWithActors()->request(
      globalCAF.mainActor(), caf::infinite, exit_atom::value, wsConnPtr);
}
