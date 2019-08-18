#include "formatcheck.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;

void FormatCheck::connectToServer()
{
    wsPtr->connectToServer(req,
                   [this](ReqResult r,
                    [[maybe_unused]] const HttpResponsePtr &resp,
                               [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                       if (r == ReqResult::Ok)
                       {
                           std::string str = "hello";
                           nlohmann::json j = str;
                           wsPtr->getConnection()->send(j.dump());
                       }
                       else
                       {
                           quit(false, "ws connection failed");
                       }
                   });
}

void FormatCheck::setMessageHandler()
{
    wsPtr->setMessageHandler([this](const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text)
        {
                // parsing input with a syntax error
                auto j =jsonparse(message);
                //std::cout << j.dump() << std::endl;
                REQUIRE(j== "Invalid Message only array handled: \"hello\"");
                return quit(true);
        } else {
            std::cout << &type;
            //quit(true);
        }
    });
}
