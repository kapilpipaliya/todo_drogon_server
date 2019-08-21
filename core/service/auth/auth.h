#ifndef AUTH_H
#define AUTH_H


#include "core/sql/Table.h"
#include "core/connection/pdb.h"
#include <json/json.h>

#include <drogon/WebSocketController.h>
using namespace drogon;

class Auth
{
public:
    Auth(const WebSocketConnectionPtr& wsConnPtr);

    Json::Value handleEvent(Json::Value event, int next, Json::Value args);

private:
    Json::Value adminLogin(Json::Value event, Json::Value args);
    Json::Value adminLogout(Json::Value event, Json::Value args);
    Json::Value isAdminAuth(Json::Value event, Json::Value args);

    Json::Value userRegister(Json::Value event, Json::Value args);
    Json::Value userLogin(Json::Value event, Json::Value args);
    Json::Value userId(Json::Value event, Json::Value args);
    Json::Value userLogout(Json::Value event, Json::Value args);
    Json::Value isUserAuth(Json::Value event, Json::Value args);
    Json::Value checkout(Json::Value event, Json::Value args);
    Json::Value saveImageMeta(Json::Value event, Json::Value args);


    const WebSocketConnectionPtr& wsConnPtr;


};
int generateContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr, std::string account_type);
void deleteAdminSession(const WebSocketConnectionPtr &wsConnPtr);
void deleteuserSession(const WebSocketConnectionPtr &wsConnPtr);

void setAdminContext( const WebSocketConnectionPtr &wsConnPtr, int in);
int getAdminContext(const WebSocketConnectionPtr &wsConnPtr);
void setUserContext( const WebSocketConnectionPtr &wsConnPtr, int in);
int getUserContext(const WebSocketConnectionPtr &wsConnPtr);

#endif // AUTH_H
