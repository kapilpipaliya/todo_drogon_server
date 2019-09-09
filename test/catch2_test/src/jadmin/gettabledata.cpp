#include "gettabledata.h"
#include "spdlogfix.h"

#include <fmt/format.h>
#include <catch2/catch.hpp>
#include "json.hpp"
using namespace nlohmann;
using namespace fmt::v5;
GetTableData::GetTableData(std::string table) : table(table) {}

void GetTableData::connectToServer() {
  getWsPtr()->connectToServer(
      getReqPtr(),
      [this](ReqResult r, [[maybe_unused]] const HttpResponsePtr &resp,
             [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
        if (r == ReqResult::Ok) {
          //
          // a JSON value
          auto in = R"(
                                            [
                                            [["auth","admin_login",0],{{"user":"kapil.pipaliya@yahoo.com","pass":"3434"}}],
                                            [["user","is_logged_in",0],[[]]],
                                            [["{0}","header",1000],{{}}],
                                            [["{1}","data",1000],[[],[],[0]]]
                                            ]
                                            )";
          auto s = format(in, table, table);
          SPDLOG_TRACE(s);
          auto j = jsonparse(s);

          wsPtr->getConnection()->send(j.dump());
        } else {
          quit(false, "ws connection failed");
        }
      });
}
void GetTableData::setMessageHandler() {
  getWsPtr()->setMessageHandler(
      [this](const std::string &message,
             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
             const WebSocketMessageType &type) {
        if (type == WebSocketMessageType::Text) {
          auto j = jsonparse(message);
          SPDLOG_TRACE(j.dump());
          // event
          auto e = j[0][0];
          REQUIRE(e[0] == "auth");
          REQUIRE(e[1] == "admin_login");
          REQUIRE(e[2] == 0);

          REQUIRE(j[0][1]["ok"] == true);

          // cookie:
          auto c = j[1][0];
          REQUIRE(c[0] == "auth");
          REQUIRE(c[1] == "set_cookie");
          REQUIRE(c[2] == 0);

          REQUIRE(j[1][1].is_number() == true);

          // is_logged_in == true
          REQUIRE(j[2][1] == true);

          // header data:
          auto h = j[3][0];
          REQUIRE(h[0] == table);
          REQUIRE(h[1] == "header");
          REQUIRE(h[2] == 1000);

          REQUIRE(j[3][1].size() == 6);

          // table data:
          auto t = j[4][0];
          REQUIRE(t[0] == table);
          REQUIRE(t[1] == "data");
          REQUIRE(t[2] == 1000);

          REQUIRE(j[4][1].size() >= 0);

          return quit(true);
        } else {
          // quit(true);
        }
      });
}
