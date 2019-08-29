#include "museractor.h"

#include "mainactortype.h"
#include "../wscontroller/wsfns.h"

MUserActor::MUserActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{

}

caf::behavior MUserActor::make_behavior()
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

void MUserActor::blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    LOG_DEBUG << "Music User is Called!";
}

nlohmann::json MUserActor::handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, nlohmann::json in)
{

}

nlohmann::json MUserActor::handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{

}
