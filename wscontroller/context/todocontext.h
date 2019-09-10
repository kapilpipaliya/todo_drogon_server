#pragma once
#include <string>

#include <drogon/WebSocketController.h>
namespace todo {

struct ContextUser {
  long id{0};
  std::string type{""};
};

class TodoContext {
 public:
  TodoContext(const drogon::HttpRequestPtr &req,
              const drogon::WebSocketConnectionPtr &wsConnPtr_);

  std::tuple<long, long> generateContext(const drogon::HttpRequestPtr &req);
  void setUser();
  long sessionId() { return current_session_id; }
  void setSessionId(long id) { current_session_id = id; }
  void setUserId(long id) { user_id = id; }
  ContextUser &getUser() { return user; }
  long getUserId() { return user_id; }

 private:
  long current_session_id = 0;
  long user_id = 0;
  ContextUser user;
  const drogon::WebSocketConnectionPtr &wsConnPtr;
};
}  // namespace todo
