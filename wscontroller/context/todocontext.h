#pragma once
#include <string>

#include <drogon/WebSocketController.h>
namespace websocket {
namespace todo {
class TodoContext {
 public:
  TodoContext(const drogon::HttpRequestPtr &req,
              const drogon::WebSocketConnectionPtr &wsConnPtr_);

  void generateContext();

  void setUser();

 private:
  const drogon::WebSocketConnectionPtr &wsConnPtr;

  std::string cookie;
};
}  // namespace todo
}  // namespace websocket
