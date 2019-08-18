#include "authcheck.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
using namespace nlohmann;

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
                                   nlohmann::json j = {{{"legacy", "auth", "user_login", 0}, {}}};
                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
                                   std::cout << &r << std::endl;
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
               // std::cout << j.dump() << std::endl;
                REQUIRE(j[0][0][0] == "legacy");
                REQUIRE(j[0][0][1] == "auth");
                REQUIRE(j[0][0][2] == "user_login");
                REQUIRE(j[0][0][3] == 0);

                REQUIRE(j[0][1]["error"] == "Error");
                REQUIRE(j[0][1]["ok"] == false);


            }
            catch (json::parse_error& e)
            {
                // output exception information
                std::cout << "message: " << e.what() << '\n'
                          << "exception id: " << e.id << '\n'
                          << "byte position of error: " << e.byte << std::endl;
                return quit(false, "Return Value must be valid Json");
            }

            return quit(true);
        } else {
            std::cout << &type;
            //quit(true);
        }
    });
}
