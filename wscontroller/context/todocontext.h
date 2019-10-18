#pragma once
#include <drogon/WebSocketController.h>

#include <string>
namespace websocket {
namespace todo {

class TodoContext {
 public:
  class User {
   public:
    std::string uid;
    std::string name;
    std::string parent_uid;
  };

  class Data {
   public:
    std::string session_uid;
  };
  Data session;
  User user;
  TodoContext(const drogon::HttpRequestPtr &req,
              const drogon::WebSocketConnectionPtr &wsConnPtr_);

  void updateContext();

 private:
  const drogon::WebSocketConnectionPtr &wsConnPtr;
  std::string cookie;
};
}  // namespace todo
}  // namespace websocket
