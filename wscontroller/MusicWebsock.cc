#include "MusicWebsock.h"

#include <unistd.h>
#include <chrono>

#include "../actor/caf.h"
#include "spdlogfix.h"

#include "../actor/mainactor.h"
#include "../actor/mainactortype.h"

#include "context/madmincontext.h"
namespace websocket {
namespace music {
void MusicWebsock::handleNewMessage(
    const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message,
    const drogon::WebSocketMessageType& type) {
  // std::chrono::seconds(10)
  superactor::system::globalCAF.communicateWithActors()
      ->request(superactor::system::globalCAF.mainActor(), caf::infinite,
                run_atom::value, superactor::MainActorType::MAdmin, wsConnPtr,
                std::move(message), type)
      .receive(
          [&]() {
            // SPDLOG_TRACE("Output: {}", message.c_str());
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
void MusicWebsock::handleNewConnection(
    const drogon::HttpRequestPtr& req,
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  std::shared_ptr<websocket::music::MAdminContext> context =
      std::make_shared<MAdminContext>(req, wsConnPtr);
  wsConnPtr->setContext(context);
}
void MusicWebsock::handleConnectionClosed(
    const drogon::WebSocketConnectionPtr& wsConnPtr) {
  superactor::system::globalCAF.communicateWithActors()->request(
      superactor::system::globalCAF.mainActor(), caf::infinite, exit_atom::value,
      wsConnPtr);
}
}  // namespace music
}  // namespace websocket
