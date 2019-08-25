#include "jadmincontext.h"
#include "spdlog/spdlog.h"

JAdminContext::JAdminContext(const HttpRequestPtr &req)
{
admin = generateContext(req,  "admin");
user = generateContext(req,  "user");
}
int JAdminContext::generateContext(const HttpRequestPtr &req, std::string account_type) {
    auto c = req->getCookie(account_type);
    if (c.empty()) {
        return 0;
    } else {
        auto sqlSession = "SELECT * FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            if (r.size() != 0) {
                auto i = r[0]["id"].as<int>();
                return i;
            } else {
                return 0;
            }
        } catch (const std::exception &e) {
            spdlog::error(e.what());
            return 0;
        }
    }
}

void JAdminContext::deleteAdminSession() {
    if (admin != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, admin);
            admin = 0;
        } catch (const std::exception &e) {
            spdlog::error(e.what());
        }
    }
}
void JAdminContext::deleteuserSession() {
    if (user != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, user);
            user = 0 ;
        } catch (const std::exception &e) {
            spdlog::error(e.what());
        }
    }
}
