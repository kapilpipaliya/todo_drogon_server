#ifndef CONTEXTBASE_H
#define CONTEXTBASE_H

#include <drogon/WebSocketController.h>
#include "../../core/jsonfns.h"
using namespace drogon;

class ContextBase
{
public:
    ContextBase(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_);

    virtual int generateContext(const HttpRequestPtr &req, std::string account_type) = 0;
    virtual void deleteAdminSession() = 0;
    virtual void deleteuserSession() = 0;

protected:
    const WebSocketConnectionPtr& wsConnPtr;
};

#endif // CONTEXTBASE_H
