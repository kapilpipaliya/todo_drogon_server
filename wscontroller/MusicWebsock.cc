#include "MusicWebsock.h"

#include <unistd.h>
#include <chrono>

#include "../actor/caf.h"
#include "spdlogfix.h"

#include "../actor/mainactor.h"
#include "../actor/mainactortype.h"

#include "context/madmincontext.h"

using namespace caf;

void MusicWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr,
                                    std::string&& message,
                                    const WebSocketMessageType& type) {
  // std::chrono::seconds(10)
  globalCAF.communicateWithActors()
      ->request(globalCAF.mainActor(), caf::infinite, run_atom::value,
                MainActorType::MAdmin, wsConnPtr, std::move(message), type)
      .receive(
          [&]() {
            // SPDLOG_TRACE("Output: {}", message.c_str());
          },
          [&](error& err) {
            aout(globalCAF.communicateWithActors())
                << " -> "
                << globalCAF.communicateWithActors()->system().render(err)
                << err.code() << std::endl;
          });
}
void MusicWebsock::handleNewConnection(
    const HttpRequestPtr& req, const WebSocketConnectionPtr& wsConnPtr) {
  std::shared_ptr<MAdminContext> context =
      std::make_shared<MAdminContext>(req, wsConnPtr);
  wsConnPtr->setContext(context);
}
void MusicWebsock::handleConnectionClosed(
    const WebSocketConnectionPtr& wsConnPtr) {
  globalCAF.communicateWithActors()->request(
      globalCAF.mainActor(), caf::infinite, exit_atom::value, wsConnPtr);
}
