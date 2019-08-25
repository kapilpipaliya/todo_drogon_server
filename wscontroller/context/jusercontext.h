#ifndef JUSER_CONTEXT_H
#define JUSER_CONTEXT_H
#include "contextbase.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class JUserContext : public ContextBase
{
public:
    JUserContext(const HttpRequestPtr &req);

    long user = 0;
    long admin = 0;

    int generateContext(const HttpRequestPtr &req, std::string account_type);
    void deleteAdminSession();
    void deleteuserSession();
};

#endif // JUSER_CONTEXT_H
