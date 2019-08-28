#ifndef CONTEXTBASE_H
#define CONTEXTBASE_H

#include <drogon/WebSocketController.h>
#include "../../core/jsonfns.h"
using namespace drogon;

class ContextBase
{
public:
    ContextBase(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_);

    virtual std::tuple<long, long> generateContext(const HttpRequestPtr &req){};
    virtual void deleteAdminSession(){};
    virtual void deleteuserSession(){};

protected:
    const WebSocketConnectionPtr& wsConnPtr;
};

#endif // CONTEXTBASE_H
