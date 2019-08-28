#include "madmincontext.h"
#include "spdlog/spdlog.h"

MAdminContext::MAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_): ContextBase(req, wsConnPtr_)
{
    auto truple = generateContext(req);
    current_session_id = std::get<0>(truple);
    user_id = std::get<1>(truple);
    if(current_session_id) setUser();
}

std::tuple<long, long> MAdminContext::generateContext(const HttpRequestPtr &req)
{
    auto c = req->getCookie("music");
    if (c.empty()) {
        return {0, 0};
    } else {
        auto session_id = stol(c);
        auto sqlSession = "SELECT * FROM music.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, session_id);
            if (r.size() != 0) {
                return {r[0]["id"].as<long>(), r[0]["user_id"].as<long>()};
            } else {
                return {0, 0};
            }
        } catch (const std::exception &e) {
            spdlog::error(e.what());
            return {0, 0};
        }
    }
}

void MAdminContext::setUser()
{
    if(!user_id) return;

    try {
        auto sqlSession = "SELECT * FROM music.user where id = $1";
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sqlSession, user_id);
        if (r.size() != 0) {
            user.id= r[0]["id"].as<long>();
            user.type = r[0]["type"].as<std::string>();
        }
    } catch (const std::exception &e) {
        spdlog::error(e.what());
    }
}

