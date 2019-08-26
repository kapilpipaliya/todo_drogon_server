#include "login.h"
#include "spdlog/spdlog.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;
using namespace  madmin;
void LogIn::connectToServer()
{
    wsPtr->connectToServer(req,
                           [this](ReqResult r,
                            [[maybe_unused]] const HttpResponsePtr &resp,
                                       [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   //
                                   // a JSON value
                                   json j = R"(
                                            [[["legacy","auth","admin_login",0],{"email":"kapil.pipaliya@yahoo.com","pass":"3434"}]]
                                            )"_json;
                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
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
            //spdlog::info(j.dump());
            // event
            auto e = j[0][0];
            REQUIRE(e[0] == "legacy");
            REQUIRE(e[1] == "auth");
            REQUIRE(e[2] == "admin_login");
            REQUIRE(e[3] == 0);

            REQUIRE(j[0][1]["ok"] == true);

            // cookie:
            auto c = j[1][0];
            REQUIRE(c[0] == "legacy");
            REQUIRE(c[1] == "auth");
            REQUIRE(c[2] == "set_cookie");
            REQUIRE(c[3] == 0);

            REQUIRE(j[1][1]["admin"].is_number() == true);
            return quit(true);
        } else {
            //quit(true);
        }
    });
}
