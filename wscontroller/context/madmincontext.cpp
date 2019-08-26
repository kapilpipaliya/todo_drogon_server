#include "madmincontext.h"
#include "spdlog/spdlog.h"

MAdminContext::MAdminContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_): ContextBase(req, wsConnPtr_)
{

}

