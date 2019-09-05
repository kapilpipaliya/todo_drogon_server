#pragma once

#include  "json.hpp"
#include <drogon/WebSocketController.h>
using namespace drogon;
using nlohmann:: json;


class JAdminContext
{
struct ContextUser {
    long id{0};
    std::string type{""};
};
public:
    JAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_);

    long current_session_id = 0;
    long user_id = 0;

    std::tuple<long, long> generateContext(const HttpRequestPtr &req, const std::string& account_type);
    void setUser();

    ContextUser user;
    const WebSocketConnectionPtr& wsConnPtr;

private:
 };
