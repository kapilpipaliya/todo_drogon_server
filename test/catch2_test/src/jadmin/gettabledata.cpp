#include "gettabledata.h"
#include "spdlog/spdlog.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
#include <fmt/format.h>
using namespace nlohmann;
using namespace fmt::v5;
GetTableData::GetTableData(std::string table): table(table)
{

}

void GetTableData::connectToServer()
{
    wsPtr->connectToServer(req,
                           [this](ReqResult r,
                            [[maybe_unused]] const HttpResponsePtr &resp,
                                       [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   //
                                   // a JSON value
                                   auto in = R"(
                                            [
                                            [["legacy","auth","admin_login",0],{{"email":"kapil.pipaliya@yahoo.com","pass":"3434"}}],
                                            [["legacy","auth","is_admin_auth",0],[[]]],
                                            [["legacy","{0}","header",1000],{{}}],
                                            [["legacy","{1}","data",1000],[[],[],[0]]]
                                            ]
                                            )";
                                   auto s = format(in, table, table);
                                   spdlog::info(s);
                                   auto j = jsonparse(s);

                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
                                   quit(false, "ws connection failed");
                               }
                           });
}
void GetTableData::setMessageHandler()
{
    wsPtr->setMessageHandler([this](const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text)
        {
            auto j =jsonparse(message);
            spdlog::info(j.dump());
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

            // is_admin_auth == true
            REQUIRE(j[2][1] == true);

            // header data:
            auto h = j[3][0];
            REQUIRE(h[0] == "legacy");
            REQUIRE(h[1] == table);
            REQUIRE(h[2] == "header");
            REQUIRE(h[3] == 1000);

            REQUIRE(j[3][1].size() == 6);

            // table data:
            auto t = j[4][0];
            REQUIRE(t[0] == "legacy");
            REQUIRE(t[1] == table);
            REQUIRE(t[2] == "data");
            REQUIRE(t[3] == 1000);

            REQUIRE(j[4][1].size() >= 0);


            return quit(true);
        } else {
            //quit(true);
        }
    });
}
