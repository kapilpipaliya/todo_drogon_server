#pragma once
#include "contextbase.h"

#include <drogon/WebSocketController.h>
using namespace drogon;


class JUserContext : public ContextBase
{
struct ContextUser {
    long id{0};
    std::string type{""};
};
public:
    JUserContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_);

    long current_session_id = 0;
    long user_id = 0;

     std::tuple<long, long>  generateContext(const HttpRequestPtr &req, std::string account_type);
     void setUser();

     ContextUser user;
};
