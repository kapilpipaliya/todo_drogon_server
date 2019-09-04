#include "useractorbase.h"
#include "spdlogfix.h"
#include "./wscontroller/wsfns.h"

UserActorBase::UserActorBase()
{

}

void UserActorBase::blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    switch (type) {
    case WebSocketMessageType::Text: {
        try
        {
            auto valin = json::parse(message);
            if (valin.is_array()){
                json out(json::array());
                for (auto i : valin) {
                    // printJson(valin);
                    auto result  = handleTextMessage(wsConnPtr, i);
                    for (auto &i : result) {
                        if(!i.is_null()){
                            out.push_back(i);
                        }
                    }
                }
                if(!out.empty()){
                    WsFns::sendJson(wsConnPtr, out);
                } else {
                    nlohmann::json j =  "Message cant served: maybe not valid events in batch: " + message;
                    WsFns::sendJson(wsConnPtr, j);
                }
            } else {
                nlohmann::json j =  "Invalid Message only array handled: " + message;
                WsFns::sendJson(wsConnPtr, j);
            }
        }
        catch (json::parse_error& e)
        {
            SPDLOG_TRACE("message: {}", e.what());
            SPDLOG_TRACE("exception id: {}", e.id);
            SPDLOG_TRACE("byte position of error:", e.byte);
            nlohmann::json j =  std::string("cant parse json reason: ") + e.what() ;
            WsFns::sendJson(wsConnPtr, j);
        }
        break;
    }
    case WebSocketMessageType::Binary: {
        auto result  = handleBinaryMessage(wsConnPtr, message);
        if(!result.is_null()){
            WsFns::sendJson(wsConnPtr, result);
        }
        break;
    }
    default:
        break;
    }
}
