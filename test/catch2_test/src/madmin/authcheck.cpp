#include "authcheck.h"
#include "spdlog/spdlog.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;
using namespace  madmin;
void AuthCheck::connectToServer()
{
    wsPtr->connectToServer(req,
                           [this](ReqResult r,
                            [[maybe_unused]] const HttpResponsePtr &resp,
                                       [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   //nlohmann::json j = {{"legacy", "auth", "user_login", 0}}; // srever crash!!
                                   //nlohmann::json j = {{{"legacy", "auth", "user_login", 0}, 1223}}; // 1223  causer execaption on server
                                   //nlohmann::json j = {{{"legacy", "auth", "user_login", 0}, {}}}; // works
                                    json j = R"( [[["user","is_logged_in",0],[[]]]] )"_json;
                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
                                   quit(false, "ws connection failed");
                               }
                           });
}
void AuthCheck::setMessageHandler()
{
    wsPtr->setMessageHandler([this](const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text)
        {
            try
            {
                // parsing input with a syntax error
                auto j = json::parse(message);
                //spdlog::info("reply {}", j.dump());
                REQUIRE(j[0][0][0] == "user");
                REQUIRE(j[0][0][1] == "is_logged_in");
                REQUIRE(j[0][0][2] == 0);

                REQUIRE(j[0][1] == false);
                //REQUIRE(j[0][1]["error"] == "Error");
                //REQUIRE(j[0][1]["ok"] == false);


            }
            catch (json::parse_error& e)
            {
                // output exception information
                spdlog::error("message: {}", e.what());
                spdlog::error("exception id: {}", e.id);
                spdlog::error("byte position of error:", e.byte);
                return quit(false, "Return Value must be valid Json");
            }

            return quit(true);
        } else {
            //quit(true);
        }
    });
}
