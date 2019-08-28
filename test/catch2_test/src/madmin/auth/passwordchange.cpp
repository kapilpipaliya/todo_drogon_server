#include "passwordchange.h"
#include "spdlog/spdlog.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;
using namespace  madmin;
void PasswordChange::connectToServer()
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
                                            [
                                            [["auth","login",0],{"user":"sadmin","pass":"123456"}],
                                            [["user","update_password",0],{"old_password":"123456","new_password":"999999"}],
                                            [["user","update_password",0],{"old_password":"999999","new_password":"123456"}]
                                            ]
                                            )"_json;
                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
                                   quit(false, "ws connection failed");
                               }
                           });
}
void PasswordChange::setMessageHandler()
{
    wsPtr->setMessageHandler([this](const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text)
        {
            auto j =jsonparse(message);
            spdlog::info("Password change result: {}", j.dump());
            // event
            auto e = j[0][0];
            REQUIRE(e[0] == "auth");
            REQUIRE(e[1] == "login");
            REQUIRE(e[2] == 0);

            REQUIRE(j[0][1]["ok"] == true);

            // cookie:
            auto c = j[1][0];
            REQUIRE(c[0] == "auth");
            REQUIRE(c[1] == "set_cookie");
            REQUIRE(c[2] == 0);

            REQUIRE(j[1][1].is_number() == true);

            REQUIRE(j[2][1]["ok"] == true);

            REQUIRE(j[3][1]["ok"] == true);
            return quit(true);
        } else {
            //quit(true);
        }
    });
}
