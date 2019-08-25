#include "contextbase.h"

ContextBase::ContextBase(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr_): wsConnPtr(wsConnPtr_)
{

}
