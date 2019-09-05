#include "madmincontext.h"
#include "./core/service/dba.h"
#include "spdlogfix.h"

MAdminContext::MAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_): wsConnPtr(wsConnPtr_)
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
    } 
        auto session_id = stol(c);
        auto sqlSession = "SELECT * FROM music.session where id = $1";
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

void MAdminContext::setUser()
{
    if(!user_id) return;

    try {
        auto sqlSession = "SELECT * FROM music.user where id = $1";
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = Dba::writeInTrans(transPtr, sqlSession, user_id);
        if (!r.empty()) {
            user.id= r[0]["id"].as<long>();
            user.type = r[0]["type"].as<std::string>();
        }
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
}

