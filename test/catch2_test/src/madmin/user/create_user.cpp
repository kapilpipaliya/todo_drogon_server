#include "create_user.h"
#include "spdlogfix.h"

#include <catch2/catch.hpp>
#include  "json.hpp"
#include <fmt/format.h>
using namespace nlohmann;
using namespace fmt::v5;
using namespace  madmin;
CreateUser::CreateUser(std::string table): table(table)
{

}

void CreateUser::connectToServer()
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
                                            [["auth","login",0],{{"user":"new_u","pass":"12345600"}}],
                                            [["user","is_logged_in",0],[[]]],
                                            [
                                             ["user","ins",null],
                                             [{{"username":"username","fullname":"fullname","email":"email@email.com","password":"password","disabled":true,"state":"state","city":"city"}},[null]]
                                             ],
                                           [
                                             ["user","upd",2],
                                             [
                                                {{"type":"executive","parent_id":null,"p_username":0,"username":"user1","fullname":"fullname1","create_date":"2019-08-28 12:04:23.440921+05:30","disabled":true,"email":"email1@gmail.com","password":"pass1","state":"state1","city":"city1"}},
                                                [null, null, null, null, "=username"]
                                             ]
                                            ],
                                            [["user","del",1000],[[null, null, null, null, "=user1"]]]
                                            ]
                                            )";
                                   auto s = format(in, table, table);
                                   SPDLOG_TRACE(s);
                                   auto j = jsonparse(s);

                                   wsPtr->getConnection()->send(j.dump());
                               }
                               else
                               {
                                   quit(false, "ws connection failed");
                               }
                           });
}
void CreateUser::setMessageHandler()
{
    wsPtr->setMessageHandler([this](const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text)
        {
            auto j =jsonparse(message);
            SPDLOG_TRACE("create user result: {}", j.dump());
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

            // is_admin_auth == true
            REQUIRE(j[2][1] == true);

            // insert success:
            auto h = j[3][0];
            REQUIRE(h[0] == table);
            REQUIRE(h[1] == "ins");
            REQUIRE(h[2].is_null());

            REQUIRE(j[3][1]["ok"] == true);

            // update success:
            auto u = j[4][0];
            REQUIRE(u[0] == table);
            REQUIRE(u[1] == "upd");
            REQUIRE(u[2] == 2);

            REQUIRE(j[4][1]["ok"] == true);

            // delete
            auto d = j[5][0];
            REQUIRE(d[0] == table);
            REQUIRE(d[1] == "del");
            REQUIRE(d[2] == 1000);

            REQUIRE(j[5][1]["ok"] == true);


            return quit(true);
        } else {
            //quit(true);
        }
    });
}
