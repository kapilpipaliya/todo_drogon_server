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
  try {
  } catch (const std::exception &e) {
    LOG_DEBUG << e.what();
    return;
  }
}
}  // namespace todo
}  // namespace websocket
