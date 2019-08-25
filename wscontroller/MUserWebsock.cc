#include "MUserWebsock.h"

#include <unistd.h>
#include <chrono>

#include "spdlog/spdlog.h"
#include "../actor/caf.h"

#include "../actor/mainactortype.h"
#include "../actor/mainactor.h"

#include "context/musercontext.h"

using namespace std::literals;
using namespace  caf;

void MUserWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // spdlog::info("Input: {}", message.c_str());
    // std::chrono::seconds(10)
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, run_atom::value,  MainActorType::MUser, wsConnPtr, std::move(message), type).receive(
        [&]() {
            //if(!message.empty()) spdlog::info("Output: {}", message.c_str());
            return;
        },
        [&](error& err) {
            aout(globalCAF.self) << " -> " << globalCAF.self->system().render(err) << err.code() << std::endl;
        }
    );
}
void MUserWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
    // LOG_DEBUG << "new websocket connection!\n";
    // auto &key=req->getHeader("Sec-WebSocket-Key");
    // LOG_DEBUG << key;
    // use cookie to set context
    // LOG_DEBUG << req->getCookie("admin");
    std::shared_ptr<MUserContext> context =  std::make_shared<MUserContext>(req, wsConnPtr);
    wsConnPtr->setContext(context);
    for (auto i : req->cookies()) {
        spdlog::info("{1}, {2}", i.first.c_str(), i.second.c_str());
    }
}
void MUserWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    globalCAF.self->request(globalCAF.mainactor, caf::infinite, exit_atom::value,  wsConnPtr);
    //LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
