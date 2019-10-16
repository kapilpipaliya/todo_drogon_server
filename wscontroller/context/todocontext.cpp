#include "todocontext.h"

namespace websocket {
namespace todo {

TodoContext::TodoContext(const drogon::HttpRequestPtr &req,
                         const drogon::WebSocketConnectionPtr &wsConnPtr_)
    : wsConnPtr(wsConnPtr_) {
  cookie = req->getCookie("time");
  generateContext();
}

void TodoContext::generateContext() {
  // get session from the session schema.
}

}  // namespace todo
}  // namespace websocket
