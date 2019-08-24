#ifndef CONTEXT_H
#define CONTEXT_H

#include "EchoWebSocket.h"
#include <drogon/WebSocketController.h>
using namespace drogon;

class Context
{
public:
    Context(const HttpRequestPtr &req);

    long user = 0;
    long admin = 0;

    int generateContext(const HttpRequestPtr &req, std::string account_type);
    void deleteAdminSession();
    void deleteuserSession();

    void setAdminContext(long in);
    long getAdminContext();
    void setUserContext(long in);
    long getUserContext();
};

#endif // CONTEXT_H
