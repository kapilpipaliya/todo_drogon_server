#ifndef CONTEXT_H
#define CONTEXT_H
#include "contextbase.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class MAdminContext : public ContextBase
{
public:
    MAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_);
};

#endif // CONTEXT_H
