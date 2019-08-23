#ifndef AUTH_H
#define AUTH_H


#include "core/sql/Table.h"
#include "core/connection/pdb.h"
#include  "json.hpp"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Auth
{
public:
    Auth(const WebSocketConnectionPtr& wsConnPtr);

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
