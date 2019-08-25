#ifndef JADMIN_CONTEXT_H
#define JADMIN_CONTEXT_H
#include "contextbase.h"

#include  "json.hpp"
#include <drogon/WebSocketController.h>
using namespace drogon;
using nlohmann:: json;

class JAdminContext : public ContextBase
{
public:
    JAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_);

    long user = 0;
    long admin = 0;

    int generateContext(const HttpRequestPtr &req, std::string account_type);
    void deleteAdminSession();
    void deleteuserSession();

    json handleEvent(json event, int next, json args);
    json handleBinaryEvent(json event, int next, std::string &message);

private:
    json adminLogin(json event, json args);
    json adminLogout(json event, json args);
    json isAdminAuth(json event, json args);

    json userRegister(json event, json args);
    json userLogin(json event, json args);
    json userId(json event, json args);
    json userLogout(json event, json args);
    json isUserAuth(json event, json args);
    json checkout(json event, json args);
    json saveImageMeta(json event, json args);

    json thumb_data( json event, json args);
    //Binary functin:
    json save_setting_attachment(json event, std::string &message);
};

#endif // JADMIN_CONTEXT_H
