#ifndef CONTEXTBASE_H
#define CONTEXTBASE_H

#include <drogon/WebSocketController.h>
using namespace drogon;

class ContextBase
{
public:
    ContextBase();

    virtual int generateContext(const HttpRequestPtr &req, std::string account_type) = 0;
    virtual void deleteAdminSession() = 0;
    virtual void deleteuserSession() = 0;

};

#endif // CONTEXTBASE_H
