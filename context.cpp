#include "context.h"

Context::Context(const HttpRequestPtr &req)
{
admin = generateContext(req,  "admin");
user = generateContext(req,  "user");
}
int Context::generateContext(const HttpRequestPtr &req, std::string account_type) {
    auto c = req->getCookie(account_type);
    if (c.empty()) {
        return 0;
    } else {
        auto sqlSession = "SELECT * FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            if (r.size() != 0) {
                auto i = r[0]["id"].as<int>();
                return i;
            } else {
                return 0;
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
}

void Context::deleteAdminSession() {
    if (admin != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, admin);
            admin = 0;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
void Context::deleteuserSession() {
    if (user != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, user);
            user = 0 ;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
