#include "madminactor.h"

#include "mainactortype.h"

MAdminActor::MAdminActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{

}

caf::behavior MAdminActor::make_behavior()
{
    return  {
        [this](const WebSocketConnectionPtr &wsConnPtr, std::string message, const WebSocketMessageType &type)-> caf::result<void>{
            blocking_run(wsConnPtr, std::move(message), type);
            return {};
        },
        [this](exit_atom)-> caf::result<void>{
            quit();
            return {};
        }
    };
}

void MAdminActor::blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    LOG_DEBUG << "Music Admin is Called!";
}

nlohmann::json MAdminActor::handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, nlohmann::json in)
{

}

nlohmann::json MAdminActor::handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{

}
