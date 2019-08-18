#include "login.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;

void LogIn::connectToServer()
{
    wsPtr->connectToServer(req,
                           [this](ReqResult r,
                            [[maybe_unused]] const HttpResponsePtr &resp,
                                       [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   nlohmann::json j = {{{"legacy", "auth", "admin_login", 0}, {}}};
                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
                                   std::cout << &r << std::endl;
                                   quit(false, "ws connection failed");
                               }
                           });
}
void LogIn::setMessageHandler()
{
    wsPtr->setMessageHandler([this](const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text)
        {
            auto j =jsonparse(message);
            std::cout << j.dump() << std::endl;
            return quit(true);
        } else {
            std::cout << &type;
            //quit(true);
        }
    });
}
