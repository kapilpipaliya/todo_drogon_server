#include "jadmincontext.h"
#include "spdlogfix.h"
#include "../wsfns.h"
#include "../../core/strfns.h"
#include "../../core/sql/query.h"

JAdminContext::JAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_): ContextBase(req, wsConnPtr_)
{
    auto truple = generateContext(req, "admin");
    current_session_id = std::get<0>(truple);
    user_id = std::get<1>(truple);
    if(current_session_id) setUser();
}
std::tuple<long, long>  JAdminContext::generateContext(const HttpRequestPtr &req, std::string account_type) {
    auto c = req->getCookie(account_type);
    if (c.empty()) {
        return {0, 0};
    } else {
        auto session_id = stol(c);
        auto sqlSession = "SELECT * FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, session_id);
            if (r.size() != 0) {
//                return {r[0]["id"].as<long>(), r[0]["user_id"].as<long>()};
                return {r[0]["id"].as<long>(), 0};
            } else {
                return {0, 0};
            }
        } catch (const std::exception &e) {
            SPDLOG_TRACE(e.what());
            return {0, 0};
        }
    }
}

void JAdminContext::setUser()
{
    if(!user_id) return;

    try {
        auto sqlSession = "SELECT * FROM entity.entity where id = $1";
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sqlSession, user_id);
        if (r.size() != 0) {
            user.id= r[0]["id"].as<long>();
            //user.type = r[0]["type"].as<std::string>();
        }
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
}

