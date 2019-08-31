#include "MusicWebsock.h"

#include <unistd.h>
#include <chrono>

#include "spdlogfix.h"
#include "../actor/caf.h"

#include "../actor/mainactortype.h"
#include "../actor/mainactor.h"

#include "context/madmincontext.h"

using namespace std::literals;
using namespace  caf;

void MusicWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
     SPDLOG_TRACE("Input: {}", message.c_str());
     //std::chrono::seconds(10)
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, run_atom::value,  MainActorType::MAdmin, wsConnPtr, std::move(message), type).receive(
        [&]() {
            //if(!message.empty()) SPDLOG_TRACE("Output: {}", message.c_str());
            return;
        },
        [&](error& err) {
            aout(globalCAF.self) << " -> " << globalCAF.self->system().render(err) << err.code() << std::endl;
        }
    );
}
void MusicWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
    // LOG_DEBUG << "new websocket connection!\n";
    // auto &key=req->getHeader("Sec-WebSocket-Key");
    // LOG_DEBUG << key;
    // use cookie to set context
    // LOG_DEBUG << req->getCookie("admin");
    std::shared_ptr<MAdminContext> context =  std::make_shared<MAdminContext>(req, wsConnPtr);
    wsConnPtr->setContext(context);
    for (auto i : req->cookies()) {
        SPDLOG_TRACE("{1}, {2}", i.first.c_str(), i.second.c_str());
        LOG_DEBUG << i.first << i.second;
    }
}
void MusicWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, exit_atom::value,  wsConnPtr);
    //LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
