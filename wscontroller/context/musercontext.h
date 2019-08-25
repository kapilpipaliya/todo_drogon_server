#ifndef MUSER_CONTEXT_H
#define MUSER_CONTEXT_H
#include "contextbase.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class MUserContext : public ContextBase
{
public:
    MUserContext(const HttpRequestPtr &req);

    long user = 0;
    long admin = 0;

    int generateContext(const HttpRequestPtr &req, std::string account_type);
    void deleteAdminSession();
    void deleteuserSession();
};

#endif // MUSER_CONTEXT_H
