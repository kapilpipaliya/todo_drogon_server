#ifndef WSFUNCTIONS_H
#define WSFUNCTIONS_H
#include <drogon/WebSocketController.h>
using namespace drogon;
int generateContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr, std::string account_type);
void deleteAdminSession(const WebSocketConnectionPtr &wsConnPtr);
void deleteuserSession(const WebSocketConnectionPtr &wsConnPtr);
std::string getEventName(const WebSocketConnectionPtr &wsConnPtr);

void admin_login(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void admin_logout(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void is_admin_auth(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void user_register(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void user_login(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void user_id(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void user_logout(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void is_user_auth(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void user_checkout(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);





void setAdminContext( const WebSocketConnectionPtr &wsConnPtr, int in);
int getAdminContext(const WebSocketConnectionPtr &wsConnPtr);
void setUserContext( const WebSocketConnectionPtr &wsConnPtr, int in);
int getUserContext(const WebSocketConnectionPtr &wsConnPtr);

#endif // WSFUNCTIONS_H
