#include "savedelete.h".h "
#include "spdlogfix.h"

#include <catch2/catch.hpp>
#include "json.hpp"

//#include <Poco/Format.h>
// using Poco::format;
#include <fmt/format.h>
using namespace nlohmann;

SaveDelete::SaveDelete(std::string table, std::string insert_query,
                       std::string update_query, std::string delete_query)
    : table(table),
      insert_query(insert_query),
      update_query(update_query),
      delete_query(delete_query) {}

void SaveDelete::connectToServer() {
  wsPtr->connectToServer(
      req, [this](ReqResult r, [[maybe_unused]] const HttpResponsePtr &resp,
                  [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
        if (r == ReqResult::Ok) {
          //
          // a JSON value
          auto in = R"(
                                            [
                                             [["auth","admin_login",0],{{"user":"kapil.pipaliya@yahoo.com","pass":"3434"}}],
                                             [["user","is_logged_in",0],[[]]],
                                             [["{0}","ins",100],{1}],
                                             [["{0}","upd",100],{2}],
                                             [["{0}","del",1000],{3}]
                                             ]
                                            )";
          auto s = fmt::v5::format(in, table, insert_query, update_query,
                                   delete_query);
          SPDLOG_TRACE(s);
          auto j = jsonparse(s);

          wsPtr->getConnection()->send(j.dump());
        } else {
          quit(false, "ws connection failed");
        }
      });
}
void SaveDelete::setMessageHandler() {
  wsPtr->setMessageHandler(
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

          REQUIRE(j[1][1]["admin"].is_number() == true);

          // is_logged_in == true
          REQUIRE(j[2][1] == true);

          // ins data:
          auto s = j[3][0];
          REQUIRE(s[0] == table);
          REQUIRE(s[1] == "ins");
          REQUIRE(s[2] == 100);

          REQUIRE(j[3][1]["ok"] == true);

          // upd data:
          auto u = j[4][0];
          REQUIRE(u[0] == table);
          REQUIRE(u[1] == "upd");
          REQUIRE(u[2] == 100);

          REQUIRE(j[4][1]["ok"] == true);

          // delete data:
          auto d = j[5][0];
          REQUIRE(d[0] == table);
          REQUIRE(d[1] == "del");
          REQUIRE(d[2] == 1000);

          REQUIRE(j[5][1]["ok"] == true);

          return quit(true);
        } else {
          quit(false, "Not a Text Type Message!!");
        }
      });
}
