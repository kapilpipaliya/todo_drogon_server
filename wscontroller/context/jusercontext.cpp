#include "jusercontext.h"
#include <boost/filesystem.hpp>
#include "../../core/sql/query.h"
#include "../../core/strfns.h"
#include "./core/sql/dba.h"
#include "spdlogfix.h"
namespace websocket {
JUserContext::JUserContext(const drogon::HttpRequestPtr &req,
                           const drogon::WebSocketConnectionPtr &wsConnPtr_)
    : wsConnPtr(wsConnPtr_) {
  auto truple = generateContext(req, "user");
  current_session_id = std::get<0>(truple);
  user_id = std::get<1>(truple);
  if (current_session_id) setUser();
}
std::tuple<long, long> JUserContext::generateContext(
    const drogon::HttpRequestPtr &req, const std::string &account_type) {
  auto c = req->getCookie(account_type);
  if (c.empty()) {
    return {0, 0};
  }
  auto session_id = stol(c);
  auto sqlSession = "SELECT * FROM user1.session where id = $1";
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    auto r = Dba::writeInTrans(transPtr, sqlSession, session_id);
    if (!r.empty()) {
      return {r[0]["id"].as<long>(), r[0]["user_id"].as<long>()};
    }
    return {0, 0};

  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    return {0, 0};
  }
}

void JUserContext::setUser() {
  if (!user_id) return;

  try {
    auto sqlSession = "SELECT * FROM user1.user where id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    auto r = Dba::writeInTrans(transPtr, sqlSession, user_id);
    if (!r.empty()) {
      user.id = r[0]["id"].as<long>();
      user.type = r[0]["type"].as<std::string>();
    }
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
  }
}
}  // namespace websocket
