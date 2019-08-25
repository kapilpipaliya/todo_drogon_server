#ifndef JADMIN_CONTEXT_H
#define JADMIN_CONTEXT_H
#include "contextbase.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class JAdminContext : public ContextBase
{
public:
    JAdminContext(const HttpRequestPtr &req);

    long user = 0;
    long admin = 0;

    int generateContext(const HttpRequestPtr &req, std::string account_type);
    void deleteAdminSession();
    void deleteuserSession();
};

#endif // JADMIN_CONTEXT_H
