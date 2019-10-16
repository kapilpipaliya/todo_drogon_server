#pragma once
#include <drogon/WebSocketController.h>

#include <string>
namespace websocket {
namespace todo {

class TodoContext {
 public:
  class User {
    std::string uid;
    std::string name;
    std::string parent_uid;
  };

  class Data {
   public:
    std::string session_uid;
  };

  TodoContext(const drogon::HttpRequestPtr &req,
              const drogon::WebSocketConnectionPtr &wsConnPtr_);

  void generateContext();

 private:
  const drogon::WebSocketConnectionPtr &wsConnPtr;
  std::string cookie;
};
}  // namespace todo
}  // namespace websocket
