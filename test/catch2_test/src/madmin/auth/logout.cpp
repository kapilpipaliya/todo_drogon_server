#include "logout.h"
#include "spdlog/spdlog.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;
using namespace  madmin;
void LogOut::connectToServer()
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
                                            [["auth","logout",0],{}],
                                            [["user","is_logged_in",0],{}]
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
void LogOut::setMessageHandler()
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

            // logout is done
            auto l = j[2][0];
            REQUIRE(l[0] == "auth");
            REQUIRE(l[1] == "logout");
            REQUIRE(l[2] == 0);
            REQUIRE(j[2][1]["ok"] == true);

            // logout is done
            auto is = j[3][0];
            REQUIRE(is[0] == "user");
            REQUIRE(is[1] == "is_logged_in");
            REQUIRE(is[2] == 0);
            REQUIRE(j[3][1] == false);

            return quit(true);
        } else {
            //quit(true);
        }
    });
}
