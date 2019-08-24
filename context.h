#ifndef CONTEXT_H
#define CONTEXT_H
#include "contextbase.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Context : public ContextBase
{
public:
    Context(const HttpRequestPtr &req);

    long user = 0;
    long admin = 0;

    int generateContext(const HttpRequestPtr &req, std::string account_type);
    void deleteAdminSession();
    void deleteuserSession();
};

#endif // CONTEXT_H
