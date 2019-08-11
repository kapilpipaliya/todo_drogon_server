#ifndef WSFUNCTIONS_H
#define WSFUNCTIONS_H
#include <drogon/WebSocketController.h>
using namespace drogon;
int generateContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr, std::string account_type);
void deleteAdminSession(const WebSocketConnectionPtr &wsConnPtr);
void deleteuserSession(const WebSocketConnectionPtr &wsConnPtr);
std::string getEventName(const WebSocketConnectionPtr &wsConnPtr);

Json::Value admin_login(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value admin_logout(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value is_admin_auth(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value user_register(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value user_login(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value user_id(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value user_logout(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value is_user_auth(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
Json::Value user_checkout(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);





void setAdminContext( const WebSocketConnectionPtr &wsConnPtr, int in);
int getAdminContext(const WebSocketConnectionPtr &wsConnPtr);
void setUserContext( const WebSocketConnectionPtr &wsConnPtr, int in);
int getUserContext(const WebSocketConnectionPtr &wsConnPtr);

#endif // WSFUNCTIONS_H
